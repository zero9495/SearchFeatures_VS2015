#pragma once
#include "CSubwordWithQuantity.h"

class CProbability
{
public:
	CProbability();
	CProbability(const double& probability);
	~CProbability();

	double GetProbability() const;
	void SetProbability(const double& prob);
	void ColculateProbability(const int& quantityOfSuccesses, const int& quantityTotal);

	virtual CProbability& operator=(const CProbability& a);

private:
	double _probability;
};

CProbability::CProbability()
{
	_probability = 0.0;
}

CProbability::CProbability(const double& probability)
{
	_probability = probability;
}

CProbability::~CProbability()
{
}

double CProbability::GetProbability() const
{
	return _probability;
}

void CProbability::SetProbability(const double& prob)
{
	_probability = prob;
}

void CProbability::ColculateProbability(const int& quantityOfSuccesses, const int& quantityTotal)
{
	_probability = quantityOfSuccesses / (double) quantityTotal;
}

CProbability& CProbability::operator=(const CProbability& a)
{
	_probability = a._probability;
}

////////////////////////////////////////////////////////////////////////

class CProbPoSProvidedThatTheSubwordAtTheEnd : public CProbability
{
public:
	CProbPoSProvidedThatTheSubwordAtTheEnd();
	CProbPoSProvidedThatTheSubwordAtTheEnd(
		const double& probability,
		const unsigned short int& nPoS, 
		const CSubwordWithQuantity& subword);
	~CProbPoSProvidedThatTheSubwordAtTheEnd();

	void SetPoS(const unsigned short int& _nPoS);
	void SetSubword(const CSubwordWithQuantity& subword);

private:
	unsigned short int _nPoS; //Part of Speech
	CSubwordWithQuantity _subword;
};

CProbPoSProvidedThatTheSubwordAtTheEnd::CProbPoSProvidedThatTheSubwordAtTheEnd()
{
}

CProbPoSProvidedThatTheSubwordAtTheEnd::CProbPoSProvidedThatTheSubwordAtTheEnd(
	const double& probability,
	const unsigned short int& nPoS, 
	const CSubwordWithQuantity& subword) : CProbability(probability)

{
	_nPoS = nPoS;
	_subword = subword;
}

CProbPoSProvidedThatTheSubwordAtTheEnd::~CProbPoSProvidedThatTheSubwordAtTheEnd()
{
}

void CProbPoSProvidedThatTheSubwordAtTheEnd::SetPoS(const unsigned short int& nPoS)
{
	_nPoS = nPoS;
}

void CProbPoSProvidedThatTheSubwordAtTheEnd::SetSubword(const CSubwordWithQuantity& subword)
{
	_subword = subword;
}