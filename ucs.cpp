#include "stdafx.h"
#include <iostream>
#include <vector>
#include <math.h>
#include <cmath>
#include <string>
#include <queue>

using namespace std;

//node struct
struct node {
	int row;
	int col;
	int cost;
	node *parent;

	node(int r, int c, int co)
	{
		row = r;
		col = c;
		cost = co;
		parent = nullptr;
	}
};

struct CompareCost
{
	bool operator()(node const& cost1, node const& cost2)
	{
		return cost1.cost < cost2.cost;
	}
};


double distance(int pacman_r, int pacman_c, int food_r, int food_c)
{
	double x = pow((pacman_r - food_r), 2);
	double y = pow((pacman_c - food_c), 2);
	return sqrt(x + y);
}

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

void ucs(int r, int c, int pacman_r, int pacman_c, int food_r, int food_c, vector <string> grid) {

	priority_queue<node, vector<node>, CompareCost> Queue;
	vector<node> visited;
	vector<node> finalPath;

	double dist = 0;

	node * root = new node(pacman_r, pacman_c, 0);

	Queue.push(*root);

	while (!Queue.empty())
	{
		*root = Queue.top();
		Queue.pop();

		node * newCreatedNode = new node(root->row, root->col, 0);
		newCreatedNode->parent = root->parent;

		//check if we have visited already
		if (checkVisited(visited, newCreatedNode) == true)
		{
			continue;
		}
		else
		{
			visited.push_back(*newCreatedNode);
		}

		//check if we reached goal state
		dist = distance(newCreatedNode->row, newCreatedNode->col, food_r, food_c);
		if (dist == 0)
		{
			break;
		}

		//if UP is traversable
		if (grid[newCreatedNode->row - 1][newCreatedNode->col] == '-')
		{
			node * newNode = new node(newCreatedNode->row - 1, newCreatedNode->col, 1);
			newNode->parent = newCreatedNode;
			if (checkVisited(visited, newNode) == false)
			{
				Queue.push(*newNode);
			}
		}
		else if (grid[newCreatedNode->row - 1][newCreatedNode->col] == '.')
		{
			node * newNode = new node(newCreatedNode->row - 1, newCreatedNode->col, 0);
			newNode->parent = newCreatedNode;
			if (checkVisited(visited, newNode) == false)
			{
				Queue.push(*newNode);
			}
		}

		//if LEFT is traversable
		if (grid[newCreatedNode->row][newCreatedNode->col - 1] == '-')
		{
			node * newNode = new node(newCreatedNode->row, newCreatedNode->col - 1, 1);
			newNode->parent = newCreatedNode;
			if (checkVisited(visited, newNode) == false)
			{
				Queue.push(*newNode);
			}
		}
		else if (grid[newCreatedNode->row][newCreatedNode->col - 1] == '.')
		{
			node * newNode = new node(newCreatedNode->row, newCreatedNode->col - 1, 0);
			newNode->parent = newCreatedNode;
			if (checkVisited(visited, newNode) == false)
			{
				Queue.push(*newNode);
			}
		}

		//if RIGHT is traversable
		if (grid[newCreatedNode->row][newCreatedNode->col + 1] == '-')
		{
			node * newNode = new node(newCreatedNode->row, newCreatedNode->col + 1, 1);
			newNode->parent = newCreatedNode;
			if (checkVisited(visited, newNode) == false)
			{
				Queue.push(*newNode);
			}
		}
		else if (grid[newCreatedNode->row][newCreatedNode->col + 1] == '.')
		{
			node * newNode = new node(newCreatedNode->row, newCreatedNode->col + 1, 0);
			newNode->parent = newCreatedNode;
			if (checkVisited(visited, newNode) == false)
			{
				Queue.push(*newNode);
			}
		}

		//if DOWN is traversable
		if (grid[newCreatedNode->row + 1][newCreatedNode->col] == '-')
		{
			node * newNode = new node(newCreatedNode->row + 1, newCreatedNode->col, 1);
			newNode->parent = newCreatedNode;
			if (checkVisited(visited, newNode) == false)
			{
				Queue.push(*newNode);
			}
		}
		else if (grid[newCreatedNode->row + 1][newCreatedNode->col] == '.')
		{
			node * newNode = new node(newCreatedNode->row + 1, newCreatedNode->col, 0);
			newNode->parent = newCreatedNode;
			if (checkVisited(visited, newNode) == false)
			{
				Queue.push(*newNode);
			}
		}
	}

	while (root->parent != NULL)
	{
		finalPath.insert(finalPath.begin(), *root);
		root = root->parent;
	}

	cout << visited.size() << endl;
	for (int i = 0; i < visited.size(); i++)
	{
		cout << visited[i].row << " " << visited[i].col << endl;
	}

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

	ucs(r, c, pacman_r, pacman_c, food_r, food_c, grid);

	return 0;
}
