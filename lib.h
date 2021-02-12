#include <cstddef>
#include <map>
#include <array>
#include <iostream>


template<class T, T def, std::size_t N>
class MatrixElement
{
    using KeyType = std::array<std::size_t, N>;

    std::map<KeyType, T> & _mat;
    KeyType _key;

public:
    MatrixElement(std::map<KeyType, T> & _mat, KeyType key):
        _mat(_mat),
        _key(key)
    {}

    operator T () const { return value(); }

    T value() const
    {
        auto itr = _mat.find(_key);
        if (itr != _mat.end()) return itr->second;
        return def;
    }

    T operator=(const T & value)
    {
        if (value == def) {
            auto itr = _mat.find(_key);
            if (itr != _mat.end()) _mat.erase(itr);
        }
        else {
            _mat[_key] = value;
        }
        return value;
    }
};


template<class T, T def, std::size_t N = 2>
class Matrix
{
    using KeyType = std::array<std::size_t, N>;
    using ElementType = MatrixElement<T, def, N>;

    std::map<KeyType, T> _mat;
    KeyType _key;
    T _tempValue = def;

public:
    T def_value() const { return def; }

    std::size_t size() const
    {
        return _mat.size();
    }

    template<class ...Args>
    ElementType operator() (Args... args)
    {
        static_assert(sizeof...(args) == N, "Matrix: wrong size");
        int dummy[sizeof...(Args)] = {(
            [](auto arg) {
                if (arg < 0) throw std::out_of_range("Matrix: invalid index");
            }(args),
            0)...};

        auto key = std::array<std::size_t, N>{static_cast<std::size_t>(args)...};

        return ElementType(_mat, key);
    }
};
