#ifndef __CSFOREST_H__
#define __CSFOREST_H__

#include "CSForestNode.h"
#include <iostream>
#include <queue>
using namespace std;

template <class N>
class CSForest
{
private:
	CSForestNode<N> *root = NULL;

private:
	static void display_BinTraverse(CSForestNode<N> *root, int layer);
	static void display_Traverse(CSForestNode<N> *root, int layer);

	static void release(CSForestNode<N> *root);

	static void traverse_PreOrder(CSForestNode<N> *root, void (*visit)(const N &));
	static void traverse_MidOrder(CSForestNode<N> *root, void (*visit)(const N &));
	static void traverse_PosOrder(CSForestNode<N> *root, void (*visit)(const N &));

	static int BinaryHeight(CSForestNode<N> *root);
	static int LeavesNum(CSForestNode<N> *root);

public:
	// constructor
	CSForest();
	CSForest(const CSForest<N> &tree);
	~CSForest();
	CSForest(N items[], int parents[], int n);

	bool is_Empty() const;
	CSForestNode<N> *get_RootPtr() const;
	int get_TreeCount() const;
	CSForestNode<N> *get_TreeRootPtr(int idx) const;
	CSForestNode<N> *get_NodePtr(const N &d) const;
	CSForestNode<N> *add_Tree(const N &d);
	CSForestNode<N> *add_Kid(CSForestNode<N> *node, const N &d);

	void traverse_PreOrder(void (*visit)(const N &)) const;
	void traverse_MidOrder(void (*visit)(const N &)) const;
	void traverse_PosOrder(void (*visit)(const N &)) const;

	CSForest<N> &operator=(const CSForest<N> &tree);

	void display(bool binary = false) const;

	int BinaryHeight() const;
	int LeavesNum() const;
};

template <class N>
CSForest<N>::CSForest() {}

// de-constructor
template <class N>
CSForest<N>::~CSForest()
{
	release(this->get_RootPtr());
	this->root = NULL;
}

template <class N>
void CSForest<N>::release(CSForestNode<N> *root)
{
	if (root == NULL)
		return;
	if (root->get_KidPtr() != NULL)
		release(root->get_KidPtr());
	if (root->get_BroPtr() != NULL)
		release(root->get_BroPtr());
	delete root;
}

// construct a forest through items array
template <class N>
CSForest<N>::CSForest(N *items, int *parents, int n)
{
	CSForestNode<N> *nodelist[n];
	for (int i = 0; i < n; i++)
	{
		CSForestNode<N> *node = new CSForestNode<N>(items[i], NULL, NULL);
		nodelist[i] = node;
		if (parents[i] != -1)
		{
			CSForestNode<N> *parent = nodelist[parents[i]];
			if (parent->get_KidPtr() == NULL)
			{
				parent->set_KidPtr(node);
			}
			else
			{
				CSForestNode<N> *LastBro = parent->get_KidPtr();
				for (; LastBro->get_BroPtr() != NULL; LastBro = LastBro->get_BroPtr())
					;
				LastBro->set_BroPtr(node);
			}
		}
		else if (i > 0)
		{
			CSForestNode<N> *LastBro = nodelist[0];
			for (; LastBro->get_BroPtr() != NULL; LastBro = LastBro->get_BroPtr())
				;
			LastBro->set_BroPtr(node);
		}
		else
		{
			this->root = node;
		}
	}
}

// construct a forest by copying
template <class N>
CSForest<N>::CSForest(const CSForest<N> &tree)
{
	if (tree.get_RootPtr() == NULL)
	{
		this->root = NULL;
		return;
	}
	else
	{
		queue<CSForestNode<N> *> treequeue;
		queue<CSForestNode<N> *> newqueue;
		this->root = new CSForestNode<N>;
		treequeue.push(tree.get_RootPtr());
		newqueue.push(this->get_RootPtr());
		while (treequeue.size() > 0)
		{
			CSForestNode<N> *treenode = treequeue.front();
			CSForestNode<N> *newnode = newqueue.front();
			treequeue.pop();
			newqueue.pop();
			newnode->set_Data(treenode->get_Data());
			if (treenode->get_KidPtr() != NULL)
			{
				treequeue.push(treenode->get_KidPtr());
				newnode->set_KidPtr(new CSForestNode<N>);
				newqueue.push(newnode->get_KidPtr());
			}
			else
			{
				newnode->set_KidPtr(NULL);
			}
			if (treenode->get_BroPtr() != NULL)
			{
				treequeue.push(treenode->get_BroPtr());
				newnode->set_BroPtr(new CSForestNode<N>);
				newqueue.push(newnode->get_BroPtr());
			}
			else
			{
				newnode->set_BroPtr(NULL);
			}
		}
		return;
	}
}

