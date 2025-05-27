#pragma once
#include "ArraySequence.h"

template <class T>
class MutableArraySequence : public ArraySequence<T> {
public:
    // явно объ€вл€ем конструкторы
    MutableArraySequence() : ArraySequence<T>() {}

    MutableArraySequence(T* items, int count) : ArraySequence<T>(items, count) {}

    explicit MutableArraySequence(int size) : ArraySequence<T>(size) {}

    MutableArraySequence(const MutableArraySequence<T>& other)
        : ArraySequence<T>(other) {}

    // ƒобавл€ем оператор присваивани€
    MutableArraySequence<T>& operator=(const MutableArraySequence<T>& other) {
        if (this != &other) {
            ArraySequence<T>::operator=(other);
        }
        return *this;
    }

    // –еализаци€ чисто виртуальных методов
    Sequence<T>* CreateEmptySequence() const override {
        return new MutableArraySequence<T>();
    }

    Sequence<T>* Instance() const override {
        return const_cast<MutableArraySequence<T>*>(this);
    }
};