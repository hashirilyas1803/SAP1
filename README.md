# SAP1 Project

A basic implementation of a Simple As Possible Computer on an online simulation platform, Wokwi.

## Usage

1. Run your own instructions on the computer by writing the instructions directly into the array indices in the C file of the RAM chip.
2. Opcodes: 0000 for Load
            0001 for Add
            0010 for Subtract
            0011 for Halt
            0101 for Bitwise XOR
3. Instruction Format: Type 1(For Load and Store): 4 bits for opcode, 4 bits for regiter address, 8 bits for memory address. <br>
                       Type 2(For operations): 4 bits for opcode, 4 bits for register 1, 4 bits for second register 2 and 4 bits for the register to load the result      into.
