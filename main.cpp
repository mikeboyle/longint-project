#include <iostream>
#include "Matrix.h"

using namespace std;

int main()
{
    Matrix m = Matrix(3, 3);
    m.print();

    cout << m[0][0] << endl;
    m[0][0] = 3;
    m.print();

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
            m[i][j] = 3 * i + j;
    }
    m.print();
}