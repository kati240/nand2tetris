// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Mult.asm

// Multiplies R0 and R1 and stores the result in R2.
// Assumes that R0 >= 0, R1 >= 0, and R0 * R1 < 32768.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)

//// Replace this comment with your code.
    @2   // loading R2 (Memory[2]) in A register
    M=0  //  M is basically Memory[A]

    @0
    D=M
    @LOOP // Loading LOOP in A
    D;JGT

    @0
    D=M
    @END
    D;JLE

(LOOP)

    @0
    M=M-1  //   R0-=1;
    @1
    D=M;   // storing R1
    @2
    M=M+D  // R2 = R2 + R1
    @0
    D=M
    @LOOP
    D;JGT

(END)