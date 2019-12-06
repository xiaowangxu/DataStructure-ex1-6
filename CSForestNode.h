#ifndef __CSFORESTNODE_H__
#define __CSFORESTNODE_H__

template <class T>
class CSForestNode
{
private:
	CSForestNode *kid = NULL;
	CSForestNode *bro = NULL;
	T data;

public:
	CSForestNode();
	// constructor with kid & bro
	CSForestNode(const T &d, CSForestNode *k, CSForestNode *b);
	~CSForestNode();

	CSForestNode *get_KidPtr() const;
	CSForestNode *get_BroPtr() const;
	void set_KidPtr(CSForestNode<T> *target);
	void set_BroPtr(CSForestNode<T> *target);
	T get_Data() const;
	void set_Data(T d);
};

template <class T>
CSForestNode<T>::CSForestNode()
{
}

template <class T>
CSForestNode<T>::CSForestNode(const T &d, CSForestNode<T> *k, CSForestNode<T> *b)
	: data(d), kid(k), bro(b) {}

template <class T>
CSForestNode<T>::~CSForestNode()
{
}

//
template <class T>
CSForestNode<T> *CSForestNode<T>::get_KidPtr() const
{
	return this->kid;
}

template <class T>
void CSForestNode<T>::set_KidPtr(CSForestNode<T> *target)
{
	this->kid = target;
}

//
template <class T>
CSForestNode<T> *CSForestNode<T>::get_BroPtr() const
{
	return this->bro;
}

template <class T>
void CSForestNode<T>::set_BroPtr(CSForestNode<T> *target)
{
	this->bro = target;
}

//
template <class T>
T CSForestNode<T>::get_Data() const
{
	return this->data;
}

//
template <class T>
void CSForestNode<T>::set_Data(T d)
{
	this->data = d;
}

#endif
