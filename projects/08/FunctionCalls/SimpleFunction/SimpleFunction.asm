(SimpleFunction.test)
@0
D=A
@SP
A=M
M=D
@SP
M=M+1
@0
D=A
@SP
A=M
M=D
@SP
M=M+1

@0
D=A
@LCL
M=M+D
A=M
D=M
@SP
A=M
M=D
@0
D=A
@LCL
M=M-D
@SP
M=M+1

@1
D=A
@LCL
M=M+D
A=M
D=M
@SP
A=M
M=D
@1
D=A
@LCL
M=M-D
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

@0
D=A
@ARG
M=M+D
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

@1
D=A
@ARG
M=M+D
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
@ARG
A=M
M=D
D=A
@SP
M=D
M=M+1
@LCL
M=M-1
A=M
D=M
@THAT
M=D
@LCL
M=M-1
A=M
D=M
@THIS
M=D
@LCL
M=M-1
A=M
D=M
@ARG
M=D
@LCL
M=M-1
A=M
D=M
@LCL
M=D
@LCL
A=M
A=A-1
A=M

