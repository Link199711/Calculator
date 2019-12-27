#include "stack.h"

template <class T>
stack<T>::stack()
{
    len = 0;
    store = new T[100];
}

template <class T>
bool stack<T>::empty()
{
    return len == 0;
}

template <class T>
void stack<T>::push(T ele)
{
    store[len] = ele;
    len ++;
}

template <class T>
void stack<T>::pop()
{
    len --;
}

template <class T>
T stack<T>::top()
{
    return store[len - 1];
}

template <class T>
stack<T>::~stack()
{
    delete [] store;
    len = 0;
}
