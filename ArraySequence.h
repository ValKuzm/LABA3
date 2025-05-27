#pragma once
#include "Sequence.h"
#include "DynamicArray.h"

template <class T>
class ArraySequence : public Sequence<T> {
protected:
    DynamicArray<T>* array;

    virtual void AppendInternal(const T& item) {
        array->Resize(array->GetSize() + 1);
        array->Set(array->GetSize() - 1, item);
    }

    virtual void PrependInternal(const T& item) {
        array->Resize(array->GetSize() + 1);
        for (int i = array->GetSize() - 1; i > 0; i--) {
            array->Set(i, array->Get(i - 1));
        }
        array->Set(0, item);
    }

    virtual void InsertAtInternal(const T& item, int index) {
        array->Resize(array->GetSize() + 1);
        for (int i = array->GetSize() - 1; i > index; i--) {
            array->Set(i, array->Get(i - 1));
        }
        array->Set(index, item);
    }

public:
    ArraySequence() : array(new DynamicArray<T>()) {}

    ArraySequence(T* items, int count) : array(new DynamicArray<T>(items, count)) {}

    explicit ArraySequence(int size) : array(new DynamicArray<T>(size)) {}

    ArraySequence(const ArraySequence<T>& other) : array(new DynamicArray<T>(*other.array)) {}

    virtual ~ArraySequence() override {
        delete array;
    }

    T GetFirst() const override {
        if (array->GetSize() == 0) throw std::out_of_range("Sequence is empty");
        return array->Get(0);
    }

    T GetLast() const override {
        if (array->GetSize() == 0) throw std::out_of_range("Sequence is empty");
        return array->Get(array->GetSize() - 1);
    }

    T Get(int index) const override {
        this->CheckIndex(index, array->GetSize());
        return array->Get(index);
    }

    int GetLength() const override {
        return static_cast<int>(array->GetSize());
    }

    Sequence<T>* GetSubsequence(int startIndex, int endIndex) const override {
        this->CheckIndex(startIndex, array->GetSize());
        this->CheckIndex(endIndex, array->GetSize());
        if (startIndex > endIndex) throw std::invalid_argument("Invalid index range");

        // Используем фабричный метод для создания подпоследовательности
        ArraySequence<T>* subSequence = static_cast<ArraySequence<T>*>(this->CreateEmptySequence());
        for (int i = startIndex; i <= endIndex; i++) {
            subSequence->AppendInternal(array->Get(i));
        }
        return subSequence;
    }

    Sequence<T>* Append(const T& item) override {
        Sequence<T>* instance = this->Instance();
        static_cast<ArraySequence<T>*>(instance)->AppendInternal(item);
        return instance;
    }

    Sequence<T>* Prepend(const T& item) override {
        Sequence<T>* instance = this->Instance();
        static_cast<ArraySequence<T>*>(instance)->PrependInternal(item);
        return instance;
    }

    Sequence<T>* InsertAt(const T& item, int index) override {
        this->CheckIndex(index, array->GetSize() + 1);
        Sequence<T>* instance = this->Instance();
        static_cast<ArraySequence<T>*>(instance)->InsertAtInternal(item, index);
        return instance;
    }

    Sequence<T>* Concat(Sequence<T>* list) const override {
        ArraySequence<T>* newSequence = static_cast<ArraySequence<T>*>(this->CreateEmptySequence());
        for (int i = 0; i < this->GetLength(); i++) {
            newSequence->AppendInternal(this->Get(i));
        }
        for (int i = 0; i < list->GetLength(); i++) {
            newSequence->AppendInternal(list->Get(i));
        }
        return newSequence;
    }

    void Set(int index, const T& value) override {
        array->Set(index, value);
    }

    Sequence<T>* Map(T(*func)(const T&)) const override {
        ArraySequence<T>* newSequence = static_cast<ArraySequence<T>*>(this->CreateEmptySequence());
        for (int i = 0; i < array->GetSize(); i++) {
            newSequence->AppendInternal(func(array->Get(i)));
        }
        return newSequence;
    }

    Sequence<T>* Where(bool (*func)(const T&)) const override {
        ArraySequence<T>* newSequence = static_cast<ArraySequence<T>*>(this->CreateEmptySequence());
        for (int i = 0; i < array->GetSize(); i++) {
            T item = array->Get(i);
            if (func(item)) {
                newSequence->AppendInternal(item);
            }
        }
        return newSequence;
    }

    T Reduce(T(*func)(const T&, const T&), T startValue) const override {
        T result = startValue;
        for (int i = 0; i < array->GetSize(); i++) {
            result = func(result, array->Get(i));
        }
        return result;
    }

protected:
    // Создает пустую последовательность соответствующего типа
    virtual Sequence<T>* CreateEmptySequence() const = 0;

    // Возвращает копию текущего объекта (для mutable) или новый объект (для immutable)
    virtual Sequence<T>* Instance() const = 0;
};


//template <class T>
//class MutableArraySequence : public ArraySequence<T> {
//public:
//    // Конструкторы
//    MutableArraySequence() : ArraySequence<T>() {}
//    MutableArraySequence(T* items, int count) : ArraySequence<T>(items, count) {}
//    explicit MutableArraySequence(int size) : ArraySequence<T>(size) {}
//    MutableArraySequence(const MutableArraySequence<T>& other) : ArraySequence<T>(other) {}
//
//    // Реализация чисто виртуальных методов
//    Sequence<T>* CreateEmptySequence() const override {
//        return new MutableArraySequence<T>();
//    }
//
//    Sequence<T>* Instance() const override {
//        return const_cast<MutableArraySequence<T>*>(this);
//    }
//
//    // Оператор присваивания
//    MutableArraySequence& operator=(const MutableArraySequence<T>& other) {
//        if (this != &other) {
//            ArraySequence<T>::operator=(other);
//        }
//        return *this;
//    }
//};
//
//template <class T>
//class ImmutableArraySequence : public ArraySequence<T> {
//public:
//    using ArraySequence<T>::ArraySequence;
//
//protected:
//    Sequence<T>* CreateEmptySequence() const override {
//        return new ImmutableArraySequence<T>();
//    }
//
//    Sequence<T>* Instance() const override {
//        return new ImmutableArraySequence<T>(*this);
//    }
//
//    void AppendInternal(const T& item) override {
//        this->array = new DynamicArray<T>(*this->array);
//        ArraySequence<T>::AppendInternal(item);
//    }
//
//    void PrependInternal(const T& item) override {
//        this->array = new DynamicArray<T>(*this->array);
//        ArraySequence<T>::PrependInternal(item);
//    }
//
//    void InsertAtInternal(const T& item, int index) override {
//        this->array = new DynamicArray<T>(*this->array);
//        ArraySequence<T>::InsertAtInternal(item, index);
//    }
//};