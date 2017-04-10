#include<iostream>
#include<string>
#include<fstream>
#include<chrono>
#include <conio.h>

using namespace std;
using namespace std::chrono;

// Use methods/clasess from AVLTree:
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

/*this hashes table has an array of 10 linked List, so to store any word in string, it'll take the first character of the string, convert it into into
it's ascii integer code, take modulo by 10 and insert into that resultant List, thats how it'll handle collisions e.g if the word is "apple", first character
is a whose ascii is 97. 97 modulo 10 is 7 so it'll insert into the List with index is 7 */

class HashTable { 
public:
	List *hashes; // array of List 
	int size;
	int num_collisions;

	HashTable() { // Constructor
		size = 10;
		num_collisions = 0;
		hashes = new List[size];
	}

	int hash_function(char c) { // based on modulo 10
		int x = c;
		return c % size; // size is 10.
	}

	bool insert(string s) { // Inserting to hash table
		int pos = hash_function(s[0]);
		if (hashes[pos].size() > 0) { // Calculating position
			num_collisions++;
		}
		Node temp;
		temp.word = s;
		hashes[pos].push_back(temp);
		return true;
	}

	bool search(string s) { // Find in hash table
		int pos = hash_function(s[0]); 
		return hashes[pos].find(s);
	}

	void display() {
		cout << "Number of lists: " << size << endl;
		for (int i = 0; i < size; i++) {
			cout << "List #" << i << endl;
			hashes[i].display();
			cout << endl;
		}
	}
};

int main() {

	fstream file; // File stream for dictionary
	string temp = ""; // temporary string to read lines from file
	Node word;
	fstream mfile; // File stream for mispelled
	List mispelled; // List to store mispelled words
	HashTable dictionary; // hash table for dictionary, it'll have 10 lists so it'll use modulo 10

	mfile.open("mispelled.txt", ios::in); // opening file, which is to be checked
	file.open("dictionary.txt", ios::in); // opening dictionary file
	if (!file && !mfile) {
		cout << "Unable to open file(s)." << endl;
	}
	else {
		while (getline(file, temp)) { // while there are lines in file
			dictionary.insert(temp); // insert into hash table
		}

		cout << "Hash table of dictionary.txt words: " << endl;
		dictionary.display(); // display hash table

		while (getline(mfile, temp, ' ')) { // reading mispelled words file on basis of spaces
			temp = str_check(temp); // removing special characters 

			word.word = temp; // storing in a Node

			mispelled.push_back(word); // inserting into a List
		}

		cout << "Mispelled.txt: " << endl;
		mispelled.display();
	} // End else

	cout << "\n\n Mispelled words are...\n";
	Node *ite = mispelled.begin(); // iterator to traverse through List
	cout << endl;

	// Wrap timer:
	high_resolution_clock::time_point t1 = high_resolution_clock::now();

	while (ite != NULL) { // looping through each word
		string temp = ite->word;
		temp = to_lower(temp); // converting to lower case

		if (!check_num(temp)) { // skip if it's a number
			if (!dictionary.search(temp)) { // dislay the word if not found in dictionary hashes table
				cout << ite->word << endl;
			}
		}
		ite = ite->next; // next word
	}

	high_resolution_clock::time_point t2 = high_resolution_clock::now();
	auto duration = duration_cast<milliseconds>(t2 - t1).count();

	cout << "\n\nTotal number of collisions: " << dictionary.num_collisions << endl;

	cout << "Total searching time: " << duration << " milliseconds." << endl;

	_getch();
}