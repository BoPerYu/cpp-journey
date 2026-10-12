// 故意编译不过：想让 char* 指向一个字符串字面量。
//
//   cmd /c "call \"E:\VS 2022\VC\Auxiliary\Build\vcvars64.bat" >nul && cl /nologo /utf-8 /EHsc /c charptr-literal.cpp"

int main() {
    char* p = "abc";        // 字符串字面量是 const char 那一类，不能交给 char*
    return 0;
}
