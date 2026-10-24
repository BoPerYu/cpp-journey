// ============================================================================
// ref05 · 类模板参考程序：Box<T> 和 Stack<T>
// ============================================================================

#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include <windows.h>

template <typename T>
class Box {
public:
    explicit Box(T value) : value_(value) {}

    T& get() {
        return value_;
    }

    const T& get() const {
        return value_;
    }

    void set(T value) {
        value_ = value;
    }

private:
    T value_;
};

template <typename T>
class Stack {
public:
    void push(const T& value) {
        data_.push_back(value);
    }

    void pop() {
        if (data_.empty()) {
            throw std::out_of_range("pop from empty Stack");
        }
        data_.pop_back();
    }

    T& top() {
        if (data_.empty()) {
            throw std::out_of_range("top from empty Stack");
        }
        return data_.back();
    }

    const T& top() const {
        if (data_.empty()) {
            throw std::out_of_range("top from empty Stack");
        }
        return data_.back();
    }

    bool empty() const {
        return data_.empty();
    }

    std::size_t size() const {
        return data_.size();
    }

private:
    std::vector<T> data_;
};

int main() {
    SetConsoleOutputCP(CP_UTF8);

    Box<int> number(42);
    std::cout << "Box<int>: " << number.get() << "\n";

    Box<std::string> text("hello");
    std::cout << "Box<string>: " << text.get() << "\n";

    const Box<int> read_only(7);
    std::cout << "const Box<int>: " << read_only.get() << "\n";

    Stack<int> numbers;
    numbers.push(10);
    numbers.push(20);
    std::cout << "Stack<int>: top=" << numbers.top()
              << " size=" << numbers.size() << "\n";

    Stack<std::string> words;
    words.push("hello");
    words.push("world");
    std::cout << "Stack<string>: top=" << words.top()
              << " size=" << words.size() << "\n";

    return 0;
}
