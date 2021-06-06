#pragma once
#include <iostream>

template<typename T>
class LinkedList
{
	struct Node
	{
		T data;
		Node* next = nullptr;
	};


public:
	LinkedList()
		: mHead(nullptr)
	{}

	~LinkedList()
	{
		if (IsEmpty())
		{
			return;
		}

		if (mHead->next == nullptr)
		{
			delete mHead;
			mHead = nullptr;
			return;
		}

		Node* previous = mHead;
		Node* current = mHead->next;

		while (current != nullptr)
		{
			delete previous;
			previous = current;
			current = current->next;
		}

		delete previous;
		mHead = nullptr;
		previous = nullptr;
	}

	void Insert(T data)
	{
		Node* newNode = CreateNode(data);
		if (IsEmpty())
		{
			mHead = newNode;
			return;
		}

		Node* currentNode = mHead;
		while (currentNode != nullptr)
		{
			if (currentNode->next == nullptr)
			{
				currentNode->next = newNode;
				currentNode = nullptr;
				break;
			}
			currentNode = currentNode->next;
		}
	}

	void Remove(T data)
	{
		if (IsEmpty())
		{
			std::cout << "The list is empty.\n";
			return;
		}

		if (mHead->data == data)
		{
			Node* temp = mHead->next;
			delete mHead;
			mHead = temp;
			temp = nullptr;
			return;
		}

		Node* currentNode = mHead->next;

		while (currentNode->next->data != data && currentNode != nullptr)
		{
			currentNode = currentNode->next;
		}

		if (currentNode == nullptr)
		{
			std::cout << "The element is not in the list.\n";
			return;
		}
		Node* temp = currentNode->next;
		currentNode->next = temp->next;
		delete temp;
		temp = nullptr;

	}

	bool IsEmpty()
	{
		return mHead == nullptr;
	}

	//Displays all the elements of the linked list
	void DisplayList()
	{
		// TODO: 1
		if (!IsEmpty()) {
			Node* curNode = mHead;
			while (curNode != nullptr) {
				std::cout << curNode->data << ", ";
				curNode = curNode->next;
			}
		}	

	}

	//ERROR: -5: In a display function, you can't modify the actual data. A good approach to this 
	// task is to create a recursive function to print like: 
	/*void printReverse(Node* node)
	{
		if (node->next != nullptr)
		{
			printReverse(node->next);
		}

		std::cout << node->data << " ";
	}*/
	//And then call inside DisplayReverseList using mHead as the initial parameter.
	
	//Displays all the elements of the linked list in reverse order
	void DisplayReverseList()
	{
		std::cout  << "\n ";
		// TODO: 2
		Node* temp = NULL;
		Node* prev = NULL;
		Node* current = (mHead);
		while (current != NULL) {
			temp = current->next;
			current->next = prev;
			prev = current;
			current = temp;
		}
		(mHead) = prev;
		DisplayList();
		//return list to normal
	}

	//ERROR -5: This method is not modifyng the content of a linked list.
	//You have to walk through the list until current == nullptr or current->data == content.
	// If current->data == content, make current->data = newContent, and return true. 
	// Otherwise return false.
	
	//This function allows the user to modify an existance data
	//Returns true if the conten was modified and false if it wasn't.
	bool ModifyContent(T content, T newContent)
	{
		// TODO: 3
		if (!IsEmpty()) {
			int x = 0;
			Node* curNode = mHead;
			while (curNode != nullptr) {
				if (x == content) {
					break;
				}
				x++;
			}
			if (curNode->data == content) {
				curNode->data = newContent;
				return true;
			}
			else {
				return false;
			}
		}
	}

	//ERROR -5: Why are you using free? We never used free in class, we are using delete...
	
	//Clear all the data from the linked list
	void ClearList()
	{
		// TODO: 4
		
		Node* current = mHead;
		Node* next = NULL;

		while (current != NULL)
		{
			next = current->next;
			free(current);
			current = next;
		}


		*mHead = NULL;
	}

private:
	Node* mHead;
	Node* mCurrent;

	Node* CreateNode(T data)
	{
		Node* newNode = new Node();
		newNode->data = data;
		return newNode;
	}
};
