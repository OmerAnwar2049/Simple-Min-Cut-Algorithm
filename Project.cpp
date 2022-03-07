#include <iostream>
#include <sstream>
#include <fstream>
#include <iostream>
#include <string>
#include <fstream>
#include <stack>
#include <queue>
#include <vector>
#include <list> 
#include <algorithm>
#include "PriorityQueue.h"
#include "List.h"
#include <chrono>
using namespace std;



class Graph
{

private:
	int** array;

	int V;										 //SIZE OF VERTICES

	int start;

	int cut;

public:


	Graph(int vertices, int testcase, int s)     // PARAMETRIZED CONSTRUCTOR
	{

		V = vertices;							 // NUMBER OF VERTICES

		cut = 10000;							 // VALUE OF CUT AT START IN INF

		start = s;								 // START POINT


		array = new int* [vertices];			 //DECLARING THE NEW MATRIX
		for (int i = 0; i < V; i++)
			array[i] = new int[V];


	}//func end


	void AddEdge(int i, int j, int flow)		 // ADDING EDGES
	{
		array[i][j] = flow;						 // STORING VALUES IN MATRIX

	}



	int Extract_Max(int* values)
	{
		vector<int> VECTOR;

		for (int i = 0; i < V; i++)				    // PUSHING VALUES IN MATRIX
		{
			VECTOR.push_back(values[i]);

		}

		make_heap(VECTOR.begin(), VECTOR.end());    // MAKING HEAP

		for (int i = 0; i < V; i++)
		{
			if (values[i] == VECTOR.front())        // comparing max value for index
			{
				return i;
			}
		}
		return 0;
	}


	void Show(int* values, int size)
	{
		for (int i = 0; i < size; i++)
		{
			cout << values[i] << " ";
		}
		cout << endl;
	}


	// TO FIND THE CUT FROM A SPECIFIC POINT
	int Find_Cut(int point)
	{

		int sum = 0;

		for (int i = 0; i < V; i++)
		{
			sum += array[point][i];
		}

		return sum;

	}


	// GRAPH ORDERING WILL BE DONE HERE   POORLY OPTIMISED O(V4)
	// WILL RETURN THE LAST 2 vertices
	/*pair<int, int> Ordering()
	{

		int* Partition = new int[V];
		int* values = new int[V];
		bool* Visited = new bool[V];

		int s, t, point = 1;


		for (int i = 0; i < V; i++)
		{
			Partition[i] = -1;
			Visited[i] = false;
			values[i] = 0;

		}

		Partition[0] = start; // filling the start node

		Visited[start] = true;

		for (int outer = 1; outer < V; outer++)
		{

			//assigning 0 to values
			for (int i = 0; i < V; i++)
			{
				values[i] = 0;
			}


			for (int i = 0; Partition[i] != -1; i++)
			{
				for (int j = 0; j < V; j++)
				{

					if (Visited[j])
						continue;

					values[j] += array[Partition[i]][j];
				}
			}

			int tightly_connected_vertix = Extract_Max(values);

			Visited[tightly_connected_vertix] = true;

			Partition[outer] = tightly_connected_vertix;

		}//main outer loop iteration that fills the partition A


		//Show(Partition, V);

		s = Partition[V - 2];
		t = Partition[V - 1];

		//cout << s << " " << t;

		delete[]Partition;
		delete[]Visited;
		delete[]values;

		if(start != 0)        //SO THAT THE VALUE OF START NODE IS REDUCED BECAUSE THE GRAPH IS BEING MERGED
		start--;

		return make_pair(s, t);
	}//func end*/





	pair<int, int> Ordering()
	{

		int* Partition = new int[V];
		int* values = new int[V];
		bool* Visited = new bool[V];

		int s, t, point = 1;


		for (int i = 0; i < V; i++)
		{
			Partition[i] = -1;
			Visited[i] = false;
			values[i] = 0;
		}

		Partition[0] = start; // filling the start node

		Visited[start] = true;

		for (int j = 0; j < V; j++)
		{
			if (Visited[j])
			{
				values[j] = -1;
			}
			else
				values[j] += array[start][j];
		}

		for (int outer = 1; outer < V; outer++)
		{

			int max = -10;
			int index = -5;

			for (int i = 0; i < V; i++)
			{
				if (values[i] > max)
				{
					max = values[i];
					index = i;
				}
			}

			int tightly_connected_vertix = index;

			Visited[tightly_connected_vertix] = true;

			values[tightly_connected_vertix] = -1;

			for (int j = 0; j < V; j++)
			{
				if (!Visited[j])
				values[j] += array[tightly_connected_vertix][j];
			}


			Partition[outer] = tightly_connected_vertix;

		}//main outer loop iteration that fills the partition A


		s = Partition[V - 2];  // THE LAST TWO VERTICES ADDED
		t = Partition[V - 1];


		delete[]Partition;
		delete[]Visited;
		delete[]values;

		if (start != 0)        //SO THAT THE VALUE OF START NODE IS REDUCED BECAUSE THE GRAPH IS BEING MERGED
			start--;

		return make_pair(s, t);
	}//func end



