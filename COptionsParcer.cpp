#include "stdafx.h"

#include "COptionsParcer.h" 
#include "COptions.h"


COptionsParcer::COptionsParcer()
{
	m_bHelpOptionFound = false;
}
	
COptionsParcer::~COptionsParcer()
{
	for(size_t i = 0; i < m_pOptionsVector.size(); i++)
		delete m_pOptionsVector[i];
}

COptionsParcer::COptionsParcer(const COptionsParcer &a)
{
}

void COptionsParcer::InitializeOptions(const vector<COption*> &optionsVector)
{
	for(size_t i = 0; i < optionsVector.size(); i++)
	{
		optionsVector[i]->AddToParcer(this);
	}
}

//COptionsParcer(const vector<COption*> &optionsVector)
//{
//	m_pOptionsVector = optionsVector;
//}

void COptionsParcer::Parse(int argc, char *argv[]) //функция разбора параметров командной строки
{
	string sCurrentOption, sOption, sArgument;
	for(int i = 1; i < argc; i++) //пропускаем нулевой параметр - имя программы
	{
		sCurrentOption = argv[i];
		if(sCurrentOption[0] == '-' && sCurrentOption[1] == '-' && sCurrentOption.length() > 2)
		{
			if(sCurrentOption.compare(2, sCurrentOption.length() - 2, "help") == 0)
				m_bHelpOptionFound = true;
				
			for(size_t j = 0; j < m_pOptionsVector.size(); j++)
			{
				sOption = m_pOptionsVector[j]->GetName();
				if(sCurrentOption.compare(2, sCurrentOption.length() - 2, sOption) == 0)
				{
					m_pOptionsVector[j]->SetFound(true);
					if(i + 1 < argc && m_pOptionsVector[j]->GetOptionType() != noArgument)
					{
						sArgument = argv[i + 1];
						if(sArgument[0] != '-' || sArgument[1] != '-' )
						{
							m_pOptionsVector[j]->ParseValue(sArgument);
							i++;
						}
						else
							m_pOptionsVector[j]->SetArgumentType(argumentNotFound);
					}
					break;
				}
			}
		}
	}
}
	
void COptionsParcer::OutputParseResults()
{
	if(HelpOptionFound())
		OutputHelp();

	COption *curOption;

	cout << "\n";

	int index = GetFirstOption(curOption);

	while (index != -1)
	{
		cout << curOption->GetName();

		if( curOption->GetOptionType() != noArgument && curOption->GetArgumentType() == argumentOk)
			cout << " = " << curOption->GetValueStr();
		else if( curOption->GetOptionType() == requiredArgument && curOption->GetArgumentType() == argumentNotFound)
			cout << " = " << "No argument";
		else if( curOption->GetOptionType() != noArgument && curOption->GetArgumentType() == argumentNotValid)
			cout << " = " << "Invalid argument";
				
		cout << "\n";

		index = GetNextOption(index, curOption);
	}
}

int COptionsParcer::GetNOptions()
{
	return m_pOptionsVector.size();
}

int COptionsParcer::GetFirstOption(COption* &option)
{
	for(size_t i = 0; i < m_pOptionsVector.size(); i++)
	{
		if(m_pOptionsVector[i]->IsFound())
		{
			option = m_pOptionsVector[i];
			
			return i + 1;
		}
	}

	return -1;
}

int COptionsParcer::GetNextOption(int iPosition, COption* &option)
{
	if(iPosition < 0)
		return -1;

	for(size_t i = iPosition; i < m_pOptionsVector.size(); i++)
	{
		if(m_pOptionsVector[i]->IsFound())
		{
			option = m_pOptionsVector[i];

			return i + 1;
		}
	}
	return -1;
}


bool COptionsParcer::HelpOptionFound()
{
	return m_bHelpOptionFound;
}

void COptionsParcer::OutputHelp()
{
	cout << "\n List of possible options: \n";
	for(size_t i = 0; i < m_pOptionsVector.size(); i++)
	{
		cout << "--" << m_pOptionsVector[i]->GetName() << " (" << m_pOptionsVector[i]->GetDescription() << ")";
		switch(m_pOptionsVector[i]->GetOptionType())
		{
		case requiredArgument:
			cout << " Argument required \n";
			break;

		case optionalArgument:
			cout << " Optional argument \n";
			break;

		case noArgument:
			cout << " No argument required \n";
			break;
		}
	}
}