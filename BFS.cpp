#include <vector>
#include <deque>
#include <iostream>
#include <list>	
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

struct node 
{
	node(int v):value(v){}	
	int distance; //distance from the parent node
	node * parent; //pointer to the parent of this node 
	int state; // NULL = 0, 1 = red, 2 = green	
	vector<node *> neighbors; // vector of nodes adjacent to the node, this is what makes adjacency list
	vector<int> neighborComp;
	int value;
};

int main(int argc, char * argv[])
{
	vector<node *> nodes; // acts as adjacency list of nodes

	//argv[2] will hold the integer argument
	string inputFile = argv[1];
	ifstream infile(inputFile.c_str());
	string line;

	int nodeCount;
	int indexCount;
	bool firstLine = true; //used to track if number of nodes extracted
	bool firstInt = true; //used to track if an integer has been extracted from the line yet
	
	while(getline(infile, line))
	{
		//iterate over the chracters in line and remove the : 
		for()
		stringstream ss(line);
		if(firstLine)
		{
			ss >> nodeCount;							
			firstLine = false;
		}
		else // need to create a node assign the value to it and build the neighbor vector for it
		{
			int val;
			char bar;
			cout << "the line is : " << line << endl;
			while(ss >> val || ss >> bar)
			{
				cout << "value is:" << val << endl;
				if(firstInt)
				{ 
			//		cout << "adding a node" << endl;
					node * newNode = new node(val); 
					nodes.push_back(newNode);	
			//		cout << nodes.size() << endl;
					firstInt = false;
				}
				else
				{
					// the plan: create a vector of ints and then later compare values to see what needs to be added
					// to the proper vector of pointers
					nodes[indexCount]->neighborComp.push_back(val);
					cout << nodes[indexCount]->neighborComp[0];
					indexCount += 1;
				}
				
				cout << "getting here ? " << endl;
			}
			firstInt = true;
		}
	}
	cout << "this is the node count: " << nodeCount << endl;
/*	cout << nodes[0]->value << endl;
	cout << nodes[1]->value << endl;
	cout << nodes[2]->value << endl;
	cout << nodes[3]->value << endl;
*/

	deque<node *> queue; // deque being used as a queue
	node * temp; // hold node pointers temporarily

/* Run BFS on the collection of nodes */

	// set all nodes to unvisited
	for(int i = 0; i < nodes.size(); i++)
	{
		nodes[i]->state = 0; //set the state of the node to 0, white
	}

	nodes[0]->distance = 0; //distance from parent will be zero
	nodes[0]->parent = 0; // 0 is null ptr
	queue.push_front(nodes[0]);
	vector<int> output; // vector for output
	
	//cout << nodes[0]->distance << endl;
	
	while(queue.size() != 0)
	{
		temp = queue.front(); // set first element in queue to temp pointer
		queue.pop_front(); // remove the element from the front of the queue
		output.push_back(temp->value); // write the output to a vector
		temp->state = 1;
		
		vector<node *> adjacent = temp->neighbors;
	
		for(int i = 0; i < adjacent.size(); i++)
		{
			if(adjacent[i]->state == 0)
			{
				queue.push_back(adjacent[i]); // push the node pointer to the queue
				adjacent[i]->state = 2; // state is now green
				adjacent[i]->distance = temp->distance + 1;
				adjacent[i]->parent = temp;
			}
		}; 
	}
	//need to free memory
	// some day :P	
	cout << "size of output: " << output.size() << endl;
	for(int i = 0; i < output.size(); i++)
	{
		cout << output[i] << endl;
	}
}
