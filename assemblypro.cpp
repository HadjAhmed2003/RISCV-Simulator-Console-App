#include<bits/stdc++.h>
using namespace std;
unordered_map<string, string> memory_locations; //variable name ---> address
unordered_map<string, string> data_values; //address ---> value
vector<string> program;
bitset<32> zero(0); 
bitset<32> ra(0); 
bitset<32> sp; 
bitset<32> gp; 
bitset<32> tp(0); 
bitset<32> t0(0); 
bitset<32> t1(0); 
bitset<32> t2(0); 
bitset<32> s0(0); 
bitset<32> s1(0); 
bitset<32> a0(0); 
bitset<32> a1(0); 
bitset<32> a2(0); 
bitset<32> a3(0); 
bitset<32> a4(0); 
bitset<32> a5(0); 
bitset<32> a6(0); 
bitset<32> a7(0); 
bitset<32> s2(0); 
bitset<32> s3(0); 
bitset<32> s4(0); 
bitset<32> s5(0); 
bitset<32> s6(0); 
bitset<32> s7(0); 
bitset<32> s8(0); 
bitset<32> s9(0);
bitset<32> s10(0); 
bitset<32> s11(0);  
bitset<32> t3(0); 
bitset<32> t4(0); 
bitset<32> t5(0); 
bitset<32> t6(0); 
int PC; 

void LUI(bitset<32>*rd, int imm){
    bitset<32> temp(imm); 
    for(int i=31; i>=12; i--){
        (*rd)[i]=temp[i];
    }
    for(int i=11; i>=0; i--){
        (*rd)[i]=0; 
    }
}

void AUIPC(bitset<32>* rd, int PC, int imm){
    int sum = PC+imm; 
    bitset<32> temp(sum); 
    for(int i=31; i>=12; i--){
        (*rd)[i]=temp[i];
    }
    for(int i=11; i>=0; i--){
        (*rd)[i]=0; 
    }
}

void AND(bitset<32>* rd, const bitset<32>* rs1, const bitset<32>* rs2){
    (*rd) = (*rs1) & (*rs2); 
}

void OR(bitset<32>* rd, const bitset<32>* rs1, const bitset<32>* rs2){
    (*rd) = (*rs1) | (*rs2); 
}

void XOR(bitset<32>* rd, const bitset<32>* rs1, const bitset<32>* rs2){
    (*rd) = (*rs1) ^ (*rs2); 
}

void ANDI(bitset<32>* rd, const bitset<32>* rs1, int imm){
    bitset<32>temp(imm); 
    for(int i=0; i<32; i++){
        (*rd)[i]=(*rs1)[i] & temp[i];
    }
}

void ORI(bitset<32>* rd, const bitset<32>* rs1, int imm){
    bitset<32>temp(imm); 
    for(int i=0; i<32; i++){
        (*rd)[i]=(*rs1)[i] | temp[i];
    }
}

void XORI(bitset<32>* rd, const bitset<32>* rs1, int imm){
    bitset<32>temp(imm); 
    for(int i=0; i<32; i++){
        (*rd)[i]=(*rs1)[i] ^ temp[i];
    }
}

void ADD(bitset<32>* rd, const bitset<32>* rs1, const bitset<32>* rs2){
    int temp1 = (int)((*rs1).to_ulong());
    int temp2 = (int)((*rs2).to_ulong());
    int sum = temp1+temp2; 
    bitset<32> temp(sum); 
    for(int i=0; i<32; i++){
        (*rd)[i]=temp[i];
    }
}

void SUB(bitset<32>* rd, const bitset<32>* rs1, const bitset<32>* rs2){
    int temp1 = (int)((*rs1).to_ulong());
    int temp2 = (int)((*rs2).to_ulong());
    int diff = temp1-temp2; 
    bitset<32> temp(diff); 
    for(int i=0; i<32; i++){
        (*rd)[i]=temp[i];
    }
}

