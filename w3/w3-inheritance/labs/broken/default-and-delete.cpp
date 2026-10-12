// 故意编译不过：用来给 `= default` 和它的兄弟 `= delete` 留证据。
//
//   cmd /c "call \"E:\VS 2022\VC\Auxiliary\Build\vcvars64.bat" >nul && cl /nologo /utf-8 /EHsc /c default-and-delete.cpp"
//
// 报错只会出现在最后那一行拷贝上——说明前面那几个 `= default` 都是合法的。

class Demo {
public:
    Demo() = default;                       // 让编译器生成默认构造函数
    virtual ~Demo() = default;              // 虚析构 + 函数体用编译器默认那份

    Demo(const Demo&) = delete;             // 明确禁止拷贝
};

int main() {
    Demo a;             // 没问题：默认构造可用
    Demo b = a;         // ← 报错：拷贝构造被 delete 掉了
    return 0;
}
