#pragma once
#include "CMyString.h"

class CSubwordWithQuantity
{
public:
	CSubwordWithQuantity();
	CSubwordWithQuantity(const int& givenSubwordLength, const CMyString& str);
	CSubwordWithQuantity(const int& givenSubwordLength, const CMyString& str, const int& givenQuantity);
	~CSubwordWithQuantity();

	char* GetStr() const;
	int GetQuantity() const;
	void IncreaseQuantity();

	void operator++();
	bool operator==(const CSubwordWithQuantity& a) const;
	CSubwordWithQuantity& operator=(const CSubwordWithQuantity& a);

private:
	char* _aStr;
	int _nQuantity;
};

CSubwordWithQuantity::CSubwordWithQuantity()
{
	_aStr = 0;
	_nQuantity = 0;
}

CSubwordWithQuantity::CSubwordWithQuantity(const int& givenSubwordLength, const CMyString& givenStr)
{
	_aStr = new char[givenSubwordLength + 1];
	for (int i = 0; i <= givenSubwordLength; i++)
	{
		_aStr[i] = givenStr.GetStr()[givenStr.GetSize() - givenSubwordLength + i];
	}

	_nQuantity = 1;
}

CSubwordWithQuantity::CSubwordWithQuantity(const int& givenSubwordLength, const CMyString& givenStr, const int& givenQuantity)
{
	_aStr = new char[givenSubwordLength + 1];
	for (int i = 0; i <= givenSubwordLength; i++)
	{
		_aStr[i] = givenStr.GetStr()[givenStr.GetSize() - givenSubwordLength + i];
	}

	_nQuantity = givenQuantity;
}

CSubwordWithQuantity::~CSubwordWithQuantity()
{
	delete[] _aStr;
}

char* CSubwordWithQuantity::GetStr() const
{
	char* newStr = 0;

	try
	{
		newStr = new char[strlen(_aStr) + 1];
	}
	catch (const bad_alloc& exc)
	{
		cout << exc.what() << endl;
		return newStr;
	}

	for (int i = 0; i <= strlen(_aStr); i++)
	{
		newStr[i] = _aStr[i];
	}

	return newStr;
}

int CSubwordWithQuantity::GetQuantity() const
{
	return _nQuantity;
}

void CSubwordWithQuantity::IncreaseQuantity()
{
	_nQuantity++;
}

void CSubwordWithQuantity::operator++()
{
	_nQuantity++;
}

bool CSubwordWithQuantity::operator==(const CSubwordWithQuantity& a) const
{
	return false;
}

CSubwordWithQuantity& CSubwordWithQuantity::operator=(const CSubwordWithQuantity& a)
{
	_aStr = new char[strlen(a.GetStr()) + 1];

	for (int i = 0; i <= strlen(a.GetStr()); i++)
	{
		_aStr[i] = a.GetStr()[i];
	}

	_nQuantity = a._nQuantity;

	return *this;
}

////////////////////////////////////////////////////////////////////////////

class CSubwordThisPoSWithQuantity : public CSubwordWithQuantity
{
public:
	CSubwordThisPoSWithQuantity();
	CSubwordThisPoSWithQuantity(
		const int& givenSubwordLength,
		const CMyString& str,
		unsigned short int givenPoS);
	CSubwordThisPoSWithQuantity(
		const int& givenSubwordLength,
		const CMyString& str,
		const int& givenQuantity,
		unsigned short int givenPoS);
	~CSubwordThisPoSWithQuantity();

private:
	unsigned short int nPoS;
};

CSubwordThisPoSWithQuantity::CSubwordThisPoSWithQuantity()
{
}

CSubwordThisPoSWithQuantity::CSubwordThisPoSWithQuantity(
	const int& givenSubwordLength, 
	const CMyString& str,
	unsigned short int givenPoS) : CSubwordWithQuantity(givenSubwordLength, str)
{
	nPoS = givenPoS;
}

CSubwordThisPoSWithQuantity::CSubwordThisPoSWithQuantity(
	const int& givenSubwordLength, 
	const CMyString& str, 
	const int& givenQuantity,
	unsigned short int givenPoS) : CSubwordWithQuantity(givenSubwordLength, str, givenQuantity)
{
	nPoS = givenPoS;
}

CSubwordThisPoSWithQuantity::~CSubwordThisPoSWithQuantity()
{
}