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

void testAdd()
{
    // Both positive
    LongInt L1(34);
    LongInt L2(68);
    LongInt sum;
    sum = L1 + L2;

    cout << L1 << " + " << L2 << " = " << L1 + L2 << endl;

    cout << L1 << " + " << sum << " = " << L1 + sum << endl;

    cout << sum << " + " << L2 << " = " << sum + L2 << endl;

    // Both negative
    LongInt L3(-34);
    LongInt L4(-68);

    cout << L3 << " + " << L4 << " = " << L3 + L4 << endl;

    // a negative, b positive
    LongInt L5(-27);
    LongInt L6(64);

    // 37
    cout << L5 << " + " << L6 << " = " << L5 + L6 << endl;

    // a positive, b negative
    LongInt L7(64);
    LongInt L8(-27);

    // 37
    cout << L7 << " + " << L8 << " = " << L7 + L8 << endl;
}

void testSingleSubtract(LongInt &a, LongInt &b)
{
    cout << a << " - " << b << " = " << a - b << endl;
}

void testSimpleSubtract()
{
    LongInt L1(7002);
    LongInt L2(5808);
    LongInt difference;
    difference = L1 - L2;

    cout << L1 << " - " << L2 << " = " << difference << endl;

    LongInt L3(-30);
    LongInt L4(-20);
    LongInt L5(20);
    LongInt L6(30);

    // Case: a == b
    cout << L5 << " - " << L5 << " = " << L5 - L5 << endl;

    // Cases where a > b
    // a > b and both positive
    testSingleSubtract(L6, L5);

    // a > b, a is positive and b is neg
    testSingleSubtract(L6, L4);

    // a > b, both negative
    testSingleSubtract(L4, L3);

    // Cases where a < b
    // a < b and both positive
    testSingleSubtract(L5, L6);

    // a < b, a is neg and b is pos
    testSingleSubtract(L4, L6);

    // a < b, both negative
    testSingleSubtract(L3, L4);
}

int main()
{
    testAdd();
    testSimpleSubtract();
    // testCompareAll();
}