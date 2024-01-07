#include<iostream>
#include<string>
#include<fstream>

using namespace std;

enum CommandType{
    C_ARITHEMATIC,
    C_PUSH,
    C_POP,
    C_LABEL,
    C_GOTO,
    C_IF,
    C_FUNCTION,
    C_RETURN,
    C_CALL,
};


class Parser{

private : 
    ifstream file;
    string curr_instruction;
    string arg_first;
    string arg_second;

public : 
    Parser(string filename){
        file.open(filename);
    }

    bool hasMoreLines(){
        if(file.peek()!=EOF){
            return true;
        }
        else{
            return false;
        }
    }
    string advance(){
        getline(file,curr_instruction);
        while(!valid(curr_instruction)){
            getline(file,curr_instruction);
        }
        return curr_instruction;
    }


    bool valid(string instruction){
        if(instruction.empty() || (instruction[0]=='/' && instruction[1]=='/')){
            return false;
        }
        string temp=(string)"";
        int started=0;
        for(int i=0;i<curr_instruction.length();i++){
            if(!started && curr_instruction[i]==' '){
                continue;
            }
            else{
                started=1;
            }
            if(started &&  curr_instruction[i]!='/'){
                temp+=curr_instruction[i];
            }
            else if(started && curr_instruction[i]=='/'){
                break;
            }
        }
        if(temp!=""){
            curr_instruction=temp;
            return true;
        }
        return false;
    }

    CommandType commandType(){
        string temp=(string)"";
        for(int i=0;i<curr_instruction.size();i++){
            if(curr_instruction[i]==' '){
                break;
            }
            else{
                temp+=curr_instruction[i];
            }
        }
        if(temp=="push"){
            return C_PUSH;
        }
        if(temp=="pop"){
            return C_POP;
        }
        if(temp=="label"){
            return C_LABEL;
        }
        if(temp=="goto"){
            return C_GOTO;
        }
        if(temp=="if-goto"){
            return C_IF;
        }
        if(temp=="Function"){
            return C_FUNCTION;
        }
        if(temp=="Call"){
            return C_CALL;
        }
        if(temp=="return"){
            return C_RETURN;
        }
        else{
            return C_ARITHEMATIC;
        }
    }

    string arg1(){
        if(this->commandType()==C_ARITHEMATIC){
            return curr_instruction;
        }
        
        arg_first=(string)"";
        arg_second=(string)"";
        int started=0;
        int count=0;
        for(int i=0;i<curr_instruction.length();i++){
            if(count==0){
                if(curr_instruction[i]==' '){
                    count=1;
                }
                continue;
            }
            if(count==1){
                if(curr_instruction[i]!=' '){
                    arg_first+=curr_instruction[i];
                }
                else{
                    count=2;
                }
            }
            else if(count==2){
                if(curr_instruction[i]!=' '){
                    arg_second+=curr_instruction[i];
                }
                else{
                    count+=3;
                }
            }
        }
        return arg_first;
    }

    int arg2(){
        return stoi(arg_second);
    }
};

class CodeWriter{
    int val=0;

public : 

    CodeWriter(){
    }

