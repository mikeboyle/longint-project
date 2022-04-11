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
    if (num == 0)
        insertLast(0);

    // copy num and add digits
    int number = abs(num);
    while (number > 0)
    {
        insertLast(number % 10);
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

ListIterator<int> LongInt::first() const
{
    return digits.iteratorBegin();
}

ListIterator<int> LongInt::last() const
{
    return digits.iteratorEnd();
}

void LongInt::insertFirst(const int &item)
{
    digits.insertFirst(item);
}

void LongInt::insertLast(const int &item)
{
    digits.insertLast(item);
}

string LongInt::toString() const
{
    stringstream out;
    out << *this;
    return out.str();
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
    ListIterator<int> thisLast = last();
    ListIterator<int> otherLast = other.last();

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

ostream &operator<<(ostream &out, const LongInt &L)
{
    if (L.isNegative)
        out << "-";

    ListIterator<int> last = L.last();
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
            L.insertFirst(L.charToDigit(currChar));
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

const LongInt &LongInt::operator+(LongInt &other)
{
    LongInt a = LongInt(*this);
    LongInt b = LongInt(other);

    LongInt *res = handleAdd(a, b);
    return *res;
}

const LongInt &LongInt::operator-(LongInt &other)
{
    LongInt a = LongInt(*this);
    LongInt b = LongInt(other);

    LongInt *res = handleSubtract(a, b);

    return *res;
}

const LongInt &LongInt::operator*(LongInt &other)
{
    LongInt a = LongInt(*this);
    LongInt b = LongInt(other);

    LongInt *res = handleMultiply(a, b);

    return *res;
}

LongInt *LongInt::handleSubtract(LongInt &a, LongInt &b)
{
    LongInt *res;
    if (a == b)
        res = new LongInt(0);
    else if (a > b)
    {
        // both are positive - straightforward case
        if (!a.isNegative && !b.isNegative)
            res = subtract(a, b);

        // a is positive, b is negative
        // a - (-b) = a + b
        // ex: 30 - -20 = 30 + 20
        else if (!a.isNegative && b.isNegative)
        {
            b.isNegative = false;
            res = add(a, b);
        }

        // else both are negative
        // -a - -b = -a + b = b - a
        // ex: -20 - (-30) = -20 + 30 = 30-20
        else
        {
            a.isNegative = false;
            b.isNegative = false;
            res = subtract(b, a);
        }
    }
    else // a < b
    {
        // both are positive
        // a - b = -(b-a)
        // ex: 20 - 30 = -(30-20)
        // note that if a < b, then a -b will always be negative
        if (!a.isNegative && !b.isNegative)
        {
            res = subtract(b, a);
            res->isNegative = true;
        }

        // a is negative, b is positive
        // negative number minus positive will always be negative
        // -a - b = -(a+b)
        // ex: -20 - 30 = -(20 + 30)
        // note that a negative number minus a positive number will always be negative
        else if (a.isNegative && !b.isNegative)
        {
            a.isNegative = false;
            res = add(a, b);
            res->isNegative = true;
        }

        // else both are negative
        // -a - -b = -a + b = -(a - b)
        // ex: -30 - -29 = -30 + 29 = -(30 - 29)
        // note that a negative number minus a larger negative number will always be negative
        else
        {
            a.isNegative = false;
            b.isNegative = false;
            res = subtract(a, b);
            res->isNegative = true;
        }
    }

    return res;
}

LongInt *LongInt::handleAdd(LongInt &a, LongInt &b)
{
    LongInt *res;

    if (a.isNegative)
    {
        if (b.isNegative)
        {
            res = add(a, b);
            res->isNegative = true;
        }
        else
        {
            // TODO: Should be a call to handleSubtract(b, a) to catch all cases
            // For now this can only handle a "straightforward" b - a where abs(a) < abs(b)
            res = subtract(b, a);
        }
    }
    else
    {
        if (b.isNegative)
        {
            // TODO: Should be a call to handleSubtract(a, b) to catch all cases
            // For now this can only handle a "straightforward" a - b where abs(b) < abs(a)
            res = subtract(a, b);
        }
        else
        {
            res = add(a, b);
        }
    }

    return res;
}

LongInt *LongInt::handleMultiply(LongInt &a, LongInt &b)
{
    LongInt *res;

    // were a and b both positive or both negative? check and save.
    bool bothSameSign = (a.isNegative && b.isNegative) || (!a.isNegative && !b.isNegative);

    // convert a and b to their absolute value, then multiply
    a.isNegative = false;
    b.isNegative = false;
    res = multiply(a, b);

    // make result negative if exactly one of a or b was negative
    if (!bothSameSign)
        res->isNegative = true;

    return res;
}

LongInt *LongInt::add(LongInt &a, LongInt &b)
{
    ListIterator<int> currA = a.first();
    ListIterator<int> currB = b.first();

    int carry = 0;

    LongInt *res = new LongInt;
    while (currA.hasNext() || currB.hasNext())
    {
        int digitA = currA.hasNext() ? *currA : 0;
        int digitB = currB.hasNext() ? *currB : 0;

        int sum = digitA + digitB + carry; // add the digits
        res->insertLast(sum % 10);         // add to sum
        carry = sum / 10;                  // carry over

        // advance iterators if they are not already finished
        if (currA.hasNext())
            currA.next();
        if (currB.hasNext())
            currB.next();
    }

    // add any remaining carry
    if (carry > 0)
        res->insertLast(carry);

    // return the result
    return res;
}

LongInt *LongInt::subtract(LongInt &a, LongInt &b)
{
    ListIterator<int> currA = a.first();
    ListIterator<int> currB = b.first();

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

        res->insertLast(digitA - digitB);
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
    if (*p > 0)
        p = *p - 1;
    else if (p.hasNext())
    {
        p = 9;
        p.next();
        borrow(p);
    }
}

LongInt *LongInt::multiply(LongInt &a, LongInt &b)
{
    // create the left matrix for a
    // TODO: more precise way to compute numLeftRows
    int numLeftRows = a.getLength() + b.getLength() - 1;
    int numLeftCols = b.getLength();

    Matrix left(numLeftRows, numLeftCols);

    int row = 0;
    ListIterator<int> currA = a.first();
    while (currA.hasNext())
    {
        int currRow = row;
        for (int col = 0; col < numLeftCols; col++)
            left[currRow++][col] = *currA;
        row++;
        currA.next();
    }

    // create the right matrix for b
    Matrix right(b.getLength(), 1);
    ListIterator<int> currB = b.first();
    for (int i = 0; i < b.getLength(); i++)
        right[i][0] = currB.next();

    Matrix product = left * right;

    // some entries in product may be > 10
    // convert product to a LongInt
    LongInt *res = new LongInt;
    int carry = 0;
    int num;
    for (int row = 0; row < product.getHeight(); row++)
    {
        num = product[row][0];
        res->insertLast((num + carry) % 10);
        carry = (num + carry) / 10;
    }

    return res;
}
