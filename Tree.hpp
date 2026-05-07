#include <iostream>
#include <vector>
#include <chrono>
#ifndef _TREE_H_
#define _TREE_H_

/*Nandini Mahesh Bhat
HW 2
This is a header and implementation file containing the class definition and method implementations for the Tree class template (implementing
a binary search tree), struct Node (used to make nodes for the Tree), and struct FootballPlayer (used for testing)*/

//FootballPlayer struct- used for testing Tree with custom type. contains two attributes, string name and int jersey_num
struct FootballPlayer {

	std::string name = "";
	int jersey_num = 0;

	bool operator<(const FootballPlayer& other) const {
		return jersey_num < other.jersey_num;
	}

	bool operator>(const FootballPlayer& other) const {
		return jersey_num > other.jersey_num;
	}

	bool operator==(const FootballPlayer& other) const {
		return jersey_num == other.jersey_num;
	}

	friend std::ostream& operator<<(std::ostream& os, const FootballPlayer &f) {
		os << f.name;
		return os;
	}

};

//Node struct- is templated. can have key of any type, left pointer to another Node<T> structure, right pointer to another Node<T> structure
template <typename T>
struct Node {

	T key;
	Node<T>* left = nullptr;
	Node<T>* right = nullptr;

};

//Tree class template- underlying structure is a linked list made up of Node<T> structs
template <class T>
class Tree {

 public:
	Tree();
	Tree(const T &val);
	~Tree();
	void insertElement(const T& val);
	bool search(const T& val) const;
	void deleteElement(const T& val);
	int get_num_nodes() const {return nodes_;} //getter for num_nodes_;
	auto timeComplexity(const T &val);

	template <typename U>
	friend std::ostream& operator<<(std::ostream& os, const Tree<U> &t);

 private:
	Node<T>* root_;
	int nodes_ = 0; //keeps track of number of nodes in the tree
	void deleteNodes(Node<T>* node); //helper for destructor
	Node<T>* deleteHelper(Node<T>* node, const T &val); //helper for deleteElement
	void inorderTraversal(Node<T>* node, std::vector<T>& vec) const; //helper for << operator overload



};


//default constructor for Tree- sets root to nullptr
template <typename T>
Tree<T>::Tree() {

	root_ = nullptr;

}

/*parameterized constructor for Tree- sets root to point at a Node<T> structure with key val. both left and right pointers remain nullptr
Parameters:
val (value of key for root)*/
template <typename T>
Tree<T>::Tree(const T &val) {

	root_ = new Node<T>;
	root_->key = val;
	nodes_++;

}

//destructor for Tree- deletes all Node<T> pointers stored in nodes_ vector
template <typename T>
Tree<T>::~Tree() {

	deleteNodes(root_);

}

/*inserts a new leaf Node<T> with key of val at appropriate place in the tree
Parameters:
val (value of key for new Node<T>)*/
template <typename T>
void Tree<T>::insertElement(const T& val) {

	if (root_ == nullptr) {

		root_ = new Node<T>;
		root_->key = val;
		nodes_++;
		return;

	}

	Node<T>* parent = nullptr;
	Node<T>* current = root_;

	/*find the right position to insert the new node at- this position is found when current == nullptr. once the position is found, the parent pointer
	will point to the parent node for the new node*/
	while (current != nullptr) {

		if (val < current->key) {
			parent = current;
			current = current->left;
		}

		else if (val > current->key) {
			parent = current;
			current = current->right;
		}

		//if you find a node where val == current->key, just return- this node is already in the tree
		else {

			return;
		}
	}

	/*if the given val is less than the parent's key, new node becomes parent's left child. set newly inserted node's key to val and
	insert pointer to this new node in nodes_ vector*/
	if (val < parent->key) {
		parent->left = new Node<T>;
		(parent->left)->key = val;
		nodes_++;
	}

	/*if the given val is greater than the parent's key, new node becomes parent's right child. set newly inserted node's key to val and
	insert pointer to this new node in nodes_ vector*/
	else {
		parent->right = new Node<T>;
		(parent->right)->key = val;
		nodes_++;
	}

	return;

}

/*searches the tree for a Node<T> with key == val. if such a node is present return true, otherwise false
Parameters:
val (value of key for Node<T> being searched for)*/
template <typename T>
bool Tree<T>::search(const T& val) const{

	//start at root
	Node<T>* current = root_;

	//if current is pointing at nullptr, end the loop as it has gone past the tree's leaf nodes
	while (current != nullptr) {

		//if val is less than current pointer's key, set current to its left child for next iteration
		if (val < current->key) {
			current = current->left;
		}

		//if val is greater than current pointer's key, set current to its right child for next iteration
		else if (val > current->key) {
			current = current->right;

		}

		//if val is equal to curren pointer's key, return true
		else {
			return true;
		}

	}

	//if loop terminates without returning, node with key == val was not found. return false
	return false;

}

