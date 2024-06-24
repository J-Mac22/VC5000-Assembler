//
//		Assembler class.  This is a container for all the components
//		that make up the assembler.
//
#pragma once 

#include "SymTab.h"
#include "Instruction.h"
#include "FileAccess.h"
#include "Emulator.h"


class Assembler {

public:
    Assembler( int argc, char *argv[] );
    ~Assembler( );

    // Pass I - establish the locations of the symbols
    void PassI( );

    // Pass II - generate a translation
	void PassII( ); 

    // Display the symbols in the symbol table.
    void DisplaySymbolTable() { m_symtab.DisplaySymbolTable(); }

/*
NAME

	RunProgramInEmulator - run emulator on the translation

SYNOPSIS

	void RunProgramInEmulator();

DESCRIPTION

	This function will declare a bool "success" and have it
	be equal to m_emul so that it will be able to successfully
	run the emulator over in Assem.cpp.
*/
    
	void RunProgramInEmulator() {

		bool success = m_emul.runProgram();
		 
	}; 

	//Convert assembly language to machine language
	int AssemToML();

private:

    FileAccess m_facc;	    // File Access object
    SymbolTable m_symtab; // Symbol table object
    Instruction m_inst;	    // Instruction object
    emulator m_emul;        // Emulator object
};

