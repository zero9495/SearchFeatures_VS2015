#pragma once

#define POS_NUMBER_NOUN 0
#define POS_NUMBER_ADJECTIVES 1
#define POS_NUMBER_ADVERBS 2
#define POS_NUMBER_NAMES 3
#define POS_NUMBER_VERB 4

#define DICT_FILENAME_NOUN "Noun_01.txt"
#define DICT_FILENAME_ADJECTIVES "Adjectives.txt"
#define DICT_FILENAME_ADVERBS "Adverbs.txt"
#define DICT_FILENAME_NAMES "Names.txt"
#define DICT_FILENAME_VERB "Verb.txt"

/*NOUN
ADJECTIVES
ADVERBS
NAMES
VERB*/

char* GetDictFileNameOfThePoSNumber(const int& nPoSNumber)
{
	switch (nPoSNumber)
	{
	case POS_NUMBER_NOUN:
		{
			int k = 0;
			return DICT_FILENAME_NOUN;
		}
	case POS_NUMBER_ADJECTIVES:
		{
			return DICT_FILENAME_ADJECTIVES;
		}
	case POS_NUMBER_ADVERBS:
		{
			return DICT_FILENAME_ADVERBS;
		}
	case POS_NUMBER_NAMES:
		{
			return DICT_FILENAME_NAMES;
		}
	case POS_NUMBER_VERB:
		{
			return DICT_FILENAME_VERB;
		}
	}
}