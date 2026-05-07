#include <iostream>
#include <vector>
#include <chrono>
#ifndef _HASHMAP_H_
#define _HASHMAP_H_

/*Nandini Mahesh Bhat
HW 2
This is a header and implementation file containing the class definition and method implementations for the HashMap class template, struct Node (used to make nodes for the Tree), and struct TechProduct (used for testing)*/


//TechProduct struct- used for testing HashMap with custom type. contains two attributes, string name and string product_code
struct TechProduct {

	std::string name;
	std::string product_code;

	bool operator==(const TechProduct& other) const {
		return product_code == other.product_code;
	}

	friend std::ostream& operator<<(std::ostream& os, const TechProduct &t) {
		os << t.name;
		return os;
	}

};

/*This is a hash specialization for the TechProduct user defined type
I referenced doctorlove's answer (highest score): https://stackoverflow.com/questions/18078969/can-i-override-stdhash
I also referenced the documentation for std::hash and custom hash: https://en.cppreference.com/w/cpp/utility/hash.html*/
namespace std {
	template<> struct hash<TechProduct> {
		size_t operator()(const TechProduct & t) const {
			 size_t h = std::hash<std::string>{}(t.product_code);
			 return h;
		}
	};
}


//HashMap class template- underlying structure is a vector of vectors (inner vectors of type T)
template <class T>
class HashMap {

	public:
		HashMap(int size);
		HashMap(const std::vector<T> &vals, int size);
		void insertElement(const T &val);
		bool search(const T &val) const;
		void deleteElement(const T &val);
		auto timeComplexity(const T &val);

		template <typename U>
		friend std::ostream& operator<<(std::ostream& os, const HashMap<U> &m);

		

	private:
		std::vector<std::vector<T>> vec_; //vector consisting of buckets
		int table_size_; //stores fixed size of hashmap
		int hashKey(const T &val) const; //used in insertElement, search, deleteElement


};

/*parameterized constructor for HashMap
Parameters:
size (size of hash table)*/
template <typename T>
HashMap<T>::HashMap(int size) {

	table_size_ = size;

	std::vector<T> bucket;

	//fill the hashmap with buckets
	for (int i = 0; i < table_size_; i++) {
		vec_.push_back(bucket);
	}

}


/*parameterized constructor for HashMap
Parameters:
vals (vector of type T consisting of starting values to insert into hashmap)
size (size of hash table)*/
template <typename T>
HashMap<T>::HashMap(const std::vector<T> &vals, int size) {

	table_size_ = size;

	std::vector<T> bucket;

	//fill the hashmap with buckets
	for (int i = 0; i < table_size_; i++) {
		vec_.push_back(bucket);
	}

	//if the input vector contains any values, insert them into the hashmap
	for (T v: vals) {
		insertElement(v);
	}

}

/*method to calculate hashKey, used for insertion into hashmap
Parameters:
val (value of type T to calculate hash key for)*/
template <typename T>
int HashMap<T>::hashKey(const T &val) const{

	//use standard library hash (works with most types, and it has been specialized for the TechProduct struct above
	size_t key_initial = std::hash<T>{}(val);
	int key_convert = static_cast<int>(key_initial % table_size_); //take the result modulo table size to get the index of bucket for insertion

	return key_convert;

}

/*method to insert an element into the hashmap- gets the appropriate key for the value using hashkey method, then inserts it into the corresponding bucket
Parameters:
val (value of type T to be inserted into the hashmap)*/
template <typename T>
void HashMap<T>::insertElement(const T &val) {

	int key = hashKey(val);

	//if value already exists in hashmap, don't add a duplicate
	for (T v: vec_[key]) {
		if (v == val) {return;}
	}

	vec_[key].push_back(val);

}

/*method to check whether a specific element in present in the hashmap or not- uses hashkey method to find bucket it should be in, then searches that bucket
Parameters:
val (value of type T to search for)*/
template <typename T>
bool HashMap<T>::search(const T &val) const {

	int key = hashKey(val);

	for(T v: vec_[key]) {
		if (v == val) {return true;}
	}

	return false;

}

/*method to delete an element from the hashmap (if the hashmap contains it)
Parameters:
val (value of type T to delete)*/
template <typename T>
void HashMap<T>::deleteElement(const T &val) {

	int key = hashKey(val); //find the key, and therefore the bucket the element should be in

	size_t len = vec_[key].size();


	//search that bucket for the element
	for (size_t i = 0; i < len; i++) {

		if (vec_[key][i] == val) {
			
			vec_[key].erase(vec_[key].begin() + i); //if present, delete the element from the bucket
			return;
			
		}

	}

	//else, return nothing
	return;

}

/*<< operator overload- used to display the hashmap and its buckets
Note: I could only test this manually (without Catch2) as the results of the std::hash function are unpredictable. the documentation
states that this is for security reasons, and to prevent denial-of-service attacks*/
template <typename U>
std::ostream& operator<<(std::ostream& os, const HashMap<U> &m) {

	for (int i = 0; i < m.table_size_; i++) {

		os << "{";

		for (size_t j = 0; j < m.vec_[i].size(); j++) {

			if (j == m.vec_[i].size() - 1) {

				os << m.vec_[i][j];

			}

			else {

				os << m.vec_[i][j] << ", ";

			}
	
		}

		os << "}";

		if (i < m.table_size_ - 1) {
			os << " ";
		}
		

	}

	return os;


}

/*a function to measure the time taken (in nanoseconds) to run search on a HashMap structure of type T
Parameters:
val (the value of type T to search for in the HashMap structure)*/
template <typename T>
auto HashMap<T>::timeComplexity(const T &val) {

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