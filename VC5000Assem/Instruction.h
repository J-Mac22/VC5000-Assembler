//
// Class to parse and provide information about instructions.  Note: you will be adding more functionality.
//
#pragma once

// The elements of an instruction.
class Instruction {

public:

    Instruction( ) { };
    ~Instruction( ) { };

    // Codes to indicate the type of instruction we are processing.  Why is this inside the
    // class?
    enum InstructionType {
        ST_MachineLanguage, 	// A machine language instruction.
        ST_AssemblerInstr,  		// Assembler Language instruction.
        ST_Comment,          		// Comment or blank line
        ST_End                   		// end instruction.
    };
    // Parse the Instruction.
	InstructionType ParseInstruction(string a_line); 

    // Compute the location of the next instruction.
	int LocationNextInstruction(int a_loc); 

	//Breaks a statement down into label, op code, operand1, and operand2
	bool ParseLineIntoFields(string a_line, string& a_label, string& a_OpCode, string& a_Operand1, string& a_Operand2); 

    // To access the label
    inline string &GetLabel( ) {

        return m_Label;
    };

    // To determine if a label is blank.
    inline bool isLabel( ) {

        return ! m_Label.empty();
    };

	//To access the OpCode
	inline string &GetOpCode() {

		return m_OpCode;
	};

	//To access the NumOpCode
	inline int &GetNumOpCode() {

		return m_NumOpCode;
	};

	//To access the first operand
	inline string &GetOperand1() {

		return m_Operand1;
	};

	//To access the second operand
	inline string &GetOperand2() {

		return m_Operand2;
	};

	//To access the instructions
	inline string &GetInstruction() {

		return m_instruction;
	};

	//To access the operand 1 value
	inline int &GetOp1Value() {

		return m_Operand1Value;
	};

	//To convert all of the opcodes to numbers
	bool opToNum(string m_OpCode);

	//To set the value of operand 1
	void SetOp1Value(const string& operand);

	//To determine if operand 1 is numeric
	bool IsNum(const string& operand);

	//To set the original instruction
	void SetOriginalInstr(const string& a_line);

	//To erase any comments
	bool EraseComments(string& a_line);


private:

    // The elemements of a instruction

    string m_Label;            // The label.
    string m_OpCode;       // The symbolic op code.
    string m_Operand1;     // The first operand. 
    string m_Operand2;     // The second operand.

 
    string m_instruction;    // The original instruction.

    // Derived values.
    int m_NumOpCode;     // The numerical value of the op code for machine language equivalents.
    InstructionType m_type; // The type of instruction.

    bool m_IsNumericOperand1;// == true if the operand is numeric.
 
    int m_Operand1Value;   // The value of the operand if it is numeric.
};

 
