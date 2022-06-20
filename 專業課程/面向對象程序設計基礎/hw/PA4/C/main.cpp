#include "Container.h"
#include <string>
#include <iostream>

using namespace std;

template<class A>
void work(Container<A> * cont)
{	
	int n;
    cin >> n;
    while(n--)
    {
        int x, y;
		string act;
        cin >> act;
        if(act == "ban")
        {
			A item;
            cin >> x >> y >> item;
            cont->insert(x, y, item);
        }
        else
        {
            cin >> x >> y;
            A* result = cont->find(x,y);
            if (result==NULL)
                cout << "open" << endl;
            else
                cout << *result << endl;
        }
    }
}

template <class A>
void start()
{
    Container<A> * cont = new Container<A>();
    work(cont);
    delete cont;
}

int main()
{
    string type;
    cin >> type;
	
    if(type == "int")
        start<int>();
    else if(type == "string")
        start<string>();
	
	return 0;
}
