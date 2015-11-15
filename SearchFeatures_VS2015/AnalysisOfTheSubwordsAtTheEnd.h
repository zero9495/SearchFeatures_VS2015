#pragma once

#include "CDictionary.h"
#include "CSubwordWithQuantity.h"
#include "PoSNumber.h"

CList<CSubwordWithQuantity>* GetListAllSubwordsAtTheEndThisPoSWithNULLQuantities(
	const CMyString& fileDictionaryName,
	const int& subwordLength)
{
	CDictionary dictionary(fileDictionaryName);
	CList<CSubwordWithQuantity>* aSubwordsOutput = new CList<CSubwordWithQuantity>;
	CListElem<CMyString>* pWords = dictionary.GetBegin();
	CListElem<CSubwordWithQuantity>* pSubword = 0;

	while (pWords)
	{
		CSubwordWithQuantity subwordOfThisWord(subwordLength, *(pWords->GetData()), 0);

		pSubword = aSubwordsOutput->GetBegin();
		while (pSubword)
		{
			if (!strcmp(subwordOfThisWord.GetStr(), pSubword->GetData()->GetStr()))
			{
				break;
			}
			else
			{
				pSubword = pSubword->GetNext();
			}
		}
		if (pSubword == 0)
		{
			aSubwordsOutput->AddElemToEnd(subwordOfThisWord);
		}
		pWords = pWords->GetNext();
	}

	return aSubwordsOutput;
}

/*void CreateFullList(const CDictionary& CDictionary, CList<CSubword>* aSubwords, const int& subwordLength)
{
	CListElem<CMyString>* pWords = CDictionary.GetBegin();
	CListElem<CSubword>* pSubword = 0;

	while (pWords)
	{
		CSubword tempSubword(subwordLength, *(pWords->GetData()), 0);

		pSubword = aSubwords->GetBegin();
		while (pSubword)
		{
			if (!strcmp(tempSubword.GetStr(), pSubword->GetData()->GetStr()))
			{
				//pSubword->_pData->IncreaseQuantity();
				break;
			}
			else
			{
				pSubword = pSubword->GetNext();
			}
		}
		if (pSubword == 0)
		{
			aSubwords->AddElemToEnd(tempSubword);
		}
		pWords = pWords->GetNext();
	}
}*/

CList<CSubwordWithQuantity>* GetListAllSubwordsAtTheEndThisPoS(
	const CMyString& fileDictionaryName,
	const int& subwordLength)
{
	CDictionary dictionary(fileDictionaryName);
	CList<CSubwordWithQuantity>* aSubwordsOutput = new CList<CSubwordWithQuantity>;
	CListElem<CMyString>* pWords = dictionary.GetBegin();
	CListElem<CSubwordWithQuantity>* pSubword = 0;

	while (pWords)
	{
		CSubwordWithQuantity subwordOfThisWord(subwordLength, *(pWords->GetData()));

		pSubword = aSubwordsOutput->GetBegin();
		while (pSubword)
		{
			if (!strcmp(subwordOfThisWord.GetStr(), pSubword->GetData()->GetStr()))
			{
				pSubword->GetData()->IncreaseQuantity();
				break;
			}
			else
			{
				pSubword = pSubword->GetNext();
			}
		}
		if (pSubword == 0)
		{
			aSubwordsOutput->AddElemToEnd(subwordOfThisWord);
		}
		pWords = pWords->GetNext();
	}

	return aSubwordsOutput;
}

/*void FillListAllSubwordsAtTheEndWithNULLQuantities(const CDictionary& CDictionary, CList<CSubword>* aSubwords, const int& subwordLength)
{
	CListElem<CMyString>* pWords = CDictionary.GetBegin();
	CListElem<CSubword>* pSubword = 0;

	while (pWords)
	{
		CSubword tempSubword(subwordLength, *(pWords->GetData()), 0);

		pSubword = aSubwords->GetBegin();
		while (pSubword)
		{
			if (!strcmp(tempSubword.GetStr(), pSubword->GetData()->GetStr()))
			{
				pSubword->GetData()->IncreaseQuantity();
				break;
			}
			else
			{
				pSubword = pSubword->GetNext();
			}
		}
		if (pSubword == 0)
		{
			aSubwords->AddElemToEnd(tempSubword);
			aSubwords->GetEnd()->GetData()->IncreaseQuantity();
		}
		pWords = pWords->GetNext();
	}
}*/

