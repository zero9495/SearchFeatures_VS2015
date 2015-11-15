#pragma once
#include "CMyString.h"

template<typename Telem>
class CListElem
{
public:
	CListElem();
	~CListElem();

	Telem* GetData() const;
	CListElem<Telem>* GetNext() const;

	void SetData(const Telem& x);
	void SetNext(CListElem<Telem>* x);
private:
	Telem* _pData;
	CListElem* _pNext;
};

template<typename Telem>
CListElem<Telem>::CListElem()
{
	_pData = new Telem;
	_pNext = 0;
}

template<typename Telem>
CListElem<Telem>::~CListElem()
{
	delete _pData;
}

template<typename Telem>
Telem* CListElem<Telem>::GetData() const
{
	return _pData;
}

template<typename Telem>
CListElem<Telem>* CListElem<Telem>::GetNext() const
{
	return _pNext;
}

template<typename Telem>
void CListElem<Telem>::SetData(const Telem& x)
{
	*_pData = x;
}

template<typename Telem>
void CListElem<Telem>::SetNext(CListElem<Telem>* x)
{
	_pNext = x;
}

///////////////////////////////////////////////////////////////////////////

template<typename Telem>
class CList
{
public:
	CList();
	CList(const CList<Telem>& givenList);
	~CList();

	int GetSize() const;
	CListElem<Telem>* GetBegin() const;
	CListElem<Telem>* GetEnd() const;
	void Clear();

	void AddElemToEnd(const Telem& x);
	void GetRidOfRepetitions();

	CList<Telem>& operator=(const CList<Telem>& a);
	CList<Telem>& operator+=(const CList<Telem>& a);

private:
	CListElem<Telem>* _pBegin;
	CListElem<Telem>* _pEnd;
	int _nSize;
};

template<typename Telem>
CList<Telem>::CList()
{
	_pBegin = 0;
	_pEnd = 0;
	_nSize = 0;
}

template<typename Telem>
CList<Telem>::CList(const CList<Telem>& givenList)
{
	CListElem<Telem>* t = givenList.GetBegin();
	while (t)
	{
		AddElemToEnd(*(t->GetData()));
		t = t->GetNext();
	}
}

template<typename Telem>
CList<Telem>::~CList()
{
	Clear();	
}

template<typename Telem>
int CList<Telem>::GetSize() const
{
	return _nSize;
}

template<typename Telem>
CListElem<Telem>* CList<Telem>::GetBegin() const
{
	return _pBegin;
}

template<typename Telem>
CListElem<Telem>* CList<Telem>::GetEnd() const
{
	return _pEnd;
}

template<typename Telem>
void CList<Telem>::Clear()
{
	while (_pBegin)
	{
		CListElem<Telem>* t = _pBegin;
		_pBegin = _pBegin->GetNext();
		delete t;
	}
	_pBegin = 0;
	_pEnd = 0;
	_nSize = 0;
}

template<typename Telem>
void CList<Telem>::AddElemToEnd(const Telem& x)
{
	CListElem<Telem>* t = new CListElem<Telem>;
	t->SetData(x);
	//*(t->_pData) = x;

	if (_pBegin == 0)
	{
		_pBegin = t;
		_pEnd = t;
		_nSize++;
		return;
	}

	_pEnd->SetNext(t);
	//_pEnd->_pNext = t;
	_pEnd = t;
	_nSize++;
}

template<typename Telem>
void CList<Telem>::GetRidOfRepetitions()
{

}

template<typename Telem>
CList<Telem>& CList<Telem>::operator=(const CList<Telem>& givenList)
{
	Clear();

	CListElem<Telem>* t = givenList.GetBegin();
	while (t)
	{
		AddElemToEnd(*(t->GetData()));
		t = t->GetNext();
	}

	return *this;
}

template<typename Telem>
CList<Telem>& CList<Telem>::operator+=(const CList<Telem>& a)
{
}