// get the RootPtr of the forest
template <class N>
CSForestNode<N> *CSForest<N>::get_RootPtr() const
{
	return this->root;
}

// get Tree Count
template <class N>
int CSForest<N>::get_TreeCount() const
{
	int count = 0;
	for (CSForestNode<N> *trees = this->get_RootPtr(); trees != NULL; trees = trees->get_BroPtr())
		count++;
	return count;
}

// get the TootPtr of idx th's tree
template <class N>
CSForestNode<N> *CSForest<N>::get_TreeRootPtr(int idx) const
{
	idx--;
	int id = 0;
	for (CSForestNode<N> *trees = this->get_RootPtr(); trees != NULL; trees = trees->get_BroPtr())
	{
		if (idx == id)
			return trees;
		id++;
	}
	return NULL;
}

// Search node
template <class N>
CSForestNode<N> *CSForest<N>::get_NodePtr(const N &d) const
{
	if (this->get_RootPtr() == NULL)
	{
		return NULL;
	}
	else
	{
		queue<CSForestNode<N> *> treequeue;
		treequeue.push(this->get_RootPtr());
		while (treequeue.size() > 0)
		{
			CSForestNode<N> *treenode = treequeue.front();
			treequeue.pop();
			if (treenode->get_Data() == d)
			{
				return treenode;
			}
			else
			{
				if (treenode->get_KidPtr() != NULL)
				{
					treequeue.push(treenode->get_KidPtr());
				}
				if (treenode->get_BroPtr() != NULL)
				{
					treequeue.push(treenode->get_BroPtr());
				}
			}
		}
		return NULL;
	}
}

// add Tree
template <class N>
CSForestNode<N> *CSForest<N>::add_Tree(const N &d)
{
	CSForestNode<N> *newnode = new CSForestNode<N>(d, NULL, NULL);
	if (this->get_RootPtr() == NULL)
	{
		this->root = newnode;
		return newnode;
	}
	else
	{
		CSForestNode<N> *p = this->get_RootPtr();
		for (; p->get_BroPtr() != NULL; p = p->get_BroPtr())
			;
		p->set_BroPtr(newnode);
		return newnode;
	}
}

// add Kid
template <class N>
CSForestNode<N> *CSForest<N>::add_Kid(CSForestNode<N> *node, const N &d)
{
	if (node == NULL)
		return NULL;
	CSForestNode<N> *newnode = new CSForestNode<N>(d, NULL, NULL);
	if (node->get_KidPtr() == NULL)
	{
		node->set_KidPtr(newnode);
		return newnode;
	}
	else
	{
		CSForestNode<N> *p = node->get_KidPtr();
		for (; p->get_BroPtr() != NULL; p = p->get_BroPtr())
			;
		p->set_BroPtr(newnode);
		return newnode;
	}
}

// get whether the forest is empty
template <class N>
bool CSForest<N>::is_Empty() const
{
	return this->get_RootPtr() == NULL;
}

// pre order traverse (one function required void func(const N &d);)
template <class N>
void CSForest<N>::traverse_PreOrder(void (*visit)(const N &)) const
{
	traverse_PreOrder(this->get_RootPtr(), visit);
}

template <class N>
void CSForest<N>::traverse_PreOrder(CSForestNode<N> *root, void (*visit)(const N &))
{
	(*visit)(root->get_Data());
	if (root->get_KidPtr() != NULL)
		traverse_PreOrder(root->get_KidPtr(), visit);
	if (root->get_BroPtr() != NULL)
		traverse_PreOrder(root->get_BroPtr(), visit);
}

//  mid order traverse
template <class N>
void CSForest<N>::traverse_MidOrder(void (*visit)(const N &)) const
{
	traverse_MidOrder(this->get_RootPtr(), visit);
}

template <class N>
void CSForest<N>::traverse_MidOrder(CSForestNode<N> *root, void (*visit)(const N &))
{
	if (root->get_KidPtr() != NULL)
		traverse_MidOrder(root->get_KidPtr(), visit);
	(*visit)(root->get_Data());
	if (root->get_BroPtr() != NULL)
		traverse_MidOrder(root->get_BroPtr(), visit);
}

//  mid order traverse
template <class N>
void CSForest<N>::traverse_PosOrder(void (*visit)(const N &)) const
{
	traverse_PosOrder(this->get_RootPtr(), visit);
}

template <class N>
void CSForest<N>::traverse_PosOrder(CSForestNode<N> *root, void (*visit)(const N &))
{
	if (root->get_KidPtr() != NULL)
		traverse_PosOrder(root->get_KidPtr(), visit);
	if (root->get_BroPtr() != NULL)
		traverse_PosOrder(root->get_BroPtr(), visit);
	(*visit)(root->get_Data());
}

