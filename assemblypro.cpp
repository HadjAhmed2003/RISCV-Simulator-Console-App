#include<bits/stdc++.h>
using namespace std;
unordered_map<string, string> memory_locations; //variable name ---> address
unordered_map<string, string> data_values; //address ---> value
vector<string> program;
const bitset<32> zero(0); 
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

void executeProgram(){
    string line = program[0];
    int i=0;
    while(line != "ecall" && line != "EBREAK" && line != "FENCE"){ 
        std::stringstream ss(line);
        string temp;
        vector<string> inputs; 
        while(std::getline(ss, temp, ' ')){
            inputs.push_back(temp);
        }
        if(inputs.size()==1){ //in case we encounter a label we go to the next line; 
            i++; 
            line = program[i]; 
            continue; 
        }
        executeInstruction(inputs); 
    }
}

void executeInstruction(vector<string> inputs){
    string instruction = inputs[0]; 
    
}

void LUI(bitset<32>& rd, int imm){
    bitset<32> temp(imm); 
    for(int i=31; i>=12; i--){
        rd[i]=temp[i];
    }
    for(int i=11; i>=0; i--){
        rd[i]=0; 
    }
}

void AUIPC(bitset<32>& rd, int PC, int imm){
    int sum = PC+imm; 
    bitset<32> temp(sum); 
    for(int i=31; i>=12; i--){
        rd[i]=temp[i];
    }
    for(int i=11; i>=0; i--){
        rd[i]=0; 
    }
}

void AND(bitset<32>& rd, const bitset<32>& rs1, const bitset<32>& rs2){
    rd = rs1 & rs2; 
}

void OR(bitset<32>& rd, const bitset<32>& rs1, const bitset<32>& rs2){
    rd = rs1 | rs2; 
}

void XOR(bitset<32>& rd, const bitset<32>& rs1, const bitset<32>& rs2){
    rd = rs1 ^ rs2; 
}

void ANDI(bitset<32>& rd, const bitset<32>& rs1, int imm){
    bitset<32>temp(imm); 
    for(int i=0; i<32; i++){
        rd[i]=rs1[i]&temp[i];
    }
}

void ORI(bitset<32>& rd, const bitset<32>& rs1, int imm){
    bitset<32>temp(imm); 
    for(int i=0; i<32; i++){
        rd[i]=rs1[i]|temp[i];
    }
}

void XORI(bitset<32>& rd, const bitset<32>& rs1, int imm){
    bitset<32>temp(imm); 
    for(int i=0; i<32; i++){
        rd[i]=rs1[i]^temp[i];
    }
}

void ADD(bitset<32>& rd, const bitset<32>& rs1, const bitset<32>& rs2){
    int temp1 = (int)(rs1.to_ulong());
    int temp2 = (int)(rs2.to_ulong());
    int sum = temp1+temp2; 
    bitset<32> temp(sum); 
    for(int i=0; i<32; i++){
        rd[i]=temp[i];
    }
}

void SUB(bitset<32>& rd, const bitset<32>& rs1, const bitset<32>& rs2){
    int temp1 = (int)(rs1.to_ulong());
    int temp2 = (int)(rs2.to_ulong());
    int diff = temp1-temp2; 
    bitset<32> temp(diff); 
    for(int i=0; i<32; i++){
        rd[i]=temp[i];
    }
}

void ADDI(bitset<32>& rd, const bitset<32>& rs1, int imm){
    int temp = (int)(rs1.to_ulong());
    int sum = temp+imm; 
    bitset<32> temp(sum); 
    for(int i=0; i<32; i++){
        rd[i]=temp[i];
    }
}

int main(){
    return 0;
}