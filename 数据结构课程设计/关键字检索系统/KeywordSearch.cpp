#include"KeywordSearch.h"

KeywordSearch::KeywordSearch(const string& keyword, const string& filename)
{
	_count = -1;
	_keyword = keyword;
	_filename = filename;
	_fin.open(_filename, ios::in);//以ios::in形式打开文件，只能读取文件
	_fin.seekg(ios::beg);//将文件标识符设置在begin位置
}

KeywordSearch::~KeywordSearch()
{
	_fin.close();
}

int KeywordSearch::getCount()
{
	//_count!=-1时说明已查找过，直接返回_count
	if (_count == -1) {
		_count = 0;
		string word;
		//当未读取到文件末尾时
		while (!_fin.eof()) {
			//清空，防止最后一行读不到东西导致最后一个单词被两次计算
			word.clear();
			_fin >> word;//从文件读取字符串，有可能连着标点符号一起读取，故需要作二次处理
			int size = word.size();
			if (!word.empty()) {
				//如果读取字符串最后一位不是字母，则说明连着标点一起读进来了
				if (word[size - 1] < 'a' || word[size - 1]>'z') {
					//获取子串，重新构造字符串
					word = word.substr(0, size - 1);
				}
				//此时字符串一定是纯英文，直接判断是否与关键字相等
				if (word == _keyword) {
					_count++;
				}
			}
		}
	}
	return _count;
}
