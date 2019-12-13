#include <iostream>
#include <fstream>
#include "CSForest.h"
using namespace std;

const int maxitems = 1000;

template <class T>
void Print(const T &d)
{
	cout << d << "  ";
}

int main()
{
	fstream test;
	test.open("test.txt", ios::in);
	int n;
	char items[maxitems] = {};
	int parents[maxitems] = {};
	while (test >> n)
	{
		for (int i = 0; i < n; i++)
		{
			test >> items[i];
		}
		for (int i = 0; i < n; i++)
		{
			test >> parents[i];
		}
		CSForest<char> forest(items, parents, n);
		forest.display();
		cout << "\n";
		forest.display(true);
		cout << "\n";
		cout << "==========\n";
		cout << "ForestCount:" << forest.get_TreeCount() << "\n";
		cout << "ForestHeight:" << forest.ForestHeight() << '\n';
		cout << "ForestLeaves:" << forest.ForestLeaves() << '\n';
		cout << "BinaryTree Height: " << forest.BinaryHeight() << '\n';
		cout << "LeavesNum: " << forest.LeavesNum() << '\n';
		cout << "==========";
		cout << "\nPreOrder: ";
		forest.traverse_PreOrder(Print);
		cout << "\nMidOrder: ";
		forest.traverse_MidOrder(Print);
		cout << "\nPosOrder: ";
		forest.traverse_PosOrder(Print);
		cout << "\n";
		cout << "==========";
		cout << "\n";
		cout << "\n";
	}
	/* char items[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G'};
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
	CopyForest.display(); */

	return 0;
}
