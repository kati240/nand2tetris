@256
D=A
@SP
M=D
@Sys.init
0;JMP
@SP
M=M-1
A=M
D=M
@SP
M=M-1
A=M
A=M
(Class1.set)
@0
D=A
@ARG
M=D+M
A=M
D=M
@SP
A=M
M=D
@0
D=A
@ARG
M=M-D
@SP
M=M+1
@SP
M=M-1
A=M
D=M
@Class1.vm16
M=D
@1
D=A
@ARG
M=D+M
A=M
D=M
@SP
A=M
M=D
@1
D=A
@ARG
M=M-D
@SP
M=M+1
@SP
M=M-1
A=M
D=M
@Class1.vm17
M=D
@0
D=A
@SP
A=M
M=D
@SP
M=M+1
@LCL
D=M
@R14
M=D
@R14
D=M
@5
A=D-A
D=M
@R13
M=D
@SP
M=M-1
A=M
D=M
@ARG
A=M
M=D
@ARG
D=M
@SP
M=D
M=M+1
@R14
D=M
@1
A=D-A
D=M
@THAT
M=D
@R14
D=M
@2
A=D-A
D=M
@THIS
M=D
@R14
D=M
@3
A=D-A
D=M
@ARG
M=D
@R14
D=M
@4
A=D-A
D=M
@LCL
M=D
@R13
A=M
0;JMP
@SP
M=M-1
A=M
D=M
@SP
M=M-1
A=M
A=M
(Class1.get)
@Class1.vm16
D=M
@SP
A=M
M=D
@SP
M=M+1
@Class1.vm17
D=M
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
@LCL
D=M
@R14
M=D
@R14
D=M
@5
A=D-A
D=M
@R13
M=D
@SP
M=M-1
A=M
D=M
@ARG
A=M
M=D
@ARG
D=M
@SP
M=D
M=M+1
@R14
D=M
@1
A=D-A
D=M
@THAT
M=D
@R14
D=M
@2
A=D-A
D=M
@THIS
M=D
@R14
D=M
@3
A=D-A
D=M
@ARG
M=D
@R14
D=M
@4
A=D-A
D=M
@LCL
M=D
@R13
A=M
0;JMP
@SP
M=M-1
A=M
D=M
@SP
M=M-1
A=M
A=M
(Sys.init)
@6
D=A
@SP
A=M
M=D
@SP
M=M+1
@8
D=A
@SP
A=M
M=D
@SP
M=M+1
@RET_ADDR0
D=A
@SP
A=M
M=D
@SP
M=M+1
@LCL
D=M
@SP
A=M
M=D
@SP
M=M+1
@ARG
D=M
@SP
A=M
M=D
@SP
M=M+1
@THIS
D=M
@SP
A=M
M=D
@SP
M=M+1
@THAT
D=M
@SP
A=M
M=D
@SP
M=M+1
@SP
D=M
@LCL
M=D
@SP
D=M
D=D-1
D=D-1
D=D-1
D=D-1
D=D-1
D=D-1
D=D-1
@ARG
M=D
@Class1.set
0;JMP
(RET_ADDR0)
@SP
M=M-1
A=M
D=M
@5
M=D
@23
D=A
@SP
A=M
M=D
@SP
M=M+1
@15
D=A
@SP
A=M
M=D
@SP
M=M+1
@RET_ADDR1
D=A
@SP
A=M
M=D
@SP
M=M+1
@LCL
D=M
@SP
A=M
M=D
@SP
M=M+1
@ARG
D=M
@SP
A=M
M=D
@SP
M=M+1
@THIS
D=M
@SP
A=M
M=D
@SP
M=M+1
@THAT
D=M
@SP
A=M
M=D
@SP
M=M+1
@SP
D=M
@LCL
M=D
@SP
D=M
D=D-1
D=D-1
D=D-1
D=D-1
D=D-1
D=D-1
D=D-1
@ARG
M=D
@Class2.set
0;JMP
(RET_ADDR1)
@SP
M=M-1
A=M
D=M
@5
M=D
@RET_ADDR2
D=A
@SP
A=M
M=D
@SP
M=M+1
@LCL
D=M
@SP
A=M
M=D
@SP
M=M+1
@ARG
D=M
@SP
A=M
M=D
@SP
M=M+1
@THIS
D=M
@SP
A=M
M=D
@SP
M=M+1
@THAT
D=M
@SP
A=M
M=D
@SP
M=M+1
@SP
D=M
@LCL
M=D
@SP
D=M
D=D-1
D=D-1
D=D-1
D=D-1
D=D-1
@ARG
M=D
@Class1.get
0;JMP
(RET_ADDR2)
@RET_ADDR3
D=A
@SP
A=M
M=D
@SP
M=M+1
@LCL
D=M
@SP
A=M
M=D
@SP
M=M+1
@ARG
D=M
@SP
A=M
M=D
@SP
M=M+1
@THIS
D=M
@SP
A=M
M=D
@SP
M=M+1
@THAT
D=M
@SP
A=M
M=D
@SP
M=M+1
@SP
D=M
@LCL
M=D
@SP
D=M
D=D-1
D=D-1
D=D-1
D=D-1
D=D-1
@ARG
M=D
@Class2.get
0;JMP
(RET_ADDR3)
(END)
@END
0;JMP
@SP
M=M-1
A=M
D=M
@SP
M=M-1
A=M
A=M
(Class2.set)
@0
D=A
@ARG
M=D+M
A=M
D=M
@SP
A=M
M=D
@0
D=A
@ARG
M=M-D
@SP
M=M+1
@SP
M=M-1
A=M
D=M
@Class2.vm16
M=D
@1
D=A
@ARG
M=D+M
A=M
D=M
@SP
A=M
M=D
@1
D=A
@ARG
M=M-D
@SP
M=M+1
@SP
M=M-1
A=M
D=M
@Class2.vm17
M=D
@0
D=A
@SP
A=M
M=D
@SP
M=M+1
@LCL
D=M
@R14
M=D
@R14
D=M
@5
A=D-A
D=M
@R13
M=D
@SP
M=M-1
A=M
D=M
@ARG
A=M
M=D
@ARG
D=M
@SP
M=D
M=M+1
@R14
D=M
@1
A=D-A
D=M
@THAT
M=D
@R14
D=M
@2
A=D-A
D=M
@THIS
M=D
@R14
D=M
@3
A=D-A
D=M
@ARG
M=D
@R14
D=M
@4
A=D-A
D=M
@LCL
M=D
@R13
A=M
0;JMP
@SP
M=M-1
A=M
D=M
@SP
M=M-1
A=M
A=M
(Class2.get)
@Class2.vm16
D=M
@SP
A=M
M=D
@SP
M=M+1
@Class2.vm17
D=M
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
@LCL
D=M
@R14
M=D
@R14
D=M
@5
A=D-A
D=M
@R13
M=D
@SP
M=M-1
A=M
D=M
@ARG
A=M
M=D
@ARG
D=M
@SP
M=D
M=M+1
@R14
D=M
@1
A=D-A
D=M
@THAT
M=D
@R14
D=M
@2
A=D-A
D=M
@THIS
M=D
@R14
D=M
@3
A=D-A
D=M
@ARG
M=D
@R14
D=M
@4
A=D-A
D=M
@LCL
M=D
@R13
A=M
0;JMP
