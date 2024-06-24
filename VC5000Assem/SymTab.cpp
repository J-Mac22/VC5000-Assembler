//
//		Implementation of the symbol table class.  This is the format I want for commenting functions.
//
#include "stdafx.h"
#include "SymTab.h"
#include "Errors.h"

/*
NAME

    AddSymbol - adds a new symbol to the symbol table.

SYNOPSIS

    void AddSymbol( const string &a_symbol, int a_loc );

DESCRIPTION

    This function will place the symbol "a_symbol" and its location "a_loc"
    in the symbol table.
*/

void 
SymbolTable::AddSymbol( const string &a_symbol, int a_loc )
{
    // If the symbol is already in the symbol table, record it as multiply defined.
    map<string, int>::iterator st = m_symbolTable.find( a_symbol );
    if( st != m_symbolTable.end() ) {

        st->second = multiplyDefinedSymbol;
        return;
    }
    // Record a the  location in the symbol table.
    m_symbolTable[a_symbol] = a_loc;
}

/*
NAME

	DisplaySymbolTable - displays the symbol table in the console window.

SYNOPSIS

	void DisplaySymbolTable();

DESCRIPTION

	This function will display the symbol table by outputting the symbol number "m_symbol++",
	symbol "symTab ->first", and location "symTab ->second" one by one.
*/

void SymbolTable::DisplaySymbolTable()
{
	//Show the symbol table as an output
	cout << "Symbol Table: " << "\n" << endl;
	cout << "Symbol #" << setw(10) << "Symbol" << setw(10) << "Location" << endl;

	int m_symbol = 0;

	//Output symbol number, symbol, and location one by one
	for (map<string, int>::iterator symTab = m_symbolTable.begin(); symTab != m_symbolTable.end(); symTab++)
	{
		cout << setw(2) << m_symbol++ << setw(12) << symTab->first << setw(9) << symTab->second << endl;
	}
}

/*
NAME

	LookupSymbol - looks up a symbol to add to the symbol table.

SYNOPSIS

	bool LookupSymbol(const string &a_symbol, int& a_loc );

DESCRIPTION

	This function will look up a symbol "a_symbol" to add to the symbol table "symTab". If
	the symbol table "symTab" does not reach the end, add another location "a_loc".
*/

bool SymbolTable::LookupSymbol(const string& a_symbol, int& a_loc)
{
	//Find a symbol to add to the table
	map<string, int>::iterator symTab = m_symbolTable.find(a_symbol);

	if (symTab != m_symbolTable.end())
	{
		a_loc = symTab->second;
		return true;
	}
	return false;
}

/*
NAME

	GetLoc - gets a location from the symbol table

SYNOPSIS

	int GetLoc(const string& a_symbol);

DESCRIPTION

	This function will look up a symbol "a_symbol" in order to get the location
	which will apply to both the symbol table and Pass II. If no symbol
	is found, return -9999.
*/

int SymbolTable::GetLoc(const string& a_symbol)
{
	map<std::string, int>::iterator symTab = m_symbolTable.find(a_symbol);

	if (symTab != m_symbolTable.end())
	{

		return symTab->second;
	}

	return -9999;
	Errors::RecordError("Symbol/location not found");
	Errors::DisplayErrors();
}