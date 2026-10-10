// 故意编译不过：把 const 写在了返回类型上，而不是参数列表后面。
//
//   cmd /c "call \"E:\VS 2022\VC\Auxiliary\Build\vcvars64.bat\" >nul && cl /nologo /utf-8 /EHsc /permissive- /c const-return-vs-const-member.cpp"

struct S {
    int v_;

    const int get_wrong() { return v_; }      // ← const 管的是【返回值】，函数本身不是 const 成员函数
    int get_right() const { return v_; }      // ← const 在这一位，才是"这个函数不改对象"
};

void take(const S& s) {
    s.get_right();      // 可以：const 成员函数，const 对象也能调
    s.get_wrong();      // ← 报错：函数不是 const 成员函数，const 对象调不了
}

int main() { return 0; }