	void Merging(int s, int t)
	{

		/// DECLARING A NEW CONTRACTED GRAPH
		int** Contracted_Graph = new int* [V - 1];
		for (int i = 0; i < V - 1; i++)
			Contracted_Graph[i] = new int[V - 1];



		// ADDING VALUES ROWWISE FROM S TO T
		for (int i = 0; i < V; i++)
		{
			if (i != s)
			{
				array[s][i] += array[t][i];
			}
		}

		// ADDING VALUES COLUNWISEWISE FROM S TO T
		for (int i = 0; i < V; i++)
		{
			if (i != s)
			{
				array[i][s] += array[i][t];
			}
		}


		int a = 0;
		int b = 0;

		/// copying graph avoiding self loops
		for (int i = 0; i < V; i++)
		{
			for (int j = 0; j < V; j++)
			{
				if ((i != t) && (j != t))
				{
					Contracted_Graph[a][b++] = array[i][j];
				}
			}
			if (i != t)
			{
				a++;
				b = 0;
			}
		}

		for (int i = 0; i < V; i++)  // DELETEING PREVIOUS MATRIX
		{
			delete[] array[i];
		}
		delete[] array;


		V--;					    //REDUCING THE  NUMBER OF VERTICES

		array = Contracted_Graph;   // POINTING CURRENT MATRIX DOUBLE PINTER TO NEW MATRIX

	}///func end



	int Min_Cut_Phase()		//STORING MIN CUT OF THAT PHASE AND GRAPH CONTRACTION WILL BE DONE HERE
	{

		pair<int, int> st;
		int min_cut = 0, s, t;

		st = Ordering();			// ORDERING OF THE GRAPH TO FIND s AND t

		s = st.first;				//storing s

		t = st.second;			    //storing t

		min_cut = Find_Cut(t);		//FINDING THE MINIMUM CUT OF THIS SPECIFIC PHASE


		Merging(s, t);				// MERGING THE GRAPH BY THE GIVEN POINT S AND T

		return min_cut;				// RETURNING MIN CUT OF THIS PHASE

	}//func end





	int Min_Cut()						// MAIN FUNCTION
	{

		while (V > 1)					// WHILE VERTICES ARE > 1
		{

			int C = Min_Cut_Phase();    // CALLING MIN CUT PHASE

			if (C < cut)				// STORING VALUE OF LEAST CUT
			{
				cut = C;
			}

		}

		return cut;						// RETURNING VALUE OF CUT

	}///func end


	void Display_Graph()
	{
		for (int i = 0; i < V; i++)
		{

			for (int j = 0; j < V; j++)
			{
				cout << array[i][j] << " ";
			}

			cout << endl;
		}

	}//func end


	~Graph()
	{

		for (int i = 0; i < V; i++)
		{
			delete[] array[i];
		}
		delete[] array;
	}

};





int main() {


	fstream input;
	input.open("Testcases.txt", ios::in);

	string S;

	getline(input, S, '\n');

	const int size = stoi(S);

	string digit;

	Graph* G;

	int F;

	int v;

	int begin;


	auto start = std::chrono::steady_clock::now();


	for (int i = 0; i < size; i++)
	{

		string vertices = "";
		string start = "";


		getline(input, vertices, '\n');
		getline(input, start, '\n');


		v = stoi(vertices);
		begin = stoi(start);



		G = new Graph(v, i + 1, begin);

		for (int j = 0; j < v; j++)
		{

			for (int k = 0; k < v; k++)
			{

				digit.clear();

				if (k != (v - 1))
					getline(input, digit, ' ');

				else
					getline(input, digit, '\n');

				F = stoi(digit);


				G->AddEdge(j, k, F);

			}
		}
		cout << "Testcase: " << i + 1 << endl;
		cout << "THE MIN CUT IS >> " << G->Min_Cut() << endl << endl;
		delete G;

	}//big for loop


	input.close();

	auto end = std::chrono::steady_clock::now();

	double time = double(std::chrono::duration_cast <std::chrono::nanoseconds>(end - start).count());

	cout << "Time Taken >> " << time/ 1e9 << " seconds\n";

	return 0;
}





