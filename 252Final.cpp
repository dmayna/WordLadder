// 252Final.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

#define LENGTH_OF_WORDS 5

class StackNode
{
public:
	string data;
	StackNode * ptrNext;
	StackNode() { ptrNext = NULL; data = ""; }
};

class LinkedStack
{
public:
	StackNode * ptrHead;
	void push(string inData);
	bool pop();
	bool visited(string toSearch);
	void userInput(int numInputs);
	void printStack();
	string top() { return ptrHead->data; }
	LinkedStack() { ptrHead = NULL; nodeCount = 0; }

private:
	int nodeCount;
};

void LinkedStack::push(string inData)
{
	// Insert at beginning - Unsorted list - Fastest insert
	if (ptrHead == NULL)
	{  // add first data to list
		ptrHead = new StackNode;
		ptrHead->data = inData;
		ptrHead->ptrNext = NULL;
	}
	else
	{
		StackNode * ptrNewNode = new StackNode;
		ptrNewNode->ptrNext = ptrHead;
		ptrNewNode->data = inData;
		ptrHead = ptrNewNode;
	}
	nodeCount++;
}

bool LinkedStack::pop()
{
	if (ptrHead == NULL)
	{   // no nodes ... nothing to do
		return false;
	}
	else if (nodeCount == 1)  // check only one node
	{
		cout << "POP\n";
		StackNode * ptrDel = ptrHead;
		delete ptrDel;
		ptrHead = NULL;
		nodeCount = 0;
		return true;
	}
	else    // multiple nodes
	{
		cout << "POP\n";
		StackNode * ptrDelete = ptrHead;
		ptrHead = ptrHead->ptrNext;
		delete ptrDelete;
		nodeCount--;
		return true;
	}
}

void LinkedStack::printStack()
{
	cout << "Printing Stack...\n";
	StackNode * ptrCurrent = ptrHead;  // start at the beginning
	while (ptrCurrent != NULL)
	{
		cout << ptrCurrent->data << endl;
		ptrCurrent = ptrCurrent->ptrNext; // advacne to next node
	}
	cout << endl;
}

void LinkedStack::userInput(int numInputs)
{
	string input;
	for (int i = 0; i < numInputs; i++)
	{
		cout << "Enter word to enter into Stack >";
		cin >> input;
		push(input);
	}
}

bool LinkedStack::visited(string toSearch)
{
	StackNode *ptrCurrentNode = ptrHead;
	if (ptrHead != NULL)
	{
		do
		{
			if (toSearch == ptrCurrentNode->data)
			{
				return true;
			}
			ptrCurrentNode = ptrCurrentNode->ptrNext;
		} while (ptrCurrentNode->ptrNext != NULL);
	}
	return false;
}

class GraphNode
{
public:
	GraphNode() { data = ""; weight = 0; }
	string data;
	int weight; // num of correct letters
	vector <GraphNode> children;
};

class WordGraph
{
public:
	WordGraph(string data, string beg, string end);
	void solve(string data, string beg, string end);
	void printAnswers(void);
	

private:
	int attempts;
	LinkedStack seenWords;
};

WordGraph::WordGraph(string data, string beg, string end)
{
	attempts = 0;
	solve(data, beg, end);
	/*root = new GraphNode;
	root->data = beg;
	string file = "words.txt"; // word file
	ifstream inFile(file); // input file
	while (!inFile)
	{
		cout << "Error opening File\n\n";
		exit(1);
	}
	string temp;
	seenWords.enqueue(beg);
	while (!inFile.eof())
	{
		cin >> temp;
		for (int i = 0; i < 4; i++)
		{
			if (seenWords.search(temp))
			{
				break;
			}
			if (beg[i] = temp[i]) // if they have at least one letter in common, add to graph
			{
				GraphNode *inChild = new GraphNode;
				inChild->data = temp;
				root->children.push_back(*inChild);
				// check for weight of added word
				for (int j = 0; j < 4; j++)
				{
					if (beg[i] == inChild->data[i])
					{
						inChild->weight++;
					}
				}
				break;
			}
		}
	}*/
}

