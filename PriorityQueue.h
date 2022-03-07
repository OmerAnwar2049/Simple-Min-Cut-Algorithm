#include <iostream>
#include "Node.h"
using namespace std;


class PriorityQueue
{
private:

public:
	Node* front;
	int size;
	PriorityQueue() {
		front = NULL;
		size = 0;
	}

	void insert(int index,int weight) {
		size++;
		Node* temp = new Node;
		Node* curr;
		temp->index = index;
		temp->weight = weight;
	
		if (this->front == NULL || this->front->weight < weight) {
			temp->next = front;
			front = temp;
		}
		else {
			curr = front;
			while (curr->next != NULL && curr->next->weight > weight) {
				curr = curr->next;
			}
			temp->next = curr->next;
			curr->next = temp;
		}
	}

	pair<int,int> deleteMax() {
		size--;
		pair<int,int> value;
		Node* temp;
		if (front == NULL) {
			cout << "Queue empty";
		}
		else {
			temp = front;
			value.first = temp->index;
			value.second = temp->weight;
			front = front->next;
		}
		return value;
	}



	bool isEmpty() {
		if (front == NULL) {
			return true;
		}
		return false;
	}

	void Display() {
		Node* curr;
		curr = front;
		if (front == NULL) {
			cout << "Queue is empty";
		}
		else {
			while (curr != NULL) {
				cout << "Queue: ";
				cout << curr->index<< " " << curr->weight << " ";
				curr = curr->next;
			}
		}
	}
};


