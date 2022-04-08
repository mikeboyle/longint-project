/**
 * @file LongInt.h
 * @author Mike Boyle
 * @brief Header file for LongInt class
 * @date 2022-04-29
 *
 */
#ifndef LONG_INT_H
#define LONG_INT_H

#include "DoublyLinkedList.cpp"
#include <string>
#include <iostream>

using namespace std;

class LongInt
{

    // Overload operator <<
    friend ostream &operator<<(ostream &, LongInt &);
    // Overload operator >>
    friend istream &operator>>(istream &, LongInt &);

private:
    DoublyLinkedList<int> digits;
    bool isNegative;
    // compare returns -1 if this is less than other,
    // 1 if this is greater than other,
    // 0 if equal
    int compare(LongInt &);
    // charToDigit converts a char from '0' to '9' into an int
    int charToDigit(const char &);

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

    // OPERATOR OVERLOADS
    // TODO: Modify iterator so we can use const lvalues here
    // Overload operator =
    const LongInt &operator=(const LongInt &);
    // Overload operator ==
    bool operator==(LongInt &);
    // Overload operator !=
    bool operator!=(LongInt &);
    // Overload operator <
    bool operator<(LongInt &);
    // Overload operator <=
    bool operator<=(LongInt &);
    // Overload operator >
    bool operator>(LongInt &);
    // Overload operator >=
    bool operator>=(LongInt &);
    // Overload operator +
    const LongInt &operator+(const LongInt &);
    // Overload operator -
    const LongInt &operator-(const LongInt &);
    // Overload operator *
    const LongInt &operator*(const LongInt &);
    // Overload operator /
    const LongInt &operator/(const LongInt &);
    // Overload operator %
    const LongInt &operator%(const LongInt &);
};

#endif