#include <cstddef>
#include <map>
#include <array>
#include <iostream>
#include <memory>


template<class T, T def, std::size_t N>
class MatrixElement
{
    using KeyType = std::array<std::size_t, N>;
    using MapType = std::map<KeyType, T>;

    std::shared_ptr<MapType> _mat;
    KeyType _key;

public:
    MatrixElement(std::shared_ptr<MapType> & _mat, KeyType key):
        _mat{ _mat },
        _key{ key }
    {}

    operator T () const { return value(); }

    T value() const
    {
        auto itr = _mat->find(_key);
        if (itr != _mat->end()) return itr->second;
        return def;
    }

    T operator=(const T & value)
    {
        if (value == def) {
            auto itr = _mat->find(_key);
            if (itr != _mat->end()) _mat->erase(itr);
        }
        else {
            _mat->operator[](_key) = value;
        }
        return value;
    }
};


template<class T, T def, std::size_t N = 2, std::size_t M = 0>
class Matrix
{
public:
    using MatrixType = Matrix<T, def, N, M>;
    using KeyType = std::array<std::size_t, N>;
    using ElementType = MatrixElement<T, def, N>;
    using MapType = std::map<KeyType, T>;
    template<std::size_t S>
    using Array = std::array<std::size_t, S>;

private:
    std::shared_ptr<MapType> _mat;
    Array<M> _indices;

    template<std::size_t ...I, class ...Args>
    auto generate_key(std::index_sequence<I...>, Args... args)
    {
        return Array<sizeof...(args) + sizeof...(I)>{
            _indices[I]...,
            static_cast<std::size_t>(args)...
        };
    }

    template<std::size_t ...I>
    auto generate_proxy(std::index_sequence<I...>, std::size_t index)
    {
        if constexpr (N == M + 1) {
            return operator()(index);
        } else {
            return Matrix<T, def, N, M + 1>(
                _mat,
                _indices[I]...,
                static_cast<std::size_t>(index));
        }
    }

public:
    Matrix() :
        _mat{ new MapType }
    {}

    template<class ...Args>
    Matrix(std::shared_ptr<MapType> & _mat, Args... args):
        _mat{ _mat },
        _indices{ args... }
    {}

    T def_value() const { return def; }

    auto size() const
    {
        if constexpr (M == 0) {
            return _mat->size();
        }
        else {
            Array<N> l, u;
            for (int i = 0; i < M; i++) {
                l[i] = u[i] = _indices[i];
            }
            for (int i = M; i < N; i++) {
                l[i] = 0;
                u[i] = std::numeric_limits<size_t>::max();
            }
            return std::distance(_mat->lower_bound(l), _mat->upper_bound(u));
        }
    }

    template<class ...Args>
    ElementType operator() (Args... args)
    {
        static_assert(sizeof...(args) == N - M, "Matrix: wrong size");
        int dummy[sizeof...(Args)] = {(
            [](auto arg) {
                if (arg < 0) throw std::out_of_range("Matrix: invalid index");
            }(args),
            0)...};

        auto key = generate_key(
            std::make_index_sequence<M>{},
            static_cast<std::size_t>(args)...);

        return ElementType(_mat, key);
    }

    auto operator[](int index)
    {
        if (index < 0) throw std::out_of_range("Matrix: invalid index");
        return generate_proxy(
            std::make_index_sequence<M>{},
            static_cast<std::size_t>(index));
    }

    auto begin() const { return _mat->begin(); }
    auto end() const { return _mat->end(); }
};