/*CList<CSubword>* CalculateSubwordsAtTheEnd(const CDictionary& dictionary, const int& subwordLength)
{
CListElem<CMyString>* pWords = dictionary.GetBegin();
CList<CSubword>* aSubwords = new CList<CSubword>;
CListElem<CSubword>* pSubword = 0;

while (pWords)
{
CSubword tempSubword(subwordLength, *(pWords->GetData()));

pSubword = aSubwords->GetBegin();
while (pSubword)
{
if (!strcmp(tempSubword.GetStr(), pSubword->GetData()->GetStr()))
{
pSubword->GetData()->IncreaseQuantity();
break;
}
else
{
pSubword = pSubword->GetNext();
}
}
if (pSubword == 0)
{
aSubwords->AddElemToEnd(tempSubword);
}
pWords = pWords->GetNext();
}

return aSubwords;
}*/

void FilingListOfTheSubwords(const CList<CSubwordWithQuantity>& listOfTheSubwords)
{
	ofstream fout("outputSubwords.txt");

	CListElem<CSubwordWithQuantity>* subwords = listOfTheSubwords.GetBegin();
	while (subwords)
	{
		fout << subwords->GetData()->GetStr() << endl;
		subwords = subwords->GetNext();
	}

	fout.close();

	fout.open("outputQuantities.txt");

	subwords = listOfTheSubwords.GetBegin();
	while (subwords)
	{
		fout << subwords->GetData()->GetQuantity() << endl;
		subwords = subwords->GetNext();
	}
}

void AddToListSubwordsAtTheEndTheOtherFromDictionary(
	CList<CSubwordThisPoSWithQuantity>* const finalList,
	const CMyString& fileDictionaryName)
{
	int subwordLength = strlen(finalList->GetBegin()->GetData()->GetStr());

	CList<CSubwordWithQuantity>* addedList =
		GetListAllSubwordsAtTheEndThisPoS(fileDictionaryName, subwordLength);
	*finalList += *addedList;
	finalList->GetRidOfRepetitions();
	delete addedList;
}

CList<CSubwordThisPoSWithQuantity>* GetListAllSubwordsAtTheEndAllPoS(const int& subwordLength)
{
	CList<CSubwordThisPoSWithQuantity>* outputListSubwordsAtTheEnd = new CList<CSubwordThisPoSWithQuantity>;

	for (int nPoSNumber = 0; nPoSNumber < 5; nPoSNumber++)
	{
		AddToListSubwordsAtTheEndTheOtherFromDictionary(
			outputListSubwordsAtTheEnd, 
			GetDictFileNameOfThePoSNumber(nPoSNumber));
	}

	return outputListSubwordsAtTheEnd;
}

void AnalysisOfTheSubwordsAtTheEnd()
{
	CList<CSubword>* listOfTheSubwordsAtTheEnd = new CList<CSubword>;
	CreateFullList(listOfTheSubwordsAtTheEnd, 1);

	CDictionary* dictionary = new CDictionary("Noun_01.txt");
	CList<CSubword>* tempListOfTheSubwordsAtTheEnd = new CList<CSubword>(*listOfTheSubwordsAtTheEnd);
	FillFullList(*dictionary, tempListOfTheSubwordsAtTheEnd, 1);
	delete dictionary;

	/*cout << "20 %" << endl;

	dictionary = new CDictionary("Adjectives.txt");
	CreateFullList(*dictionary, listOfTheSubwordsAtTheEnd, 3);
	delete dictionary;

	cout << "40 %" << endl;

	dictionary = new CDictionary("Adverbs.txt");
	CreateFullList(*dictionary, listOfTheSubwordsAtTheEnd, 3);
	delete dictionary;

	cout << "60 %" << endl;

	dictionary = new CDictionary("Names.txt");
	CreateFullList(*dictionary, listOfTheSubwordsAtTheEnd, 3);
	delete dictionary;

	cout << "80 %" << endl;

	dictionary = new CDictionary("Verb.txt");
	CreateFullList(*dictionary, listOfTheSubwordsAtTheEnd, 3);
	delete dictionary;

	cout << "100 %" << endl;*/

	PrintListOfTheSubwords(*tempListOfTheSubwordsAtTheEnd);
}