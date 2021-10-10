#include"KeywordSearch.h"

KeywordSearch::KeywordSearch(const string& keyword, const string& filename)
{
	_count = -1;
	_keyword = keyword;
	_filename = filename;
	_fin.open(_filename, ios::in);//��ios::in��ʽ���ļ���ֻ�ܶ�ȡ�ļ�
	_fin.seekg(ios::beg);//���ļ���ʶ��������beginλ��
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
		//��δ��ȡ���ļ�ĩβʱ
		while (!_fin.eof()) {
			//��գ���ֹ���һ�ж����������������һ�����ʱ����μ���
			word.clear();
			_fin >> word;//���ļ���ȡ�ַ������п������ű�����һ���ȡ������Ҫ�����δ���
			int size = word.size();
			if (!word.empty()) {
				//�����ȡ�ַ������һλ������ĸ����˵�����ű��һ���������
				if (word[size - 1] < 'a' || word[size - 1]>'z') {
					//��ȡ�Ӵ������¹����ַ���
					word = word.substr(0, size - 1);
				}
				//��ʱ�ַ���һ���Ǵ�Ӣ�ģ�ֱ���ж��Ƿ���ؼ������
				if (word == _keyword) {
					_count++;
				}
			}
		}
	}
	return _count;
}