void ADDI(bitset<32>* rd, const bitset<32>* rs1, int imm){
    int rs = (int)((*rs1).to_ulong());
    int sum = rs+imm; 
    bitset<32> temp(sum); 
    for(int i=0; i<32; i++){
        (*rd)[i]=temp[i];
    }
}

void SRL(bitset<32>* rd, const bitset<32>* rs1, const bitset<32>* rs2){
    bitset<5> temp; 
    for(int i=0; i<5; i++){
        temp[i]= (*rs2)[i];
    }
    int shift_amount = temp.to_ulong(); 
    (*rd) = (*rs1) >> shift_amount; 
}

void SRA(bitset<32>* rd, const bitset<32>* rs1, const bitset<32>* rs2){
    bitset<5> temp; 
    for(int i=0; i<5; i++){
        temp[i]= (*rs2)[i];
    }
    int shift_amount = temp.to_ulong(); 
    signed int rs = (int)(*rs1).to_ulong();
    (*rd) = (rs) >> shift_amount;
}

void SLL(bitset<32>* rd, const bitset<32>* rs1, const bitset<32>* rs2){
    bitset<5> temp; 
    for(int i=0; i<5; i++){
        temp[i]= (*rs2)[i];
    }
    int shift_amount = temp.to_ulong(); 
    (*rd) = (*rs1) << shift_amount; 
}

void SLT(bitset<32>* rd, const bitset<32>* rs1, const bitset<32>* rs2){
    int first = (int)(*rs1).to_ulong();
    int second = (int)(*rs2).to_ulong();
    (*rd) = (first<second); 
}

void SLTU(bitset<32>* rd, const bitset<32>* rs1, const bitset<32>* rs2){
    unsigned int first = (*rs1).to_ulong();
    unsigned int second = (*rs2).to_ulong();
    (*rd) = (first<second); 
}

void SLTI(bitset<32>* rd, const bitset<32>* rs1, int imm){
    int first = (int)(*rs1).to_ulong();
    bitset<12> temp(imm); 
    int t = (int)temp.to_ulong();
    if(t==2048){
        t = -2048;
    }
    cout << t << endl;
    (*rd) = (first<t); 
}

void SLTIU(bitset<32>* rd, const bitset<32>* rs1, int imm){
    int first = (int)(*rs1).to_ulong();
    bitset<12> temp(imm); 
    unsigned int t = temp.to_ulong();
    (*rd) = (first<t); 
}

void SLLI(bitset<32>* rd, const bitset<32>* rs1, int imm){
    bitset<5> temp(imm); 
    int shift_amount = temp.to_ulong(); 
    (*rd) = (*rs1) << shift_amount; 
}

void SRLI(bitset<32>* rd, const bitset<32>* rs1, int imm){
    bitset<5> temp(imm); 
    int shift_amount = temp.to_ulong(); 
    (*rd) = (*rs1) >> shift_amount; 
}

void SRAI(bitset<32>* rd, const bitset<32>* rs1, int imm){
    bitset<5> temp(imm); 
    int shift_amount = temp.to_ulong(); 
    signed int rs = (int)(*rs1).to_ulong();
    (*rd) = (rs) >> shift_amount;
}

