#include <iostream>
#include <cassert>

using namespace std;

int main()
{
#ifndef NDEBUG
	cout << "发生异常的函数:" << sizeof(__func__) << endl;
	cout << "异常行号:" << __LINE__ << endl;
	cout << "文件最近编译时间:" << __DATE__ << "  " << __TIME__ << endl;
#endif
	assert(false);

	return 0;
}
