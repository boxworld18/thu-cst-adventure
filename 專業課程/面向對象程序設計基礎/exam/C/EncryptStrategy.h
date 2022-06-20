#pragma once
# include <string>

class EncryptStrategy{
public:
	EncryptStrategy() {}
	virtual std::string encode(std::string mes) = 0;
};

class InsertStrategy: public EncryptStrategy {
public:
	using EncryptStrategy::EncryptStrategy;
	std::string encode(std::string mes) {
		std::string a = "";
		int len = mes.length();
		for (int i = 0; i < len; i++) {
			a = a + mes[i] + '#';
		}
		return a;
	}
};

class InvertStrategy: public EncryptStrategy {
public:
	using EncryptStrategy::EncryptStrategy;
	std::string encode(std::string mes) {
		std::string a = "";
		int len = mes.length();
		for (int i = len - 1; i >= 0; i--) {
			a = a + mes[i];
		}
		return a;
	}
};