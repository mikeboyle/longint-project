/**
 * @file LongInt.cpp
 * @author Mike Boyle
 * @brief Implementation file for LongInt class
 * @date 2022-04-29
 *
 */
#include "LongInt.h"
#include "Matrix.h"
#include "ListIterator.h"

#include <iostream>
#include <stdexcept>
#include <string>

using namespace std;

LongInt::LongInt()
{
    isNegative = false;
}

LongInt::LongInt(const int &num)
{
    isNegative = num < 0;

    // copy num and add digits
    int number = abs(num);
    while (number > 0)
    {
        digits.insertLast(number % 10);
        number = number / 10;
    }
}

LongInt::LongInt(const LongInt &other)
{
    isNegative = other.isNegative;
    digits = other.digits;
}

const LongInt &LongInt::operator=(const LongInt &other)
{
    if (this != &other)
    {
        isNegative = other.isNegative;
        digits = other.digits;
    }
    return *this;
}

LongInt::~LongInt()
{
}

int LongInt::getLength() const
{
    return digits.getLength();
}

int LongInt::compare(LongInt &other)
{
    // First compare isNegative
    if (isNegative && !other.isNegative) // this is negative; other is not
        return -1;
    else if (!isNegative && other.isNegative) // other is negative; this is not
        return 1;

    // From here forward, numbers are either BOTH negativer or BOTH positive
    else if (getLength() < other.getLength()) // other has more digits
        return isNegative ? 1 : -1;           // a "smaller" negative number is bigger
    else if (getLength() > other.getLength()) // other has fewer digits
        return isNegative ? -1 : 1;           // a "bigger" negative number is smaller

    // Numbers are the same length and both positive / both negative
    ListIterator<int> thisLast = digits.iteratorEnd();
    ListIterator<int> otherLast = other.digits.iteratorEnd();

    while (thisLast.hasPrev() && otherLast.hasPrev())
    {
        if (*thisLast < *otherLast)
            return isNegative ? 1 : -1;
        else if (*thisLast > *otherLast)
            return isNegative ? -1 : 1;
        else
        {
            thisLast.prev();
            otherLast.prev();
        }
    }

    // If we get this far, the numbers are equal
    return 0;
}

// TODO: Modify iterator class & methods so &L can be const
ostream &operator<<(ostream &out, LongInt &L)
{
    if (L.isNegative)
        out << "-";

    ListIterator<int> last = L.digits.iteratorEnd();
    while (last.hasPrev())
    {
        out << *last;
        last.prev();
    }

    return out;
}

// Begin code from https://stackoverflow.com/a/30727561
int LongInt::charToDigit(const char &c)
{
    return (int)c - 48;
}
// End adapted code

istream &operator>>(istream &in, LongInt &L)
{
    char currChar;
    bool isFirstDigit = true;
    while (in.peek() != '\n')
    {
        if (isFirstDigit && in.peek() == '-')
        {
            L.isNegative = true;  // set negative to true
            in.ignore();          // skip the minus sign
            isFirstDigit = false; // set flag to false
        }
        else
        {
            isFirstDigit = false; // set flag to false
            in >> currChar;
            L.digits.insertFirst(L.charToDigit(currChar));
        }
    }

    return in;
}

bool LongInt::operator==(LongInt &other)
{
    return compare(other) == 0;
}

bool LongInt::operator!=(LongInt &other)
{
    return compare(other) != 0;
}

bool LongInt::operator<(LongInt &other)
{
    return compare(other) == -1;
}

bool LongInt::operator<=(LongInt &other)
{
    return compare(other) <= 0;
}

bool LongInt::operator>(LongInt &other)
{
    return compare(other) == 1;
}

bool LongInt::operator>=(LongInt &other)
{
    return compare(other) >= 0;
}

LongInt &LongInt::operator+(LongInt &other)
{
    // return handleAdd(other);
    LongInt a = LongInt(*this);
    LongInt b = LongInt(other);
    LongInt *res = add(a, b);

    return *res;
}

LongInt &LongInt::operator-(LongInt &other)
{
    LongInt a = LongInt(*this);
    LongInt b = LongInt(other);
    LongInt *res = subtract(a, b);

    return *res;
}

// LongInt &LongInt::handleAdd(LongInt &other)
// {
//     LongInt a = LongInt(*this);
//     LongInt b = LongInt(other);
//     LongInt *res = new LongInt;

//     if (isNegative)
//     {
//         if (other.isNegative)
//         {
//             LongInt sum = add(a, b);
//             sum.isNegative = true;
//             res = &sum;
//         }
//         else
//         {
//             LongInt diff = b - a;
//             res = &diff;
//         }
//     }
//     else
//     {
//         if (other.isNegative)
//         {
//             LongInt diff = a - b;
//             res = &diff;
//         }
//         else
//         {
//             LongInt sum = add(a, b);
//             res = &sum;
//         }
//     }

//     return *res;
// }

LongInt *LongInt::add(LongInt &a, LongInt &b)
{
    ListIterator<int> currA = a.digits.iteratorBegin();
    ListIterator<int> currB = b.digits.iteratorBegin();

    int carry = 0;

    LongInt *res = new LongInt;
    while (currA.hasNext() || currB.hasNext())
    {
        int digitA = currA.hasNext() ? *currA : 0;
        int digitB = currB.hasNext() ? *currB : 0;

        int sum = digitA + digitB + carry; // add the digits
        res->digits.insertLast(sum % 10);  // add to sum
        carry = sum / 10;                  // carry over

        // advance iterators if they are not already finished
        if (currA.hasNext())
            currA.next();
        if (currB.hasNext())
            currB.next();
    }

    // add any remaining carry
    if (carry > 0)
        res->digits.insertLast(carry);

    // return the result
    return res;
}

LongInt *LongInt::subtract(LongInt &a, LongInt &b)
{
    ListIterator<int> currA = a.digits.iteratorBegin();
    ListIterator<int> currB = b.digits.iteratorBegin();

    LongInt *res = new LongInt;
    while (currA.hasNext() || currB.hasNext())
    {
        int digitA = currA.hasNext() ? *currA : 0;
        int digitB = currB.hasNext() ? *currB : 0;

        if (digitA < digitB)
        {
            // borrow
            ListIterator<int> copyA(currA);
            copyA.next();
            borrow(copyA);
            currA = *currA + 10;
            digitA = *currA;
        }
        // subtract the current digits

        res->digits.insertLast(digitA - digitB);
        // advance iterators if they are not already finished
        if (currA.hasNext())
            currA.next();
        if (currB.hasNext())
            currB.next();
    }
    return res;
}

void LongInt::borrow(ListIterator<int> &p)
{
    cout << "borrowing from " << *p << endl;
    if (*p > 0)
        p = *p - 1;
    else if (p.hasNext())
    {
        p = 9;
        p.next();
        borrow(p);
    }
}
