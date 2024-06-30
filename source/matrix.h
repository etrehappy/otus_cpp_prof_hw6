#pragma once

#include <map>
#include <tuple>
#include <iostream>

using Key = std::tuple<size_t, size_t>;

template<typename T, T default_value>
class Matrix
{
public:
    Matrix();  

    void PrintRange(Key begin, Key end);
    void PrintSize() const;
    void PrintAllWithPosition() const;

    class Proxy;
    Proxy& operator[](size_t row);

private:
    void XInitialisation(size_t min, size_t max);
    void Emplace(Key key, T value);
    auto Size() const;
        
    std::map<Key, T> matrix_map_;
    Proxy proxy_;
};

template<typename T, T default_value>
class Matrix<T, default_value>::Proxy
{
public:
    Proxy(std::map<Key, T>& data, size_t row);

    Proxy& operator[](size_t col);
    Proxy& operator=(T value);
    operator T() const;

    void ChangeCurrentRow(size_t row);

private:
    std::map<Key, T>& ref_matrix_;
    size_t row_, col_;
};

#include "matrix.ipp"