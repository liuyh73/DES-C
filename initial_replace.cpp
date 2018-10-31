#include <iostream>
using std::string;
int initial_replace_matrix[8][8] = {
	{58, 50, 42, 34, 26, 18, 10, 2},
	{60, 52, 44, 36, 28, 20, 12, 4},
	{62, 54, 46, 38, 30, 22, 14, 6},
	{64, 56, 48, 40, 32, 24, 16, 8},
	{57, 49, 41, 33, 25, 17, 9, 1},
	{59, 51, 43, 35, 27, 19, 11, 3},
	{61, 53, 45, 37, 29, 21, 13, 5},
	{63, 55, 47, 39, 31, 23, 15, 7},
}

class InitialReplace {
public:
	string initial_replace(string clear_text) {
		string clear_text_init_replace = "";
		for(int i=0;i<8;i++)
			for(int j=0;j<8;j++)
				clear_text_init_replace+=string(clear_text[initial_replace_matrix[i][j]-1]);
		return clear_text_init_replace;
	}
private:
	InitialReplace(){}
	~InitialReplace(){
		delete initialReplace;
	}
	static InitialReplace* initialReplace = nullptr;
}