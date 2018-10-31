#include <iostream>
#include "cipher_code.hpp"
using std::string;
// #define DEBUG
int pc_1[56] = {
	57, 49, 41, 33, 25, 17, 9,
	1, 58, 50, 42, 34, 26, 18,
	10, 2, 59, 51, 43, 35, 27,
	19, 11, 3, 60, 52, 44, 36,
	63, 55, 47, 39, 31, 23, 15,
	7, 62, 54, 46, 38, 30, 22,
	14, 6, 61, 53, 45, 37, 29,
	21, 13, 5, 28, 20, 12, 4,
};

int pc_2[48] = {
	14, 17, 11, 24, 1, 5,
	3, 28, 15, 6, 21, 10,
	23, 19, 12, 4, 26, 8,
	16, 7, 27, 20, 13, 2,
	41, 52, 31, 37, 47, 55,
	30, 40, 51, 45, 33, 48,
	44, 49, 39, 56, 34, 53,
	46, 42, 50, 36, 29, 32,
};

int displacements[16]={1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1};

CipherCode* CipherCode::cipherCode = nullptr;

CipherCode* CipherCode::getInstance(){
	if(cipherCode == nullptr) {
		cipherCode = new CipherCode();
	}
	return cipherCode;
}
void CipherCode::getKeys(string key, string keys[]) {
	for(int i=1;i<=16;i++){
		keys[i-1] = getCipherCodeN(i, key);
#ifdef DEBUG
		std::cout<<keys[i-1]<<std::endl;
#endif
	}
}
string CipherCode::getCipherCodeN(int round, string key) {
	int CNDN[56];
	getCNDN(round, CNDN);
	return replace(CNDN, key);
}

void CipherCode::getCNDN(int round, int CNDN[]){
	int CN[28], DN[28];
	getCN(round, CN);
	getDN(round, DN);
	for(int i=0;i<28;i++){
		CNDN[i]=CN[i];
		CNDN[i+28]=DN[i];
#ifdef DEBUG
		std::cout<<CNDN[i]<<std::endl;
#endif
	}
}

void CipherCode::getCN(int round, int CN[]){
	int displacement = getDisplacements(round);
	for(int i=displacement;i<28;i++){
		CN[i-displacement]=pc_1[i];
	}
	for(int i=0;i<displacement;i++){
		CN[28-displacement+i] = pc_1[i];
	}
}

void CipherCode::getDN(int round, int DN[]){
	int displacement = getDisplacements(round);
	for(int i=28+displacement;i<56;i++){
		DN[i-28-displacement] = pc_1[i];
	}
	for(int i=28;i<28+displacement;i++){
		DN[i-displacement] = pc_1[i];
	}
}

int CipherCode::getDisplacements(int round){
	int displacement = 0;
	for(int i=0;i<round;i++){
		displacement+=displacements[i];
	}
	return displacement;
}

string CipherCode::replace(int CNDN[], string key){
	string initial_sipher_code_replace = "";
	for(int i=0;i<56;i++){
		initial_sipher_code_replace += key[CNDN[i]-1];
	}
#ifdef DEBUG
	std::cout<<initial_sipher_code_replace<<std::endl;
#endif
	string cipher_code_replace = "";
	for(int i=0;i<48;i++){
		cipher_code_replace += initial_sipher_code_replace[pc_2[i]-1];
	}
#ifdef DEBUG
	std::cout<<cipher_code_replace<<std::endl;
#endif
	return cipher_code_replace;
}
CipherCode::CipherCode(){}
CipherCode::~CipherCode(){
	delete cipherCode;
}