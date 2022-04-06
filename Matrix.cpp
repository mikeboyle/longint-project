/**
 * @file Matrix.cpp
 * @author Mike Boyle
 * @brief Implementation file for Matrix class
 * @date 2022-04-29
 *
 */

#include <iostream>
#include <stdexcept>
#include "Matrix.h"
#include "Row.h"

using namespace std;

Matrix::Matrix(int h, int w, double initialValue)
{
    if (h < 1 || w < 1)
        throw std::invalid_argument("height and width must be 1 or greater");

    height = h;
    width = w;
    matrix = new double *[height];
    for (int i = 0; i < height; i++)
    {
        matrix[i] = new double[width];
        for (int j = 0; j < width; j++)
            matrix[i][j] = initialValue;
    }
}

Matrix::~Matrix()
{
    delete[] matrix;
}

Row &Matrix::operator[](int i)
{
    if (i < 0 || i > height - 1)
        throw std::invalid_argument("row index out of range");
    Row *r = new Row(matrix[i], width);
    return *r;
}

void Matrix::print()
{
    cout << "[";
    for (int i = 0; i < height; i++)
    {
        cout << "[";
        for (int j = 0; j < width; j++)
        {
            cout << matrix[i][j];
            if (j < width - 1)
                cout << " ";
        }
        cout << "]";
        if (i < height - 1)
            cout << endl;
    }
    cout << "]" << endl;
}