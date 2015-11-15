#pragma once
#include <iostream>
#include <fstream>
#include "CMyString.h"
#include "CList.h"

class CDictionary
{
public:
	CDictionary();
	CDictionary(const CMyString& fileName);
	~CDictionary();

	void LoadCDictionary(const CMyString& fileName);
	int GetSize() const;
	void Clear();

	CListElem<CMyString>* GetBegin() const;
	CListElem<CMyString>* GetEnd() const;	

private:
	CList<CMyString> _listWords;
};

CDictionary::CDictionary()
{
}

CDictionary::CDictionary(const CMyString& fileName)
{
	LoadCDictionary(fileName);
}

CDictionary::~CDictionary()
{
}

void CDictionary::LoadCDictionary(const CMyString& fileName)
{
	_listWords.Clear();

	CMyString path = "data/Dictionaries/";
	path += fileName;

	ifstream fin(path.GetStr());
	char c[256];
	CMyString str;

	while (fin >> c)
	{
		str = c;
		_listWords.AddElemToEnd(str);
	}

	fin.close();
}

int CDictionary::GetSize() const
{
	return _listWords.GetSize();
}

void CDictionary::Clear()
{
	_listWords.Clear();
}

CListElem<CMyString>* CDictionary::GetBegin() const
{
	return _listWords.GetBegin();
}

CListElem<CMyString>* CDictionary::GetEnd() const
{
	return _listWords.GetEnd();
}