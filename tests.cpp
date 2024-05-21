#include <iostream>
#include "Fp.hpp"
#include "HammingCode.hpp"
#include "Matrix.hpp"
using namespace std;

int main() {
    Fp<7> a(3);
    cout << "Constructor: " << a.val() << endl;
    
    Fp<7> b(4);
    Fp<7> add = a + b;
    cout << "Addition: " << add.val() << endl;
    Fp<7> sub = a - b;
    cout << "Subtraction: " << sub.val() << endl;
    Fp<7> mul = a * b;
    cout << "Multiplication: " << mul.val() << endl;
    Fp<7> f(5);
    Fp<7> div = a / f;
    cout << "Division: " << div.val() <<endl;
    Fp<7> neg = -a;
    cout << "Negation: " << neg.val() <<endl;

    Fp<7> as;
    as = 6;
    cout << "Assignment: " << as.val() << endl;
    Fp<7> cur(2);
    cur += b;
    cout << "Addition assignment: " << cur.val() << endl;
    cur -= b;
    cout << "Subtraction assignment: " << cur.val() << endl;
    cur *= b;
    cout << "Multiplication assignment: " << cur.val() << endl;
    cur /= b;
    cout << "Division assignment: " << cur.val() << endl;

    cout << "Equality: " << (a == Fp<7>(3)) << endl;
    cout << "Inequality: " << (a != Fp<7>(4)) << endl;

    HammingCode<2> hamming(4);
    Matrix<Fp<2>> H = hamming.get_H();
    Matrix<Fp<2>> G = hamming.get_G();
    cout << "Hamming code matrix H: " << endl;
    cout << H << endl;
    cout << "Hamming code matrix G: " << endl;
    cout << G << endl;
    return 0;
}