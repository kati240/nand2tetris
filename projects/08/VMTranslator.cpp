#include<iostream>
#include<string>
#include<fstream>
#include<filesystem>
#include<dirent.h>

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
            if(!started && (curr_instruction[i]==' ' || curr_instruction[i]==9 || curr_instruction[i]=='\n')){
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
            while(temp[temp.size()-1]==' ' || temp[temp.size()-1]==9){
                temp.pop_back();
            }

            curr_instruction=temp;
            return true;
        }
        return false;
    }

    CommandType commandType(){
        string temp=(string)"";
        for(int i=0;i<curr_instruction.size();i++){
            if(curr_instruction[i]==' ' || curr_instruction[i]==9 || curr_instruction[i]=='\n'){
                break;
            }
            else{
                temp+=curr_instruction[i];
            }
        }

        while(!((temp.back()>='0' && temp.back()<='9') || (temp.back()>='a' && temp.back()<='z') || (temp.back()>='A' && temp.back()<='Z') )){
            temp.pop_back();
        }
        // cout<<temp<<endl;
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
        if(temp=="function"){
            return C_FUNCTION;
        }
        if(temp=="call"){
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
                if(curr_instruction[i]!=' ' && curr_instruction[i]!=9){
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

int calls;
class CodeWriter{
    int val=0;

public : 

    CodeWriter(){

    }

    CodeWriter(string &s){
        string output=(string)"";
        output+="@256\n";
        output+="D=A\n";
        output+="@SP\n";
        output+="M=D\n";
        output+="@Sys.init\n";
        output+="0;JMP\n";
        s+=output;

    }

    string writeArithematic(string command){
        
        while(command.size() &&   !((command.back()>='0' && command.back()<='9') || (command.back()>='a' && command.back()<='z') || (command.back()>='A' && command.back()<='Z') )){
            command.pop_back();
        }
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
                ret+="@SP\nA=M\nM=1\n@continue";
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
        else if(command=="neg" || command=="not"){
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
        else{

        }
    }

    string writePushPop(CommandType command , string segment ,string filename , int index){
        
        string ret=(string)"";

        if(segment=="constant"){
            if(command==C_PUSH){

                ret+="@";
                ret+=to_string(index);
                ret+="\n";
                ret+="D=A\n@SP\nA=M\nM=D\n@SP\nM=M+1\n";
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
                ret+="M=D+M\n";
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
                ret+="M=D+M\n";
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
                ret+="M=D+M\n";
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
                ret+="M=D+M\n";
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
                ret+="M=D+M\n";
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
                ret+="M=D+M\n";
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
                ret+="M=D+M\n";
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
                ret+="M=D+M\n";
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
            cout<<filename<<endl;
            if(command==C_POP){

                index+=16;
                ret+="@SP\n";
                ret+="M=M-1\n";
                ret+="A=M\n";
                ret+="D=M\n";
                ret+="@";
                ret+=filename;
                ret+=to_string(index);
                ret+="\n";
                ret+="M=D\n";
            }
            else{
                index+=16;
                ret+="@";
                ret+=filename;
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

    string witeLabel(string label){
        string output="(";
        output+=label;
        output+=")";
        output+='\n';
        return output;
    }

    string writeGoto(string label){

        string output="@";
        output+=label;
        output+='\n';
        output+="0;JMP\n";
        return output;

    }

    string writeIf(string label){

        string output=(string)"";
        output+="@SP\n";
        output+="M=M-1\n";
        output+="A=M\n";
        output+="D=M\n";
        output+="@";
        output+=label;
        output+='\n';
        output+="D;JGT\n";
        return output;

    }

    string writeFunction(string function_name, int n_vars){
        string output=(string)"";
        output+="(";
        output+=function_name;
        output+=")\n";
        for(int i=0;i<n_vars;i++){

            output+="@0\n";
            output+="D=A\n";
            output+="@SP\n";
            output+="A=M\n";
            output+="M=D\n";
            output+="@SP\n";
            output+="M=M+1\n";

        }

        return output;

    }

    string writeCall(string function_name, int n_vars){
        string output=(string)"";
        output+="@RET_ADDR";
        output+=to_string(calls);
        output+='\n';
        output+="D=A\n";
        output+="@SP\n";
        output+="A=M\n";
        output+="M=D\n";
        output+="@SP\n";
        output+="M=M+1\n";

        output+="@LCL\n";
        output+="D=M\n";
        output+="@SP\n";
        output+="A=M\n";
        output+="M=D\n";
        output+="@SP\n";
        output+="M=M+1\n";

        output+="@ARG\n";
        output+="D=M\n";
        output+="@SP\n";
        output+="A=M\n";
        output+="M=D\n";
        output+="@SP\n";
        output+="M=M+1\n";

        output+="@THIS\n";
        output+="D=M\n";
        output+="@SP\n";
        output+="A=M\n";
        output+="M=D\n";
        output+="@SP\n";
        output+="M=M+1\n";

        output+="@THAT\n";
        output+="D=M\n";
        output+="@SP\n";
        output+="A=M\n";
        output+="M=D\n";
        output+="@SP\n";
        output+="M=M+1\n";

        output+="@SP\n";
        output+="D=M\n";
        output+="@LCL\n";
        output+="M=D\n";

        output+="@SP\n";
        output+="D=M\n";
        for(int i=0;i<5+n_vars;i++){
            output+="D=D-1\n";
        }
        output+="@ARG\n";
        output+="M=D\n";

        output+="@";
        output+=function_name;
        output+='\n';
        output+="0;JMP\n";

        output+="(";
        output+="RET_ADDR";
        output+=to_string(calls);
        output+=")\n";

        calls+=1;
        return output;

    }

    string writeReturn (){

        string output=(string)"";
        output+="@LCL\n";
        output+="D=M\n";
        output+="@R14\n";
        output+="M=D\n";

        output+="@R14\n";
        output+="D=M\n";
        output+="@5\n";
        output+="A=D-A\n";
        output+="D=M\n";
        output+="@R13\n";
        output+="M=D\n";

        output+="@SP\n";
        output+="M=M-1\n";
        output+="A=M\n";
        output+="D=M\n";
        output+="@ARG\n";
        output+="A=M\n";
        output+="M=D\n";

        output+="@ARG\n";
        output+="D=M\n";
        output+="@SP\n";
        output+="M=D\n";
        output+="M=M+1\n";

        output+="@R14\n";
        output+="D=M\n";
        output+="@1\n";
        output+="A=D-A\n";
        output+="D=M\n";
        output+="@THAT\n";
        output+="M=D\n";

        output+="@R14\n";
        output+="D=M\n";
        output+="@2\n";
        output+="A=D-A\n";
        output+="D=M\n";
        output+="@THIS\n";
        output+="M=D\n";

        output+="@R14\n";
        output+="D=M\n";
        output+="@3\n";
        output+="A=D-A\n";
        output+="D=M\n";
        output+="@ARG\n";
        output+="M=D\n";


        output+="@R14\n";
        output+="D=M\n";
        output+="@4\n";
        output+="A=D-A\n";
        output+="D=M\n";
        output+="@LCL\n";
        output+="M=D\n";

        output+="@R13\n";
        output+="A=M\n";
        output+="0;JMP\n";

        return output;

    }

};


void fileParser(string filename, string& fName ,string& outfile){
    Parser p1(filename);
    
    CodeWriter c1;

    while(p1.hasMoreLines()){
        string instruction = p1.advance();
        CommandType ct=p1.commandType();

        if(ct==C_ARITHEMATIC){

            string arg = p1.arg1();
            string assembly_instruction = c1.writeArithematic(arg);
            outfile+=assembly_instruction;
        }
        else if(ct==C_POP){
            string arg1 = p1.arg1();
            int index=  p1.arg2();
            string assembly_instruction = c1.writePushPop(C_POP,arg1,fName,index);
            outfile+=assembly_instruction;

        }
        else if(ct==C_PUSH){
            string arg1 = p1.arg1();
            int index=  p1.arg2();
            cout<<fName<<endl;
            string assembly_instruction = c1.writePushPop(C_PUSH,arg1,fName,index);
            outfile+=assembly_instruction;
        }
        else if(ct==C_LABEL){
            string arg1 = p1.arg1();
            
            while(!((arg1.back()>='0' && arg1.back()<='9') || (arg1.back()>='a' && arg1.back()<='z') || (arg1.back()>='A' && arg1.back()<='Z') )){
                arg1.pop_back();

            }
            string assembly_instruction = c1.witeLabel(arg1);
            outfile+=assembly_instruction;
        }
        else if(ct==C_IF){
            string arg1 = p1.arg1();
            string assembly_instruction = c1.writeIf(arg1);
            outfile+=assembly_instruction;
        }
        else if(ct==C_GOTO){
            string arg1 = p1.arg1();
            string assembly_instruction = c1.writeGoto(arg1);
            outfile+=assembly_instruction;
        }
        else if(ct==C_FUNCTION){
            string arg1 = p1.arg1();
            int arg2=p1.arg2();
            string assembly_instruction = c1.writeFunction(arg1,arg2);
            outfile+=assembly_instruction;
        }
        else if(ct==C_RETURN){
            string arg1 = p1.arg1();
            string assembly_instruction = c1.writeReturn();
            outfile+=assembly_instruction;
        }
        else if(ct==C_CALL){
            string arg1 = p1.arg1();
            int arg2=p1.arg2();
            string assembly_instruction = c1.writeCall(arg1,arg2);
            outfile+=assembly_instruction;
        }
    }

    return ;

}


void recursiveParse(const char *  entry, string& ans){
    DIR* dir = opendir(entry);
    if(dir==NULL){
        return ;
    }
    
    struct dirent* entity;
    entity=readdir(dir);
    while(entity!=NULL){
        

        if(entity->d_type==DT_DIR ){
            if(strcmp(entity->d_name,".")!=0  && strcmp(entity->d_name,"..")!=0 ){
                char path[100]= {0};
                strcat(path, entry);
                strcat(path, "/");
                strcat(path , entity->d_name);
                recursiveParse(path , ans);
            }
        }
        else{  
            char path[100]= {0};
            strcat(path, entry);
            strcat(path, "/");
            strcat(path , entity->d_name);
            string filename=(string)"";
            filename+=entity->d_name;
            cout<<filename<<endl;
            fileParser(path,filename,ans);
        }
        entity=readdir(dir);
    }
}




int main(int argc , char**argv){
    
    if(argc!=2){
        cout<<"Usage is ./VMTranslator <input file or directory>"<<endl;
        return 1;
    }
    string filename = argv[1];
    
    
    if(filesystem::is_directory(filename)){
        char* outfile = {argv[1]};
        char * infile = {argv[1]};
    
        string ans=(string)"";
        CodeWriter c1(ans);

        recursiveParse(infile , ans);

        strcat(outfile, ".asm");
        ofstream of;
        of.open(outfile);

        of<<ans<<endl;

    }
    else{
        string outfile = argv[1];
        int len=outfile.length();
        outfile[len-2]='a';
        outfile[len-1]='s';
        outfile+='m';


        string ans=(string)"";
        CodeWriter c1(ans);

        fileParser(filename,filename,ans);

        ofstream of;
        of.open(outfile);
        of<<ans<<endl;
    }

    return 0;

}