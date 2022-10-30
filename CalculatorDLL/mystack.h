#pragma once
#include <iostream>
#include <exception>

const int MyStack_SIZE = 50;

template<typename T>
class MyStack {
    T* data;
    size_t size = 0;
public:

    MyStack() {
        data = new T[MyStack_SIZE];
    }

    MyStack(MyStack const& lMyStack) {
        data = new T[MyStack_SIZE];
        for (int i = 0; i < lMyStack.size; i++) {
            data[i] = lMyStack.data[i];
        }
        size = lMyStack.size;
    }

    MyStack(MyStack&& rMyStack) {
        data = rMyStack.data;
        size = rMyStack.size;

        rMyStack.data = nullptr;
        rMyStack.size = 0;
    }

    MyStack& operator=(MyStack const& lMyStack) {
        if (data == nullptr) {
            data = new T[MyStack_SIZE];
        }
        for (int i = 0; i < lMyStack.size; i++) {
            data[i] = lMyStack.data[i];
        }
        size = lMyStack.size;

        return this;
    }

    MyStack& operator=(MyStack&& rMyStack) {
        data = rMyStack.data;
        size = rMyStack.size;

        rMyStack.data = nullptr;
        rMyStack.size = 0;

        return this;
    }

    void push(const T& value) {
        if (size >= MyStack_SIZE) {
            throw std::exception("Error: Stack overflow");
        }
        else {
            data[size] = value;
            size++;
        }
    }
    T pop() {
        if (size <= 0) {
            throw std::exception("Error: Empty stack");
        }
        else {
            size--;
            return data[size];
        }
    }
    T peek() {
        if (size <= 0) {
            throw std::exception("Error: Empty stack");
        }
        else {
            return data[size - 1];
        }
    }

    operator bool() {
        return size != 0;
    }

    ~MyStack() {
        delete[] data;
    }
};