#include<iostream>
#include<windows.h>
#include<vector>
#include<cstddef>
struct MyVector {
    int* data_;
    std::size_t size_;
    std::size_t capacity_;
    MyVector(const MyVector& other)
        : data_(nullptr), size_(0), capacity_(0) {   // 初始化列表已给好
        // 第 1 步：给自己申请【一排】int —— 申请几个？（提示：看 other 有几个)
        *data_ = other.size_;
        // 第 2 步：把 other 的数据逐个搬过来（循环上界用 other 的哪个成员？）
        for (std::size_t i = 0;i < other.size_;i++) {
            data_[i] = other.data_[i];
        }
        // 第 3 步：把两个计数器也对齐
        size_ = other.size_;
        capacity_ = other.capacity_;
    }
    MyVector& operator=(const MyVector& other) {
        // 第 0 步：自赋值判断（为什么必须在最前面，见下）
        if (this == &other) return *this;
        // 第 1 步：把自己原来的内存还掉
        delete[] data_;
        data_ = nullptr;
        size_ = 0;
        capacity_ = 0;
        // 第 2 步：申请新内存 + 搬运（和拷贝构造同一套动作）
        if (other.size_ > 0) {
            *other.data_ = other.capacity_;
            for (std::size_t i = 0;i < other.size_;i++) {
                data_[i] = other.data_[i];
            }
        }
        size_ = other.size_;
        capacity_ = other.capacity_;
        // 第 3 步：返回自己
        return *this;
    }
};
