@17
D=A
@SP
A=M
M=D
@SP
M=M+1
@17
D=A
@SP
A=M
M=D
@SP
M=M+1
@SP
M=M-1
A=M
D=M
@SP
M=M-1
A=M
A=M
D=D-A
@zero1
D;JEQ
@nonzero1
D;JNE
(zero1)
@SP
A=M
M=-1
@continue1
0;JEQ
(nonzero1)
@SP
A=M
M=0
@continue1
0;JEQ
(continue1)
@SP
M=M+1

@17
D=A
@SP
A=M
M=D
@SP
M=M+1
@16
D=A
@SP
A=M
M=D
@SP
M=M+1
@SP
M=M-1
A=M
D=M
@SP
M=M-1
A=M
A=M
D=D-A
@zero2
D;JEQ
@nonzero2
D;JNE
(zero2)
@SP
A=M
M=-1
@continue2
0;JEQ
(nonzero2)
@SP
A=M
M=0
@continue2
0;JEQ
(continue2)
@SP
M=M+1

@16
D=A
@SP
A=M
M=D
@SP
M=M+1
@17
D=A
@SP
A=M
M=D
@SP
M=M+1
@SP
M=M-1
A=M
D=M
@SP
M=M-1
A=M
A=M
D=D-A
@zero3
D;JEQ
@nonzero3
D;JNE
(zero3)
@SP
A=M
M=-1
@continue3
0;JEQ
(nonzero3)
@SP
A=M
M=0
@continue3
0;JEQ
(continue3)
@SP
M=M+1

@892
D=A
@SP
A=M
M=D
@SP
M=M+1
@891
D=A
@SP
A=M
M=D
@SP
M=M+1
@SP
M=M-1
A=M
D=M
@SP
M=M-1
A=M
A=M
D=A-D
@lt4
D;JLT
@nlt4
D;JGE
(lt4)
@SP
A=M
M=-1
@continue4
0;JEQ
(nlt4)
@SP
A=M
M=0
@continue4
0;JEQ
(continue4)
@SP
M=M+1

@891
D=A
@SP
A=M
M=D
@SP
M=M+1
@892
D=A
@SP
A=M
M=D
@SP
M=M+1
@SP
M=M-1
A=M
D=M
@SP
M=M-1
A=M
A=M
D=A-D
@lt5
D;JLT
@nlt5
D;JGE
(lt5)
@SP
A=M
M=-1
@continue5
0;JEQ
(nlt5)
@SP
A=M
M=0
@continue5
0;JEQ
(continue5)
@SP
M=M+1

@891
D=A
@SP
A=M
M=D
@SP
M=M+1
@891
D=A
@SP
A=M
M=D
@SP
M=M+1
@SP
M=M-1
A=M
D=M
@SP
M=M-1
A=M
A=M
D=A-D
@lt6
D;JLT
@nlt6
D;JGE
(lt6)
@SP
A=M
M=-1
@continue6
0;JEQ
(nlt6)
@SP
A=M
M=0
@continue6
0;JEQ
(continue6)
@SP
M=M+1

@32767
D=A
@SP
A=M
M=D
@SP
M=M+1
@32766
D=A
@SP
A=M
M=D
@SP
M=M+1
@SP
M=M-1
A=M
D=M
@SP
M=M-1
A=M
A=M
D=A-D
@gt7
D;JGT
@ngt7
D;JLE
(gt7)
@SP
A=M
M=-1
@continue7
0;JEQ
(ngt7)
@SP
A=M
M=0
@continue7
0;JEQ
(continue7)
@SP
M=M+1

@32766
D=A
@SP
A=M
M=D
@SP
M=M+1
@32767
D=A
@SP
A=M
M=D
@SP
M=M+1
@SP
M=M-1
A=M
D=M
@SP
M=M-1
A=M
A=M
D=A-D
@gt8
D;JGT
@ngt8
D;JLE
(gt8)
@SP
A=M
M=-1
@continue8
0;JEQ
(ngt8)
@SP
A=M
M=0
@continue8
0;JEQ
(continue8)
@SP
M=M+1

@32766
D=A
@SP
A=M
M=D
@SP
M=M+1
@32766
D=A
@SP
A=M
M=D
@SP
M=M+1
@SP
M=M-1
A=M
D=M
@SP
M=M-1
A=M
A=M
D=A-D
@gt9
D;JGT
@ngt9
D;JLE
(gt9)
@SP
A=M
M=-1
@continue9
0;JEQ
(ngt9)
@SP
A=M
M=0
@continue9
0;JEQ
(continue9)
@SP
M=M+1

@57
D=A
@SP
A=M
M=D
@SP
M=M+1
@31
D=A
@SP
A=M
M=D
@SP
M=M+1
@53
D=A
@SP
A=M
M=D
@SP
M=M+1
@SP
M=M-1
A=M
D=M
@SP
M=M-1
A=M
A=M
D=D+A
@SP
A=M
M=D
@SP
M=M+1

@112
D=A
@SP
A=M
M=D
@SP
M=M+1
@SP
M=M-1
A=M
D=M
@SP
M=M-1
A=M
A=M
D=A-D
@SP
A=M
M=D
@SP
M=M+1

@SP
M=M-1
A=M
D=M
D=-D
@SP
A=M
M=D
@SP
M=M+1

@SP
M=M-1
A=M
D=M
@SP
M=M-1
A=M
A=M
D=D&A
@SP
A=M
M=D
@SP
M=M+1

@82
D=A
@SP
A=M
M=D
@SP
M=M+1
@SP
M=M-1
A=M
D=M
@SP
M=M-1
A=M
A=M
D=D|A
@SP
A=M
M=D
@SP
M=M+1

@SP
M=M-1
A=M
D=M
D=!D
@SP
A=M
M=D
@SP
M=M+1

