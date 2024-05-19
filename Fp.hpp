#pragma once    
#include <iostream>
using namespace std;

template<int p>
class Fp {
private:
    int value; //Значение элемента поля

public:
    // Конструктор
    //Много %p, чтобы через одно выражение обрабатывались и полож и отриц числа
    Fp(int x = 0): value((x % p + p) % p) {}

    // Возвращает значение элемента поля
    int val() const{
      return value;
    }

    // Операция присваивания от целого числа
    Fp<p>& operator=(int x){
      value = (x % p + p) % p;
      return *this;
    } 

    //Арифметические операции
    //Сложение
    Fp<p> operator+(const Fp<p>& other) const{
      return Fp<p>((value + other.value) % p);
    }
    //Вычитание
    //Дополнительно прибавляем p, т.к. при вычитании можем получить отрицательное число
    Fp<p> operator-(const Fp<p>& other) const{
      return Fp<p>((value - other.value + p) % p);
    }
    //Умножение
    Fp<p> operator*(const Fp<p>& other) const{
      return Fp<p>((value * other.value) % p);
    }
    //Возведение в степень(для деления)(алгоритм быстрого возведения в степень)
    Fp<p> pow(int exp) const{
      Fp<p> res = 1;
      Fp<p> base = value;
      while(exp > 0){
        if(exp % 2 == 1){
          res *= base;
        }
        base *= base;
        exp /= 2;
      }
      return res;
    }
    //Нахождение обратного. Нужно, для деления. Используем малую теорему Ферма. a^p = a(mod p) --> a^(p-2) = a^-1 (mod p)
    Fp<p> inverse() const{
      return pow(p - 2);
    }
    //Деление
    Fp<p> operator/(const Fp<p>& other) const{
      return (*this) * other.inverse();
    }
    //Смена знака
    Fp<p> operator-() const{
      return Fp<p>((-value + p) % p);
    }

    //Операторы присваивания
    //Операция += (сложение с присваиванием)
    Fp<p>& operator+=(const Fp<p>& other){
      value = (value + other.value) % p;
      return *this;
    }
    //Операция -= (вычитание с присваиванием)
    Fp<p>& operator-=(const Fp<p>& other){
      value = (value - other.value + p) % p;
      return *this;
    }
    //Операция *= (умножение с присваиванием)
    Fp<p>& operator*=(const Fp<p>& other){
      value = (value * other.value) % p;
      return *this;
    }
    //Операция /= (деление с присваиванием)
    Fp<p>& operator/=(const Fp<p>& other){
      *this = *this / other;
      return *this;
    }

    //Операторы сравнения
    //Операция сравнения на равенство
    bool operator==(const Fp<p>& other) const{
      return value == other.value;
    }
    //Операция сравнения на неравенство
    bool operator!=(const Fp<p>& other) const{
      return value != other.value;
    }

    // Вывод элемента
    template <int Tstream>
    friend ostream &operator<<(ostream &out, const Fp<Tstream>& el);
};

// Вывод элемента
template <int Tstream>
ostream &operator<<(ostream &out, const Fp<Tstream>& el) {
    out << el.val();
    return out;
}