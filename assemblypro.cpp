#include<bits/stdc++.h>
using namespace std;
unordered_map<string, int> memory_locations; 
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