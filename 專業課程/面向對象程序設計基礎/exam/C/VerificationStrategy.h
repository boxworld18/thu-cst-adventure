#pragma once
# include <string>

class VerificationStrategy{
public:
	VerificationStrategy() {}
	virtual std::string verify(std::string mes) = 0;
};

class PrefixStrategy: public VerificationStrategy {
public:
	using VerificationStrategy::VerificationStrategy;
	std::string verify(std::string mes) {
		std::string a = "";
		for (int i = 0; i < 3; i++) {
			a += mes[i];
		}
		return a;
	}
};

class IntervalStrategy: public VerificationStrategy {
public:
	using VerificationStrategy::VerificationStrategy;
	std::string verify(std::string mes) {
		std::string a = "";
		int len = mes.length();
		for (int i = 0; i < len; i++) 
		if (i % 2 == 0){
			a += mes[i];
		}
		return a;
	}
};