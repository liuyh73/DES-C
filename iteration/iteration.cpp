#include <iostream>
#include <string>
#include "iteration.hpp"
using std::string;
// #define DEBUG
int extended_replacement_matrix[8][6] = {
	{32, 1, 2, 3, 4, 5},
	{4, 5, 6, 7, 8, 9},
	{8, 9, 10, 11, 12, 13},
	{12, 13, 14, 15, 16, 17},
	{16, 17, 18, 19, 20, 21},
	{20, 21, 22, 23, 24, 25},
	{24, 25, 26, 27, 28, 29},
	{28, 29, 30, 31, 32, 1},
};

int s_box[8][4][16] = {
	{
		{14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7},
		{0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8},
		{4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0},
		{15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13},
	},
	{
		{15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10},
		{3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5},
		{0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15},
		{13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9},
	},
	{
		{10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8},
		{13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1},
		{13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7},
		{1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12},
	},
	{
		{7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15},
		{13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9},
		{10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4},
		{3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14},
	},
	{
		{2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9},
		{14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6},
		{4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14},
		{11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3},
	},
	{
		{12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11},
		{10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8},
		{9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6},
		{4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13},
	},
	{
		{4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1},
		{13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6},
		{1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2},
		{6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12},
	},
	{
		{13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7},
		{1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2},
		{7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8},
		{2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11},
	},
};

int p_box[32] = {
	16, 7, 20, 21, 29, 12, 28, 17, 1, 15, 23, 26, 5, 18, 31, 10,
	2, 8, 24, 14, 32, 27, 3, 9, 19, 13, 30, 6, 22, 11, 4, 25,
};

Iteration* Iteration::iter = nullptr;
Iteration *Iteration::getInstance(){
	if(iter == nullptr){
		iter = new Iteration();
	}
	return iter;
}
string Iteration::F(string clear_text_init_replace, string keys[]) {
	string L[17], R[17];
	L[0] = clear_text_init_replace.substr(0,32);
	R[0] = clear_text_init_replace.substr(32);
	string R_extended, R_extended_xor, R_extended_xor_S_trans, R_extended_xor_S_P_trans,R_extended_xor_S_P_trans_xor;
	for(int k=0;k<16;k++){
		// Extended replacement
		R_extended = extendReplacement(R[k]);
		// xor with keys[k]
		R_extended_xor = xorWithKeys_K(R_extended, keys[k]);
		// S-box transfer
		R_extended_xor_S_trans = sBoxTransfer(R_extended_xor);
		// P-box transfer
		R_extended_xor_S_P_trans = pBoxTransfer(R_extended_xor_S_trans);
		// xor with L[k]
		R_extended_xor_S_P_trans_xor = xorWithL_K(R_extended_xor_S_P_trans, L[k]);

		L[k+1] = R[k];
		R[k+1] = R_extended_xor_S_P_trans_xor;
#ifdef DEBUG
		std::cout<<L[k+1]<<" "<<R[k+1]<<std::endl;
		if(k==0){
			std::cout<<R_extended<<std::endl;
			std::cout<<R_extended_xor<<std::endl;
			std::cout<<R_extended_xor_S_trans<<std::endl;
			std::cout<<R_extended_xor_S_P_trans<<std::endl;
			std::cout<<R_extended_xor_S_P_trans_xor<<std::endl;
		}
#endif
	}
	string R_16_L_16 = R[16]+L[16];
	return R_16_L_16;
}

string Iteration::extendReplacement(string R_K) {
	string R_extended = "";
	for(int i=0;i<8;i++){
		for(int j=0;j<6;j++){
			R_extended += R_K[extended_replacement_matrix[i][j] - 1];
		}
	}
	return R_extended;
}

string Iteration::xorWithKeys_K(string R_extended, string keys_K) {
	string R_extended_xor = "";
	for (int i = 0; i < keys_K.length(); i++) {
		R_extended_xor += (int(R_extended[i]-'0') ^ int(keys_K[i]-'0')) + '0';
	}
	return R_extended_xor;
}

string Iteration::sBoxTransfer(string R_extended_xor) {
	string R_extended_xor_S_trans = "";
	string R_extended_xor_slice = "";
	for(int i=0;i<8;i++){
		R_extended_xor_slice = R_extended_xor.substr(6*i, 6);
		int row = getRow(R_extended_xor_slice[0], R_extended_xor_slice[5]);
		int column = getColumn(R_extended_xor_slice.substr(1,4));
		int S_trans_data = s_box[i][row][column];
		R_extended_xor_S_trans += utils->decimalToBinary(S_trans_data);
	}
	return R_extended_xor_S_trans;
}

string Iteration::pBoxTransfer(string R_extended_xor_S_trans) {
	string R_extended_xor_S_P_trans = "";
	for(int i=0;i<32;i++){
		R_extended_xor_S_P_trans += R_extended_xor_S_trans[p_box[i]-1];
	}
	return R_extended_xor_S_P_trans;
}

string Iteration::xorWithL_K(string R_extended_xor_S_P_trans, string L_K) {
	string R_extended_xor_S_P_trans_xor = "";
	for(int i=0;i<32;i++){
		R_extended_xor_S_P_trans_xor += (int(R_extended_xor_S_P_trans[i] - '0') ^ int(L_K[i] - '0')) + '0';
	}
	return R_extended_xor_S_P_trans_xor;
}

int Iteration::getRow(char num1, char num2) {
	string row= "";
	row=row + num1+num2;
	return std::stoi(row.c_str(), 0, 2);
}

int Iteration::getColumn(string column) {
	return std::stoi(column.c_str(), 0, 2);
}

Iteration::Iteration(){
	utils = Utils::getInstance();
};
Iteration::~Iteration(){
	delete iter;
};