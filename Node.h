#pragma once


#include <iostream>
#include <sstream>
using namespace std;


struct Node
{
	int index;
	int weight;
	Node* next;
	Node* previous;


	//////////////////////////////

	Node()
	{
		//Normal 
		index = 0;
		weight = 0;
		next = NULL;
		previous = NULL;
		
	}//constructor


};

