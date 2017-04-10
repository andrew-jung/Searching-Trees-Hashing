#include<iostream>
#include<string>
#include<fstream>
#include<chrono>
#include <conio.h>

using namespace std;
using namespace std::chrono;

// Reference: http://proprogramming.org/c-program-to-implement-avl-tree/

int max(int x, int y) { // Function to find the greater number, determines height of tree
	if (x > y)
		return x;
	else
		return y;
}

string to_lower(string s) { // Lower case strings for comparisons
	string temp = s;
	for (int i = 0; i < s.length(); i++) { // Loop through string and check each char
		temp[i] = tolower(s[i]); 
	}
	return temp;
}

bool check_num(string s) { // Check if the string is a number 
	for (int i = 0; i < s.length(); i++) {
		int code = s[i];
		if (code < 48 || code > 57) // If ASCII code is not between 48 - 57 -> not a number
			return false;
	}
	return true;
}

string str_check(string s) { // Remove special characters from strings
	string temp = s;
	for (int i = 0; i < temp.length(); i++) { // Remove these characters
		if (temp[i] == ',' || temp[i] == '"' || temp[i] == '(' || temp[i] == ')' || temp[i] == '#' || temp[i] == '&' || temp[i] == '.' || temp[i] == '\n') {
			temp.erase(i, 1); // Delete the character
			i--;
		}
	}
	return temp;
}

struct Node { // Node for a List
	string word = "";
	Node * next = NULL;
};

class List { // Linked List
public: // Linked list methods:
	Node *head;

	List() { // Constructor
		head = NULL;
	}

	bool push_back(Node n) { // Inserting in a linked List
		Node *e = new Node;
		*e = n; // Temp
		if (head == NULL) {
			head = e;
			return true;
		}
		else {
			Node* current = head;
			while (current->next != NULL) {
				current = current->next;
			}
			current->next = e;
			return true;
		}
	}

	bool remove(int m) { // Removing elements from List
		Node *current = head;
		if (m == 1) {
			Node * temp = head;
			head = head->next;
			delete temp;
			return true;
		}

		int count = 1;
		while (count < m - 1) {
			current = current->next;
			count++;
		}

		Node *temp = current->next;
		current->next = current->next->next;
		delete temp;
		return true;
	}

	Node *begin() { // giving address of start of List
		return head;
	}

	int size() { // return size of List
		int count = 0;
		Node * current = head;
		while (current != NULL) {
			count++;
			current = current->next;
		}
		return count;
	}

	void display() { // displaying linked List
		Node * current = head;
		while (current != NULL) {
			cout << current->word << " ";
			current = current->next;
		}
		cout << endl;
	}

	bool find(string s) { // searching for a string in a list
		Node * current = head;
		while (current != NULL)
		{
			if (current->word == s)
			{
				return true;
			}
			current = current->next;
		}
		return false;
	}

};

struct AVLNode { // Node for an avl tree
	string word;
	AVLNode *left;
	AVLNode *right;
}*root; // declaring pointer root 

class AVLTree { // AVL tree class
public:
	AVLTree() { // Constructor
		root = NULL;
	}

	int height(AVLNode *temp) { // height of avl tree
		int h = 0;
		if (temp != NULL) {

			int leftHeight = height(temp->left); // height of a left subtree

			int rightHeight = height(temp->right); // height of a right subtree

			int maxHeight = max(leftHeight, rightHeight); // height of tree is one plus the height of greater subtree

			h = maxHeight + 1;
		}
		return h;
	}

	int difference(AVLNode *temp) { // calculating difference in height of tree

		int leftHeight = height(temp->left);

		int rightHeight = height(temp->right);

		int b_factor = leftHeight - rightHeight; // ?

		return b_factor;
	}


	// Rotations: https://www.cise.ufl.edu/~nemo/cop3530/AVL-Tree-Rotations.pdf
	// https://www.tutorialspoint.com/data_structures_algorithms/avl_tree_algorithm.htm

	AVLNode *rr_rotation(AVLNode *parent) { // right-right rotation
		AVLNode *temp;

		temp = parent->right;

		parent->right = temp->left;

		temp->left = parent;

		return temp;
	}


	AVLNode *ll_rotation(AVLNode *parent) { // left-left rotation
		AVLNode *temp;

		temp = parent->left;

		parent->left = temp->right;

		temp->right = parent;

		return temp;

	}

