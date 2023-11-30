#include<iostream>
#include<fstream>
#include<string>
#include<map>

using namespace std;

enum InstructionType{
    A_INSTRUCTION,
    C_INSTRUCTION,
    L_INSTRUCTION, // label  eg. (LOOP)
};

class Parser{
    ifstream file;
    int curr_line;
    InstructionType instruction_type;
    string curr_instruction="";
public:

    Parser(string fileName){
        // open the file
        file.open(fileName);
        curr_line=-1;
    }

    // check if there is more work to do 
    bool hasMoreLines(){
        return file.peek()!=EOF;
    }

    // advances the current instruction line to next line and returns the next instruction
    string advance(){
        getline(file, curr_instruction);
        curr_line+=1;

        while(!valid(curr_instruction)){
            getline(file, curr_instruction);
        }
        setType(curr_instruction);
        return curr_instruction;
    }

    // return the current instruction type
    InstructionType instructionType(){
        return instruction_type;
    }

    // returns the symbol in current instruction
    // used for A instruction and L instruction 
    string symbol(){
        string symbol=(string)"";
        if(instruction_type==L_INSTRUCTION){
            for(int i=1;i<curr_instruction.length()-1;i++){
                symbol+=curr_instruction[i];
            }
        }
        if(instruction_type==A_INSTRUCTION){
            for(int i=1;i<curr_instruction.length();i++){
                symbol+=curr_instruction[i];
            }   
        }
        return symbol;
    }

    // returns the destination field
    string dest(){
        string dest=(string)"";

        // is just the string before = sign 
        if(instruction_type==C_INSTRUCTION){
            int equal_sign_index=0;
            
            for(int i=0;i<curr_instruction.length();i++){
                if(curr_instruction[i]=='='){
                    equal_sign_index=i;
                    break;
                }
            }
            for(int i=0;i<equal_sign_index;i++){
                dest+=curr_instruction[i];
            }
        }
        return dest;
    }

    // returns the computation field
    string comp(){

        // string between = and ; sign 
        string comp=(string)"";
        if(instruction_type==C_INSTRUCTION){
            int equal_sign_index=-1;
            int colon_sign_index=curr_instruction.length();
            
            for(int i=0;i<curr_instruction.length();i++){
                if(curr_instruction[i]=='='){
                    equal_sign_index=i;
                    break;
                }
            }
            for(int i=0;i<curr_instruction.length();i++){
                if(curr_instruction[i]==';'){
                    colon_sign_index=i;
                    break;
                }
            }
            for(int i=equal_sign_index+1;i<colon_sign_index;i++){
                comp+=curr_instruction[i];
            }
        }
        return comp;
    }

    // returns the jump field
    string jump(){

        // is the string after the ; 
        string jump=(string)"";

        if(instruction_type==C_INSTRUCTION){
            int colon_sign_index=curr_instruction.length();
            
            for(int i=0;i<curr_instruction.length();i++){
                if(curr_instruction[i]==';'){
                    colon_sign_index=i;
                    break;
                }
            }
            for(int i=colon_sign_index+1;i<curr_instruction.length();i++){
                jump+=curr_instruction[i];
            }
        }
        return jump;
    }

    int getCurrLine(){
        return curr_line;
    }

