# include <iostream>
# include <string>
# include "User.h"
# include "UserProxy.h"
# include "EncryptStrategy.h"
# include "VerificationStrategy.h"
using namespace std;

int main(){
	int N;
	cin >> N;
	for (int i = 0; i < N; ++ i) {
		int ens, verf;
		string uname, message;
		cin >> ens >> verf;
		cin >> uname >> message;
		EncryptStrategy* encStr;
		if (ens == 1)
			encStr = new InsertStrategy();
		else if (ens == 2)
			encStr = new InvertStrategy();
		VerificationStrategy* verStr;
		if (verf == 1)
			verStr = new PrefixStrategy();
		else if (verf == 2)
			verStr = new IntervalStrategy();
		RealUser* ruser = new RealUser(uname);
		UserProxy* uproxy = new UserProxy(ruser, encStr, verStr);

		uproxy->sendMessage(message);
	}
	return 0;
}
