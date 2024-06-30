////////////////////////////////////////////////////////////////////////////////
// class Matrix
////////////////////////////////////////////////////////////////////////////////

template<typename T, T default_value>
Matrix<T, default_value>::Matrix()
    :matrix_map_{}, proxy_{matrix_map_, default_value}
{
    XInitialisation(0, 9);
}

template<typename T, T default_value>
void Matrix<T, default_value>::Emplace(Key key, T value)
{
    matrix_map_.emplace(key, value);
}

template<typename T, T default_value>
void Matrix<T, default_value>::XInitialisation(size_t min, size_t max)
{   
    //   X
    // -----
    // 1   3
    //   2
    // 1   3     

    
    for (size_t row = min; row <= max; row++)
    {
        for (size_t col = min; col <= max; col++)
        {
            if (col == row && row != default_value)
            {
                Emplace(Key{row, col}, static_cast<T>(row));
            }
            else if (max - row == col && col != default_value)
            {
                Emplace(Key{row, col}, static_cast<T>(col));
            }
        }
    }
}

template<typename T, T default_value>
auto Matrix<T, default_value>::Size() const
{
    return matrix_map_.size();
}

template<typename T, T default_value>
void Matrix<T, default_value>::PrintRange(Key begin, Key end)
{ 
    auto [row_min, col_min] = begin;
    auto [row_max, col_max] = end;

    for (size_t row = row_min; row <= row_max; row++)
    {
        std::cout << "row " << row << "-> ";
        for (size_t col = col_min; col <= col_max; col++)
        {
            std::cout << (*this)[row][col];
            std::cout << "   ";
        }
        std::cout << std::endl;
    }
}

template<typename T, T default_value>
void Matrix<T, default_value>::PrintSize() const
{
    std::cout << "size: " << Size() << std::endl;
}

template<typename T, T default_value>
void Matrix<T, default_value>::PrintAllWithPosition() const
{
    for (const auto& [key, value] : matrix_map_)
    {
        auto [row, col] = key;
        std::cout << "value: " << value <<
            "(row " << row <<
            ", col " << col << ")" <<
            std::endl;
    }
}

template<typename T, T default_value>
typename Matrix<T, default_value>::Proxy& Matrix<T, default_value>::operator[](size_t row)
{
    proxy_.ChangeCurrentRow(row);

    return proxy_; 
}




////////////////////////////////////////////////////////////////////////////////
// class Matrix::Proxy
////////////////////////////////////////////////////////////////////////////////

template<typename T, T default_value>
Matrix<T, default_value>::Proxy::Proxy(std::map<Key, T>& matrix, size_t row)
    : ref_matrix_(matrix), row_(row), col_(default_value)
{}


template<typename T, T default_value>
typename Matrix<T, default_value>::Proxy& Matrix<T, default_value>::Proxy::operator[](size_t col)
{    
    col_ = col;
    return *this;
}

template<typename T, T default_value>
typename Matrix<T, default_value>::Proxy& Matrix<T, default_value>::Proxy::operator=(T value)
{
    Key key{row_, col_};  

    if (value == default_value)
    {
        ref_matrix_.erase(key);
    }
    else
    {
        ref_matrix_[key] = value;
    }

    return *this;
}

template<typename T, T default_value>
Matrix<T, default_value>::Proxy::operator T() const
{
    auto it = ref_matrix_.find(Key{row_, col_});

    if (it != ref_matrix_.end()) 
    {
        return it->second;
    }

    return default_value; 
}

template<typename T, T default_value>
void Matrix<T, default_value>::Proxy::ChangeCurrentRow(size_t row)
{
    row_ = row;
}