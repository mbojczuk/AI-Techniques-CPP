#include "stdafx.h"
#include <iostream>
#include <vector>
#include <math.h>
#include <cmath>
#include <string>

using namespace std;

//node struct with constructor for new node
struct node {
	int row;
	int col;
	node *parent;

	node(int r, int c)
	{
		row = r;
		col = c;
		parent = nullptr;
	}
};

//checks distance between pacman and the food, returns a double
double distance(int pacman_r, int pacman_c, int food_r, int food_c)
{
	double x = pow((pacman_r - food_r), 2);
	double y = pow((pacman_c - food_c), 2);
	return sqrt(x + y);
}

//Boolean checker for visited path using the node we are currently on
bool checkVisited(vector<node> & visitedList, node * tempNode)
{
	for (int i = 0; i < visitedList.size(); i++)
	{
		if (visitedList[i].row == tempNode->row && visitedList[i].col == tempNode->col)
		{
			return true;
		}
	}
	return false;
}

void dfs(int r, int c, int pacman_r, int pacman_c, int food_r, int food_c, vector <string> grid) {

	//initializers
	vector<node> stack;
	vector<node> visited;
	vector<node> finalPath;

	double dist = 0;

	node * root = new node(pacman_r, pacman_c);
	//push the first node onto the stack with our starting position
	stack.push_back(*root);

	//while the stack is not empty
	while (!stack.empty())
	{
		//in c++ as this is dfs its first in last out, so we grab the back value
		*root = stack.back();
		//pop the back of the stack off
		stack.pop_back();

		//create a new node here and set values
		node * newCreatedNode = new node(root->row, root->col);	//created this one as before was passing across root which was just a reference to the memory location
		newCreatedNode->parent = root->parent;

		cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
		cout << "Pop Stack " << newCreatedNode->row << " " << newCreatedNode->col << endl;
		if (newCreatedNode->parent != NULL && newCreatedNode->parent->parent != NULL)
		{
			cout << "Parents Parent Row: " << newCreatedNode->parent->parent->row << " Parents Parent Col: " << newCreatedNode->parent->parent->col << endl;
		}

		//check if we have visited already
		if (checkVisited(visited, newCreatedNode) == true)
		{
			cout << "Visited: " << newCreatedNode->row << " " << newCreatedNode->col << endl;
			continue;
		}
		else
		{
			visited.push_back(*newCreatedNode);
			cout << "Push Stack ~ Not Visited " << newCreatedNode->row << " " << newCreatedNode->col << endl;
		}

		//check if we reached goal state, if we have reached goal state (dist == 0) then break from the while loop
		dist = distance(newCreatedNode->row, newCreatedNode->col, food_r, food_c);
		if (dist == 0)
		{
			break;
		}
		
		//if UP is traversable "-" == walkable and "." == food
		if (grid[newCreatedNode->row - 1][newCreatedNode->col] == '-' || grid[newCreatedNode->row - 1][newCreatedNode->col] == '.')
		{
			node * newNode = new node(newCreatedNode->row - 1, newCreatedNode->col);
			newNode->parent = newCreatedNode;
			if (checkVisited(visited, newNode) == false)
			{
				stack.push_back(*newNode);
				cout << "Push Stack UP " << newNode->row << " " << newNode->col << endl;
				if (newCreatedNode->parent != NULL)
				{
					cout << "Parent  row: " << newCreatedNode->parent->row << " Parent col: " << newCreatedNode->parent->col << endl;
				}
			}
		}
		
		//if LEFT is traversable "-" == walkable and "." == food
		if (grid[newCreatedNode->row][newCreatedNode->col -1] == '-' || grid[newCreatedNode->row][newCreatedNode->col - 1] == '.')
		{
			node * newNode = new node(newCreatedNode->row, newCreatedNode->col-1);
			newNode->parent = newCreatedNode;
			if (checkVisited(visited, newNode) == false)
			{
				stack.push_back(*newNode);
				cout << "Push Stack LEFT " << newNode->row << " " << newNode->col << endl;
				if (newCreatedNode->parent != NULL)
				{
					cout << "Parent row: " << newCreatedNode->parent->row << " Parent col: " << newCreatedNode->parent->col << endl;
				}
				
			}
		}

		//if RIGHT is traversable "-" == walkable and "." == food
		if (grid[newCreatedNode->row][newCreatedNode->col + 1] == '-' || grid[newCreatedNode->row][newCreatedNode->col + 1] == '.')
		{
			node * newNode = new node(newCreatedNode->row, newCreatedNode->col+1);
			newNode->parent = newCreatedNode;
			if (checkVisited(visited, newNode) == false)
			{
				stack.push_back(*newNode);
				cout << "Push Stack RIGHT " << newNode->row << " " << newNode->col << endl;
				if (newCreatedNode->parent != NULL)
				{
					cout << "Parent row: " << newCreatedNode->parent->row << " Parent col: " << newCreatedNode->parent->col << endl;
				}
			}
		}

		//if DOWN is traversable "-" == walkable and "." == food
		if (grid[newCreatedNode->row + 1][newCreatedNode->col] == '-' || grid[newCreatedNode->row + 1][newCreatedNode->col] == '.')
		{
			node * newNode = new node(newCreatedNode->row + 1, newCreatedNode->col);
			newNode->parent = newCreatedNode;
			if (checkVisited(visited, newNode) == false)
			{
				stack.push_back(*newNode);
				cout << "Push Stack DOWN " << newNode->row << " " << newNode->col << endl;
				if (newCreatedNode->parent != NULL)
				{
					cout << "Parent row: " << newCreatedNode->parent->row << " Parent col: " << newCreatedNode->parent->col << endl;
				}
			}
		}
	}

	cout << "While Loop finished Node = " << root->row << " " << root->col << " Parent: " << root->parent->row << " " << root->parent->col << endl;

	while (root->parent != NULL)
	{
		if (root->parent != NULL)
		{
			cout << "Parent row final: " << root->parent->row << " Parent col final: " << root->parent->col << endl;
		}
		finalPath.insert(finalPath.begin(), *root);
		cout << "Final path insert: " << root->row << " " << root->col << endl;
		cout << "Parent row: " << root->parent->row << " Parent col: " << root->parent->col << endl;
		root = root->parent;
		
	}

	//print the visited size and list, these are all the nodes that we went to including dead ends
	cout << visited.size() << endl;
	for (int i = 0; i < visited.size(); i++)
	{
		cout << visited[i].row << " " << visited[i].col << endl;
	}

	//final path inserts at first position of the list and walks back through each parent node
	cout << finalPath.size() << endl;
	cout << pacman_r << " " << pacman_c << endl;
	for (int i = 0; i < finalPath.size(); i++)
	{
		cout << finalPath[i].row << " " << finalPath[i].col << endl;
	}
}

int main(void) {

	int r, c, pacman_r, pacman_c, food_r, food_c;

	cin >> pacman_r >> pacman_c;
	cin >> food_r >> food_c;
	cin >> r >> c;

	vector <string> grid;

	for (int i = 0; i<r; i++) {
		string s; cin >> s;
		grid.push_back(s);
	}

	dfs(r, c, pacman_r, pacman_c, food_r, food_c, grid);

	return 0;
}
