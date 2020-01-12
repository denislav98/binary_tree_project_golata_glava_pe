#include <iostream>
#include<iomanip>

using namespace std;

class Tree
{
public:
	virtual void print() = 0;
};

class Node : public Tree
{
private:
	string name;
	int data;
	Node* left, * right;
public:
	Node(string name, int data)
	{
		this->name = name;
		this->data = data;
		this->left = this->right = NULL;
	}

	~Node()
	{
		cout << "Node deleted !" << endl;
	}

	string getName()
	{
		return this->name;
	}

	void setName(string name)
	{
		this->name = name;
	}

	int getData()
	{
		return this->data;
	}

	void setData(int data)
	{
		this->data = data;
	}

	Node* getLeft()
	{
		return this->left;
	}

	void setLeftNode(Node* left)
	{
		this->left = left;
	}

	Node* getRight()
	{
		return this->right;
	}

	void setRightNode(Node* right)
	{
		this->right = right;
	}

	void print()
	{
		cout << "Name: " << this->name << endl << "Data : " << this->data << endl;
	}
};

Node* insertNode(Node* root, Node* newNode)
{
	if (root == NULL)
	{
		root = newNode;
	}
	else
	{
		if (newNode->getData() < root->getData())
		{
			if (root->getLeft() == NULL)
			{
				root->setLeftNode(newNode);
			}
			else
			{
				insertNode(root->getLeft(), newNode);
			}
		}
		else
		{
			if (root->getRight() == NULL)
			{
				root->setRightNode(newNode);
			}
			else
			{
				insertNode(root->getRight(), newNode);
			}
		}
	}
	return root;
}


void printAllNodes(Node* node)
{
	if (node == NULL)
	{
		return;
	}
	else
	{
		printAllNodes(node->getLeft());
		node->print();
		printAllNodes(node->getRight());
	}
}

Node* findNodeByData(Node* node, int data)
{
	if (node != NULL)
	{
		if (node->getData() == data)
		{
			return node;
		}
		else
		{
			Node* foundNode = findNodeByData(node->getLeft(), data);
			if (foundNode == NULL)
			{
				foundNode = findNodeByData(node->getRight(), data);
			}
			return foundNode;
		}
	}
	return NULL;
}

Node* findNodeByName(Node* node, string name)
{
	if (node != NULL)
	{
		if (node->getName() == name)
		{
			return node;
		}
		else
		{
			Node* foundNode = findNodeByName(node->getLeft(), name);
			if (foundNode == NULL)
			{
				foundNode = findNodeByName(node->getRight(), name);
			}
			return foundNode;
		}
	}
	else
	{
		return NULL;
	}
}
class binaryTreeException : exception
{
public:
	binaryTreeException() : exception()
	{
		cout << "Something wrong is happend" << endl;
	}

	explicit binaryTreeException(string s) : exception()
	{
		cout << s << endl;
	}
};
pair<Node*, Node*> findNodeAndParByName(Node* root, string nodeToDelete) // dete -> roditel
{
	if (root != NULL)
	{
		//if (root->getName().compare(nodeToDelete) == 0)
		if (root->getName() == nodeToDelete)
		{
			return pair<Node*, Node*>(NULL, root);

		}
		else
		{
			if (root->getLeft() != NULL && root->getLeft()->getName() == nodeToDelete)
			{
				return pair<Node*, Node*>(root, root->getLeft());
			}
			if (root->getRight() != NULL && root->getRight()->getName().compare(nodeToDelete) == 0)
			{
				return pair<Node*, Node*>(root, root->getRight());
			}
			pair<Node*, Node*> p = findNodeAndParByName(root->getLeft(), nodeToDelete);
			if (p.second != NULL)
			{
				return p;
			}
			p = findNodeAndParByName(root->getRight(), nodeToDelete);
			if (p.second != NULL)
			{
				return p;
			}
		}
	}
	return pair<Node*, Node*>(NULL, NULL);
}

