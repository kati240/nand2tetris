// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Fill.asm

// Runs an infinite loop that listens to the keyboard input.
// When a key is pressed (any key), the program blackens the screen
// by writing 'black' in every pixel;
// the screen should remain fully black as long as the key is pressed. 
// When no key is pressed, the program clears the screen by writing
// 'white' in every pixel;
// the screen should remain fully clear as long as no key is pressed.

//// Replace this comment with your code.

// take input from the register mapped to keyboard input 
// then if value is >0 go to blacken function 
// that runs a loop for memory map of the screen and makes them black 
// then return back to original function where we take input 
// similarly the mirror case

(TAKE_INPUT)

    @24575
    D=A
    @1
    M=D

    @24576 // kb input
    D=M

    @BLACKEN
    D;JGT

    @24576 
    D=M

    @WHITEN
    D;JEQ

(BLACKEN)

    @16384
    D=A
    @2
    M=D

    @1
    D=M-D

    @LOOP_B
    D;JGE

    @RETURN
    D;JLT

(LOOP_B)
    // 2 has current address that need to be adressed
    @2
    A=M
    M=-1  // apparently the code is -1 not 1 

    @2
    M=M+1
    D=M

    @24575
    D=A-D

    @1
    M=D

    @LOOP_B
    D;JGE

    @RETURN
    D;JLT

(RETURN)

    @TAKE_INPUT
    D;JLT

(WHITEN)

    @16384
    D=A

    @2
    M=D

    @1
    D=M-D

    @LOOP_W
    D;JGE

    @RETURN
    D;JLT

(LOOP_W)

    @2
    A=M
    M=0

    @2
    M=M+1
    D=M

    @24575
    D=A-D

    @1
    M=D

    @LOOP_W
    D;JGE

    @RETURN
    D;JLT
