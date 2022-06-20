#pragma once
#include <string>
#include <iostream>
#include "EncryptStrategy.h"
#include "User.h"
#include "VerificationStrategy.h"

class UserProxy: public User {
    EncryptStrategy* enc;
	VerificationStrategy* ver;
	RealUser* rus;
public:
    UserProxy(RealUser* ruser, EncryptStrategy*encStr, VerificationStrategy*verStr): rus(ruser), enc(encStr), ver(verStr) {

    }
    void sendMessage(std::string message) {
        rus->sendMessage(enc->encode(message));
        std::cout << ver->verify(message) << std::endl;
    }
};