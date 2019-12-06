#ifndef __CSFOREST_H__
#define __CSFOREST_H__

#include "CSForestNode.h"
#include <iostream>

template <class N>
class CSForest
{
private:
	CSForestNode<N> *root = NULL;

private:
	static void display_BinTraverse(CSForestNode<N> *root, int layer);
	static void display_Traverse(CSForestNode<N> *root, int layer);

public:
	// constructor
	CSForest();
	~CSForest();
	CSForest(N items[], int parents[], int n);

	CSForestNode<N> *get_Root() const;
	int get_TreeCount() const;
	CSForestNode<N> *get_TreeRoot(int idx) const;

	void display(bool binary = false) const;
};

template <class N>
CSForest<N>::CSForest() {}

template <class N>
CSForest<N>::~CSForest()
{
}

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

//
template <class N>
CSForestNode<N> *CSForest<N>::get_Root() const
{
	return this->root;
}

//
template <class N>
int CSForest<N>::get_TreeCount() const
{
	int count = 0;
	for (CSForestNode<N> *trees = this->get_Root(); trees != NULL; trees = trees->get_BroPtr())
		count++;
	return count;
}

//
template <class N>
CSForestNode<N> *CSForest<N>::get_TreeRoot(int idx) const
{
	idx--;
	int id = 0;
	for (CSForestNode<N> *trees = this->get_Root(); trees != NULL; trees = trees->get_BroPtr())
	{
		if (idx == id)
			return trees;
		id++;
	}
	return NULL;
}

//
template <class N>
void CSForest<N>::display_BinTraverse(CSForestNode<N> *root, int layer)
{
	for (int i = 0; i < layer; i++)
		std::cout << "   ";
	std::cout << root->get_Data() << "\n";
	if (root->get_KidPtr() != NULL)
		display_BinTraverse(root->get_KidPtr(), layer + 1);
	if (root->get_BroPtr() != NULL)
		display_BinTraverse(root->get_BroPtr(), layer + 1);
}

template <class N>
void CSForest<N>::display_Traverse(CSForestNode<N> *root, int layer)
{
	for (int i = 0; i < layer; i++)
		std::cout << "   ";
	std::cout << root->get_Data() << "\n";
	if (root->get_KidPtr() != NULL)
		display_Traverse(root->get_KidPtr(), layer + 1);
	for (CSForestNode<N> *bros = root->get_BroPtr(); bros != NULL; bros = bros->get_BroPtr())
		display_Traverse(bros, layer);
}

template <class N>
void CSForest<N>::display(bool binary) const
{
	if (binary)
		display_BinTraverse(this->get_Root(), 0);
	else
		display_Traverse(this->get_Root(), 0);
}

#endif
