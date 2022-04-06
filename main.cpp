#include <iostream>
#include "Matrix.h"

using namespace std;

int main()
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