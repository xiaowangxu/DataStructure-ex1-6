#include <iostream>
#include "CSForest.h"
using namespace std;

int main()
{
	char items[] = {'a', 'b', 'c', 'd'};
	int parents[] = {-1, -1, 1, 2};
	CSForest<char> Forest(items, parents, 4);
	Forest.display(true);
	cout << "\n";
	Forest.display();
	cout << "\nTree Count = " << Forest.get_TreeCount();
	cout << "\n1st Tree Root = " << Forest.get_TreeRoot(1)->get_Data();
	cout << "\n2nd Tree Root = " << Forest.get_TreeRoot(2)->get_Data();
	cout << "test\n";
	return 0;
}
