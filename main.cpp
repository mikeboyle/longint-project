#include <iostream>
#include <string>
#include "LongInt.h"

using namespace std;

bool testCompare(int a, int b)
{
    LongInt L1(a);
    LongInt L2(b);

    int numOps = 6;
    string boolToString[] = {"false", "true"};
    string ops[] = {"==", "!=", "<", "<=", ">", ">="};
    bool expected[] = {(a == b), (a != b), (a < b), (a <= b), (a > b), (a >= b)};
    bool actual[] = {(L1 == L2), (L1 != L2), (L1 < L2), (L1 <= L2), (L1 > L2), (L1 >= L2)};

    for (int i = 0; i < numOps; i++)
    {
        bool currExpected = expected[i];
        bool currActual = actual[i];
        if (currExpected != currActual)
        {
            cout << "Uh-oh! Expected " << L1 << " " << ops[i] << " " << L2
                 << " to be " << boolToString[currExpected] << " but got: "
                 << boolToString[currActual] << endl;
            return false;
        }
    }

    return true;
}

void testCompareAll()
{
    int total = 12;
    int passed = 0;
    passed += testCompare(12345, 12345);
    passed += testCompare(-12345, -12345);
    passed += testCompare(-12345, 12345);
    passed += testCompare(12345, -12345);
    passed += testCompare(1234, 12345);
    passed += testCompare(-1234, -12345);
    passed += testCompare(12345, 1234);
    passed += testCompare(-12345, -1234);
    passed += testCompare(12345, 10095);
    passed += testCompare(-12345, -10095);
    passed += testCompare(19000, 15999);
    passed += testCompare(-19000, -15999);

    cout << "test comparision operators | passed " << passed << " of " << total << endl;
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

void testSubtract()
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

void testSingleMultiply(LongInt &a, LongInt &b)
{
    cout << a << " * " << b << " = " << a * b << endl;
}

void testMultiply()
{
    LongInt L1(123);
    LongInt L2(321);
    LongInt L3(-123);
    LongInt L4(-321);

    testSingleMultiply(L1, L2);
    testSingleMultiply(L2, L1);
    testSingleMultiply(L1, L4);
    testSingleMultiply(L4, L1);
    testSingleMultiply(L2, L3);
    testSingleMultiply(L3, L2);
    testSingleMultiply(L3, L4);
    testSingleMultiply(L4, L3);
}

int main()
{
    testCompareAll();
    // testAdd();
    // testSubtract();
    // testMultiply();
}