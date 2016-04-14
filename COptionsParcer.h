#pragma once

#include "COptions.h"

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

class COptionsParcer
{
public:

	friend class COption;
	friend class COptionDouble;
	friend class COptionInt;
	friend class COptionString;
	
	COptionsParcer();
	~COptionsParcer();
	COptionsParcer(const COptionsParcer &a);
	
	//void Add(COption *option)
	//{
	//	m_pOptionsVector.push_back(new COption(*option));
	//}

	void InitializeOptions(const vector<COption*> &optionsVector);
	void Parse(int argc, char *argv[]); //функция разбора параметров командной строки
	void OutputParseResults();
	void OutputHelp();

	int GetNOptions();
	int GetFirstOption(COption* &option); //возвращает индекс первой обнаруженной опции в массиве. -1 Если считанных опций не найдено.
	int GetNextOption(int iPosition, COption* &option); // возвращает индекс найденной  в массиве. Возвращает -1, если считанных опций не найдено.
	bool HelpOptionFound();				// возвращает m_bHelpOptionFound

private:

	bool m_bHelpOptionFound;			// флаг, отвечающий за то, была ли встречена опция --help
	vector<COption*> m_pOptionsVector;	// вектор указателей допустимых опций в командной строке. В этот же вектор записываетсяя результат обработки строки 
};