bitset<32>* getRegister(string operand){
    if(operand == "zero" || operand == "x0"){
        return &zero; 
    }
    if(operand == "ra" || operand == "x1"){
        return &ra; 
    }
    if(operand == "sp" || operand == "x2"){
        return &sp; 
    }
    if(operand == "gp" || operand == "x3"){
        return &gp; 
    }
    if(operand == "tp" || operand == "x4"){
        return &tp; 
    }
    if(operand == "t0" || operand == "x5"){
        return &t0; 
    }
    if(operand == "t1" || operand == "x6"){
        return &t1; 
    }
    if(operand == "t2" || operand == "x7"){
        return &t2; 
    }
    if(operand == "s0" || operand == "x8"){
        return &s0; 
    }
    if(operand == "s1" || operand == "x9"){
        return &s1; 
    }
    if(operand == "a0" || operand == "x10"){
        return &a0; 
    }
    if(operand == "a1" || operand == "x11"){
        return &a1; 
    }
    if(operand == "a2" || operand == "x12"){
        return &a2; 
    }
    if(operand == "a3" || operand == "x13"){
        return &a3; 
    }
    if(operand == "a4" || operand == "x14"){
        return &a4; 
    }
    if(operand == "a5" || operand == "x15"){
        return &a5; 
    }
    if(operand == "a6" || operand == "x16"){
        return &a6; 
    }
    if(operand == "a7" || operand == "x17"){
        return &a7; 
    }
    if(operand == "s2" || operand == "x18"){
        return &s2; 
    }
    if(operand == "s3" || operand == "x19"){
        return &s3; 
    }
    if(operand == "s4" || operand == "x20"){
        return &s4; 
    }
    if(operand == "s5" || operand == "x21"){
        return &s5; 
    }
    if(operand == "s6" || operand == "x22"){
        return &s6; 
    }
    if(operand == "s7" || operand == "x23"){
        return &s7; 
    }
    if(operand == "s8" || operand == "x24"){
        return &s8; 
    }
    if(operand == "s9" || operand == "x25"){
        return &s9; 
    }
    if(operand == "s10" || operand == "x26"){
        return &s10; 
    }
    if(operand == "s11" || operand == "x27"){
        return &s11; 
    }
    if(operand == "t3" || operand == "x28"){
        return &t3; 
    }
    if(operand == "t4" || operand == "x29"){
        return &t4; 
    }
    if(operand == "t5" || operand == "x30"){
        return &t5; 
    }
    if(operand == "t6" || operand == "x31"){
        return &t6; 
    }
    return NULL;
}

void ReadData(){
    string path; 
    cout << "Enter Data file path: ";
    cin >> path;
    fstream fin;
    string line;
    fin.open(path, ios::in);
    while(std::getline(fin, line))
    {
        std::stringstream ss(line);
        string temp;
        vector<string> inputs; 
        while(std::getline(ss, temp, ',')){
            inputs.push_back(temp);
        }
        memory_locations[inputs[0]] = inputs[1]; 
        int inc = 0; 
        int address = stoi(inputs[1]); 
        for(int i=2; i<inputs.size(); i++){
            int adr = address+inc; 
            data_values[to_string(adr)] = inputs[i];
            inc+=4; 
        } 
    } 
    fin.close();
}

void uploadProgram(){
    PC = stoi(data_values[memory_locations["PC"]]);
    string path; 
    cout << "Enter your program file: "; 
    cin >> path;
    fstream fin;
    string line;
    fin.open(path, ios::in);
    int inc = 0;
    while(std::getline(fin, line))
    {
        program.push_back(line); 
        std::stringstream ss(line);
        string temp;
        vector<string> inputs; 
        while(std::getline(ss, temp, ' ')){
            inputs.push_back(temp);
        }
        if(inputs.size()==1){
            memory_locations[inputs[0]] = to_string(PC+(inc*4)); //keeping the labels' locations. 
        }
        inc++; 
    }
    fin.close();
}

