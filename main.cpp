#include <iostream>
#include "CSForest.h"
using namespace std;

template <class T>
void Print(const T &d)
{
	cout << d << "  ";
}

int main()
{
	char items[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G'};
	int parents[] = {-1, -1, 0, 0, 2, 2, 1};
	CSForest<char> Forest(items, parents, 7);
	Forest.display(true);
	cout << "\n";
	Forest.display();
	cout << "\nTree Count = " << Forest.get_TreeCount();
	cout << "\n1st Tree Root = " << Forest.get_TreeRootPtr(1)->get_Data();
	cout << "\n2nd Tree Root = " << Forest.get_TreeRootPtr(2)->get_Data();
	cout << "\n";
	Forest.traverse_PreOrder(Print);
	return 0;
}