// operator
template <class N>
CSForest<N> &CSForest<N>::operator=(const CSForest<N> &tree)
{
	release(this->get_RootPtr());
	if (tree.get_RootPtr() == NULL)
	{
		this->root = NULL;
		return *this;
	}
	else
	{
		queue<CSForestNode<N> *> treequeue;
		queue<CSForestNode<N> *> newqueue;
		this->root = new CSForestNode<N>;
		treequeue.push(tree.get_RootPtr());
		newqueue.push(this->get_RootPtr());
		while (treequeue.size() > 0)
		{
			CSForestNode<N> *treenode = treequeue.front();
			CSForestNode<N> *newnode = newqueue.front();
			treequeue.pop();
			newqueue.pop();
			newnode->set_Data(treenode->get_Data());
			if (treenode->get_KidPtr() != NULL)
			{
				treequeue.push(treenode->get_KidPtr());
				newnode->set_KidPtr(new CSForestNode<N>);
				newqueue.push(newnode->get_KidPtr());
			}
			else
			{
				newnode->set_KidPtr(NULL);
			}
			if (treenode->get_BroPtr() != NULL)
			{
				treequeue.push(treenode->get_BroPtr());
				newnode->set_BroPtr(new CSForestNode<N>);
				newqueue.push(newnode->get_BroPtr());
			}
			else
			{
				newnode->set_BroPtr(NULL);
			}
		}
		return *this;
	}
}

// display the forest (in binary style or forest style)
template <class N>
void CSForest<N>::display(bool binary) const
{
	if (this->get_RootPtr() != NULL)
		if (binary)
			display_BinTraverse(this->get_RootPtr(), 0);
		else
			display_Traverse(this->get_RootPtr(), 0);
}

template <class N>
void CSForest<N>::display_BinTraverse(CSForestNode<N> *root, int layer)
{
	if (root == NULL)
		return;
	for (int i = 0; i < layer; i++)
		std::cout << "|  ";
	std::cout << "+ ";
	std::cout << "[" << root->get_Data() << "]\n";
	if (root->get_KidPtr() != NULL)
		display_BinTraverse(root->get_KidPtr(), layer + 1);
	if (root->get_BroPtr() != NULL)
		display_BinTraverse(root->get_BroPtr(), layer + 1);
}

template <class N>
void CSForest<N>::display_Traverse(CSForestNode<N> *root, int layer)
{
	if (root == NULL)
		return;
	for (int i = 0; i < layer; i++)
		std::cout << "|  ";
	if (root->get_BroPtr() == NULL)
		std::cout << "+ ";
	else
		std::cout << "+ ";
	std::cout << "[" << root->get_Data() << "]\n";
	if (root->get_KidPtr() != NULL)
		display_Traverse(root->get_KidPtr(), layer + 1);
	if (root->get_BroPtr() != NULL)
		display_Traverse(root->get_BroPtr(), layer);
}

//Get Binary Tree Height(recursion version)
template <class N>
int CSForest<N>::BinaryHeight(CSForestNode<N> *root)
{
	if (root == NULL)
		return 0;
	int lheight = BinaryHeight(root->get_KidPtr()) + 1;
	int rheight = BinaryHeight(root->get_BroPtr()) + 1;
	return lheight > rheight ? lheight : rheight;
}

template <class N>
int CSForest<N>::BinaryHeight() const
{
	return BinaryHeight(get_RootPtr());
}

//Get leaves count (recursion version)
//loop version is commented
template <class N>
int CSForest<N>::LeavesNum(CSForestNode<N> *root)
{
	/* int ans = 0;
	queue<CSForestNode<N> *> treequeue;
	treequeue.push(root);
	while (treequeue.size() > 0)
	{
		CSForestNode<N> *treenode = treequeue.front();
		treequeue.pop();
		if (treenode->get_KidPtr() == NULL && treenode->get_BroPtr() == NULL)
		{
			ans++;
		}
		else
		{
			if (treenode->get_KidPtr() != NULL)
			{
				treequeue.push(treenode->get_KidPtr());
			}
			if (treenode->get_BroPtr() != NULL)
			{
				treequeue.push(treenode->get_BroPtr());
			}
		}
	}
	return ans; */
	if (root->get_KidPtr() == NULL && root->get_BroPtr() == NULL)
		return 1;
	return LeavesNum(root->get_KidPtr()) + LeavesNum(root->get_BroPtr());
}

template <class N>
int CSForest<N>::LeavesNum() const
{
	return LeavesNum(get_RootPtr());
}

#endif
