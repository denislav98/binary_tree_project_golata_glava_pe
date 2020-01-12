#include <iostream>
#include <stdio.h>
#include <string>
#include<bits/stdc++.h> 

using namespace std;

class Book {
private:
	string titles;
	string* authors;
	string date;
	bool isAvailable;
public:
	Book();
	void showBook();
	string getDate() {
		return date;
	}
	bool getIsAvailable() {
		return isAvailable;
	}
	~Book() {
		cout << "Destroy Book!";
	}
};

Book::Book() {
	cout << "Zaglawie: ";
	cin >> titles;
	cout << "Count Avtori: ";
	int a;
	cin >> a;
	authors = new string[a];
	for (int i = 0; i < a; i++)
	{
		cout << "Awtor: ";
		cin >> authors[i];
		cout << " ";
	}
	cout << "Date: ";
	cin >> date;
}

void Book::showBook() {
	cout << "Zaglawie " << titles << endl;
	for (int i = 0; i < sizeof(authors); i++)
	{
		cout << "Awtor " << authors[i] << endl;
	}
	cout << "Date " << date << endl;
}

class Library {
private:
	int count;
	Book* books;
public:
	Library();
	void getBooks(string dates);
	~Library() {
		cout << "Destroy Library!";
	}
};

Library::Library() {
	cout << "Count Knigi: ";
	cin >> count;
	books = new Book[count];
}

void Library::getBooks(string dates) {
	for (int i = 0; i < count; i++)
	{
		Book* b;
		b = &books[i];
		if (b->getDate() == dates)
		{
			b->showBook();
		}
	}
}

void sortString(string& str)
{
	sort(str.begin(), str.end());
	cout << str;
}

int main() {
	Library l;

	string date;
	cin >> date;

	l.getBooks(date);
}

void loadMenu(Node* root)
{

	int choice;
	cout << right << setw(80) << setfill('-') << "----------" << endl;
	cout << "			" << "1.Add Node" << endl;
	cout << "			" << "2.Delete Node by Name" << endl;
	cout << "			" << "3.Find Node by Data" << endl;
	cout << "			" << "4.Display all nodes" << endl;
	cout << "			" << "5.Exit" << endl;
	cout << right << setw(80) << setfill('-') << "----------" << endl;
	cout << right << setw(60) << setfill(' ') << "\nEnter your choice:" << endl << endl;
	cin >> choice;
	system("cls");

	switch (choice)
	{

	case 1:
	{
		int data = 0;
		string name = "";
		cout << "Enter new Node name : " << endl;
		cin >> name;
		cout << "Enter new Node data : " << endl;
		cin >> data;
		Node* newNode = new Node(name, data);
		root = insertNode(root, newNode);
		printAllNodes(root);
		loadMenu(root);
		break;
	}
	case 2:
	{
		string name = "";
		cout << "Enter Node name to delete node : " << endl;
		cin >> name;
		pair<Node*, Node*> p = findNodeAndParByName(root, name);
		if (p.second == NULL)
		{
			cout << "No such node : " << name << " exists!" << endl;
			loadMenu(root);
		}
		Node* node = deleteNodeByName(p.first, p.second);
		loadMenu(root);
		break;
	}
	case 3:
	{
		int data = 0;
		cout << "Enter data to find Node : " << endl;
		cin >> data;
		Node* nodeToFind = findNodeByData(root, data);
		if (nodeToFind == NULL) {
			cout << "No such node with data : " << data << endl;
			loadMenu(root);
			break;
		}
		nodeToFind->print();
		loadMenu(root);
		break;
	}
	case 4:
	{
		printAllNodes(root);
		loadMenu(root);
		break;
	}
	case 5:
	{
		exit(0);
		break;
	}
	}
}

int main()
{
	Node* root = new Node("root", 5);
	Node* rootLeft = new Node("left", 3);
	Node* rootRight = new Node("right", 6);
	Node* rootLeftLeft = new Node("left1", 2);
	Node* rootLeftRight = new Node("right1", 12);
	root->setLeftNode(rootLeft);
	root->setRightNode(rootRight);
	root->getLeft()->setLeftNode(rootLeftLeft);
	root->getLeft()->setRightNode(rootLeftRight);
	loadMenu(root);
	return 0;
}