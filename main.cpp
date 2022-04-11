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

    cout << "test comparison | passed " << (passed / total) * 100 << "% ("
         << passed << " of " << total << ")" << endl;
}

bool testAdd(const int &a, const int &b)
{
    LongInt L1(a);
    LongInt L2(b);

    string expected = to_string(a + b);
    string actual = (L1 + L2).toString();

    if (expected != actual)
    {
        cout << "Uh oh! Expected " << a << " + " << b << " = " << expected
             << " but got: " << actual << endl;
        return false;
    }

    return true;
}

void testAddAll()
{
    cout << "testing addition ... " << endl;
    int total = 9;
    int passed = 0;

    // Specific cases
    passed += testAdd(-1001, 4);
    passed += testAdd(-525, 9157);
    passed += testAdd(266, -11296);
    passed += testAdd(34, 68);
    passed += testAdd(68, 34);
    passed += testAdd(-34, -68);
    passed += testAdd(-68, -34);
    passed += testAdd(-27, 64);
    passed += testAdd(64, -27);

    // Broad check
    for (int a = -1001; a < 1001; a += 7)
    {
        for (int b = -100001; b < 100001; b += 113)
        {
            total++;
            passed += testAdd(a, b);
        }
    }

    cout << "passed " << (passed / total) * 100
         << "% (" << passed << " of " << total << ")" << endl;
}

void testSingleSubtract(LongInt &a, LongInt &b)
{
    cout << a << " - " << b << " = " << a - b << endl;
}

bool testSubtract(const int &a, const int &b)
{
    LongInt L1(a);
    LongInt L2(b);

    string expected = to_string(a - b);
    string actual = (L1 - L2).toString();

    if (expected != actual)
    {
        cout << "Uh oh! Expected " << a << " - " << b << " = " << expected
             << " but got: " << actual << endl;
        return false;
    }

    return true;
}

void testSubtractAll()
{
    cout << "testing subtraction ... " << endl;
    int total = 9;
    int passed = 0;

    // Specific cases
    passed += testSubtract(7002, 5808);
    passed += testSubtract(20, 20);
    passed += testSubtract(-20, -20);
    passed += testSubtract(30, 20);
    passed += testSubtract(30, -20);
    passed += testSubtract(-20, -30);
    passed += testSubtract(20, 30);
    passed += testSubtract(-20, 30);
    passed += testSubtract(-30, -20);

    // broad check
    for (int a = -1001; a < 1001; a += 7)
    {
        for (int b = -100001; b < 100001; b += 113)
        {
            total++;
            passed += testSubtract(a, b);
        }
    }

    cout << "passed " << (passed / total) * 100
         << "% (" << passed << " of " << total << ")" << endl;
}

void testSingleMultiply(LongInt &a, LongInt &b)
{
    cout << a << " * " << b << " = " << a * b << endl;
}

bool testMultiply(const int &a, const int &b)
{
    LongInt L1(a);
    LongInt L2(b);

    string expected = to_string(a * b);
    string actual = (L1 * L2).toString();

    if (expected != actual)
    {
        cout << "Uh oh! Expected " << a << " * " << b << " = " << expected
             << " but got: " << actual << endl;
        return false;
    }

    return true;
}

void testMultiplyAll()
{
    cout << "testing multiplication ... " << endl;
    int total = 2;
    int passed = 0;

    passed += testMultiply(347, 0);
    passed += testMultiply(0, 347);

    for (int a = -1001; a < 1001; a += 7)
    {
        for (int b = -100001; b < 100001; b += 113)
        {
            total++;
            passed += testMultiply(a, b);
        }
    }
    cout << "passed " << (passed / total) * 100
         << "% (" << passed << " of " << total << ")" << endl;
}

bool testDivide(const int &a, const int &b)
{
    LongInt L1(a);
    LongInt L2(b);

    string expected = to_string(a / b);
    string actual = (L1 / L2).toString();

    if (expected != actual)
    {
        cout << "Uh oh! Expected " << a << " / " << b << " = " << expected
             << " but got: " << actual << endl;
        return false;
    }

    return true;
}

void testDivideAll()
{
    cout << "testing division ... " << endl;
    int total = 6;
    int passed = 0;

    passed += testDivide(20, 20);
    passed += testDivide(20, 1);
    passed += testDivide(6, -1);
    passed += testDivide(20, 6);
    passed += testDivide(6, 20);
    passed += testDivide(16384, 16);

    for (int a = -100001; a < 100001; a += 113)
    {
        for (int b = -1001; b < 1001; b += 7)
        {
            if (b != 0)
            {
                total++;
                passed += testDivide(a, b);
            }
        }
    }

    cout << "passed " << (passed / total) * 100
         << "% (" << passed << " of " << total << ")" << endl;
}

void testVeryLongInts()
{
    string ones = "1111111111111111111111111";
    string twos = "2222222222222222222222222";
    string threes = "3333333333333333333333333";

    LongInt L1(ones);
    LongInt L2(twos);
    LongInt L3(threes);
    LongInt sum = L1 + L2;
    cout << "expected\t" << threes << endl;
    cout << "actual\t\t" << sum << endl;

    cout << L1 << " + " << L2 << " = " << sum << endl;
    cout << L3 << " - " << L2 << " = " << L3 - L2 << endl;
    LongInt product = L2 * L3;
    cout << L2 << " * " << L3 << " = " << product << endl;
    cout << L3 << " / " << L1 << " = " << L3 / L1 << endl;

    LongInt L123("123456789");
    LongInt L321("987654321");
    cout << L123 << endl;
    cout << L321 << endl;
    cout << L123 * L321 << endl;
}

int main()
{
    testVeryLongInts();
    testCompareAll();
    testAddAll();
    testSubtractAll();
    testMultiplyAll();
    testDivideAll();
}