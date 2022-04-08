#include <iostream>
#include "Matrix.h"
#include "LongInt.h"

using namespace std;

void testMatrix()
{
    Matrix a = Matrix(2, 2);
    a[0][0] = 1;
    a[0][1] = 2;
    a[1][0] = 3;
    a[1][1] = 4;
    a.print();

    Matrix x = Matrix(2, 1);
    x[0][0] = 5;
    x[1][0] = 10;
    x.print();

    Matrix b = a * x;
    b.print();
}

int main()
{
    LongInt L(-12345);
    cout << L << endl;

    LongInt L2(-13345);
    cout << L2 << endl;
    cout << (L2.compare(L)) << endl;

    // LongInt L3;
    // cout << "Enter an integer: ";
    // cin >> L3;
    // cout << L3 << endl;
}