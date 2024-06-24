#include "stdafx.h"    // This must be present if you use precompiled headers which you will use. 

#include "Errors.h"

vector<string> Errors::m_ErrorMsgs;


/*
NAME

	DisplayErrors - displays each error 

SYNOPSIS

	void DisplayErrors();

DESCRIPTION

	This function will be following up on the ReportError function.
	Once an error has been reported in the program, this function
	will display the error that is causing this program to not
	work correctly. 
*/

void Errors::DisplayErrors()
{
	for (int i = 0; i < m_ErrorMsgs.size(); i++)
	{
		cout << m_ErrorMsgs.at(i) << endl;
		return;
	}
}
