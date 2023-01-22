#define _CRT_SECURE_NO_WARNINGS 1
#pragma once
#include <iostream>
#include <cstring>
#include <cassert>
#include <cstdio>
namespace mystring//由于下面的函数声明的参数用到了mystring::string类因此,需要提前声明
{
    class string;
}
    std::ostream&operator<<(std::ostream& _cout, const mystring::string& s);//当类定义在某个命名空间中时,如不想将友元函数也定义在同个命名空间中
    std::istream&operator>>(std::istream& _cin, mystring::string& s);//则必须提前进行全局函数声明,并在声明为类的友元函数时,使用::指明为全局作用域函数
                                                                     //具体原因见"杂疑补充"
    namespace mystring
{
    class string
    {
       
        friend std::ostream & ::operator<<(std::ostream & _cout, const mystring::string & s);
        friend std::istream& ::operator>>(std::istream& _cin, mystring::string& s);
    public:
        typedef char* iterator;
    public:
        string(const char* str = "");
        string(const string& s);
        string& operator=(const string& s);
        ~string();

        /* iterator*/
        iterator begin();
        iterator end();

         /*modify*/
        void push_back(char c);
        string& operator+=(char c);
        void append(const char* str);
        string& operator+=(const char* str);
        void clear();
        void swap(string& s);
        const char* c_str()const;

        // capacity
        size_t size()const;
        size_t capacity()const;
        bool empty()const;

        void resize(size_t n, char c = '\0');
        void reserve(size_t n);

        // access
        char& operator[](size_t index);
        const char& operator[](size_t index)const;

        //relational operators
        bool operator<(const string& s);
        bool operator<=(const string& s);
        bool operator>(const string& s);
        bool operator>=(const string& s);
        bool operator==(const string& s);
        bool operator!=(const string& s);

        // 返回c在string中第一次出现的位置
        size_t find(char c, size_t pos = 0) const;
        // 返回子串s在string中第一次出现的位置
        size_t find(const char* s, size_t pos = 0) const;
        //在pos位置上插入字符c/字符串str，并返回该对象
        string& insert(size_t pos, char c);
        string& insert(size_t pos, const char* str);

        // 删除pos位置上的元素，并返回该对象
        string& erase(size_t pos=0, size_t len=npos);
    private:
        char* _str;
        size_t _capacity;
        size_t _size;
        static const size_t npos = -1;//注意,static静态成员变量不可以在类中直接声明缺省值,但static const和static constexpr可以
    };
}