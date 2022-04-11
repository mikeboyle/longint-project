/**
 * @file LongInt.h
 * @author Mike Boyle
 * @brief Header file for LongInt class
 * @date 2022-04-29
 *
 * TODO: Algorithm for divide?
 * TODO: Cases for handleDivide (easy-ish), handleModulo (?)
 *
 *
 * for a % b: IF BOTH SAME SIGN
 * if a == b: return 0
 * if a < b: return a
 * else return a - (b * (a/b))
 */
#ifndef LONG_INT_H
#define LONG_INT_H

#include "DoublyLinkedList.cpp"
#include "ListIterator.h"
#include "Matrix.h"
#include <string>
#include <iostream>

using namespace std;

class LongInt
{

    // Overload operator <<
    friend ostream &operator<<(ostream &, const LongInt &);
    // Overload operator >>
    friend istream &operator>>(istream &, LongInt &);

private:
    DoublyLinkedList<int> digits;
    bool isNegative;
    // compare returns -1 if this is less than other,
    // 1 if this is greater than other,
    // 0 if equal
    int compare(const LongInt &);
    // charToDigit converts a char from '0' to '9' into an int
    int charToDigit(const char &);
    // handleAdd determines which computation to perform when the '+' operator is called
    LongInt *handleAdd(LongInt &, LongInt &);
    // handleSubtract determines which computation to perform when the '-' operator is called
    LongInt *handleSubtract(LongInt &, LongInt &);
    // handleMultiply determines which computation to perform when the '*' operator is called
    LongInt *handleMultiply(LongInt &, LongInt &);
    // handleDivide determines which computation to perform when the '/' operator is called
    LongInt *handleDivide(LongInt &, LongInt &);
    // handleModulo determines which computation to perform when the '%' operator is called
    LongInt *handleModulo(LongInt &, LongInt &);
    // add returns the sum of two LongInts
    LongInt *add(LongInt &, LongInt &);
    // subtract returns the difference of two LongInts (first arg minus second arg)
    LongInt *subtract(LongInt &, LongInt &);
    // multiply returns the product of two LongInts
    LongInt *multiply(LongInt &, LongInt &);
    // divide returns the quotient of two LongInts (first arg divided by second arg)
    LongInt *divide(LongInt &, LongInt &);
    // borrow recursively borrows 1 from a digit's neighbors as part of subtraction
    void borrow(ListIterator<int> &);

public:
    // Default constructor
    LongInt();
    // Construct a LongInt from a string representation of a number
    LongInt(string);
    // Construct a LongInt from an array of digits, length, bool (assume 1s place is in index 0)
    LongInt(int *, int, bool = false);
    // Construct a LongInt from an int
    LongInt(const int &);
    // Copy constructor
    LongInt(const LongInt &);
    // Destructor
    ~LongInt();

    // getLength() returns the number of digits in the LongInt
    int getLength() const;

    // first() returns an iterator at the first digit in the LongInt
    ListIterator<int> first() const;

    // last() returns an iterator at the last digit in the LongInt
    ListIterator<int> last() const;

    // insertFirst() adds a digit to the front of the LongInt
    void insertFirst(const int &);

    // insertLast() adds a digit to the back of the LongInt
    void insertLast(const int &);

    // toString() returns a string representation of the LongInt
    string toString() const;

    // OPERATOR OVERLOADS
    // TODO: Modify iterator so we can use const lvalues here
    // Overload operator =
    const LongInt &operator=(const LongInt &);
    // Overload operator ==
    bool operator==(const LongInt &);
    // Overload operator !=
    bool operator!=(const LongInt &);
    // Overload operator <
    bool operator<(const LongInt &);
    // Overload operator <=
    bool operator<=(const LongInt &);
    // Overload operator >
    bool operator>(const LongInt &);
    // Overload operator >=
    bool operator>=(const LongInt &);
    // Overload operator +
    const LongInt &operator+(LongInt &);
    // Overload operator -
    const LongInt &operator-(LongInt &);
    // Overload operator *
    const LongInt &operator*(LongInt &);
    // Overload operator /
    const LongInt &operator/(LongInt &);
    // Overload operator %
    const LongInt &operator%(LongInt &);
};

#endif