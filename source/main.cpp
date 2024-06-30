#include "matrix.h"

template<typename T, T default_value = 0>
void CheckHW(Matrix<T, default_value>& matrix)
{
    std::cout << "\n\nmatrix[100][100]: " << matrix[100][100];

    ((matrix[100][100] = 314) = 0) = 217;
    std::cout << "\n((matrix[100][100] = 314) = 0) = 217;\nmatrix[100][100]: " << matrix[100][100] << "\n";
    matrix.PrintSize();

    matrix[100][100] = 0;
    std::cout << "\nmatrix[100][100] = 0;" << "\n";
    matrix.PrintSize();
}

int main()
{
    Matrix<int, 0> matrix{};

    Key begin{1, 1}, end{8, 8};

    matrix.PrintRange(begin, end);
    matrix.PrintSize();
    matrix.PrintAllWithPosition();

    CheckHW(matrix);

    

    return 0;
}


