#ifndef LIST_H
#define LIST_H
#include <iostream>

class List
{
protected:
	class ListNode
	{
	public:
		double data;
		ListNode *next;
		ListNode(double d, ListNode* p = nullptr)
		{
			data = d;
			next = p;
		}
	};
	ListNode* head;
public:
	List() { head = nullptr; }
	~List();
	void add(double number);
	void remove(double number);
	void displayList() const;
	bool isEmpty() const;
};

void List::add(double number)
{
	if (List::isEmpty())
	{
		head = new ListNode(number);
	}
	else
	{
		ListNode *nodePtr = head;
		while (nodePtr->next != nullptr)
			nodePtr = nodePtr->next;
		nodePtr->next = new ListNode(number);
	}
}

inline void List::remove(double number)
{
	if (List::isEmpty())
	{
		// Nothing to do if there are no values in the list
		return;
	}
	ListNode* nodePtr = head;
	ListNode* prevNode = head;
	double val;
	while (nodePtr)
	{
		val = nodePtr->data;
		if (val == number)
		{
			// Need to update head if the head has the value being deleted
			if (nodePtr == head)
			{
				head = nodePtr->next;
			}
			prevNode->next = nodePtr->next;
			nodePtr->next = nullptr;
			delete nodePtr;
			break;
		}
		else
		{
			prevNode = nodePtr;
			nodePtr = nodePtr->next;
		}
	}

}

void List::displayList() const
{
	ListNode *nodePtr = head;
	while (nodePtr)
	{
		std::cout << nodePtr->data << " ";
		nodePtr = nodePtr->next;
	}
}

inline bool List::isEmpty() const
{
	return head == nullptr;
}

List::~List()
{
	ListNode *nodePtr = head;
	while (nodePtr != nullptr)
	{
		ListNode *garbage = nodePtr;
		nodePtr = nodePtr->next;
		delete garbage;
	}
}
#endif // !LIST_H

