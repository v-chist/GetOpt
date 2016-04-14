#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>

class COptionsParcer;

using namespace std;

enum optionType		// перечисление, описывающее тип опции
{
	noArgument = 0,			// не требует аргумента
	requiredArgument = 1,	// требует аргумента
	optionalArgument = 2	// необязательный аргумент
};

enum argumentType	// пересичление, описывающее тип аргумента
{
	argumentOk = 0,			// аргумент задан корректно
	argumentNotFound = 1,	// аргумент не задан
	argumentNotValid = 2	// аргумент задан некорректно
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

	string m_sName;			// имя параметра
	string m_sDescription;	// описание параметра
	int m_optionType;		// тип опции (принимает одно из значений optionType)
	int m_argumentType;		// тип аргумента (принимает одно из значений argumentType)
	bool m_bFound;			// флаг, отвечающий за то, был ли найден параметр при разборе
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



