/**
 * @file Row.cpp
 * @author Mike Boyle
 * @brief Implementation file for Matrix Row
 * @date 2022-04-18
 *
 *
 */

#include "Row.h"
#include <stdexcept>

Row::Row(double *array, int l)
{
    arr = array;
    length = l;
}

Row::~Row()
{
    delete[] arr;
};

double &Row::operator[](int col)
{
    if (col < 0 || col > length - 1)
        throw std::invalid_argument("col index out of range");
    return arr[col];
}