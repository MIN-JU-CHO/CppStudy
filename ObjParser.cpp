#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;
float GetReal(string str, int begin, int end)
{
	if (begin > end)
	{
		return 0;
	}
	bool minus = false;
	if (str[begin] == '-')
	{
		minus = true;
	}
	if (str[begin] == '-' || str[begin] == '+')
	{
		++begin;
	}
	bool is_int = true;
	float num = 0, decimal = 1;
	for (int i = begin; i <= end; ++i)
	{
		if (isdigit(str[i]) && is_int)
		{
			num *= 10;
			num += str[i] - '0';
		}
		// 첫 . 만 가능
		else if (str[i] == '.' && is_int)
		{
			is_int = false;
		}
		else if (isdigit(str[i]) && !is_int)
		{
			decimal /= 10;
			num += decimal * (str[i] - '0');
		}
		else
		{
			break;
		}
	}
	// 음수는 마지막에 처리해줘야 수 읽기의 덧셈 연산이 정상적으로 수행됨
	if (minus)
	{
		num *= -1;
	}
	return num;
}

int main(void)
{
	ifstream file("D:/GitHub/CppStudy/Sting-Sword-lowpoly.obj");
	bool isV = true, isVt = false, isVn = false, isF = false;
	vector<vector<float>> vp;
	vector<vector<float>> vt;
	vector<vector<float>> vn;
	vector<unsigned int> vindex, uvindex, nindex;
	string line;
	if (file.is_open())
	{
		while (getline(file, line))
		{
			if (isV && line[0] == 'v' && line[1] == ' ')
			{
				vector<float> f(3);
				int begin = 2, end = 2;
				for (int i = 0; i < 3; ++i)
				{
					for (;end < line.size() && line[end] != ' '; ++end)
					{

					}
					f[i] = GetReal(line, begin, end - 1);
					begin = end + 1;
					++end;
				}
				vector<float> temp = { f[0], f[1], f[2] };
				vp.push_back(temp);
			}
			else if (isV && line[0] == 'v' && line[1] == 't')
			{
				isV = false;
				isVt = true;
			}
			if (isVt && line[0] == 'v' && line[1] == 't')
			{
				vector<float> f(2, 0);
				int begin = 3, end = 3;
				for (int i = 0; i < 2; ++i)
				{
					for (;end < line.size() && line[end] != ' '; ++end)
					{

					}
					f[i] = GetReal(line, begin, end - 1);
					begin = end + 1;
					++end;
				}
				vector<float> temp = { f[0], f[1] };
				vt.push_back(temp);
			}
			else if (isVt && line[0] == 'v' && line[1] == 'n')
			{
				isVt = false;
				isVn = true;
			}
			if (isVn && line[0] == 'v' && line[1] == 'n')
			{
				vector<float> f(3, 0);
				int begin = 3, end = 3;
				for (int i = 0; i < 3; ++i)
				{
					for (;end < line.size() && line[end] != ' '; ++end)
					{

					}
					f[i] = GetReal(line, begin, end - 1);
					begin = end + 1;
					++end;
				}
				vector<float> temp = { f[0], f[1], f[2] };
				vn.push_back(temp);
			}
			else if (isVn && line[0] == 'f')
			{
				isVn = false;
				isF = true;
			}
			if (isF && line[0] == 'f' && line[1] == ' ')
			{
				int begin = 2, end = 2;
				int b = 2;
				while (b--)
				{
					for (;end < line.size() && line[end] != '/' && line[end] != ' '; ++end)
					{

					}
					unsigned int a = (unsigned int)GetReal(line, begin, end - 1);
					vindex.push_back(a);
					begin = end + 1;
					++end;
					for (;end < line.size() && line[end] != '/' && line[end] != ' '; ++end)
					{

					}
					a = (unsigned int)GetReal(line, begin, end - 1);
					uvindex.push_back(a);
					begin = end + 1;
					++end;
					for (;end < line.size() && line[end] != '/' && line[end] != ' '; ++end)
					{

					}
					a = (unsigned int)GetReal(line, begin, end - 1);
					nindex.push_back(a);
					begin = end + 1;
					++end;
				}
			}
			else if (isF)
			{
				for (int i = 0; i <= vindex.size() - 4; ++i)
				{
					if (vindex[i] - 1 < vp.size() && nindex[i] - 1 < vn.size() && uvindex[i] - 1 < vt.size())
					{
						for (auto f : vp[vindex[i] - 1])
						{
							cout << f << " ";
						}
						for (auto f : vn[nindex[i] - 1])
						{
							cout << f << " ";
						}
						for (auto f : vt[uvindex[i] - 1])
						{
							cout << f << " ";
						}
						cout << endl;
					}
				}
				isF = false;
				isV = true;
				vp.clear();
				vn.clear();
				vt.clear();
			}
		}
		file.close();
	}
	else
	{
		return 0;
	}
}