/*helper function for destructor- recursively deletes nodes in tree
Parameters:
node (generally going to be the root*/
template <typename T>
void Tree<T>::deleteNodes(Node<T>* node) {

	//base case- if you reach nullptr, return
	if (node == nullptr) {
		return;
	}

	deleteNodes(node->left); //recursively call on node's left subtree
	deleteNodes(node->right); //recursively call on node's right subtree

	delete node; //delete the node
	nodes_--; //decrement number of nodes in tree
	
	return;


}

/*recursive method to delete an element from the tree
Parameters:
node (top of tree being searched)
val (value to be removed from the tree)*/
template <typename T>
Node<T>* Tree<T>::deleteHelper(Node<T>* node, const T &val) {

	if (node == nullptr) {return nullptr;} //if node is nullptr, simply return nullptr

	//if value less than current node key, recurse down left subtree (will also return new root of left subtree)
	else if (val < node->key) {

		node->left = deleteHelper(node->left, val);
	}

	//if value greater than current node key, recurse down right subtree (will also return new root of right subtree)
	else if (val > node->key) {

		node->right = deleteHelper(node->right, val);
	}

	//logic to follow once value has been found
	else {

		//if leaf node, delete node and set pointer to nullptr
		if (node->left == nullptr && node->right == nullptr) {

			delete node;
			nodes_--;
			node = nullptr;
		}

		//if node has only left subtree, replace node with root of left subtree, then delete original node
		else if (node->right == nullptr) {

			Node<T>* t = node; //temporary pointer to node
			node = node->left;
			delete t;
			nodes_--;

		}

		//if node has only right subtree, replace node with root of right subtree, then delete original node
		else if (node->left == nullptr) {

			Node<T>* t = node; //temporary pointer to node
			node = node->right;
			delete t;
			nodes_--;

		}

		//logic to follow if node has only two children
		else {

			//search for node's successor- start from right child, then go as far down the left subtree as possible (if there is one)
			Node<T>* successor = node->right;

			while (successor->left != nullptr) {

				successor = successor->left;

			}

			//set node's key to successor's key
			node->key = successor->key;

			//call deleteHelper to delete the successor, now that its key has been transferred to node. start from node->right
			node->right = deleteHelper(node->right, successor->key);

		}
		
	}

	//return the root of tree or subtree
	return node;
	
}

/*method to delete a single element from the tree. calls deleteHelper as helper function- sets root to result
Parameters:
val (value to be removed from the tree)*/
template <typename T>
void Tree<T>::deleteElement (const T& val) {

	root_ = deleteHelper(root_, val);

}

/*helper function for << operator overload
Parameters:
node (node to start traversal from, generally root)
vec (vector passed by reference, contains elements in inorder traversal)*/
template <typename T>
void Tree<T>::inorderTraversal(Node<T>* node, std::vector<T>& vec) const {

	if (node == nullptr) {return;}

	inorderTraversal(node->left, vec);

	vec.push_back(node->key);

	inorderTraversal(node->right, vec);

}



//<< operator overload- used to display elements in tree as an inorder traversal
template <typename U>
std::ostream& operator<<(std::ostream& os, const Tree<U> &t) {

	std::vector<U> vec;

	t.inorderTraversal(t.root_, vec);

	size_t len = vec.size();

	os << "{";

	for (size_t i = 0; i < len; i++) {

		if (i == len - 1) {

			os << vec[i];
		}

		else {

			os << vec[i];
			os << ", ";

		}

	}

	os << "}";
	return os;


}

/*a function to measure the time taken (in nanoseconds) to run search on a Tree structure of type T
Parameters:
val (the value of type T to search for in the Tree structure)*/
template <typename T>
auto Tree<T>::timeComplexity(const T &val) {

	/*I got this technique of measuring a function's runtime 
	from StackOverflow: https://stackoverflow.com/questions/21856025/getting-an-accurate-execution-time-in-c-micro-seconds
	(answer by Ranjeet R Patil and Myeongkil Kim). Based on the suggestion in the answer, I used steady_clock instead of 
	high_resolution_clock*/
	
	auto start = std::chrono::steady_clock::now();
	search(val);
	auto finish = std::chrono::steady_clock::now();

	auto time = std::chrono::duration_cast<std::chrono::nanoseconds>(finish - start).count();
	

	return time;

	
}


#endif