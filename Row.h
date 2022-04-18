/**
 * @file Row.h
 * @author Mike Boyle
 * @brief Header file for Matrix Row
 * @date 2022-04-18
 *
 *
 */
#ifndef ROW_H
#define ROW_H

class Row
{
private:
    double *arr;
    int length;

public:
    Row(double *array, int l);
    ~Row();
    double &operator[](int col);
};

#endif