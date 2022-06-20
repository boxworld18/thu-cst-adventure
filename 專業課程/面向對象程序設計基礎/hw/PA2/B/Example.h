#ifndef __EXAMPLE__
#define __EXAMPLE__
	
class Example {
		
private:

	// (1)
	static int totalCase;
	int num, ID;

public:
	
	Example(int data);
	void getData();
	~Example();
	
};
		
#endif