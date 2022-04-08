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

void testCompare(int a, int b)
{
    LongInt L1(a);
    LongInt L2(b);
    cout << endl;
    cout << "L1 = " << L1 << endl;
    cout << "L2 = " << L2 << endl;

    cout << L2 << " == " << L1 << ": " << (L2 == L1 ? "true" : "false") << endl;
    cout << L2 << " != " << L1 << ": " << (L2 != L1 ? "true" : "false") << endl;
    cout << L2 << " <  " << L1 << ": " << (L2 < L1 ? "true" : "false") << endl;
    cout << L2 << " <= " << L1 << ": " << (L2 <= L1 ? "true" : "false") << endl;
    cout << L2 << " >  " << L1 << ": " << (L2 > L1 ? "true" : "false") << endl;
    cout << L2 << " >= " << L1 << ": " << (L2 >= L1 ? "true" : "false") << endl;
}

void testCompareAll()
{
    testCompare(12345, 12345);
    testCompare(-12345, -12345);
    testCompare(-12345, 12345);
    testCompare(12345, -12345);
    testCompare(1234, 12345);
    testCompare(-1234, -12345);
    testCompare(12345, 1234);
    testCompare(-12345, -1234);
    testCompare(12345, 10095);
    testCompare(-12345, -10095);
    testCompare(19000, 15999);
    testCompare(-19000, -15999);
}

int main()
{
    LongInt L1(34);
    LongInt L2(68);
    LongInt sum;
    sum = L1 + L2;

    cout << L1 << " + " << L2 << " = " << L1 + L2 << endl;

    cout << L1 << " + " << sum << " = " << L1 + sum << endl;

    cout << sum << " + " << L2 << " = " << sum + L2 << endl;

    // testCompareAll();
}