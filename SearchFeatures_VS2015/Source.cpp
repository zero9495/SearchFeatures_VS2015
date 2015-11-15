/*////////////////////////////////////

Венгерская нотация

C - класс
n - int
p - указатель
a - динамический массив
_ - поле класса

*/////////////////////////////////////

#include <iostream>
#include <list>
#include <fstream>
#include <Windows.h>
#include "CMyString.h"
//#include <vld.h>
#include "CList.h"
#include "CDictionary.h"
#include "CSubwordWithQuantity.h"
#include "AnalysisOnTheCountOfOccurrences.h"
#include "AnalysisOfTheSubwordsAtTheEnd.h"
#include "Probability.h"

using namespace std;

CList<CSubwordThisPoSWithQuantity>*
FillListOfTheSubwordsOfWordsFromTheDictionary(
	const CList<CSubwordThisPoSWithQuantity>* fullListOfTheSubwordsAtTheEnd,
	const char* fileDictionaryName)
{
	CList<CSubwordThisPoSWithQuantity>* outputListSubwordsAtTheEnd = new CList<CSubwordThisPoSWithQuantity>(*fullListOfTheSubwordsAtTheEnd);
	AddToListSubwordsAtTheEndTheOtherFromDictionary(outputListSubwordsAtTheEnd, fileDictionaryName);

	return outputListSubwordsAtTheEnd;
}

CList<CSubwordThisPoSWithQuantity>** FillListOfTheSubwordsAtTheEndAllPoS(
	const CList<CSubwordThisPoSWithQuantity>* const listOfTheSubwordsAtTheEnd)
{
	CList<CSubwordThisPoSWithQuantity>** outputListOfTheSubwordsAtTheEndAllPoS = new CList<CSubwordThisPoSWithQuantity>*[5];

	for (int nPoS = 0; nPoS < 5; nPoS++)
	{
		outputListOfTheSubwordsAtTheEndAllPoS[nPoS] = FillListOfTheSubwordsOfWordsFromTheDictionary(
			listOfTheSubwordsAtTheEnd, GetDictFileNameOfThePoSNumber(nPoS));
		cout << 20 * (nPoS + 1) << " %" << endl;
	}
}

CList<CSubwordThisPoSWithQuantity>** GetListOfTheSubwordsAtTheEndAllPoS(const int& subwordLength)
{
	CList<CSubwordThisPoSWithQuantity>* listOfTheSubwordsAtTheEnd = GetListAllSubwordsAtTheEndAllPoS(subwordLength);
	return FillListOfTheSubwordsAtTheEndAllPoS(listOfTheSubwordsAtTheEnd);
}

CProbPoSProvidedThatTheSubwordAtTheEnd** ColculateProbPoSProvidedThatTheSubwordAtTheEnd(const int& subwordLength, int& quantity)
{
	CList<CSubwordThisPoSWithQuantity>** listOfTheSubwordsAtTheEndPoS = GetListOfTheSubwordsAtTheEndAllPoS(subwordLength);

	CProbPoSProvidedThatTheSubwordAtTheEnd** outputCounts = new CProbPoSProvidedThatTheSubwordAtTheEnd*[5];
	for (int i = 0; i < 5; i++)
	{
		outputCounts[i] = new CProbPoSProvidedThatTheSubwordAtTheEnd[listOfTheSubwordsAtTheEndPoS[0]->GetSize()];
	}

	CListElem<CSubwordThisPoSWithQuantity>* pointer0 = listOfTheSubwordsAtTheEndPoS[0]->GetBegin();
	CListElem<CSubwordThisPoSWithQuantity>* pointer1 = listOfTheSubwordsAtTheEndPoS[1]->GetBegin();
	CListElem<CSubwordThisPoSWithQuantity>* pointer2 = listOfTheSubwordsAtTheEndPoS[2]->GetBegin();
	CListElem<CSubwordThisPoSWithQuantity>* pointer3 = listOfTheSubwordsAtTheEndPoS[3]->GetBegin();
	CListElem<CSubwordThisPoSWithQuantity>* pointer4 = listOfTheSubwordsAtTheEndPoS[4]->GetBegin();

	int* sum = 0;
	for (int i = 0; i < listOfTheSubwordsAtTheEndPoS[0]->GetSize(); i++)
	{
		sum = 0;
		sum += pointer0->GetData()->GetQuantity();
		sum += pointer1->GetData()->GetQuantity();
		sum += pointer2->GetData()->GetQuantity();
		sum += pointer3->GetData()->GetQuantity();
		sum += pointer4->GetData()->GetQuantity();

		pointer0 = pointer0->GetNext();
		pointer1 = pointer1->GetNext();
		pointer2 = pointer2->GetNext();
		pointer3 = pointer3->GetNext();
		pointer4 = pointer4->GetNext();
	}



	int nSubwordNumber = 0;
	CListElem<CSubwordThisPoSWithQuantity>* pSubword = 0;

	for (int nPoS = 0; nPoS < 5; nPoS++)
	{
		pSubword = listOfTheSubwordsAtTheEndPoS[nPoS]->GetBegin();
		while (pSubword)
		{
			outputCounts[nPoS][nSubwordNumber].ColculateProbability(pSubword->GetData()->GetQuantity(), sum[nSubwordNumber]);
			outputCounts[nPoS][nSubwordNumber].SetPoS(nPoS);
			outputCounts[nPoS][nSubwordNumber].SetSubword(*(pSubword->GetData()));
			nSubwordNumber++;
			pSubword = pSubword->GetNext();
		}
	}

	quantity = nSubwordNumber;

	return outputCounts;
}

int** GetIntFromProb(const int& subwordLength)
{
	int quantity;
	CProbPoSProvidedThatTheSubwordAtTheEnd** prob = ColculateProbPoSProvidedThatTheSubwordAtTheEnd(subwordLength, quantity);
	int** k = new int*[5];
	for (int i = 0; i < 5; i++)
	{
		*k = new int[quantity];
		for (int j = 0; j < quantity; j++)
		{
			k[i][j] = prob[i][j].GetProbability();
		}
	}

	return k;
}

int main()
{
	setlocale(LC_ALL, "RUS");

	//AnalysisOfTheSubwordsAtTheEnd();	
	//AnalysisOnTheCountOfOccurrences();

	int** k = GetIntFromProb(1);
	SaveMatrixForExcel(k, 5, 31);

	cout << "Программа успешно выполнена" << endl;

	system("pause");
	return 0;
}