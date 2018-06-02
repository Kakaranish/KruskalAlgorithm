#ifndef _QUEUE_H
#define _QUEUE_H

#include <iostream>
#include <cstdio>
#include <exception>
#include "Pair.h"

template <typename TValue, typename TPriority = int>
class Queue
{
  private:
	struct Node<typename _TValue, typename _TPriority>
	{
		using Node<_TValue, _TPriority> = NodeType;

		_TValue value;
		_TPriority priority;
		NodeType *nextNode = nullptr;

		Node(_TValue _value, _TPriority _priority, NodeType *_nextNode) : value(_value),
																		  priority(_priority),
																		  nextNode(_nextNode) {}
	};
	using Node<_TValue, _TPriority> = NodeType;

	NodeType *head = nullptr;
	std::size_t size = 0;
	bool highPriorityFirst = true; //Front returns element with highest priority

  public:
	Queue(bool _highPriorityFirst = true) : highPriorityFirst(_highPriorityFirst) {}

	inline bool empty() const { return size > 0 ? false : true; }
	inline std::size_t getSize() const { return size; }

	void push(TValue value, TPriority priority)
	{
		if (empty())
			head = new NodeType(value, priority);
		else
		{
			NodeType *tempNode = head;

			while (tempNode->nextNode)
				tempNode = tempNode->nextNode;

			tempNode->nextNode = new Node<T>(value);
		}

		++size;
	}

	void pop()
	{
		if (empty())
			throw std::range_error("Stack is empty! Unable to .pop()");
		Node<T> *tempNode = head->nextNode;
		delete head;

		head = tempNode;
		--size;
	}

	T front()
	{
		if (empty())
			throw std::range_error("Stack is empty! Unable to .front()");
		return head->value;
	}

	T back()
	{
		if (empty())
			throw std::range_error("Stack is empty! Unable to .back()");
		NodeType *tempNode = head;

		while (tempNode->nextNode)
			tempNode = tempNode->nextNode;

		return tempNode->value;
	}

	void show()
	{
		if (empty())
		{
			std::cout << "Queue is empty" << std::endl;
			return;
		}

		NodeType *tempNode = head;
		std::cout << "Queue: (value, priority) " << std::endl;
		while (tempNode)
		{
			std::cout << "(" << tempNode->value << "," << tempNode->priority << ")\t";
			tempNode = tempNode->nextNode;
		}
		std::cout << std::endl;
	}
};

#endif