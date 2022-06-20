#include <iostream>
#include <string>
#include "Calculator.h"
#include "LevelStrategy.h"
#include "PerformStrategy.h"
using namespace std;

int main() {
	int n;
	cin >> n;
	for (int i = 0; i < n; ++ i){
		string level;
		double perform;
		cin >> level >> perform;

		LevelStrategy* m_levelStrategy;

		if (level == "P1")
			m_levelStrategy = new P1LStrategy();
		else if (level == "P2")
			m_levelStrategy = new P2LStrategy();
		else if (level == "P3")
			m_levelStrategy = new P3LStrategy();
		else {
			cout << "not such level" << endl;
			exit(1);
		}

		PerformStrategy* m_perfomStrategy;
		if (perform >= 0 && perform < 0.5)
			m_perfomStrategy = new sPerformStrategy(perform);
		else if (perform >= 0.5 && perform < 0.8)
			m_perfomStrategy = new mPerformStrategy(perform);
		else if (perform >= 0.8 && perform <= 1)
			m_perfomStrategy = new lPerformStrategy(perform);		
		else{
			cout << "not such performance" << endl;
			exit(1);
		}

		Calculator calculator = Calculator(m_levelStrategy, m_perfomStrategy);

		int base = calculator.get_base();
		int total = calculator.get_total(base);
		cout << total << endl;
	}

	return 0;
}