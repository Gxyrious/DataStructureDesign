#include"KeywordSearch.h"

KeywordSearch::KeywordSearch(const string& keyword, const string& filename)
{
	_count = -1;
	_keyword = keyword;
	_filename = filename;
	_fin.open(_filename, ios::in);
	//_fin.seekg(ios::beg);//////////
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
		while (!_fin.eof()) {
			word.clear();//清空，防止最后一行读不到东西导致最后一个单词被两次计算
			_fin >> word;
			int size = word.size();
			if (!word.empty()) {
				if (word[size - 1] < 'a' || word[size - 1]>'z') {
					word = word.substr(0, size - 1);
				}
				if (word == _keyword) {
					_count++;
				}
			}
		}
	}
	return _count;
}
