//
//		Emulator class - supports the emulation of VC1620 programs
//
#ifndef _EMULATOR_H      // UNIX way of preventing multiple inclusions.
#define _EMULATOR_H
#include <assert.h>
#include "Errors.h"

class emulator {

public:

    const static int MEMSZ = 1000000;	// The size of the memory of the VC5000.
    emulator() {

         m_memory.resize(MEMSZ, 0);
    }

    // Records instructions and data into VC5000 memory.
	bool insertMemory(int a_location, int a_contents) { 
		assert(a_location >= 0 && a_location < 1000000); //From Pres.4 mini lecture
		m_memory[a_location] = a_contents; //Part of Miller code
		return true;
	}
    
	/*
NAME

	runProgram - runs the VC5000 program recorded in memory

SYNOPSIS

	bool runProgram();

DESCRIPTION

	This function will declare a switch statement that goes through each
	register (or case), takes memory from Pass II, and outputs it in the emulator.
	If there is illegal Op Code in the emulator, then the program will stop
	and record an error.
*/

    //Not working but honest attempt at it
	bool runProgram()
	{

		int loc = 100;
		int dloc = m_memory[0];

		while(true)
		{
			
			int instr = m_memory[100];
			int opCode = instr / 1000000;
			int regNum = instr / 1000000 % 10;
			int address = instr % 1000000;
			
			switch (opCode) {

			case 1: //Add
				m_reg[regNum] = m_memory[address] + m_reg[regNum];
				break;

			case 2: //Subtract
				m_reg[regNum] = m_memory[address] - m_reg[regNum];
				break;

			case 3: //Multiply
				m_reg[regNum] = m_memory[address] * m_reg[regNum];
				break;

			case 4: //Divide
				m_reg[regNum] = m_memory[address] / m_reg[regNum];
				break;

			case 5: //Load
				m_reg[regNum] = m_memory[m_memory[address]] % 1000000;
				break;

			case 6: //Store
				m_memory[m_memory[address]] = m_reg[regNum];
				break;

			case 7: //Read
				cout << "? ";
				cin >> m_memory[m_memory[address]];
				break;

			case 8: //Write
				m_tmpAddr = dloc;
				cout << m_memory[dloc] % 1000000 << endl;
				dloc = m_tmpAddr;
				dloc++;
				break;

			case 9: //Branch
				dloc = m_memory[address];
				break;

			case 10: //Branch Minus
				if (m_reg[regNum] < 0)
				{
					dloc = m_memory[address];
				}
				dloc++;
				break;

			case 11: //Branch Zero
				if (m_reg[regNum] == 0)
				{

					dloc = m_memory[address];
					break;
				}
				dloc++;
				break;

			case 12: //Branch Positive
				if (m_reg[regNum] > 0)
				{
					dloc = m_memory[address];
					break;
				}
				dloc++;
				break;

			case 13: //Halt
				cout << "\nEnd of Emulation\n";
				return true;
				break;

			default: //Illegal opCode

				string err = "Illegal opCode (for the Emulator)";
				Errors::RecordError(err);
				return false;
			}
		}
	};

private:

    vector<int> m_memory;         	// Memory for the VC5000
    int m_reg[10];                  // Registers for the VC5000
	int m_tmpAddr;					// for "write" register
};

#endif

