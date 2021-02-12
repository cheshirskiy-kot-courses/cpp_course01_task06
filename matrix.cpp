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
            std::cout << m[i][j];
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
        m[i][i] = m[N - 1 - i][i] = i;
    }

    for (int i = 0; i < 10; i += 2) {
        for (int j = 0; j < 10; j += 2) {
            m[i][j] = m.def_value();
            m[i + 1][j + 1] = m.def_value();
        }
    }

    print_part(m, 1, 8);
    std::cout << std::endl;

    std::cout << m.size() << std::endl;
    std::cout << std::endl;

    for (const auto & e : m) {
        std::cout << "[ ";
        int j = 0;
        for (auto i : e.first) {
            std::cout << i;
            if (j++ < e.first.size() - 1) {
                std::cout << ", ";
            }
        }
        std::cout << " ]: ";

        std::cout << e.second << std::endl;
    }

    return 0;
}
