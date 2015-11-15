#pragma once
#include "CDictionary.h"

int* CalcualteCountsAllLetters(const CMyString& givenString)
{
	char* string = givenString.GetStr();
	int* counts = new int[33];
	for (int i = 0; i < 33; i++)
	{
		counts[i] = 0;
	}

	for (int i = 0; i < strlen(string); i++)
	{
		if ((string[i] - 'à' >= 0) &&
			(string[i] - 'à' < 33))
		{
			counts[string[i] - 'à']++;
		}

		/*if ((string[i] + 32 >= 0) &&
		(string[i] + 32 < 33))
		counts[string[i] + 32]++;*/
	}

	return counts;
}

int** CalculateAllCountsAllLetters(const CDictionary& dictionary)
{
	int** counts = new int*[10];
	for (int i = 0; i < 10; i++)
	{
		counts[i] = new int[33];
		for (int j = 0; j < 33; j++)
		{
			counts[i][j] = 0;
		}
	}

	int num = 0;
	int* k = 0;
	CListElem<CMyString>* pWords = dictionary.GetBegin();
	while (pWords)
	{
		num++;
		k = CalcualteCountsAllLetters(*(pWords->GetData()));

		for (int i = 0; i < 33; i++)
		{
			//cout << k[i];
			counts[k[i]][i]++;
		}
		//cout << endl;

		if (num % 100 == 0)
		{
			cout << num << endl;
		}

		delete[] k;
		if (pWords->GetNext() == 0)
		{
			break;
		}
		pWords = pWords->GetNext();
	}

	return counts;
}

void SaveMatrixForExcel(int** matrix, const int& countColumns, const int& countLines)
{
	ofstream foutt("output/output.txt");
	for (char i = 'à'; i <= 'ÿ'; i++)
	{
		foutt << i << endl;
	}
	foutt.close();

	CMyString fileName = "";
	char tempStr[256];

	for (int counterColumns = 0; counterColumns < countColumns; counterColumns++)
	{
		fileName = "output/output";

		_itoa_s(counterColumns, tempStr, 2, 10);
		fileName += tempStr;

		fileName += ".txt";
		ofstream fout(fileName.GetStr());

		for (int counterLines = 0; counterLines < countLines; counterLines++)
		{
			fout << matrix[counterColumns][counterLines] << endl;
		}

		fout.close();

		fileName = "";
	}

	int fileNum = countColumns;
	int err = 0;

	while (err == 0)
	{
		fileName = "output/output";

		_itoa_s(fileNum, tempStr, 3, 10);
		fileName += tempStr;

		fileName += ".txt";
		err = remove(fileName.GetStr());
		fileNum++;
	}
}

void AnalysisOnTheCountOfOccurrences()
{
	CDictionary* dictionary = new CDictionary("Noun_01.txt");

	int count[10];
	for (int i = 0; i < 10; i++)
	{
		count[i] = 0;
	}

	int** k = CalculateAllCountsAllLetters(*dictionary);
	SaveMatrixForExcel(k, 10, 33);

	delete dictionary;
}