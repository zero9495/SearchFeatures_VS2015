#pragma once
#include <iostream>
#include <vector>

using namespace std;

class CMyString
{
public:
	CMyString();
	CMyString(const char* x);
	CMyString(const CMyString& x);
	~CMyString();

	int GetSize() const;
	char* GetStr() const;

	//vector<int>* CalcualteLetters() const;

	bool operator==(const CMyString& a) const;
	bool operator<(const CMyString& a) const;
	CMyString& operator=(const CMyString& a);
	CMyString& operator=(const char* a);
	CMyString& operator+=(const CMyString& a);
	friend ostream& operator<<(ostream& out, const CMyString &a);

private:
	char* _aStr;
	int _nSize;
};

CMyString::CMyString()
{
	_aStr = 0;
	_nSize = 0;
}

CMyString::CMyString(const char* x)
{
	_nSize = strlen(x);

	_aStr = new char[_nSize + 1];

	for (int i = 0; i <= _nSize; i++)
	{
		_aStr[i] = x[i];
	}
}

CMyString::CMyString(const CMyString& a)
{
	_nSize = a._nSize;

	try
	{
		_aStr = new char[_nSize + 1];
	}
	catch (const bad_alloc& exc)
	{
		cout << exc.what() << endl;
		return;
	}

	for (int i = 0; i <= _nSize; i++)
	{
		_aStr[i] = a._aStr[i];
	}
}

CMyString::~CMyString()
{
	delete[] _aStr;
}

int CMyString::GetSize() const
{
	return _nSize;
}

char* CMyString::GetStr() const
{
	char* newStr = 0;

	try
	{
		newStr = new char[_nSize + 1];
	}
	catch (const bad_alloc& exc)
	{
		cout << exc.what() << endl;
		return newStr;
	}

	for (int i = 0; i <= _nSize; i++)
	{
		newStr[i] = _aStr[i];
	}
	return newStr;
}

/*vector<int>* CMyString::CalcualteLetters() const
{
	char* alphabet = "אבגדהו¸זחטיךכלםמןנסעףפץצקרשתûü‎‏ÿ";
	CList<CSubword>* aSubwords = new CList<CSubword>;

	for (int i = 0; i < 33; i++)
	{
		char* tempStr = new char[2];
		tempStr[0] = alphabet[i];
		tempStr[0] = NULL;

		aSubwords->AddElemToEnd(CSubword(1, tempStr));

		delete tempStr;
	}
}*/

bool CMyString::operator==(const CMyString& a) const
{
	if (_nSize != a._nSize)
	{
		return false;
	}

	int i = 0;

	while (i <= min(_nSize, a._nSize))
	{
		if (_aStr[i] != a._aStr[i])
		{
			return false;
		}
		i++;
	}

	return true;
}

bool CMyString::operator<(const CMyString& a) const
{
	int i = 0;

	while (i <= min(_nSize, a._nSize))
	{
		if (_aStr[i] > a._aStr[i])
		{
			return false;
		}
		i++;
	}

	return true;
}

CMyString& CMyString::operator=(const CMyString& a)
{
	if (this)
	{
		delete[] _aStr;
	}

	_nSize = a._nSize;

	try
	{
		_aStr = new char[_nSize + 1];
	}
	catch (const bad_alloc& exc)
	{
		cout << exc.what() << endl;
		return *this;
	}

	for (int i = 0; i <= _nSize; i++)
	{
		_aStr[i] = a._aStr[i];
	}

	return *this;
}

CMyString& CMyString::operator=(const char* a)
{
	delete[] _aStr;

	_nSize = strlen(a);

	_aStr = new char[_nSize + 1];

	for (int i = 0; i <= _nSize; i++)
	{
		_aStr[i] = a[i];
	}

	return *this;
}

CMyString& CMyString::operator+=(const CMyString& a)
{
	int newSize = this->_nSize + a._nSize;
	char* tempString = new char[this->_nSize + 1];

	for (int i = 0; i < this->_nSize; i++)
	{
		tempString[i] = this->_aStr[i];
	}

	delete[] _aStr;

	_aStr = new char[newSize + 1];

	for (int i = 0; i < _nSize; i++)
	{
		_aStr[i] = tempString[i];
	}

	for (int i = _nSize; i <= newSize; i++)
	{
		_aStr[i] = a._aStr[i - _nSize];
	}

	_nSize = newSize;
	delete[] tempString;

	return *this;
}

ostream& operator<<(ostream& out, const CMyString &a)
{
	out << a._aStr;
	return out;
}