    bool valid(string instruction){
        if(instruction.empty() || (instruction[0]=='/' && instruction[1]=='/')){
            return false;
        }
        string temp=(string)"";
        int started=0;
        for(int i=0;i<curr_instruction.length();i++){
            if(curr_instruction[i]==' '){
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

    void setType(string instruction){
        if(instruction[0]=='@'){
            instruction_type=A_INSTRUCTION;
        }
        else if(instruction[0]=='('){
            instruction_type=L_INSTRUCTION;
            curr_line-=1; // they dont count
        }
        else{
            instruction_type=C_INSTRUCTION;
        }
        return;
    }

    InstructionType getInstructionType(){
        return instruction_type;
    }

    ~Parser(){
        file.close();
    }
};

class Code{
    map<string ,string>destMap;
    map<string ,string>compMap;
    map<string ,string>jumpMap;

public :
    Code(){
        destMap[""]="000";
        destMap["M"]="001";
        destMap["D"]="010";
        destMap["A"]="100";
        destMap["DM"]="011";
        destMap["MD"]="011";
        destMap["AM"]="101";
        destMap["MA"]="101";
        destMap["AD"]="110";
        destMap["DA"]="110";
        destMap["ADM"]="111";

        compMap["0"]="101010";
        compMap["1"]="111111";
        compMap["-1"]="111010";
        compMap["D"]="001100";
        compMap["A"]="110000";
        compMap["M"]="110000";
        compMap["!D"]="001101";
        compMap["!A"]="110001";
        compMap["!M"]="110001";
        compMap["-D"]="001111";
        compMap["-A"]="110011";
        compMap["-M"]="110011";
        compMap["D+1"]="011111";
        compMap["A+1"]="110111";
        compMap["M+1"]="110111";
        compMap["D-1"]="001110";
        compMap["A-1"]="110010";
        compMap["M-1"]="110010";
        compMap["D+A"]="000010";
        compMap["D+M"]="000010";
        compMap["D-A"]="010011";
        compMap["D-M"]="010011";
        compMap["A-D"]="000111";
        compMap["M-D"]="000111";
        compMap["D&A"]="000000";
        compMap["D&M"]="000000";
        compMap["D|A"]="010101";
        compMap["D|M"]="010101";

        jumpMap[""]="000";
        jumpMap["JGT"]="001";
        jumpMap["JEQ"]="010";
        jumpMap["JGE"]="011";
        jumpMap["JLT"]="100";
        jumpMap["JNE"]="101";
        jumpMap["JLE"]="110";
        jumpMap["JMP"]="111";

    }

    // returns the binary given the destination 
    string dest(string dest){
        return destMap[dest];
    }

    // returns the binary if the parsed computation
    string comp(string comp){
        return compMap[comp];
    }

    // returns the binary of the jump 
    string jump(string jump){
        return jumpMap[jump];
    }
};


class SymbolTable{
    map<string,int>symbolTable;

public :

    SymbolTable(){
        symbolTable["R0"]= 0;
        symbolTable["R1"]= 1;
        symbolTable["R2"]= 2;
        symbolTable["R3"]= 3;
        symbolTable["R4"]= 4;
        symbolTable["R5"]= 5;
        symbolTable["R6"]= 6;
        symbolTable["R7"]= 7;
        symbolTable["R8"]= 8;
        symbolTable["R9"]= 9;
        symbolTable["R10"]= 10;
        symbolTable["R11"]= 11;
        symbolTable["R12"]= 12;
        symbolTable["R13"]= 13;
        symbolTable["R14"]= 14;
        symbolTable["R15"]= 15;
        symbolTable["SCREEN"]= 16384;
        symbolTable["KBD"]= 24576;
        symbolTable["SP"]=0 ;
        symbolTable["LCL"]= 1;
        symbolTable["ARG"]=2 ;
        symbolTable["THIS"]= 3;
        symbolTable["THAT"]= 4;
    }
    void addEntry(string symbol , int address){
        symbolTable[symbol]=address;
        return;
    }

    bool contains(string symbol){
        return symbolTable.find(symbol)!=symbolTable.end();
    }

    int getAddress(string symbol){
        return symbolTable[symbol];
    }
};

string intToBinaryString(int a){
    int temp  = a;
    string ans="0000000000000000";
    long long int curr=1;
    int mult=0;
    while(mult<15){
        if(temp%2==1){
            ans[15-mult]='1';
        }
        temp/=2;
        mult+=1;
    }
    return ans;
}

string stringIntToBinaryString(string a){
    int temp  = stoi(a);
    return intToBinaryString(temp);
}

int main(int argc , char **argv){

    if(argc!=2){
        cout<<"Usage is ./HackAssembler <input file>"<<endl;
        return 1;
    }

    // call the Parser constructor with the fileName given in the args 
    string fileName=argv[1];
    Parser p1 =Parser(fileName);

    SymbolTable st=SymbolTable();

    // first pass
    while(p1.hasMoreLines()){
        string instruction = p1.advance();
        InstructionType type = p1.getInstructionType();
        if(type==A_INSTRUCTION){

        }
        if(type==L_INSTRUCTION){
            string symbol = p1.symbol();
            int addresss = p1.getCurrLine()+1;

            if(!st.contains(symbol)){
                st.addEntry(symbol , addresss);
            }
        }
        if(type==C_INSTRUCTION){
            
        }
    }

    // second pass 
    Parser p =Parser(fileName);
    Code c = Code();


    // naming the output file
    string outFile=fileName;
    outFile[fileName.length()-3]='h';
    outFile[fileName.length()-2]='a';
    outFile[fileName.length()-1]='c';
    outFile+='k';
    ofstream of;
    of.open(outFile);


    int address=16; // start of the variables in memory

    while(p.hasMoreLines()){
        string binary_instruciton=(string)"";
        string instruction = p.advance();
        InstructionType type = p.getInstructionType();


        if(type==A_INSTRUCTION){

            string symbol = p.symbol();
            if(symbol[0]<'0' || symbol[0]>'9'){
                if(!st.contains(symbol)){
                    st.addEntry(symbol,address);
                    address+=1;
                }
                binary_instruciton=intToBinaryString(st.getAddress(symbol));
            }
            else{
                binary_instruciton=stringIntToBinaryString(symbol);
            }
        }
        if(type==L_INSTRUCTION){
            
        }
        if(type==C_INSTRUCTION){
            string dest=p.dest();
            string comp = p.comp();
            string jump = p.jump();

            char m_used='0';

            for(int i=0;i<comp.length();i++){
                if(comp[i]=='M'){
                    m_used='1';
                    break;
                }
            }
            binary_instruciton+="111";
            binary_instruciton+=m_used;
            binary_instruciton+=c.comp(comp);
            binary_instruciton+=c.dest(dest);
            binary_instruciton+=c.jump(jump);   
        }
        if(binary_instruciton!=""){
            of<<binary_instruciton;
            of<<endl;
        } 
    }
    of.close();
    return 0;
}