// ============================================================================
// W5D6 可复用练习 · Stack<T> 类模板
// ----------------------------------------------------------------------------
// 用 std::vector<T> 作为内部存储，做一个类型安全的栈。
// 你只填 TODO；测试代码已经写好。
// ============================================================================

#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include <windows.h>

template <typename T>
class Stack {
public:
    void push(const T& value) {
        // TODO 1：把 value 放到 data_ 末尾。
        data_.push_back(value);
    }
    void pop() {
        // TODO 2：空栈抛 std::out_of_range；否则删末尾。
        if (data_.size() == 0) {
            throw std::out_of_range("错误，栈为空");
        }
        else {
            data_.pop_back();
        }
    }

    T& top() {
        // TODO 3：空栈抛 std::out_of_range；否则返回末尾元素的引用。
        if (data_.size() == 0) {
            throw std::out_of_range("错误，栈为空");
        }
        return data_.back();
    }

    const T& top() const {
        // TODO 4：const 版本，返回 const T&。
        if (data_.size() == 0) {
            throw std::out_of_range("错误，栈为空");
        }
        else {
            const T& a= data_[data_.size() - 1];
            return a;
        }
    }

    bool empty() const {
        // TODO 5：返回 data_ 是否为空。
        return data_.empty();
    }

    std::size_t size() const {
        return data_.size();
    }

private:
    std::vector<T> data_;
};

int run_selftests() {
    int passed = 0;
    int failed = 0;

    auto check = [&](bool ok, const char* name) {
        if (ok) {
            ++passed;
            std::cout << "[PASS] " << name << "\n";
        } else {
            ++failed;
            std::cout << "[FAIL] " << name << "\n";
        }
    };

    Stack<int> numbers;
    check(numbers.empty() && numbers.size() == 0, "empty stack");

    numbers.push(10);
    numbers.push(20);
    check(numbers.size() == 2 && numbers.top() == 20,
          "int push/top");

    numbers.pop();
    check(numbers.size() == 1 && numbers.top() == 10,
          "int pop");

    numbers.pop();
    check(numbers.empty(), "empty after pops");

    bool threw = false;
    try {
        numbers.pop();
    } catch (const std::out_of_range&) {
        threw = true;
    }
    check(threw, "pop empty throws");

    Stack<std::string> words;
    words.push("hello");
    words.push("world");
    check(words.top() == "world" && words.size() == 2,
          "string stack");

    const Stack<std::string>& read_only = words;
    check(read_only.top() == "world", "const top");

    std::cout << "\n" << passed << " passed, " << failed << " failed\n";
    return failed == 0 ? 0 : 1;
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    return run_selftests();
}
