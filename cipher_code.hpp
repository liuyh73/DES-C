#ifndef CIPHER_CODE_HPP
#define CIPHER_CODE_HPP
#include <iostream>
using std::string;
class CipherCode {
public:
	static CipherCode* getInstance();
	void getKeys(string key, string keys[]);
	string getCipherCodeN(int round, string key);

	void getCNDN(int round, int CNDN[]);
	void getCN(int round, int CN[]);
	void getDN(int round, int DN[]);

	int getDisplacements(int round);
	string replace(int CNDN[], string key);
private:
	CipherCode();
	~CipherCode();
	static CipherCode* cipherCode;
};
#endif