//
//      Implementation of the Assembler class.
//
#include "stdafx.h"
#include "Assembler.h"
#include "Errors.h"
#include "Emulator.h"


// Constructor for the assembler.  Note: we are passing argc and argv to the file access constructor.
// See main program.  
Assembler::Assembler( int argc, char *argv[] )
: m_facc( argc, argv )
{
    // Nothing else to do here at this point.
}
// Destructor currently does nothing.  You might need to add something as you develope this project.
Assembler::~Assembler( )
{
}
// Pass I establishes the location of the labels.  You will write better function comments according to the coding standards.
void Assembler::PassI( ) 
{
    int loc = 0;        // Tracks the location of the instructions to be generated.

    // Successively process each line of source code.
    for( ; ; ) {

        // Read the next line from the source file.
        string line; 
        if( ! m_facc.GetNextLine( line ) ) {

            // If there are no more lines, we are missing an end statement.
            // We will let this error be reported by Pass II.
            return;
        }
        // Parse the line and get the instruction type.
        Instruction::InstructionType st =  m_inst.ParseInstruction( line );

		

        // If this is an end statement, there is nothing left to do in pass I.
        // Pass II will determine if the end is the last statement.
        if( st == Instruction::ST_End ) return;

        // Labels can only be on machine language and assembler language
        // instructions.  So, skip other instruction types.  Currently this is only comments.
        if( st != Instruction::ST_MachineLanguage && st != Instruction::ST_AssemblerInstr ) 
        {
        	continue;
	  }
        // If the instruction has a label, record it and its location in the
        // symbol table.
        if( m_inst.isLabel( ) ) {

            m_symtab.AddSymbol( m_inst.GetLabel( ), loc );
        }
        // Compute the location of the next instruction.
        loc = m_inst.LocationNextInstruction( loc );
    }
}

/*
NAME

	AssemToML - converts assembly language to machine language

SYNOPSIS

	int AssemToML();

DESCRIPTION

	This function will take assembly language and change it to 
	machine language if the numeric Op Code is equal to 13. In
	addition, it will check "dc" and "read" parts of the Op Code and
	return values if the Op Code is equal to each part.
*/
int Assembler::AssemToML() {

	int macInstruction = 0;
	int digit_loc = 1'000'000;

	int reg = (1 * digit_loc);
	int unusedReg = (9 * digit_loc);

	string opCode = m_inst.GetOpCode();
	string operand1 = m_inst.GetOperand1();
	string operand2 = m_inst.GetOperand2();
	int operand1Value = m_inst.GetOp1Value();

	if (m_inst.opToNum(opCode)) 
	{
		int macOpCode = m_inst.GetNumOpCode();

		macInstruction += (digit_loc * 10 * macOpCode);

		if (macOpCode == 13)
		{
			macInstruction += unusedReg;
			return macInstruction;
		}

	}

	//Check other parts of original statement
	if (opCode == "dc")
	{
		macInstruction += operand1Value;
	}
	else if (opCode == "read")
	{
		macInstruction += (unusedReg + m_symtab.GetLoc(operand1));
	}
	else
	{
		macInstruction += (reg * operand1Value + m_symtab.GetLoc(operand2));
	}

	return macInstruction;
}

/*
NAME

	PassII - generates a translation

SYNOPSIS

	void PassII();

DESCRIPTION

	This function will process each line while rewinding the file pointer.
	It will then parse each line to get the instruction type. If the instruction
	type is machine language, translate it.
	If the instruction type is assembly language, output it by using each ST in the 
	Instruction class. Once that is all done, compute the location of the
	next instruction.
*/

void Assembler::PassII()
{
	 
	int loc = 0;        
	string line;

	//Process each line and translate 
	cout << "\n";
	cout << "Translation of Program:" << endl;
	cout << "\n";
	cout << "Location    Contents      Original Statement" << endl;

	//Rewind the file pointer
	m_facc.rewind();
 
	while (!m_facc.GetNextLine(line) == false)
	{
		// Parse the line to get the instruction type
		Instruction::InstructionType st = m_inst.ParseInstruction(line);


		//If machine language instruction, translate it
		if (st == Instruction::ST_MachineLanguage || m_inst.GetOpCode() == "dc")
		{
			string macInstruct = to_string(AssemToML());
			
			while (macInstruct.length() != 9)
			{
				macInstruct.insert(macInstruct.begin(), 1, '0');
			}

			if (!m_emul.insertMemory(loc, stoi(macInstruct)))
			{
				Errors::RecordError("Cannot place in location");
			}

			cout << to_string(loc) << "         " << macInstruct << "        " << m_inst.GetInstruction() << endl;
		}

		else if (st == Instruction::ST_Comment)
		{
			cout << "                          " << m_inst.GetInstruction() << endl;
		}

		else if (st == Instruction::ST_End)
		{
			cout << "			    " << m_inst.GetInstruction() << endl;
			return;
		}

		else
		{
			cout << to_string(loc) << "	                     " << m_inst.GetInstruction() << endl;
		}

		//Compute the location of the next instruction
		loc = m_inst.LocationNextInstruction(loc);

	}
}

 