	AVLNode * lr_rotation(AVLNode *parent) { // left-right rotation
		AVLNode *temp;

		temp = parent->left;

		parent->left = rr_rotation(temp);

		return ll_rotation(parent);

	}

	AVLNode * rl_rotation(AVLNode *parent) { // right-left rotation
		AVLNode *temp;

		temp = parent->right;

		parent->right = ll_rotation(temp);

		return rr_rotation(parent);

	}

	AVLNode *balance(AVLNode *temp) { // Balance the tree
		int bal_factor = difference(temp); // check the difference of tree

		if (bal_factor > 1) { // If difference is greater than 1
			if (difference(temp->left) > 0) {
				temp = ll_rotation(temp); // Do LL rotation
			}

			else {
				temp = lr_rotation(temp); // Otherwise do LR rotation
			}
		}

		else if (bal_factor < -1) { // If difference  is less then -1
			if (difference(temp->right) > 0) {
				temp = rl_rotation(temp); // Do RL rotation
			}

			else {
				temp = rr_rotation(temp); // Otherwise do RR rotation
			}
		}
		return temp;

	}

	AVLNode *insert(AVLNode *root, string value) { // Insert method for tree
		if (root == NULL) { // if tree is empty
			root = new AVLNode;

			root->word = value;

			root->left = NULL;

			root->right = NULL;

			return root;
		}

		else if (value < root->word) { // if word is 'smaller' than root word
			root->left = insert(root->left, value);

			root = balance(root);
		}

		else if (value >= root->word) { // if word is greater than root word
			root->right = insert(root->right, value);

			root = balance(root);
		}
		return root;
	}

	void display(AVLNode *ptr, int level) { // Displaying tree in a form of tree, used reference
		int i;
		if (ptr != NULL) {

			display(ptr->right, level + 1);
			cout << "\n";

			if (ptr == root) {
				cout << "Root -> ";
			}

			for (i = 0; i < level && ptr != root; i++) {
				cout << "        ";
			}

			cout << ptr->word;
			display(ptr->left, level + 1);
		}
	}

	bool search(AVLNode* r, string w) { // searching in a tree
		if (r == NULL) {
			return false;
		}

		if (r->word == w) {
			return true;
		}

		else if (w >= r->word) {
			return search(r->right, w);
		}

		else if (w < r->word) {
			return search(r->left, w);
		}
	}
};


int main() {

	// Variables
	AVLTree dictionary;
	fstream file; // file handler
	string temp = ""; // Temp string for file
	Node word;
	fstream mfile; // file handle 
	List mispelled; // List to store mispelled words

	mfile.open("mispelled.txt", ios::in); // opening mispelled.txt to compare against Dictionary
	file.open("dictionary.txt", ios::in); // opening Dictionary.txt file

	if (!file && !mfile) {
		cout << "Unable to open file(s)." << endl;
	}

	else {
		while (getline(file, temp)) { // while there are lines in file
			root = dictionary.insert(root, temp); // Insert
		}

		cout << "AVL Tree - Dictionary.txt: " << endl;

		dictionary.display(root, 1); // Print

		while (getline(mfile, temp, ' ')) { // Reading mispelled words file on basis of spaces
			temp = str_check(temp); // Removing special characters 

			word.word = temp; // storing in a Node

			if (temp != "")
				mispelled.push_back(word); // inserting into a List
		}
		cout << "\n\nList of words to be checked are: \n\n";
		mispelled.display();
	}

	cout << "\nMispelled words are: " << endl;

	Node *ite = mispelled.begin(); // iterator to traverse through List
	cout << endl;

	high_resolution_clock::time_point t1 = high_resolution_clock::now();

	while (ite != NULL) { // looping through each word
		string temp = ite->word;
		temp = to_lower(temp); // converting to lower case

		if (!check_num(temp)) { // skip if it's a number
			if (!dictionary.search(root, temp)) // dislay the word if not found in dictionary hash table
				cout << ite->word << endl;
		}
		ite = ite->next; // next word
	}

	high_resolution_clock::time_point t2 = high_resolution_clock::now();

	auto duration = duration_cast<milliseconds>(t2 - t1).count();

	cout << "Total searching time for all the words: " << duration << " milliseconds" << endl;

	_getch();
}