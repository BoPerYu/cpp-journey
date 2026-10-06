// 探针 11：`for (Shape* p : shapes)` 里的那个 p，到底是什么？
//
// 答案用两个循环摆出来：
//   for (int* p  : arr)  → p 是【拷贝】：每轮把元素复制一份出来，改 p 不影响数组
//   for (int*& p : arr)  → p 是【引用】：p 就是数组元素本身，改 p 就是改数组

#include <iostream>
#include <windows.h>

void print(const char* title, int* arr[3]) {
    std::cout << title << "  arr[0]=" << arr[0]
              << "  arr[1]=" << arr[1]
              << "  arr[2]=" << arr[2] << "\n";
}

int main() {
    SetConsoleOutputCP(CP_UTF8);

    int a = 1, b = 2, c = 3;
    int* arr[3] = { &a, &b, &c };

    std::cout << "=== 探针 11：range-for 里的变量 ===\n\n";
    print("初始            :", arr);

    for (int* p : arr) {            // p 是拷贝：等于在循环体里写 int* p = arr[i];
        p = nullptr;
    }
    print("int* p 那轮之后 :", arr);
    std::cout << "   ↑ 数组没变：改 p 只是改掉了那个临时拷贝\n\n";

    for (int*& p : arr) {           // p 是引用：p 就是 arr[i] 本身
        p = nullptr;
    }
    print("int*& p 那轮之后:", arr);
    std::cout << "   ↑ 数组被改了：引用就是元素本身\n\n";

    std::cout << "所以 `Shape* p : shapes` 里的 p：\n";
    std::cout << "  · 由这个 for 语句【当场声明】，作用域只在循环体里，循环一结束 p 就没了\n";
    std::cout << "  · 每一轮用数组里的下一个元素【初始化】它（所以每轮都指向不同的对象）\n";
    std::cout << "  · 它是元素的【拷贝】——p 里存的地址和 shapes[i] 里的地址是同一个\n";
    std::cout << "    所以 delete p 删掉的，正是 shapes[i] 指着的那个对象\n";

    return 0;
}
