#pragma once

template <typename T>
struct Stack
{
	T* items;
	int top;
	unsigned int maxSize;

	void init (unsigned int size);
	void copyStack (const Stack<T> &s);
	void release ();

	bool isEmpty ();
	void push (T newItem);
	T pop ();
	T topValue ();

	void print ();
};

#include "stack.cpp"