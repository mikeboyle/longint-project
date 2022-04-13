#include <iostream>
#include <string>
#include <functional>
#include "LongInt.h"

using namespace std;

const bool VERBOSE = false;

bool testFunc(const int &a, const int &b, char op)
{
    LongInt L1(a);
    LongInt L2(b);
    string expected, actual;

    switch (op)
    {
    case '+':
        expected = to_string(a + b);
        actual = (L1 + L2).toString();
        break;
    case '-':
        expected = to_string(a - b);
        actual = (L1 - L2).toString();
        break;
    case '*':
        expected = to_string(a * b);
        actual = (L1 * L2).toString();
        break;
    case '/':
        expected = to_string(a / b);
        actual = (L1 / L2).toString();
        break;
    case '%':
        expected = to_string(a % b);
        actual = (L1 % L2).toString();
        break;
    default:
        cout << "invalid op " << op << endl;
        return false;
    }

    if (VERBOSE && expected != actual)
    {
        cout << a << " " << op << " " << b << ", expected: " << expected
             << ", actual: " << actual << endl;
    }

    return expected == actual;
}

void displayTestProgress(double passed, double total)
{
    if ((int)passed % 5317 == 0 || passed == total)
    {
        cout << "passed " << (int)((passed / total) * 100)
             << "% (" << passed << " of " << total << ")\r";
        cout.flush();
    }
}

void testOperation(char op, int lowerA, int upperA, int stepA, int lowerB, int upperB, int stepB)
{
    double passed = 0;
    double total = 0;
    bool canCompute = true;

    // loop through all numbers twice; first to get total, then to test
    for (int i = 0; i < 2; i++)
    {
        for (int a = lowerA; a < upperA; a += stepA)
        {
            for (int b = lowerB; b < upperB; b += stepB)
            {
                // do not divide by zero
                if ((op == '/' || op == '%') && b == 0)
                    canCompute = false;
                else
                    canCompute = true;

                if (canCompute)
                {
                    if (i == 0)
                        total++;
                    else
                    {
                        passed += testFunc(a, b, op);
                        displayTestProgress(passed, total);
                    }
                }
            }
        }
    }

    displayTestProgress(passed, total);
    cout << endl;
}

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
    double total = 12;
    double passed = 0;
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
    cout << L123 << " * " << L321 << " = " << L123 * L321 << endl;
    cout << (L123 * L321).toString() << " should = "
         << "121932631112635269" << endl;
}

void testAddAll()
{
    cout << "testing addition..." << endl;
    testOperation('+', -1001, 1001, 7, -100001, 100001, 113);
}

void testSubtractAll()
{
    cout << "testing subtraction..." << endl;
    testOperation('-', -1001, 1001, 7, -100001, 100001, 113);
}

void testMultiplyAll()
{
    cout << "testing multiplication..." << endl;
    testOperation('*', -1001, 1001, 7, -100001, 100001, 113);
}

void testDivideAll()
{
    cout << "testing division..." << endl;
    testOperation('/', -100001, 100001, 113, -1001, 1001, 7);
}

void testModuloAll()
{
    cout << "testing modulo..." << endl;
    testOperation('%', -1001, 1001, 11, -1001, 1001, 1);
}

int main()
{
    testCompareAll();
    testAddAll();
    testSubtractAll();
    testMultiplyAll();
    testDivideAll();
    testModuloAll();
    testVeryLongInts();
}