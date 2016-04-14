#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>

class COptionsParcer;

using namespace std;

enum optionType		// ������������, ����������� ��� �����
{
	noArgument = 0,			// �� ������� ���������
	requiredArgument = 1,	// ������� ���������
	optionalArgument = 2	// �������������� ��������
};

enum argumentType	// ������������, ����������� ��� ���������
{
	argumentOk = 0,			// �������� ����� ���������
	argumentNotFound = 1,	// �������� �� �����
	argumentNotValid = 2	// �������� ����� �����������
};

////////////////////////////
/////   class COption     //
////////////////////////////

class COption
{
public:
	
	COption(string name, string description, int optionType);
	COption(string name, string description, int optionType, int argumentType, bool bFound);
	COption();
	virtual ~COption() {}

	bool IsFound() const;
	int GetArgumentType() const;
	int GetOptionType() const;
	string GetName() const; 
	string GetDescription() const;
	
	void SetName(string str);
	void SetDescription(string str);
	void SetFound(bool bFound);
	void SetArgumentType(int type);
	
	virtual string GetValueStr() const { return ""; }
	virtual void SetDefault() {}
	virtual bool ParseValue(string str) { return true;}
	virtual void AddToParcer(COptionsParcer *parcer);

protected:

	string m_sName;			// ��� ���������
	string m_sDescription;	// �������� ���������
	int m_optionType;		// ��� ����� (��������� ���� �� �������� optionType)
	int m_argumentType;		// ��� ��������� (��������� ���� �� �������� argumentType)
	bool m_bFound;			// ����, ���������� �� ��, ��� �� ������ �������� ��� �������
};


//////////////////////////////////
/////   class COptionDouble     //
//////////////////////////////////

class COptionDouble: public COption
{
public:

	COptionDouble();
	COptionDouble(string name, string description, int optionType );
	COptionDouble(string name, string description, int optionType, int argumentType, bool bFound );
	
	double GetDefaultValue() const;	
	double GetValue() const;
	
	void SetValue(double dValue);
	void SetDefaultValue(double dDefaultValue);
	
	virtual string GetValueStr() const;
	virtual void SetDefault();
	virtual bool ParseValue(string str);
	virtual void AddToParcer(COptionsParcer *parcer);
	
private:
	
	double m_dValue;
	double m_dDefaultValue;
};

///////////////////////////////
/////   class COptionInt     //
///////////////////////////////

class COptionInt: public COption
{
public:

	COptionInt();
	COptionInt(string name, string description, int optionType );	
	COptionInt(string name, string description, int optionType, int argumentType, bool bFound );
	
	int GetValue() const;
	double GetDefaultValue() const;
	
	void SetValue(int iValue);
	void SetDefaultValue(int iDefaultValue);
	
	virtual string GetValueStr() const;
	virtual bool ParseValue(string str);
	virtual void SetDefault();
	virtual void AddToParcer(COptionsParcer *parcer);

private:
	
	int m_iValue;
	int m_iDefaultValue;

};

//////////////////////////////////
/////   class COptionString     //
//////////////////////////////////

class COptionString: public COption
{
public:

	COptionString();
	COptionString(string name, string description, int optionType );
	COptionString(string name, string description, int optionType, int argumentType, bool bFound );
	
	string GetValue() const;
	string GetDefaultValue() const;
	
	void SetValue(string sValue);
	void SetDefaultValue(string sDefaultValue);
	
	virtual string GetValueStr() const;
	virtual bool ParseValue(string str);
	virtual void SetDefault();
	virtual void AddToParcer(COptionsParcer *parcer);

private:
	
	string m_sValue;
	string m_sDefaultValue;
};



