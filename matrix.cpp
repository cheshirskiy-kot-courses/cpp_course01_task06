#include <iostream>

#include "lib.h"


template<class T, T def, std::size_t N>
void print_part(
    Matrix<T, def, N> & m,
    const int begin,
    const int end)
{
    for (int i = begin; i < end; i++) {
        for (int j = begin; j < end; j++) {
            std::cout << m(i, j);
            if (j != end - 1) std::cout << " ";
        }
        std::cout << std::endl;
    }
}


int main()
{
    Matrix<int, 0> m;

    const int N = 10;
    for (int i = 0; i < N; ++i) {
        m(i, i) = m(N - 1 - i, i) = i;
    }

    for (int i = 0; i < 10; i += 2) {
        for (int j = 0; j < 10; j += 2) {
            m(i, j) = m.def_value();
            m(i + 1, j + 1) = m.def_value();
        }
    }

    print_part(m, 1, 8);

    std::cout << m.size() << std::endl;

    // Вывести все занятые ячейки вместе со своими позициями.

    //4 Доступ к элементам матрицы через[].Паттерн Proxy.

    //2 Вывод всех ячеек через range for loop.Паттерн Iterator.

    // Дана оценка сложности присваивания ячейки произвольным значением и значением по
    //умолчанию
    // O(logN), O(logN)

    return 0;
}