void WordGraph::solve(string data, string beg, string end)
{
	bool solved = false;
	GraphNode *ptrCurrenNode = new GraphNode;
	ptrCurrenNode->data = beg;
	seenWords.push(ptrCurrenNode->data);

	while (!solved)
	{
		string file = data; // word file
		ifstream inFile(file); // input file
		while (!inFile)
		{
			cout << "Error opening File\n\n";
			exit(1);
		}
		string temp;
		GraphNode *ptrMaxWeight = new GraphNode;
		while(inFile >> temp)
		{
			//cin >> t;
			//getline(inFile, temp);
			cout << temp << "\n";
			for (int i = 0; i < LENGTH_OF_WORDS; i++)
			{
				//if (seenWords.visited(temp))
				//{
					//break; // skip if already visited still need to fix
				//}
				if (ptrCurrenNode->data[i] = temp[i]) // if they have at least one letter in common, add to graph
				{
					GraphNode *inChild = new GraphNode;
					inChild->data = temp;
					cout << inChild->data << endl; // test
					ptrCurrenNode->children.push_back(*inChild); 
					// check for weight of added word
					for (int j = 0; j < LENGTH_OF_WORDS; j++)
					{
						if (end[i] == inChild->data[i])
						{
							cout << "---ADDED WEIGHT----\n";
							inChild->weight++;
							if (inChild->weight >= ptrMaxWeight->weight)
							{
								ptrMaxWeight = inChild; // change Max weight if new word has more weight
							}
						}
					}
					cout << "-----MAX WEIGHT = " << ptrMaxWeight->data << "\n\n";
					break; // break loop if they already have at least 1 letter in common
				}
			}
		}
		// after it goes thru the whole file 
		// does not reach end of file
		ptrCurrenNode = ptrMaxWeight; // change current node to max weight node
		cout << "-------------Seen: " << ptrMaxWeight->data << "\n\n\n\n\n";
		seenWords.push(ptrMaxWeight->data); // mark word as seen
		attempts++; 
		if (ptrCurrenNode->data == end)
		{
			cout << "Completed word ladder!\n\n";
			solved = true;
		}
	}
}

void WordGraph::printAnswers(void)
{
	seenWords.printStack();
}

class WordLadder
{
public:
	WordLadder(string inFile) { beg = ""; end = ""; attempts = 0; file = inFile; }
	void start(void);
	void getWords(void);
private:
	string beg;
	string end;
	int attempts;
	string file;
};

void WordLadder::getWords(void)
{
	bool valid = false;
	while (!valid)
	{
		cout << "Enter first" << LENGTH_OF_WORDS << " letter word > ";
		cin >> beg;
		cout << "Enter second" << LENGTH_OF_WORDS << " letter word > ";
		cin >> end;
		if (beg.length() == LENGTH_OF_WORDS && end.length() == LENGTH_OF_WORDS) // also need to check if real words
		{
			valid = true;
		}
		else
		{
			cout << "\nPlease enter only " << LENGTH_OF_WORDS << " letter words\n";
		}
	}
}

void WordLadder::start(void)
{
	getWords();
	WordGraph Ladder(file, beg, end);
	Ladder.printAnswers();
}

int main()
{
	/*string file = "words.txt"; // word file
	ifstream inFile(file); // input file
	while (!inFile)
	{
		cout << "Error opening File\n\n";
		exit(1);
	}
	cout << "Opened File\n";
	string temp = " ";
	while (!inFile.eof())
	{
		cout << "Opened File\n";
		cin >> temp;
		cout << temp << "\n";
	}*/
	WordLadder game("words.txt");
	game.start();



	/* for bst
	string max = "0";
	string min = "100";

	for (int i = 0; i < 4; i++)
	{
	if (q.head() > max)
	{
	max = q.head();
	}
	if (q.head() < min)
	{
	min = q.head();
	}
	q.head();
	q.dequeue();
	}
	cout << "Max = " << max << "\n";
	cout << "Min = " << min << "\n";


	*/
    return 0;
}