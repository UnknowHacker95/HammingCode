#pragma once
#include "Matrix.hpp"
#include "Fp.hpp"
#include <cmath>
using namespace std;

template<int p>
class HammingCode {
private:
    // Атрибуты
    size_t n;    // Количество символов в кодовом слове
    size_t k;    // Количество информационных символов
    size_t m;    // Количество проверочных символов
    Matrix<Fp<p>> H; // Проверочная матрица
    Matrix<Fp<p>> G; // Порождающая матрица

    //Вспомогательные методы

    //Методы для проверки столбца
    //разложение числа по модулю p
    vector<Fp<p>> decompose(size_t num) const {
        vector<Fp<p>> result(m);
        size_t i = 0;
        for (i = 0; i < m; i++) {
            result[i] = num % p;
            num /= p;
        }
        return result;
    }
    //проверка коллинеарности единичной матрице
    //(если есть коллинеарность, то возвращается false)
    //т.е. тут мы считаем количество единиц в столбце
    //если их 1 шт, то коллинеарна и все плохо
    bool is_valid_column(const vector<Fp<p>>& col) const {
        size_t count = 0, i, j = col.size();
        for (i = 0; i < j; i++){
            int cur = col[i].val();
            if (cur != 0) {
                count++;
            }
        }
        return count != 1;
    }
    //проверка того, что один столбец кратен другому
    bool is_multiple(const vector<Fp<p>>& col, const vector<Fp<p>>& temp) const {
        size_t ind = 0, i;
        //ищем первый ненулевой элемент
        while (ind < m && temp[ind].val() == 0 && col[ind].val() == 0) {
            ind++;
        }
        //оба столбика нулевые
        if (ind >= m) {
            return false;
        }
        //один стобиц нулевой, т.е. на месте одного стобика, у которого число, у другого стоит нолик. они сто процентов не кратны
        if (temp[ind].val() == 0 || col[ind].val() == 0) {
            return false;
        }
        //вычисляем отношени элемента одного столбца к элементу другому
        Fp<p> otnosh = temp[ind] / col[ind];
        for (i = ind; i < m; i++){
            //пропуск нулевых элементов
            if (temp[i].val() == 0 && col[i].val() == 0) {
                continue;
            }
            //проверка отношения следующих элементов
            //если зашли в if, то кратность нарушена
            if (temp[i].val() != col[i].val() * otnosh.val()){
                return false; 
            }
        }
        //иначе столбцы кратны
        return true;
    }
    //проверка линейной независимости с другими столбцами 
    bool is_dependent(const vector<vector<Fp<p>>>& A_data, const vector<Fp<p>>& temp) const {
        size_t i;
        for(i = 0; i < A_data.size(); i++) {
            const vector<Fp<p>>& col = A_data[i];
            if (is_multiple(col, temp)) {
                return true;
            }
        }
        return false;
    }

    //генерация матриц
    void generate_matrices(){
        //Это типо значения для последующего построения Аt
        vector<vector<Fp<p>>> A_data; 
        size_t i, num = pow(p, m) - 1;
        //храним тут столбик, который планируем добавить в Аt
        vector<Fp<p>> temp; 
        for(i = 1; i <= num; i++){
            //раскладываем число по модулю p
            temp = decompose(i); 
            //проверяем, что столбик не коллинеарен
            //столбцам единичной матрицы и что он линейно независим
            //с остальными столбцами
            if(is_valid_column(temp) && !is_dependent(A_data, temp)){
                A_data.push_back(temp);
            }
        }
        //построение Аt
        k = A_data.size();
        n = m + k;
        Matrix<Fp<p>> At(A_data);
        Matrix<Fp<p>> A = At.transpose();
        Matrix<Fp<p>> Eh = A.eye(m);
        Matrix<Fp<p>> Eg = A.eye(k);
        H = A.horizontal_concatenate(Eh);
        G = Eg.horizontal_concatenate(At);
    }

public:
    //Конструктор
    HammingCode(size_t m): m(m){
        generate_matrices();
    }

    Matrix<Fp<p>> get_H() const{
        return H;
    }

    Matrix<Fp<p>> get_G() const{
        return G;
    }
};
