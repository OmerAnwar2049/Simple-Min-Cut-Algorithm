#pragma once
#include "Node.h"



class List
{
private:
	Node* tail;
	int size = 0;
public:
	Node* head;
	List()
	{
		head = NULL;
		tail = NULL;
		size = 0;

	}///end


	void PushBack(int index, int weight)
	{

		size++;
	

		Node* temp = new Node();
		

		temp->next = NULL;
		temp->index = index;
		temp->weight = weight;


		if (head == NULL) {

			head = temp;
			tail = temp;
			//head->data = n;
			temp->previous = NULL;
		}
		else {
			temp->previous = tail;
			tail->next = temp;
			tail = temp;
		}

	}///func end



	Node*& getHead()
	{
		return head;

	}


	void PushFront(int index,int weight) {

		size++;

		Node* temp = new Node();
		

		temp->next = NULL;
		temp->index = index;
		temp->weight=  weight;

		if (head == NULL) {

			head = temp;
			tail = temp;
			//head->data = n;
			temp->previous = NULL;
		}

		else {
			temp->next = head;
			tail->previous = NULL;
			head = temp;

		}

	}///func end


	void PopBack() {

		size--;

		tail = tail->previous;
		delete tail->next;
		tail->next = NULL;

	}

	int getSize()
	{
		return size;
	}


	pair<int,int> PopFront() {
		size--;

		pair<int, int> check;
		check.first = head->index;
		check.second = head->weight;

		head = head->next;
	

		return check;

	}


	

	bool isEmpty() {
		if (size == 0)
			return true;

		return false;
	}


	void ClearList() {

		Node* i = head;
		Node* j = NULL;

		while (i != NULL)
		{
			j = i->next;
			delete i;
			i = j;
		}

	}///func end



	void Display() {

		Node* i;
		for (i = head->next; i != NULL; i = i->next)
		{
			
		}
		cout << endl;

	}

	~List() {

		

	}

	////////////////Haroon part


};
#pragma once
