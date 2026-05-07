#include <iostream>
#include <vector>
#include <stdexcept>
#include <chrono>
#ifndef _LINEAR_H_
#define _LINEAR_H_

/*Nandini Mahesh Bhat
HW 2
This is a header and implementation file containing the class definition and method implementations for the Linear class template, and struct
VideoGameChar (used for testing)*/

//VideoGameChar struct- used for testing Linear with custom type. only contains one attribute, string name
struct VideoGameChar {

	std::string name;

	bool operator==(const VideoGameChar& other) const {
      return name == other.name;
  }

	friend std::ostream& operator<<(std::ostream& os, const VideoGameChar &c) {

		os << c.name;

		return os;

	}

};

//Linear class template- underlying structure is a vector of type T
template <class T>
class Linear {

 public:
	void insertElement(const T &val);
	T getElementAtIndex(const int &index) const;
	bool search(const T &val) const;
	void deleteElement(const T &val);
	auto timeComplexity(const T &val);

	

	template <typename U>
	friend std::ostream& operator<<(std::ostream& os, const Linear<U> &l);

 private:
	std::vector<T> linear_vect_;
	

};

/*Insert an element at the end of the linear_vect_ private vector
Parameters:
val (value to be inserted)*/
template <typename T>
void Linear<T>::insertElement(const T &val) {

	//if value already exists in linear_vect_, don't add a duplicate
	if (search(val) == true) {return;}

	linear_vect_.push_back(val);

}

/*Retrieve the element at specified index in linear_vect_ private vector
Parameters:
index (index at which the element to be retrieved is located)*/
template <typename T>
T Linear<T>::getElementAtIndex(const int &index) const {

	//throws error if index is negative (https://stackoverflow.com/questions/8480640/how-to-throw-a-c-exception)
	if (index < 0) { throw std::runtime_error ("index cannot be negative value"); }

	//uses .at() method for bounds checking (https://stackoverflow.com/questions/16620222/vector-going-out-of-bounds-without-giving-error)
	return linear_vect_.at(index); 

}

/*Search linear_vect_ private attribute for specified val- if found return true, else return false
Parameters:
val (value of element to search for in vector)*/
template <typename T>
bool Linear<T>::search(const T &val) const {

	for (T v: linear_vect_) {
		if (v == val) { return true; }
	}
	
	return false;

}

/*Search linear_vect_ private attribute for specified val- if found delete the element and return, else just return
Parameters:
val (value of element to delete in vector)*/
template <typename T>
void Linear<T>::deleteElement (const T &val) {

	size_t len = linear_vect_.size(); //using size_t as -Wconversion is a bit sensitive about converting size_t to int

	//using iterator based for 
	for (size_t i = 0; i < len; i++) {

		if (linear_vect_[i] == val) {

			linear_vect_.erase(linear_vect_.begin() + i);
			return;
		}
	}

	return;
}

//<< operator overload- used to display elements in linear_vect
template <typename U>
std::ostream& operator<<(std::ostream& os, const Linear<U> &l) {

	os << "{";

	size_t len = l.linear_vect_.size();

	for (size_t i = 0; i < len; i++) {

		if (i == len-1) { 

			os << l.linear_vect_[i];
		}

		else {

			os << l.linear_vect_[i];
			os << ", ";
		}

	}

	os << "}";
	
	return os;
}

/*a function to measure the time taken (in nanoseconds) to run search on a Linear structure of type T
Parameters:
val (the value of type T to search for in the Linear structure)*/
template <typename T>
auto Linear<T>::timeComplexity(const T &val) {

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