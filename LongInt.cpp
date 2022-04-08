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