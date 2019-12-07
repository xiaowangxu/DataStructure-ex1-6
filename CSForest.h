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
	static void traverse_PreOrder(CSForestNode<N> *root, void (*visit)(const N &));

public:
	// constructor
	CSForest();
	~CSForest();
	CSForest(N items[], int parents[], int n);

	bool is_Empty() const;
	CSForestNode<N> *get_RootPtr() const;
	int get_TreeCount() const;
	CSForestNode<N> *get_TreeRootPtr(int idx) const;

	void traverse_PreOrder(void (*visit)(const N &)) const;

	void display(bool binary = false) const;
};

template <class N>
CSForest<N>::CSForest() {}

template <class N>
CSForest<N>::~CSForest()
{
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

// display the forest (in binary style or forest style)
template <class N>
void CSForest<N>::display(bool binary) const
{
	if (binary)
		display_BinTraverse(this->get_RootPtr(), 0);
	else
		display_Traverse(this->get_RootPtr(), 0);
}

template <class N>
void CSForest<N>::display_BinTraverse(CSForestNode<N> *root, int layer)
{
	for (int i = 0; i < layer; i++)
		std::cout << "©¦ ";
	if (root->get_BroPtr() == NULL)
		std::cout << "©¸ ";
	else
		std::cout << "©À ";
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
		std::cout << "©¦ ";
	if (root->get_BroPtr() == NULL)
		std::cout << "©¸ ";
	else
		std::cout << "©À ";
	std::cout << root->get_Data() << "\n";
	if (root->get_KidPtr() != NULL)
		display_Traverse(root->get_KidPtr(), layer + 1);
	for (CSForestNode<N> *bros = root->get_BroPtr(); bros != NULL; bros = bros->get_BroPtr())
		display_Traverse(bros, layer);
}

#endif