pair<Node*, Node*> findLeafAndParent(Node* node)
{
	if (node != NULL)
	{
		if (node->getLeft() == NULL && node->getRight() == NULL)
		{
			return pair<Node*, Node*>(NULL, node);
		}
		if (node->getLeft() != NULL)
		{
			if (node->getLeft()->getLeft() == NULL && node->getLeft()->getRight() == NULL)
			{
				return pair<Node*, Node*>(node, node->getLeft());
			}
		}
		if (node->getRight() != NULL)
		{
			if (node->getRight()->getLeft() == NULL && node->getRight()->getRight() == NULL)
			{
				return pair<Node*, Node*>(node, node->getRight());
			}
		}
		pair<Node*, Node*> p = findLeafAndParent(node->getLeft());
		if (p.second != NULL)
		{
			return p;
		}
		p = findLeafAndParent(node->getRight());
		if (p.second != NULL)
		{
			return p;
		}
		throw binaryTreeException();
	}
	return pair<Node*, Node*>(NULL, NULL);
}

void transfer_node_content(Node* n1, Node* n2)
{
	n1->setData(n2->getData());
	n1->setName(n2->getName());
}

Node* deleteNodeByName(Node* parent, Node* nodeToDelete)
{
	if (nodeToDelete->getLeft() == NULL && nodeToDelete->getRight() == NULL)
	{
		cout << "Leaf" << endl;
		nodeToDelete->print();
		if (parent->getLeft() != NULL && parent->getLeft()->getName() == nodeToDelete->getName())
		{
			parent->setLeftNode(NULL);
		}
		else if (parent->getRight() != NULL && parent->getRight()->getName() == nodeToDelete->getName())
		{
			parent->setRightNode(NULL);
		}
		else
		{
			throw binaryTreeException();
		}
		delete nodeToDelete;
		return nodeToDelete;
	}
	else if (nodeToDelete->getLeft() == NULL && nodeToDelete->getRight() != NULL)
	{
		cout << "Node with right child" << endl;
		nodeToDelete->print();
		if (parent->getLeft()->getName() == nodeToDelete->getName())
		{
			parent->setLeftNode(nodeToDelete->getRight());
		}
		else if (parent->getRight()->getName() == nodeToDelete->getName())
		{
			parent->setRightNode(nodeToDelete->getRight());
		}
		else
		{
			throw binaryTreeException();
		}
		delete nodeToDelete;
		return nodeToDelete;
	}
	else if (nodeToDelete->getRight() == NULL && nodeToDelete->getLeft() != NULL)
	{
		cout << "Node with left child" << endl;
		nodeToDelete->print();
		if (parent->getLeft()->getName() == nodeToDelete->getName())
		{
			parent->setLeftNode(nodeToDelete->getLeft());
		}
		else if (parent->getRight()->getName() == nodeToDelete->getName())
		{
			parent->setRightNode(nodeToDelete->getLeft());
		}
		else
		{
			throw binaryTreeException();
		}
		delete nodeToDelete;
		return nodeToDelete;
	}
	else
	{
		cout << "Node with more childs" << endl;
		pair<Node*, Node*> tmp = findLeafAndParent(nodeToDelete);
		if (tmp.first != NULL)
		{
			if (tmp.first->getLeft()->getName() == tmp.second->getName())
			{
				tmp.first->setLeftNode(nullptr);
			}
			else if (tmp.first->getRight()->getName() == tmp.second->getName())
			{
				tmp.first->setRightNode(nullptr);
			}
			else
			{
				throw binaryTreeException();
			}
			transfer_node_content(nodeToDelete, tmp.second);
			delete tmp.second;
			return tmp.second;
		}
		else
		{
			throw binaryTreeException();
		}
	}
	return nullptr;
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
		string nodeToDelete;
		cout << "Enter the name of the node you want to delete: " << endl;
		cin >> nodeToDelete;
		pair<Node*, Node*> p = findNodeAndParByName(root, nodeToDelete);
		if (p.second == NULL)
		{
			cout << "There is no node with this name! " << endl;
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
	Node* node1 = new Node("node1", 3);
	Node* node2 = new Node("node2", 6);
	Node* node3 = new Node("node3", 2);
	Node* node4 = new Node("node4", 12);
	insertNode(root, node1);
	insertNode(root, node2);
	insertNode(root, node3);
	insertNode(root, node4);
	loadMenu(root);
	return 0;
}