#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <string>
#include <sstream>

using namespace std;

constexpr int line = 6;

int getMaxLen(string *, int);

int main()
{
	string train[line] = {
		{"    .---- -. -. .  .   ."},
		{"    \\_/      ;--:-          __--------------------__"},
		{"  __U__n_^_''__[.  ooo___  | |_!_||_!_||_!_||_!_| |]"},
		{"c(_ ..(_ ..(_ ..( /,,,,,,] | |___||___||___||___| |"},
		{",_\\___________'_|,L______],|______________________|"},
		{"/;_(@)(@)==(@)(@)   (o)(o)      (o)^(o)--(o)^(o)   "}
	};
	stringstream buf;
	for(int i = 129, count = 1; i >= 0; --i, ++count)
	{
		system("clear");
		for(int j = 0; j < line; ++j)
		{
			int t = train[j].size();
			int len = t - count;
			if(len < 0)
				len = 0;
			for(int y = 0; y < i; ++y)
				buf << ' ';
			for(auto beg = train[j].begin(), End = train[j].end() - len; beg != End; ++beg)
				buf << *beg;
			buf << endl;
		}
		cout << buf.str().c_str() << endl;
		buf.str("");
		usleep(10000);
	}

	int maxlen = getMaxLen(train, line);
	for(int i = 0; i < maxlen; ++i)
	{
		system("clear");
		for(int j = 0; j < line; ++j)
		{
			if(i > train[j].size())
				goto CONTINUE;
			for(auto beg = train[j].begin() + i; beg != train[j].end(); ++beg)
				buf << *beg;
CONTINUE:
			buf << endl;
		}
		cout << buf.str().c_str() << endl;
		buf.str("");
		usleep(10000);
	}
	system("clear");
	return 0;
}

int getMaxLen(string *array, int len)
{
	int maxIndex = 0;
	for(int i = 0; i < len; ++i)
	{
		if(array[maxIndex].size() < array[i].size())
			maxIndex = i;
	}
	return array[maxIndex].size();
}