void executeInstruction(vector<string> inputs){
    string instruction = inputs[0];
    if(instruction=="srai" || instruction == "SRAI"){
        inputs[1].pop_back();
        bitset<32>* rd = getRegister(inputs[1]);
        inputs[2].pop_back();
        bitset<32>* rs1 = getRegister(inputs[2]);
        int imm = stoi(inputs[3]);
        SRAI(rd, rs1, imm);
        return; 
    }
    if(instruction=="srli" || instruction == "SRLI"){
        inputs[1].pop_back();
        bitset<32>* rd = getRegister(inputs[1]);
        inputs[2].pop_back();
        bitset<32>* rs1 = getRegister(inputs[2]);
        int imm = stoi(inputs[3]);
        SRLI(rd, rs1, imm);
        return; 
    }
    if(instruction=="slli" || instruction == "SLLI"){
        inputs[1].pop_back();
        bitset<32>* rd = getRegister(inputs[1]);
        inputs[2].pop_back();
        bitset<32>* rs1 = getRegister(inputs[2]);
        int imm = stoi(inputs[3]);
        SLLI(rd, rs1, imm);
        return; 
    }
    if(instruction=="sltiu" || instruction == "SLTIU"){
        inputs[1].pop_back();
        bitset<32>* rd = getRegister(inputs[1]);
        inputs[2].pop_back();
        bitset<32>* rs1 = getRegister(inputs[2]);
        int imm = stoi(inputs[3]);
        SLTIU(rd, rs1, imm);
        return; 
    }
    if(instruction=="slti" || instruction == "SLTI"){
        inputs[1].pop_back();
        bitset<32>* rd = getRegister(inputs[1]);
        inputs[2].pop_back();
        bitset<32>* rs1 = getRegister(inputs[2]);
        int imm = stoi(inputs[3]);
        SLTI(rd, rs1, imm);
        return; 
    }
    if(instruction=="sltu" || instruction == "SLTU"){
        inputs[1].pop_back();
        bitset<32>* rd = getRegister(inputs[1]);
        inputs[2].pop_back();
        bitset<32>* rs1 = getRegister(inputs[2]);
        bitset<32>* rs2 = getRegister(inputs[3]);
        SLTU(rd, rs1, rs2);
        return; 
    }
    if(instruction=="slt" || instruction == "SLT"){
        inputs[1].pop_back();
        bitset<32>* rd = getRegister(inputs[1]);
        inputs[2].pop_back();
        bitset<32>* rs1 = getRegister(inputs[2]);
        bitset<32>* rs2 = getRegister(inputs[3]);
        SLT(rd, rs1, rs2);
        return; 
    }
    if(instruction=="sll" || instruction == "SLL"){
        inputs[1].pop_back();
        bitset<32>* rd = getRegister(inputs[1]);
        inputs[2].pop_back();
        bitset<32>* rs1 = getRegister(inputs[2]);
        bitset<32>* rs2 = getRegister(inputs[3]);
        SLL(rd, rs1, rs2);
        return; 
    }
    if(instruction=="sra" || instruction == "SRA"){
        inputs[1].pop_back();
        bitset<32>* rd = getRegister(inputs[1]);
        inputs[2].pop_back();
        bitset<32>* rs1 = getRegister(inputs[2]);
        bitset<32>* rs2 = getRegister(inputs[3]);
        SRA(rd, rs1, rs2);
        return; 
    }
    if(instruction=="srl" || instruction == "SRL"){
        inputs[1].pop_back();
        bitset<32>* rd = getRegister(inputs[1]);
        inputs[2].pop_back();
        bitset<32>* rs1 = getRegister(inputs[2]);
        bitset<32>* rs2 = getRegister(inputs[3]);
        SRL(rd, rs1, rs2);
        return; 
    }
    if(instruction=="lui" || instruction == "LUI"){
        inputs[1].pop_back();
        bitset<32>* rd = getRegister(inputs[1]);
        int imm = stoi(inputs[2]); 
        LUI(rd, imm);
        return;
    }
    if(instruction=="auipc" || instruction == "AUIPC"){
        inputs[1].pop_back();
        bitset<32>* rd = getRegister(inputs[1]);
        int imm = stoi(inputs[2]); 
        AUIPC(rd, PC, imm);
        return; 
    }
    if(instruction=="and" || instruction == "AND"){
        inputs[1].pop_back();
        bitset<32>* rd = getRegister(inputs[1]);
        inputs[2].pop_back();
        bitset<32>* rs1 = getRegister(inputs[2]);
        bitset<32>* rs2 = getRegister(inputs[3]);
        AND(rd, rs1, rs2);
        return; 
    }
    if(instruction=="or" || instruction == "OR"){
        inputs[1].pop_back();
        bitset<32>* rd = getRegister(inputs[1]);
        inputs[2].pop_back();
        bitset<32>* rs1 = getRegister(inputs[2]);
        bitset<32>* rs2 = getRegister(inputs[3]);
        OR(rd, rs1, rs2);
        return; 
    }
    if(instruction=="xor" || instruction == "XOR"){
        inputs[1].pop_back();
        bitset<32>* rd = getRegister(inputs[1]);
        inputs[2].pop_back();
        bitset<32>* rs1 = getRegister(inputs[2]);
        bitset<32>* rs2 = getRegister(inputs[3]);
        XOR(rd, rs1, rs2);
        return; 
    }
    if(instruction=="andi" || instruction == "ANDI"){
        inputs[1].pop_back();
        bitset<32>* rd = getRegister(inputs[1]);
        inputs[2].pop_back();
        bitset<32>* rs1 = getRegister(inputs[2]);
        int imm = stoi(inputs[3]);
        ANDI(rd, rs1, imm);
        return; 
    }
    if(instruction=="ori" || instruction == "ORI"){
        inputs[1].pop_back();
        bitset<32>* rd = getRegister(inputs[1]);
        inputs[2].pop_back();
        bitset<32>* rs1 = getRegister(inputs[2]);
        int imm = stoi(inputs[3]);
        ORI(rd, rs1, imm);
        return; 
    }
    if(instruction=="xori" || instruction == "XORI"){
        inputs[1].pop_back();
        bitset<32>* rd = getRegister(inputs[1]);
        inputs[2].pop_back();
        bitset<32>* rs1 = getRegister(inputs[2]);
        int imm = stoi(inputs[3]);
        XORI(rd, rs1, imm);
        return; 
    }
    if(instruction=="add" || instruction == "ADD"){
        inputs[1].pop_back();
        bitset<32>* rd = getRegister(inputs[1]);
        inputs[2].pop_back();
        bitset<32>* rs1 = getRegister(inputs[2]);
        bitset<32>* rs2 = getRegister(inputs[3]);
        ADD(rd, rs1, rs2);
        return; 
    }
    if(instruction=="sub" || instruction == "SUB"){
        inputs[1].pop_back();
        bitset<32>* rd = getRegister(inputs[1]);
        inputs[2].pop_back();
        bitset<32>* rs1 = getRegister(inputs[2]);
        bitset<32>* rs2 = getRegister(inputs[3]);
        SUB(rd, rs1, rs2);
        return; 
    }
    if(instruction=="addi" || instruction == "ADDI"){
        inputs[1].pop_back();
        bitset<32>* rd = getRegister(inputs[1]);
        inputs[2].pop_back();
        bitset<32>* rs1 = getRegister(inputs[2]);
        int imm = stoi(inputs[3]);
        ADDI(rd, rs1, imm);
        return; 
    }
}

void executeProgram(){
    string line = program[0];
    int i=0;
    while(line != "ECALL" && line != "EBREAK" && line != "FENCE"){ 
        std::stringstream ss(line);
        string temp;
        vector<string> inputs; 
        while(std::getline(ss, temp, ' ')){
            inputs.push_back(temp);
        }
        if(inputs.size()==1){ //in case we encounter a label we go to the next line; 
            i++; 
            line = program[i]; 
            PC = stoi(memory_locations[inputs[0]])+4; 
            continue; 
        }
        executeInstruction(inputs); 
        i++; 
        line = program[i];
        PC+=4; 
    }
}

int main(){
    ReadData(); 
    uploadProgram();
    executeProgram();
    cout << t0 << endl; 
    return 0;
}