    string writeArithematic(string command){
        val+=1;

        if(command!="neg" && command!="not"){
            string ret=(string)"";
            ret+="@SP\nM=M-1\nA=M\nD=M\n@SP\nM=M-1\nA=M\nA=M\n";

            if(command=="add"){
                ret+="D=D+A\n";
                ret+="@SP\nA=M\nM=D\n@SP\nM=M+1\n";

            }
            if(command=="sub"){
                ret+="D=A-D\n";
                ret+="@SP\nA=M\nM=D\n@SP\nM=M+1\n";
            }
            if(command=="eq"){

                ret+="D=D-A\n";
                ret+="@zero";
                ret+=to_string(val);
                ret+="\n";
                ret+="D;JEQ\n";

                ret+="@nonzero";
                ret+=to_string(val);
                ret+="\n";
                ret+="D;JNE\n";

                ret+="(zero";
                ret+=to_string(val);
                ret+=")\n";
                ret+="@SP\nA=M\nM=-1\n@continue";
                ret+=to_string(val);
                ret+="\n";
                ret+="0;JEQ\n";

                ret+="(nonzero";
                ret+=to_string(val);
                ret+=")\n";
                ret+="@SP\nA=M\nM=0\n@continue";
                ret+=to_string(val);
                ret+="\n";
                ret+="0;JEQ\n";

                ret+="(continue";
                ret+=to_string(val);
                ret+=")\n";
                ret+="@SP\nM=M+1\n";
            }
            if(command=="gt"){

                ret+="D=A-D\n";
                ret+="@gt";
                ret+=to_string(val);
                ret+="\n";
                ret+="D;JGT\n";

                ret+="@ngt";
                ret+=to_string(val);
                ret+="\n";
                ret+="D;JLE\n";

                ret+="(gt";
                ret+=to_string(val);
                ret+=")\n";
                ret+="@SP\nA=M\nM=-1\n@continue";
                ret+=to_string(val);
                ret+="\n";
                ret+="0;JEQ\n";

                ret+="(ngt";
                ret+=to_string(val);
                ret+=")\n";
                ret+="@SP\nA=M\nM=0\n@continue";
                ret+=to_string(val);
                ret+="\n";
                ret+="0;JEQ\n";

                ret+="(continue";
                ret+=to_string(val);
                ret+=")\n";
                ret+="@SP\nM=M+1\n";
            }
            if(command=="lt"){

                ret+="D=A-D\n";
                ret+="@lt";
                ret+=to_string(val);
                ret+="\n";
                ret+="D;JLT\n";

                ret+="@nlt";
                ret+=to_string(val);
                ret+="\n";
                ret+="D;JGE\n";

                ret+="(lt";
                ret+=to_string(val);
                ret+=")\n";
                ret+="@SP\nA=M\nM=-1\n@continue";
                ret+=to_string(val);
                ret+="\n";
                ret+="0;JEQ\n";

                ret+="(nlt";
                ret+=to_string(val);
                ret+=")\n";
                ret+="@SP\nA=M\nM=0\n@continue";
                ret+=to_string(val);
                ret+="\n";
                ret+="0;JEQ\n";

                ret+="(continue";
                ret+=to_string(val);
                ret+=")\n";
                ret+="@SP\nM=M+1\n";
            }
            if(command=="and"){
                ret+="D=D&A\n";
                ret+="@SP\nA=M\nM=D\n@SP\nM=M+1\n";
            }
            if(command=="or"){
                ret+="D=D|A\n";
                ret+="@SP\nA=M\nM=D\n@SP\nM=M+1\n";
            }

            return ret;
        }
        else{
            string ret=(string)"";
            ret+="@SP\nM=M-1\nA=M\nD=M\n";

            if(command=="not"){
                ret+="D=!D\n";
            }

            if(command=="neg"){
                ret+="D=-D\n";
            }
            ret+="@SP\nA=M\nM=D\n@SP\nM=M+1\n";

            return ret;
        }
    }

