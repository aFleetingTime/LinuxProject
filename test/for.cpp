#include <iostream>
#include <vector>

using namespace std;

void getNum(vector<int> &nums)
{
	for(int i = 0; cin >> i && i != -1; nums.push_back(i));
}

int isPrefix(const vector<int> ivec1, const vector<int> ivec2)
{
	int retFlag = 0;
	auto minSize = ivec1.size() < ivec2.size() ? retFlag = 1, ivec1.size() : ivec1.size() > ivec2.size() ? retFlag = -1, ivec2.size() : ivec1.size();
	if(minSize == 0)
		return false;
	decltype(minSize) count = 0;
	for(decltype(minSize) i = 0; i < minSize && ivec1[i] == ivec2[i]; ++i, ++count);
	if(count == minSize)
		return true;
	else
		return false;
}

int main()
{
	vector<int> ivec[2]{};

	for(int i = 0; i < 2; ++i)
	{
		cout << "请输入第" << i + 1 << "组整数" << endl;
		getNum(ivec[i]);
	}

	if(isPrefix(ivec[0], ivec[1]))
		cout << "包含前缀" << endl;
	else
		cout << "不包含前缀" << endl;

	return 0;
}
