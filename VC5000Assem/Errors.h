//
// Class to manage error reporting. Note: all members are static so we can access them anywhere.
// What other choices do we have to accomplish the same thing?
//
#ifndef _ERRORS_H
#define _ERRORS_H

#include <string>
#include <vector>

class Errors {

public:
    
    // Initializes error reports.
	static void InitErrorReporting()
	{
		m_ErrorMsgs.clear();
	};
    // Records an error message.
	static void RecordError(string a_emsg) { m_ErrorMsgs.push_back(a_emsg); }; //From Pres. 3 lecture

    // Displays the collected error message.
	static void DisplayErrors();

private:

    static vector<string> m_ErrorMsgs;  // This must be declared in the .cpp file.  Why?
};
#endif