#pragma once
#include "MutableArraySequence.h"
#include <stdexcept>
#include <cmath>
#include <iomanip>
#include <sstream>

template <class T>
class SquareMatrix {
private:
    MutableArraySequence<T>* data;
    size_t size;

    void CheckIndices(size_t row, size_t col) const {
        if (row >= size || col >= size)
            throw std::out_of_range("Matrix indices out of range");
    }

public:
    // Конструкторы
    SquareMatrix(size_t size, const T& defaultValue = T()) : size(size) {
        if (size == 0)
            throw std::invalid_argument("Matrix size cannot be zero");

        data = new MutableArraySequence<T>(size * size);
        try {
            for (size_t i = 0; i < size * size; i++) {
                data->Set(i, defaultValue);
            }
        }
        catch (...) {
            delete data;
            throw;
        }
    }
    SquareMatrix(const SquareMatrix<T>& other) : size(other.size) {
        data = new MutableArraySequence<T>(other.size * other.size);
        for (size_t i = 0; i < size * size; i++) {
            data->Set(i, other.data->Get(i));
        }
    }

    // Деструктор
    ~SquareMatrix() {
        delete data;
    }

    // Оператор присваивания
    SquareMatrix<T>& operator=(const SquareMatrix<T>& other) {
        if (this != &other) {
            MutableArraySequence<T>* newData = new MutableArraySequence<T>(*other.data);
            delete data;
            data = newData;
            size = other.size;
        }
        return *this;
    }

    // Остальные методы остаются без изменений
    size_t GetSize() const { return size; }

    T Get(size_t row, size_t col) const {
        CheckIndices(row, col);
        return data->Get(row * size + col);
    }

    void Set(size_t row, size_t col, const T& value) {
        CheckIndices(row, col);
        data->Set(row * size + col, value);
    }

    // Математические операции (3 балла)
    SquareMatrix<T> operator+(const SquareMatrix<T>& other) const {
        if (size != other.size)
            throw std::invalid_argument("Matrix sizes must match");

        SquareMatrix<T> result(size);
        for (size_t i = 0; i < size * size; i++) {
            result.data->Set(i, data->Get(i) + other.data->Get(i));
        }
        return result;
    }

    SquareMatrix<T> operator*(const T& scalar) const {
        SquareMatrix<T> result(size);
        for (size_t i = 0; i < size * size; i++) {
            result.data->Set(i, data->Get(i) * scalar);
        }
        return result;
    }

    SquareMatrix<T> operator*(const SquareMatrix<T>& other) const {
        if (size != other.size)
            throw std::invalid_argument("Matrix sizes must match");

        SquareMatrix<T> result(size);
        for (size_t i = 0; i < size; i++) {
            for (size_t j = 0; j < size; j++) {
                T sum = T();
                for (size_t k = 0; k < size; k++) {
                    sum += Get(i, k) * other.Get(k, j);
                }
                result.Set(i, j, sum);
            }
        }
        return result;
    }

    // Специальные операции (2 балла)
    SquareMatrix<T> Transpose() const {
        SquareMatrix<T> result(size);
        for (size_t i = 0; i < size; i++) {
            for (size_t j = 0; j < size; j++) {
                result.Set(j, i, Get(i, j));
            }
        }
        return result;
    }

    T Trace() const {
        T sum = T();
        for (size_t i = 0; i < size; i++) {
            sum += Get(i, i);
        }
        return sum;
    }

    bool IsSymmetric() const {
        for (size_t i = 0; i < size; i++) {
            for (size_t j = 0; j < i; j++) {
                if (Get(i, j) != Get(j, i)) {
                    return false;
                }
            }
        }
        return true;
    }

    // Дополнительные функции (0.5 балла)
    void Print() const {
        const int width = 10;
        for (size_t i = 0; i < size; i++) {
            for (size_t j = 0; j < size; j++) {
                std::cout << std::setw(width) << Get(i, j) << " ";
            }
            std::cout << "\n";
        }
    }
};