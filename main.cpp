#include <iostream>
#include <set>
using namespace std;

template<class T> class Node {
private:
public:
	T data;

	Node<T>* left = NULL;
	Node<T>* right = NULL;
};

template <class T> class tree {
private:
	Node<T>* root;	
	void p_insert(Node<T>* node, T _data) {
		if (node == NULL) {
			Node<T>* _new;
			_new = new Node<T>;
			_new->data = _data;
			_new->left = _new->right = NULL;
			node = _new;
		}
		else {
			if (node->data == _data) {
				cout << "The data has existed.\n";
			}
			else if (node->data > _data) {
				p_insert(node->left, _data);
			}
			else {
				p_insert(node->right, _data);
			}
		}
	}
	void p_delete(Node<T>* node, T _data) {
		if (node == NULL) {
			cout << "The data don't exist.\n";
		}
		else if (node->data > _data) {
			p_delete(node->left, _data);
		}
		else if(node->data < _data){
			p_delete(node->right, _data);
		}
		else if (node->left && node->right) {
			Node<T>* temp = findPredecessor(node->left);
			node->data = temp->data;
			p_delete(node->left, temp->data);
		}
		else {
			Node<T>* temp = node;
			if (node->left == NULL && node->right == NULL) {
				node = NULL;
			}
			else if(node->left != NULL){
				node = node->left;
			}
			else {
				node = node->right;
			}
			delete[] temp;
			temp = NULL;
		}
	}
	Node<T>* findPredecessor(Node<T>* node) {
		Node<T>* temp = node;
		if (node->right != NULL) {
			temp = findPredecessor(node->right);
		}
		return temp;
	}
	Node<T>* findSuccessor(Node<T>* node) {
		Node<T>* temp = node;
		if (node->left != NULL) {
			temp = findSuccessor(node->left);
		}
		return temp;
	}
	int p_height(Node<T>* node) {
		if (node == NULL)return 0;
		int leftHeight = p_height(node->left);
		int rightHeight = p_height(node->right);
		if (leftHeight >= rightHeight) return leftHeight + 1;
		else return rightHeight;
	}
	int p_totalNodes(Node<T>* node) {
		if (node == NULL) return 0;
		return p_totalNodes(node->left) + p_totalNodes(node->right) + 1;
	}
	int p_totalExternalNodes(Node<T>* node) {
		if (node == NULL) return  0;
		if (node->left == NULL && node->fight == NULL) return 1;
		return p_totalExternalNodes(node->left) + p_totalExternalNodes(node->right);
	}
	void p_mirrorImage(Node<T>* node) {
		if (node != NULL) {
			p_mirrorImage(node->left);
			p_mirrorImage(node->right);
			Node<T>* temp = node->left;
			node->left = node->right;
			node->right = temp;
		}
	}
	void p_print(Node<T>* node) {
		if (node != NULL) {
			cout << node->data;
			if (node->left != NULL)	p_print(node->left);
			if (node->right != NULL) p_print(node->right);
		}
		else {
			printf(" ");
		}		
	}

public:
	tree() :root(NULL) {}
	bool search(T _data) {
		Node<T>* temp = root;
		while (temp != NULL) {
			if (temp->data == _data) {				
				return true;
			}
			else {
				if (temp->data > _data) {
					temp = temp->left;
				}
				else {
					temp = temp->right;
				}
			}
		}
		return false;
	}
	void insert(T _data) {
		p_insert(root, _data);
		/*if (root != NULL) {
			p_insert(root, _data);
		}
		else
		{
			root = new Node<T>;
			root->data = _data;
			root->left = NULL;
			root->right = NULL;
		}*/
	}
	void delete_element(T _data) {
		p_delete(root, _data);
	}
	int Height() {
		return p_height(root);
	}
	int totalNodes() {
		return p_totalNodes(root);
	}
	int totalExternalNodes() {
		return p_totalExternalNodes(root);
	}
	void mirrorImage() {
		p_mirrorImage(root);
	}
	void print() {
		p_print(root);
		printf("\n");
	}
};

int main(void) {
	tree<int> b;
	int a;
	for (int i = 0; i < 3; ++i) {
		cin >> a;
		b.insert(a);
	}
	cout << b.Height() << endl;
	b.print();
}