    string writePushPop(CommandType command , string segment , int index){
        string ret=(string)"";

        if(segment=="constant"){
            if(command==C_PUSH){

                ret+="@";
                ret+=to_string(index);
                ret+="\n";
                ret+="D=A\n@SP\nA=M\nM=D\n@SP\nM=M+1";
            }
            else{
                
            }
        }
        if(segment=="local"){
            if(command==C_POP){
                /*
                get the val from stack and put it in the segment 
                */
                ret+="@";
                ret+=to_string(index);
                ret+="\n";
                ret+="D=A\n";
                ret+="@LCL\n";
                ret+="M=M+D\n";
                ret+="@SP\n";
                ret+="M=M-1\n";
                ret+="A=M\n";
                ret+="D=M\n";
                ret+="@LCL\n";
                ret+="A=M\n";
                ret+="M=D\n";
                ret+="@";
                ret+=to_string(index);
                ret+="\n";
                ret+="D=A\n";
                ret+="@LCL\n";
                ret+="M=M-D\n";
            }
            else{

                // get from segment and push to stack
                ret+="@";
                ret+=to_string(index);
                ret+="\n";
                ret+="D=A\n";
                ret+="@LCL\n";
                ret+="M=M+D\n";
                ret+="A=M\n";
                ret+="D=M\n";
                ret+="@SP\n";
                ret+="A=M\n";
                ret+="M=D\n";
                ret+="@";
                ret+=to_string(index);
                ret+="\n";
                ret+="D=A\n";
                ret+="@LCL\n";
                ret+="M=M-D\n";
                ret+="@SP\n";
                ret+="M=M+1\n"; 
            }
        }
        if(segment=="argument"){
            if(command==C_POP){

                ret+="@";
                ret+=to_string(index);
                ret+="\n";
                ret+="D=A\n";
                ret+="@ARG\n";
                ret+="M=M+D\n";
                ret+="@SP\n";
                ret+="M=M-1\n";
                ret+="A=M\n";
                ret+="D=M\n";
                ret+="@ARG\n";
                ret+="A=M\n";
                ret+="M=D\n";
                ret+="@";
                ret+=to_string(index);
                ret+="\n";
                ret+="D=A\n";
                ret+="@ARG\n";
                ret+="M=M-D\n";
            }
            else{

                ret+="@";
                ret+=to_string(index);
                ret+="\n";
                ret+="D=A\n";
                ret+="@ARG\n";
                ret+="M=M+D\n";
                ret+="A=M\n";
                ret+="D=M\n";
                ret+="@SP\n";
                ret+="A=M\n";
                ret+="M=D\n";
                ret+="@";
                ret+=to_string(index);
                ret+="\n";
                ret+="D=A\n";
                ret+="@ARG\n";
                ret+="M=M-D\n";
                ret+="@SP\n";
                ret+="M=M+1\n";
            }
        }
        if(segment=="this"){
            if(command==C_POP){

                ret+="@";
                ret+=to_string(index);
                ret+="\n";
                ret+="D=A\n";
                ret+="@THIS\n";
                ret+="M=M+D\n";
                ret+="@SP\n";
                ret+="M=M-1\n";
                ret+="A=M\n";
                ret+="D=M\n";
                ret+="@THIS\n";
                ret+="A=M\n";
                ret+="M=D\n";
                ret+="@";
                ret+=to_string(index);
                ret+="\n";
                ret+="D=A\n";
                ret+="@THIS\n";
                ret+="M=M-D\n";
            }
            else{

                ret+="@";
                ret+=to_string(index);
                ret+="\n";
                ret+="D=A\n";
                ret+="@THIS\n";
                ret+="M=M+D\n";
                ret+="A=M\n";
                ret+="D=M\n";
                ret+="@SP\n";
                ret+="A=M\n";
                ret+="M=D\n";
                ret+="@";
                ret+=to_string(index);
                ret+="\n";
                ret+="D=A\n";
                ret+="@THIS\n";
                ret+="M=M-D\n";
                ret+="@SP\n";
                ret+="M=M+1\n";
            }
        }
        if(segment=="that"){
            if(command==C_POP){

                ret+="@";
                ret+=to_string(index);
                ret+="\n";
                ret+="D=A\n";
                ret+="@THAT\n";
                ret+="M=M+D\n";
                ret+="@SP\n";
                ret+="M=M-1\n";
                ret+="A=M\n";
                ret+="D=M\n";
                ret+="@THAT\n";
                ret+="A=M\n";
                ret+="M=D\n";
                ret+="@";
                ret+=to_string(index);
                ret+="\n";
                ret+="D=A\n";
                ret+="@THAT\n";
                ret+="M=M-D\n";
            }
            else{

                ret+="@";
                ret+=to_string(index);
                ret+="\n";
                ret+="D=A\n";
                ret+="@THAT\n";
                ret+="M=M+D\n";
                ret+="A=M\n";
                ret+="D=M\n";
                ret+="@SP\n";
                ret+="A=M\n";
                ret+="M=D\n";
                ret+="@";
                ret+=to_string(index);
                ret+="\n";
                ret+="D=A\n";
                ret+="@THAT\n";
                ret+="M=M-D\n";
                ret+="@SP\n";
                ret+="M=M+1\n";  
            }
        }
        if(segment=="static"){
            if(command==C_POP){
                /*
                static is from 16 to 255
                0->16;
                1->17;
                ...
                */
                index+=16;
                ret+="@SP\n";
                ret+="M=M-1\n";
                ret+="A=M\n";
                ret+="D=M\n";
                ret+="@";
                ret+=to_string(index);
                ret+="\n";
                ret+="M=D\n";
            }
            else{
                index+=16;
                ret+="@";
                ret+=to_string(index);
                ret+="\n";
                ret+="D=M\n";
                ret+="@SP\n";
                ret+="A=M\n";
                ret+="M=D\n";
                ret+="@SP\n";
                ret+="M=M+1\n";
            }
        }
        if(segment=="temp"){
            if(command==C_POP){
                /*
                temp is from 5 to 12
                0->5;
                1->6;
                ...
                */
                index+=5;
                ret+="@SP\n";
                ret+="M=M-1\n";
                ret+="A=M\n";
                ret+="D=M\n";
                ret+="@";
                ret+=to_string(index);
                ret+="\n";
                ret+="M=D\n";
            }
            else{
                index+=5;
                ret+="@";
                ret+=to_string(index);
                ret+="\n";
                ret+="D=M\n";
                ret+="@SP\n";
                ret+="A=M\n";
                ret+="M=D\n";
                ret+="@SP\n";
                ret+="M=M+1\n";  
            }
        }
        if(segment=="pointer"){

            if(index==0){
                if(command==C_PUSH){

                    ret+="@THIS\n";
                    ret+="D=M\n";
                    ret+="@SP\n";
                    ret+="A=M\n";
                    ret+="M=D\n";
                    ret+="@SP\n";
                    ret+="M=M+1\n";
                }
                else{
        
                    ret+="@SP\n";
                    ret+="M=M-1\n";
                    ret+="A=M\n";
                    ret+="D=M\n";
                    ret+="@THIS\n";
                    ret+="M=D\n";
                }
            }
            else{
                if(command==C_PUSH){

                    ret+="@THAT\n";
                    ret+="D=M\n";
                    ret+="@SP\n";
                    ret+="A=M\n";
                    ret+="M=D\n";
                    ret+="@SP\n";
                    ret+="M=M+1\n"; 
                }
                else{

                    ret+="@SP\n";
                    ret+="M=M-1\n";
                    ret+="A=M\n";
                    ret+="D=M\n";
                    ret+="@THAT\n";
                    ret+="M=D\n";
                }
            }   
        }
        return ret;
    }
};

int main(int argc , char**argv){
    
    if(argc!=2){
        cout<<"Usage is ./VMTranslator <input file>"<<endl;
        return 1;
    }

    string filename = argv[1];
    Parser p1(filename);
    

    string outfile = argv[1];
    int len=outfile.length();
    outfile[len-2]='a';
    outfile[len-1]='s';
    outfile+='m';
    CodeWriter c1;

    ofstream of;
    of.open(outfile);
    while(p1.hasMoreLines()){
        string instruction = p1.advance();
        CommandType ct=p1.commandType();

        if(ct==C_ARITHEMATIC){

            string arg = p1.arg1();
            string assembly_instruction = c1.writeArithematic(arg);
            of<<assembly_instruction<<endl;
        }
        else if(ct==C_POP){
            string arg1 = p1.arg1();
            int index=  p1.arg2();
            string assembly_instruction = c1.writePushPop(C_POP,arg1,index);
            of<<assembly_instruction<<endl;

        }
        else if(ct==C_PUSH){
            string arg1 = p1.arg1();
            int index=  p1.arg2();
            string assembly_instruction = c1.writePushPop(C_PUSH,arg1,index);
            of<<assembly_instruction<<endl;
        }
    }
    of.close();

    return 0;

}