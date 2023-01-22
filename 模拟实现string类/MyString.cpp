#include "MyString.h"
using namespace std;
mystring::string::string(const char* str)
{
	int length = strlen(str) + 1;
	int slength = (length / 16 + 1)*16;//��֤ʵ��������ֽ���Ϊ16�ı���
	_str = new char[slength];
	strcpy(_str, str);
	_size = length-1;//_size������\0;
	_capacity = slength - 1;//������\0
}
mystring::string::string(const string& s)
{
	_str = new char[s._capacity];
	for (int i = 0; i <= s._size; i++)//<=ȷ����'\0'Ҳ���ƹ���
	{
		_str[i] = s._str[i];
	}
	_size = s._size;
	_capacity = s._capacity;
}
void mystring::string::swap(string& s)
{
	std::swap(_str, s._str);//����_strָ��ָ�������
	_size = s._size;
	_capacity = s._capacity;
}
mystring::string& mystring::string::operator=(const string& s)
{
	string tmp(s);
	swap(tmp);
	return *this;
}
mystring::string::~string()
{
	delete[] _str;
	_str = nullptr;
}
ostream& operator<<(std::ostream& _cout, const mystring::string& s)
{
	for (int i=0; i < s._size; i++)
		_cout << s._str[i];
	return _cout;
}
void mystring::string::reserve(size_t n)
{
	if (n <= _capacity)
		return;
	char* tmp = new char[(n / 16 + 1) * 16];
	for (int i = 0; i <= _size; i++)//ע��Ҫ��'\0'Ҳ���ƹ�ȥ
		tmp[i] = _str[i];
	delete[] _str;
	_str = tmp;
	_capacity = (n / 16 + 1) * 16-1;//'\0'����
}
istream& operator>>(std::istream& _cin, mystring::string& s)
{	
	char tmp = getchar();
	for (s._size = 0; tmp != '\n'; s._size++)
	{
		if (s._size == s._capacity)
			s.reserve((s._capacity+1)*1.5);
		s._str[s._size] = tmp;
		tmp = getchar();
	}
	s._str[s._size]= '\0';//�պ�!
	return _cin;
}
// iterator
mystring::string::iterator mystring::string::begin()
{
	return _str;
}
mystring::string::iterator mystring::string::end()
{
	return _str + _size;
}
/*modify*/
void mystring::string::push_back(char c)
{	
	if (_size == _capacity)
		reserve((_capacity + 1) * 1.5);
	_str[_size] = c;
	_size++;
	_str[_size] = '\0';
}
mystring::string& mystring::string:: operator+=(char c)
{
	push_back(c);
	return *this;
}
void mystring::string::append(const char* str)
{	
	int length = strlen(str);//���ﲻ��Ҫ+1��,��Ϊcapacity�Ѿ���ȥ���'\0'���ֽ���
	while(_size+length > _capacity)
		reserve((_capacity+1)*1.5);
	strcpy(_str + _size, str);
	_size += length;
	_str[_size] = '\0';
}
mystring::string& mystring::string:: operator+=(const char* str)
{
	append(str);
	return *this;
}
void mystring::string::clear()
{
	_size = 0;
}
const char* mystring::string::c_str()const
{
	return _str;
}
// capacity
size_t mystring::string::size()const
{
	return _size;
}
size_t mystring::string::capacity()const
{
	return _capacity;
}
bool mystring::string::empty()const
{
	return _size == 0 ? true : false;
}
void mystring::string::resize(size_t n, char c)
{
	if (n > _capacity)//����ռ䲻��Ҫ��,������
		reserve(n);
	if (_size < n)
	{
		while (_size < n)
			_str[_size++] = c;
	}
	else
	{
		_size = n;
	}
	_str[_size] = '\0';
}
// access
char& mystring::string::operator[](size_t index)
{
	return _str[index];
}
const char& mystring::string::operator[](size_t index)const
{
	return _str[index];
}
//relational operators
bool mystring::string::operator<(const string& s)
{
	int i = 0;
	while (i < _size && i <s. _size)
	{
		if (_str[i] < s._str[i])
			return true;
		else if (_str[i] > s._str[i])
			return false;
		i++;
	}
	if (i == _size && i < s._size)//���thisָ����ַ��������Ѿ�������,������s��û����,˵��ǰ��С�ں���,���򷵻ؼ�
		return true;
	else
		return false;
}
bool mystring::string::operator<=(const string& s)
{
	return *this < s || *this == s;
}
bool mystring::string::operator>(const string& s)
{
	return !(*this<s)&&!(*this==s);
}
bool mystring::string::operator>=(const string& s)
{
	return !(*this < s);
}
bool mystring::string::operator==(const string& s)
{
	int i = 0;
	while (i < _size && i < s._size)
	{
		 if (_str[i] != s._str[i])
			return false;
		i++;
	}
	if (i == _size && i == s._size)
		return true;
	else
		return false;
}
bool mystring::string::operator!=(const string& s)
{
	return !(*this == s);
}
// ����c��string�е�һ�γ��ֵ�λ��
size_t  mystring::string::find(char c, size_t pos) const
{	
	assert(pos >= 0);
	for (int i = pos; i < _size; i++)
	{
		if (_str[i] == c)
			return i;
	}
	return npos;
}
// �����Ӵ�s��string�е�һ�γ��ֵ�λ��
size_t mystring::string::find(const char* s, size_t pos) const
{	
	int slength = strlen(s),i=0,j=0;
	for (i = pos; i < _size; i++,j++)
	{	
		if (j == slength)
			break;
		if (_str[i] != s[j])
		{	
			i = i - j;
			j = -1;
		}
	}
	if (j == slength)
		return i - slength;
	else
		return npos;
}
// ��posλ���ϲ����ַ�c/�ַ���str�������ظö���
mystring::string& mystring::string::insert(size_t pos, char c)
{	
	assert(pos >= 0 && pos <= _size);
	int end = _size+1;//'\0'ҲҪ��
	if (end > _capacity)
		reserve((_capacity + 1) * 1.5);
	while (end>pos)
	{
		_str[end] = _str[end - 1];
		end--;
	}
	_str[pos] = c;
	_size++;
	return *this;
}
mystring::string& mystring::string::insert(size_t pos, const char* str)
{
	assert(pos >= 0 && pos <= _size);
	int slength = strlen(str);
	int end = _size + slength;
	while (end > _capacity)
		reserve((_capacity + 1) * 1.5);
	while (end >=pos + slength)//ע��������Ҫ��>=,ǰ��һ��������end>pos����Ϊ��ȷ����ӵ��ַ���һ��,�Ұ벿��û��+1
	{
		_str[end] = _str[end - slength];
		end--;
	}
	memmove(_str + pos, str, slength);
	_size += slength;
	return *this;
}
// ɾ��posλ���ϵ�Ԫ�أ������ض���
mystring::string& mystring::string::erase(size_t pos, size_t len)
{	
	assert(pos >= 0 && pos < _size&&len>0);
	if (len>=_size-pos)
	{
		_size = pos;
		_str[_size] = '\0';
		return *this;
	}
	int begin = pos;
	while (begin <= _size - len)
	{
		_str[begin] = _str[begin + len];
		begin++;
	}
	_size -= len;
	return *this;
}
