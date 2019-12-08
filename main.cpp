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
	cout << "ForestHeight:" << Forest.ForestHeight() << '\n';
	cout << "ForestLeaves:" << Forest.ForestLeaves() << '\n';
	cout << "BinaryTree Height: " << Forest.BinaryHeight() << '\n';
	cout << "LeavesNum: " << Forest.LeavesNum() << '\n';
	Forest.display();
	cout << "\nTree Count = " << Forest.get_TreeCount();
	cout << "\n1st Tree Root = " << Forest.get_TreeRootPtr(1)->get_Data();
	cout << "\n2nd Tree Root = " << Forest.get_TreeRootPtr(2)->get_Data();
	cout << "\n";
	Forest.traverse_PreOrder(Print);
	cout << "\n";
	Forest.traverse_MidOrder(Print);
	cout << "\n";
	Forest.traverse_PosOrder(Print);
	cout << "\n";
	CSForest<char> CopyForest;
	CopyForest = Forest;
	cout << "\n";
	Forest.display();
	cout << "\n";
	CopyForest.display();
	// CopyForest.get_NodePtr('A')->set_Data('X');
	// CopyForest.get_NodePtr('D')->set_Data('Z');
	CopyForest.add_Kid(CopyForest.get_NodePtr('A'), 'Y');
	CopyForest.add_Tree('1');
	cout << "\n";
	CopyForest.display();

	return 0;
}
