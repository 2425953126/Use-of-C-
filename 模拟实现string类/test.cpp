#include "MyString.h"
using namespace std;
int main()
{
	try 
	{
		mystring::string a("abcdacdefg");
		mystring::string b("cde");
		a += " hello";
		cout << a << endl;
		a.resize(100, 'x');
		cout << a << endl;
		a.resize(10);
		cout << a << endl;
		a.erase(7, 2);
		cout << a << endl;
		cout << a.find('e') << endl;
		cout << a.find('dac') << endl;
	}
	catch (std::bad_alloc& e) {
		// �����ڴ�����쳣
		cout << "#�ڴ�����ʧ��!" << endl;
	}
	return 0;
}