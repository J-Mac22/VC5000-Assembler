#include "stdafx.h"
#include "Instruction.h"
#include "Errors.h"

//Using lecture code (Credit to Dr.Miller)

// Function to break down a statement into label, op code, operand1, operand2
// If it returns an empty string for the op code, it indicates an empty string
// The return value is false if there are extra fields.
bool Instruction::ParseLineIntoFields(string a_line, string& a_label, string& a_OpCode, string& a_Operand1, string& a_Operand2)
{
	
	// Get rid of any commas from the line.
	replace(a_line.begin(), a_line.end(), ',', ' ');

	// Get the elements of the line.  That is the label, op code, operand1, and operand2.
	string endStr;
	a_label = a_OpCode = a_Operand1 = a_Operand2 = "";

	istringstream ins(a_line);

	if (a_line[0] == ' ' || a_line[0] == '\t')
	{
		a_label = "";
		ins >> a_OpCode >> a_Operand1 >> a_Operand2 >> endStr;
	}
	else
	{
		ins >> a_label >> a_OpCode >> a_Operand1 >> a_Operand2 >> endStr;
	}
	// If there is extra data, return false.
 
	
	return endStr.empty() ? true : false;
}

/*
NAME

	ParseInstruction - parses a line to bring to the translation

SYNOPSIS

	InstructionType ParseInstruction(string a_line);

DESCRIPTION

	This function will parse a string "a_line" over to the translation.
	First, it will erase the comments and then it will check to see if
	no extra fields are found or if Machine Language instruction is found.
*/

Instruction::InstructionType Instruction::ParseInstruction(string a_line)
{
	//The original instruction for Pass II
	SetOriginalInstr(a_line);

	//After the comments are deleted, the statement will become empty 
	if (EraseComments(a_line))
	{
		m_type = ST_Comment;
		return m_type;
	}

	//If no extra fields are found
	if (ParseLineIntoFields(a_line, m_Label, m_OpCode, m_Operand1, m_Operand2))
	{
		if (IsNum(m_Operand1))
		{
			SetOp1Value(m_Operand1);
		}

		m_type = ST_AssemblerInstr;

		//If there is Machine Language instruction, numeric code must be obtained.
		if (opToNum(m_OpCode))
		{
			m_type = ST_MachineLanguage;
		}

		if (m_OpCode == "end")
		{
			m_type = ST_End;
		}
	}

	else
	{
		Errors::RecordError("There are too many fields.");
	}

	return m_type;
}

/*
NAME

	LocationNextInstruction - locates the next instruction for the translation

SYNOPSIS

	int LocationNextInstruction (int a_loc);

DESCRIPTION

	This function will check to see if the type is either machine language or 
	assembly language and then return an int "a_loc to Pass II.
*/

int Instruction::LocationNextInstruction(int a_loc)
{
	//Create a switch statement to distinguish instruction types
	switch (m_type)
	{

	case ST_MachineLanguage:
		return ++a_loc;

	case ST_AssemblerInstr:

		if (m_OpCode == "org" || m_OpCode == "ds")
		{
			return a_loc + m_Operand1Value;
		}

		else
		{
			return ++a_loc;
		}

	default:
		return a_loc;
	}
}

/*
NAME

	IsNum - checks to see if operand 1 is numeric

SYNOPSIS

	bool IsNum(const string& operand);

DESCRIPTION

	This function will check to see if operand 1 has become
	a numeric operand. If it hasn't then return it as false.
*/

bool Instruction::IsNum(const string& operand)
{
	m_IsNumericOperand1 = true;

	for (char const& c : operand) {

		if (isdigit(c) == 0)
		{
			m_IsNumericOperand1 = false;
		}
	}
	return m_IsNumericOperand1;
}

/*
NAME

	opToNum - converts the OpCode to numeric based on name

SYNOPSIS

	bool opToNum(string m_OpCode);

DESCRIPTION

	This function will check to see if a string "m_OpCode" corresponds to
	a name on the machine language program. If it matches, then it will be converted
	to numeric OpCode.
*/

bool Instruction::opToNum(string m_OpCode)
{
	//Check to see if OpCode matches each name

	if (m_OpCode == "add") 
	{
		m_NumOpCode = 1;
	}

	else if (m_OpCode == "sub") 
	{
		m_NumOpCode = 2;
	}

	else if (m_OpCode == "mult") 
	{
		m_NumOpCode = 3;
	}

	else if (m_OpCode == "div") 
	{
		m_NumOpCode = 4;
	}

	else if (m_OpCode == "load") 
	{
		m_NumOpCode = 5;
	}

	else if (m_OpCode == "store") 
	{
		m_NumOpCode = 6;
	}

	else if (m_OpCode == "read") 
	{
		m_NumOpCode = 7;
	}

	else if (m_OpCode == "write") 
	{
		m_NumOpCode = 8;
	}

	else if (m_OpCode == "b") 
	{
		m_NumOpCode = 9;
	}
	else if (m_OpCode == "bm") 
	{
		m_NumOpCode = 10;
	}
	else if (m_OpCode == "bz") 
	{
		m_NumOpCode = 11;
	}
	else if (m_OpCode == "bp") 
	{
		m_NumOpCode = 12;
	}
	else if (m_OpCode == "halt") 
	{
		m_NumOpCode = 13;
	}
	else 
	{
		m_NumOpCode = -99;   
		return false;
	}

	return true;
}

/*
NAME

	SetOriginalInstr - sets the original instruction for Pass II

SYNOPSIS

	void SetOriginalInstr(const string& a_line);

DESCRIPTION

	This function will convert the instruction to a string "a_line"
	therefore setting the original instruction to be used in 
	Pass II.
*/

void Instruction::SetOriginalInstr(const string& a_line)
{
	m_instruction = a_line;
	return;
}

/*
NAME

	SetOp1Value - sets the value for operand 1

SYNOPSIS

	void SetOp1Value(const string& operand);

DESCRIPTION

	This function will create a stringstream to convert operand1 
	to an int which will later become "m_Operand1Value".
*/

void Instruction::SetOp1Value(const string& operand)
{
	stringstream convert_to_int;
	convert_to_int << m_Operand1;
	convert_to_int >> m_Operand1Value;
	return;
}

/*
NAME

	EraseComments - erases comments that are indicated by the semicolon

SYNOPSIS

	bool EraseComments(string& a_line);

DESCRIPTION

	This function will search for a semicolon in a string "a_line"
	and if a semicolon exists, removes a comment indicated by said
	semicolon.
*/

bool Instruction::EraseComments(string& a_line)
{
	//Again using lecture code (Credit to Dr.Miller)
	size_t semi = a_line.find(';');

	// Searching for the first semicolon in a string and deleting it
	// and everything after it. If there is no semicolon, nothing will be deleted.
	if (semi != string::npos) {
		a_line.erase(semi);     
	}
	// If there is extra data, return false.
	return a_line.empty() ? true : false;
}


 