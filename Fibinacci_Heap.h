
// C++ program to demonstrate building 
// and inserting in a Fibonacci heap 
#include <cstdlib> 
#include <iostream> 
#include <malloc.h> 
using namespace std;




class Fibonacci_Heap {

struct node 
{
	node* parent; // Parent pointer 
	node* child; // Child pointer 
	node* left; // Pointer to the node on the left 
	node* right; // Pointer to the node on the right 
	int key; // Value of the node 
	int weight;
	int degree; // Degree of the node 
	char mark; // Black or white mark of the node 
	char c; // Flag for assisting in the Find node function 
};


public:


	Fibonacci_Heap()
	{
		
	}


	struct node* mini = NULL;

	// Declare an integer for number of nodes in the heap 
	int no_of_nodes = 0;

	void insertion(int val, int w)
	{
		struct node* new_node = (struct node*)malloc(sizeof(struct node));
		new_node->key = val;
		new_node->weight = w;
		new_node->degree = 0;
		new_node->mark = 'W';
		new_node->c = 'N';
		new_node->parent = NULL;
		new_node->child = NULL;
		new_node->left = new_node;
		new_node->right = new_node;
		if (mini != NULL) {
			(mini->left)->right = new_node;
			new_node->right = mini;
			new_node->left = mini->left;
			mini->left = new_node;
			if (new_node->weight > mini->weight)
				mini = new_node;
		}
		else {
			mini = new_node;
		}
		no_of_nodes++;
	}


	////////////////////////////////
	// Function to display the heap 




	// Linking the heap nodes in parent child relationship 
	void Fibonnaci_link(struct node* ptr2, struct node* ptr1)
	{
		(ptr2->left)->right = ptr2->right;
		(ptr2->right)->left = ptr2->left;
		if (ptr1->right == ptr1)
			mini = ptr1;
		ptr2->left = ptr2;
		ptr2->right = ptr2;
		ptr2->parent = ptr1;
		if (ptr1->child == NULL)
			ptr1->child = ptr2;
		ptr2->right = ptr1->child;
		ptr2->left = (ptr1->child)->left;
		((ptr1->child)->left)->right = ptr2;
		(ptr1->child)->left = ptr2;
		if (ptr2->weight > (ptr1->child)->weight)
			ptr1->child = ptr2;
		ptr1->degree++;
	}

	void Consolidate()
	{
		int temp1;
		float temp2 = (log(no_of_nodes)) / (log(2));
		struct node* arr[temp2];
		for (int i = 0; i <= temp2; i++)
			arr[i] = NULL;
		node* ptr1 = mini;
		node* ptr2;
		node* ptr3;
		node* ptr4 = ptr1;
		do {
			ptr4 = ptr4->right;
			temp1 = ptr1->degree;
			while (arr[temp1] != NULL) {
				ptr2 = arr[temp1];
				if (ptr1->weight > ptr2->weight) {
					ptr3 = ptr1;
					ptr1 = ptr2;
					ptr2 = ptr3;
				}
				if (ptr2 == mini)
					mini = ptr1;
				Fibonnaci_link(ptr2, ptr1);
				if (ptr1->right == ptr1)
					mini = ptr1;
				arr[temp1] = NULL;
				temp1++;
			}
			arr[temp1] = ptr1;
			ptr1 = ptr1->right;
		} while (ptr1 != mini);
		mini = NULL;
		for (int j = 0; j <= temp2; j++) {
			if (arr[j] != NULL) {
				arr[j]->left = arr[j];
				arr[j]->right = arr[j];
				if (mini != NULL) {
					(mini->left)->right = arr[j];
					arr[j]->right = mini;
					arr[j]->left = mini->left;
					mini->left = arr[j];
					if (arr[j]->weight > mini->weight)
						mini = arr[j];
				}
				else {
					mini = arr[j];
				}
				if (mini == NULL)
					mini = arr[j];
				else if (arr[j]->weight > mini->weight)
					mini = arr[j];
			}
		}
	}


	void Extract_min()
	{
		if (mini == NULL)
			cout << "The heap is empty" << endl;
		else {
			node* temp = mini;
			node* pntr;
			pntr = temp;
			node* x = NULL;
			if (temp->child != NULL) {

				x = temp->child;
				do {
					pntr = x->right;
					(mini->left)->right = x;
					x->right = mini;
					x->left = mini->left;
					mini->left = x;
					if (x->weight > mini->weight)
						mini = x;
					x->parent = NULL;
					x = pntr;
				} while (pntr != temp->child);
			}
			(temp->left)->right = temp->right;
			(temp->right)->left = temp->left;
			mini = temp->right;
			if (temp == temp->right && temp->child == NULL)
				mini = NULL;
			else {
				mini = temp->right;
				Consolidate();
			}
			no_of_nodes--;
		}
	}



	void Cut(struct node* found, struct node* temp)
	{
		if (found == found->right)
			temp->child = NULL;

		(found->left)->right = found->right;
		(found->right)->left = found->left;
		if (found == temp->child)
			temp->child = found->right;

		temp->degree = temp->degree - 1;
		found->right = found;
		found->left = found;
		(mini->left)->right = found;
		found->right = mini;
		found->left = mini->left;
		mini->left = found;
		found->parent = NULL;
		found->mark = 'B';
	}


	// Recursive cascade cutting function 
	void Cascase_cut(struct node* temp)
	{
		node* ptr5 = temp->parent;
		if (ptr5 != NULL) {
			if (temp->mark == 'W') {
				temp->mark = 'B';
			}
			else {
				Cut(temp, ptr5);
				Cascase_cut(ptr5);
			}
		}
	}


	// Function to decrease the value of a node in the heap 
	void Decrease_key(struct node* found, int val)
	{
		if (mini == NULL)
			cout << "The Heap is Empty" << endl;

		if (found == NULL)
			cout << "Node not found in the Heap" << endl;

		found->key = val;

		struct node* temp = found->parent;
		if (temp != NULL && found->weight > temp->weight) {
			Cut(found, temp);
			Cascase_cut(temp);
		}
		if (found->weight > mini->weight)
			mini = found;
	}




	void display()
	{
		node* ptr = mini;
		if (ptr == NULL)
			cout << "The Heap is Empty" << endl;

		else {
			cout << "The root nodes of Heap are: " << endl;
			do {
				cout << ptr->key;
				ptr = ptr->right;
				if (ptr != mini) {
					cout << "-->";
				}
			} while (ptr != mini && ptr->right != NULL);
			cout << endl
				<< "The heap has " << no_of_nodes << " nodes" << endl
				<< endl;
		}
	}




};
