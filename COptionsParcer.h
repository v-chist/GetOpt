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
	void Parse(int argc, char *argv[]); //������� ������� ���������� ��������� ������
	void OutputParseResults();
	void OutputHelp();

	int GetNOptions();
	int GetFirstOption(COption* &option); //���������� ������ ������ ������������ ����� � �������. -1 ���� ��������� ����� �� �������.
	int GetNextOption(int iPosition, COption* &option); // ���������� ������ ���������  � �������. ���������� -1, ���� ��������� ����� �� �������.
	bool HelpOptionFound();				// ���������� m_bHelpOptionFound

private:

	bool m_bHelpOptionFound;			// ����, ���������� �� ��, ���� �� ��������� ����� --help
	vector<COption*> m_pOptionsVector;	// ������ ���������� ���������� ����� � ��������� ������. � ���� �� ������ ������������� ��������� ��������� ������ 
};