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
	//_count!=-1ʱ˵���Ѳ��ҹ���ֱ�ӷ���_count
	if (_count == -1) {
		_count = 0;
		string word;
		while (!_fin.eof()) {
			word.clear();//��գ���ֹ���һ�ж����������������һ�����ʱ����μ���
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
