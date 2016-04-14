#include "stdafx.h"

#include "COptions.h" 
#include "COptionsParcer.h" 

////////////////////////////
/////   class COption     //
////////////////////////////


COption::COption(string name, string description, int optionType)
{
	m_sName = name;
	m_sDescription = description;
	m_optionType = optionType;
	m_argumentType = argumentNotFound;
	m_bFound = false;
}

COption::COption(string name, string description, int optionType, int argumentType, bool bFound )
{
	m_sName = name;
	m_sDescription = description;
	m_optionType = optionType;
	m_argumentType = argumentType;
	m_bFound = bFound;
}

COption::COption()
{
	m_sName = "";
	m_sDescription = "";
	m_optionType = noArgument;
	m_argumentType = argumentNotFound;
	m_bFound = false;
}

int COption::GetArgumentType() const 
{
	return m_argumentType;
}

int COption::GetOptionType() const
{
	return m_optionType;
}

bool COption::IsFound() const
{
	return m_bFound;
}

string COption::GetName() const 
{
	return m_sName;
}

string COption::GetDescription() const
{
	return m_sDescription;
}

void COption::SetName(string str)
{
	m_sName = str; 
}

void COption::SetDescription(string str)
{
	m_sDescription = str; 
}

void COption::SetFound(bool bFound)
{
	m_bFound = bFound;
}

void COption::SetArgumentType(int type)
{
	m_argumentType = type;
}

void COption::AddToParcer(COptionsParcer *parcer) 
{
	parcer->m_pOptionsVector.push_back(new COption(*this));
}



///////////////////////////////////
///// class COptionDouble  ////////
///////////////////////////////////


COptionDouble::COptionDouble()
{
	m_sName = "";
	m_sDescription = "";
	m_bFound = false;
	m_argumentType = noArgument;
	m_optionType = requiredArgument;
	m_dValue = 0;
	m_dDefaultValue = 0;
}

COptionDouble::COptionDouble(string name, string description, int optionType ):	
COption(name, description, optionType)
{
	m_dValue = 0;
	m_dDefaultValue = 0;
}

COptionDouble::COptionDouble(string name, string description, int optionType, int argumentType, bool bFound ):
COption(name, description, optionType, argumentType, bFound )
{
	m_dValue = 0;
	m_dDefaultValue = 0;
}

double COptionDouble::GetValue() const
{
	return m_dValue;
}

double COptionDouble::GetDefaultValue() const 
{
	return m_dDefaultValue;
}

void COptionDouble::SetValue(double dValue)
{
	m_dValue = dValue;
}

void COptionDouble::SetDefaultValue(double dDefaultValue)
{
	m_dDefaultValue = dDefaultValue;
}

void COptionDouble::SetDefault()
{
	m_dValue = m_dDefaultValue;
}

bool COptionDouble::ParseValue(string str)
{
	try
	{
		m_dValue = stod(str);
	}
	catch(...)
	{
		cerr << "Cannot convert argument value from string to double." << endl;

		m_argumentType = argumentNotValid;
		return false; 
	}

	m_argumentType = argumentOk;
	return true;
}

void COptionDouble::AddToParcer(COptionsParcer *parcer) 
{
	parcer->m_pOptionsVector.push_back(new COptionDouble(*this));
}

string COptionDouble::GetValueStr() const
{
	string result;
	
	if(m_argumentType == argumentNotFound || m_argumentType == argumentNotValid)
		return "";
	else
	{
		result = to_string((long double)m_dValue);
		return result;
	}
}

////////////////////////////////
///// class COptionInt  ////////
////////////////////////////////

COptionInt::COptionInt()
{
	m_sName = "";
	m_sDescription = "";
	m_bFound = false;
	m_argumentType = noArgument;
	m_optionType = requiredArgument;
	m_iValue = 0;
	m_iDefaultValue = 0;
}

COptionInt::COptionInt(string name, string description, int optionType ):	
COption(name, description, optionType)
{
	m_iValue = 0;
	m_iDefaultValue = 0;
}

COptionInt::COptionInt(string name, string description, int optionType, int argumentType, bool bFound ):
COption(name, description, optionType, argumentType, bFound )
{
	m_iValue = 0;
	m_iDefaultValue = 0;
}

int COptionInt::GetValue() const 
{
	return m_iValue;
}

double COptionInt::GetDefaultValue() const 
{
	return m_iDefaultValue;
}

void COptionInt::SetValue(int iValue)
{
	m_iValue = iValue;
}
	
void COptionInt::SetDefaultValue(int iDefaultValue)
{
	m_iDefaultValue = iDefaultValue;
}

bool COptionInt::ParseValue(string str)
{
	try
	{
		m_iValue = stoi(str);
	}
	catch(...)
	{
		cerr << "Cannot convert argument value from string to int." << endl;
		m_argumentType = argumentNotValid;
		return false;
	}

	m_argumentType = argumentOk;
	return true;
}

void COptionInt::SetDefault()
{
	m_iValue = m_iDefaultValue;
}

void COptionInt::AddToParcer(COptionsParcer *parcer) 
{
	parcer->m_pOptionsVector.push_back(new COptionInt(*this));
}

string COptionInt::GetValueStr() const
{
	string result;
	
	if(m_argumentType == argumentNotFound || m_argumentType == argumentNotValid)
		return "";
	else
	{
		stringstream stream;
		stream << m_iValue;
		result = stream.str();
		return result;
	}
}


///////////////////////////////////
///// class COptionString  ////////
///////////////////////////////////

COptionString::COptionString()
{
	m_sName = "";
	m_sDescription = "";
	m_bFound = false;
	m_argumentType = noArgument;
	m_optionType = requiredArgument;
	m_sValue = "";
	m_sDefaultValue = "";
}

COptionString::COptionString(string name, string description, int optionType ):	
COption(name, description, optionType)
{
	m_sValue = "";
	m_sDefaultValue = "";
}

COptionString::COptionString(string name, string description, int optionType, int argumentType, bool bFound ):
COption(name, description, optionType, argumentType, bFound )
{
	m_sValue = "";
	m_sDefaultValue = "";
}

string COptionString::GetValue() const 
{
	return m_sValue;
}

void COptionString::SetValue(string sValue)
{
	m_sValue = sValue;
}

string COptionString::GetDefaultValue() const 
{
	return m_sDefaultValue;
}

void COptionString::SetDefaultValue(string sDefaultValue)
{
	m_sDefaultValue = sDefaultValue;
}

bool COptionString::ParseValue(string str)
{
	m_sValue = str;
	m_argumentType = argumentOk;
	return true;
}

void COptionString::SetDefault()
{
	m_sValue = m_sDefaultValue;
}

void COptionString::AddToParcer(COptionsParcer *parcer) 
{
	parcer->m_pOptionsVector.push_back(new COptionString(*this));
}

string COptionString::GetValueStr() const
{
	if(m_argumentType == argumentNotFound || m_argumentType == argumentNotValid)
		return "";
	else
		return m_sValue;
}
