#define CATCH_CONFIG_MAIN
#include <fstream>
#include <string>
#include "catch.hpp"
#include "Linear.hpp"
#include "Tree.hpp"
#include "HashMap.hpp"

/*Nandini Mahesh Bhat
HW 2
This is a test file created to test functionality for the class templates Linear, Tree, and HashMap using the Catch2 framework*/


TEST_CASE ( "Linear", "[test_linear]") {


	//testing Linear class with type int
	SECTION("Test with int") {

		//creating an object and inserting some elements
		//added the -Wconversion flag to Makefile to prevent doubles, floats being truncated and added to the vector. throws compiler error if this happens
		Linear<int> l;
		
		l.insertElement(5);
		l.insertElement(-2);
		
		
		/*checking whether elements have been inserted at correct positions, correct error thrown if out of bounds position 
		checked or negative index entered*/
		REQUIRE( l.getElementAtIndex(0) == 5);
		REQUIRE( l.getElementAtIndex(1) == -2);
		REQUIRE_THROWS_WITH(l.getElementAtIndex(-1), "index cannot be negative value");
		REQUIRE_THROWS_WITH(l.getElementAtIndex(5), "vector::_M_range_check: __n (which is 5) >= this->size() (which is 2)");
		
	
		/*checking whether inserted elements can be found, non-inserted elements not found (if fractional values entered, compiler will 
		throw an error due to conversion)*/
		REQUIRE( l.search(5) == true);
		REQUIRE( l.search(-5) == false);
		REQUIRE( l.search(-2) == true);
		REQUIRE( l.search(2) == false);

		/*checking whether deletion of element works, and if said element can still be found in vector after deletion. also make sure
		that deletion of non-existent element does not affect existing elements*/

		
		l.deleteElement(-2); //delete existing element
		l.deleteElement(7); //delete non-existent element
		l.insertElement(5); //testing to make sure duplicate cannot be added to vector
		
		std::stringstream ss;
		ss << l;
		REQUIRE(ss.str() == "{5}");
		ss.clear();
		ss.str(std::string());


	}

	SECTION("Test with double") { 

		//creating an object and inserting some elements
		//non-fractional elements allows, converted to doubles
		Linear<double> l;
		
		l.insertElement(5.7);
		l.insertElement(-6); //allowed and converted to -6.0

		/*checking whether elements have been inserted at correct positions, correct error thrown if out of bounds position 
		checked or negative index entered*/
		REQUIRE( l.getElementAtIndex(0) == 5.7);
		REQUIRE( l.getElementAtIndex(1) == -6.0);
		REQUIRE_THROWS_WITH(l.getElementAtIndex(-1), "index cannot be negative value");
		REQUIRE_THROWS_WITH(l.getElementAtIndex(5), "vector::_M_range_check: __n (which is 5) >= this->size() (which is 2)");

		//checking whether inserted elements can be found, non-inserted elements not found
		REQUIRE( l.search(5.7) == true);
		REQUIRE( l.search(-5.7) == false);
		REQUIRE( l.search(-6.0) == true);
		REQUIRE( l.search(6) == false);

		/*checking whether deletion of element works, and if said element can still be found in vector after deletion. also make sure
		that deletion of non-existent element does not affect existing elements. also check to make sure duplicates cannot be added*/

		l.deleteElement(5.7); //delete existing element
		l.deleteElement(1.75); //delete non-existent element
		l.insertElement(-6.0); //testing to make sure duplicate cannot be added to vector
		
		std::stringstream ss;
		ss << l;
		REQUIRE(ss.str() == "{-6}");
		ss.clear();
		ss.str(std::string());


	}


	SECTION("Test with string") {

		//creating an object and inserting some elements
		Linear<std::string> l;
		
		l.insertElement("aaa");
		l.insertElement("bbb");

		/*checking whether elements have been inserted at correct positions, correct error thrown if out of bounds position 
		checked or negative index entered*/
		REQUIRE( l.getElementAtIndex(0) == "aaa");
		REQUIRE( l.getElementAtIndex(1) == "bbb");
		REQUIRE_THROWS_WITH(l.getElementAtIndex(-1), "index cannot be negative value");
		REQUIRE_THROWS_WITH(l.getElementAtIndex(5), "vector::_M_range_check: __n (which is 5) >= this->size() (which is 2)");

		//checking whether inserted elements can be found, non-inserted elements not found
		REQUIRE( l.search("aaa") == true);
		REQUIRE( l.search("aba") == false);
		REQUIRE( l.search("bbb") == true);
		REQUIRE( l.search("bab") == false);

		/*checking whether deletion of element works, and if said element can still be found in vector after deletion. also make sure
		that deletion of non-existent element does not affect existing elements. also check to make sure duplicates cannot be added*/

		l.deleteElement("bbb"); //delete existing element
		l.deleteElement("ccc"); //delete non-existent element
		l.insertElement("aaa"); //testing to make sure duplicate cannot be added to vector
		
		std::stringstream ss;
		ss << l;
		REQUIRE(ss.str() == "{aaa}");
		ss.clear();
		ss.str(std::string());


	}

	SECTION("Test with VideoGameChar struct") {

		//creating an object and inserting some elements
		Linear<VideoGameChar> l;

		VideoGameChar v1{"Gordon Freeman"};
		VideoGameChar v2{"Raiden"};
		VideoGameChar v3{"Vortigaunt"};
		VideoGameChar v4{"Solid Snake"};
		VideoGameChar v5{"RuneScape Woodcutting Pure"};
		
		l.insertElement(v1);
		l.insertElement(v2);

		/*checking whether elements have been inserted at correct positions, correct error thrown if out of bounds position 
		checked or negative index entered*/
		REQUIRE( l.getElementAtIndex(0) == v1);
		REQUIRE( l.getElementAtIndex(1) == v2);
		REQUIRE_THROWS_WITH(l.getElementAtIndex(-1), "index cannot be negative value");
		REQUIRE_THROWS_WITH(l.getElementAtIndex(5), "vector::_M_range_check: __n (which is 5) >= this->size() (which is 2)");

		//checking whether inserted elements can be found, non-inserted elements not found
		REQUIRE( l.search(v1) == true);
		REQUIRE( l.search(v3) == false);
		REQUIRE( l.search(v2) == true);
		REQUIRE( l.search(v4) == false);

		/*checking whether deletion of element works, and if said element can still be found in vector after deletion. also make sure
		that deletion of non-existent element does not affect existing elements. also check to make sure duplicates cannot be added*/

		l.deleteElement(v1); //delete existing element
		l.deleteElement(v5); //delete non-existent element
		l.insertElement(v2); //testing to make sure duplicate cannot be added to vector
		
		std::stringstream ss;
		ss << l;
		REQUIRE(ss.str() == "{Raiden}");
		ss.clear();
		ss.str(std::string());
		
	}

}

TEST_CASE ( "BST", "[test_bst]") {

	SECTION("Test with int") {

		//creating Tree object with root 64
		Tree<int> t(64);

		//creating a vector of elements to insert into the tree- insert, then search to make sure element is present
		std::vector<int> test_ints = {50, 70, 40, 60, 65, 89, 21, 61, 80, 20000, -20000, 30, 30000, -30000};

		for(int i: test_ints) {

			t.insertElement(i);
			REQUIRE( t.search(i) == true);

		}

		//make sure number of nodes is 15
		REQUIRE( t.get_num_nodes() == 15);

		//check inorder traversal output- if correct, nodes have been inserted in correct positions
		std::stringstream ss;
		ss << t;
		REQUIRE(ss.str() == "{-30000, -20000, 21, 30, 40, 50, 60, 61, 64, 65, 70, 80, 89, 20000, 30000}");
		ss.clear();
		ss.str(std::string());

		//elements that have not been inserted should not be detected
		REQUIRE( t.search(63) == false);
		REQUIRE( t.search(30001) == false);
		REQUIRE( t.search(-20001) == false);

		//mix up some of the previously inserted elements, and then delete them. search to make sure they cannot be found in the tree
		std::vector<int> test_ints_t1 = {65, 89, 21, 61, 80, 50, 70, 40, -20000, 30, 30000, -30000, 64};

		for(int i: test_ints_t1) {

			t.deleteElement(i);
			REQUIRE( t.search(i) == false);

		}

		//try deleting a node that was not present in the tree
		t.deleteElement(59);

		//try inserting a duplicate element into the tree
		t.insertElement(60);

		/*number of nodes should be 2 now, and inorder traversal should be as expected below. deletion of nonexistent element should not have
		affected this*/
		REQUIRE( t.get_num_nodes() == 2);

		ss << t;
		REQUIRE(ss.str() == "{60, 20000}");
		ss.clear();
		ss.str(std::string());

		//delete the remaining elements
		t.deleteElement(60);
		t.deleteElement(20000);

		REQUIRE( t.get_num_nodes() == 0);

		ss << t;
		REQUIRE(ss.str() == "{}");
		ss.clear();
		ss.str(std::string());

		//now insert some elements- we should be able to rebuild tree from ground up
		t.insertElement(32);
		t.insertElement(-85);
		t.insertElement(45);

		REQUIRE( t.get_num_nodes() == 3);

		ss << t;
		REQUIRE(ss.str() == "{-85, 32, 45}");
		ss.clear();
		ss.str(std::string());

	}

	SECTION("Test with double") {

		//creating Tree object with root 10000.752
		Tree<double> t(10000.752);

		//creating a vector of elements to insert into the tree- insert, then search to make sure element is present
		std::vector<double> test_doubles = {100.752, 15000.23, -75.049, 7000.000, 13000.785, 17000.459, 50.005, 12000.142, 92.6, 11000.725, 10000.95};

		for(double d: test_doubles) {

			t.insertElement(d);
			REQUIRE( t.search(d) == true);

		}

		//make sure number of nodes is 12
		REQUIRE( t.get_num_nodes() == 12);

		//check inorder traversal output- if correct, nodes have been inserted in correct positions
		/*I had to round the expected output values to match the stringstream rounding (precision of 6 digits). I considered using setprecision,
		but did not want to affect any autograder tests that may be testing the << overload with doubles*/
		std::stringstream ss;
		ss << t;
		REQUIRE(ss.str() == "{-75.049, 50.005, 92.6, 100.752, 7000, 10000.8, 10001, 11000.7, 12000.1, 13000.8, 15000.2, 17000.5}"); 
		ss.clear();
		ss.str(std::string());

		/*to ensure that checking of equivalence of doubles is precise, I have used the test values below. elements that have not been inserted should 
		not be detected*/
		REQUIRE( t.search(10000.7519) == false);
		REQUIRE( t.search(-75.0489) == false);
		REQUIRE( t.search(17000.4589) == false);

		//mix up some of the previously inserted elements, and then delete them. search to make sure they cannot be found in the tree
		std::vector<double> test_doubles_t1 = {10000.752, 13000.785, 17000.459, 50.005, 100.752, 15000.23, -75.049, 92.6, 11000.725, 10000.95};

		for(double d: test_doubles_t1) {

			t.deleteElement(d);
			REQUIRE( t.search(d) == false);

		}

		//try deleting a node that was not present in the tree
		t.deleteElement(12000.1419);

		//try inserting a duplicate element into the tree
		t.insertElement(12000.142);

		/*number of nodes should be 2 now, and inorder traversal should be as expected below. deletion of nonexistent element should not have
		affected this*/
		REQUIRE( t.get_num_nodes() == 2);

		ss << t;
		REQUIRE(ss.str() == "{7000, 12000.1}");
		ss.clear();
		ss.str(std::string());

		//we know that the functionality to rebuild the tree works from the int test, so we will skip those here

	}


	SECTION("Test with string") {

		//creating Tree object with root "hhh", inserting some elements
		Tree<std::string> t("hhh");

		//creating a vector of elements to insert into the tree- insert, then search to make sure element is present
		std::vector<std::string> test_strings = {"rrr", "lll", "mmm", "nnn", "sss", "vvv"};

		for(std::string s: test_strings) {

			t.insertElement(s);
			REQUIRE( t.search(s) == true);

		}

		//make sure number of nodes is 7
		REQUIRE( t.get_num_nodes() == 7);

		//check inorder traversal output- if correct, nodes have been inserted in correct positions
		std::stringstream ss;
		ss << t;
		REQUIRE(ss.str() == "{hhh, lll, mmm, nnn, rrr, sss, vvv}");
		ss.clear();
		ss.str(std::string());

		//elements that have not been inserted should not be detected
		REQUIRE( t.search("hah") == false);
		REQUIRE( t.search("vav") == false);
		REQUIRE( t.search("nan") == false);

		//testing root deletion with this tree structure (this was an issue before). make sure root element was deleted
		t.deleteElement("hhh");
		REQUIRE( t.search("hhh") == false);

		//make sure the inserted non-root strings are still there
		for(std::string s: test_strings) {

			REQUIRE( t.search(s) == true);

		}

		//try deleting a node that was not present in the tree
		t.deleteElement("nan");

		//try inserting a duplicate element into the tree
		t.insertElement("rrr");

		/*number of nodes should be 6 now, and inorder traversal should be as expected below. deletion of nonexistent element should not have
		affected this*/
		REQUIRE( t.get_num_nodes() == 6);

		ss << t;
		REQUIRE(ss.str() == "{lll, mmm, nnn, rrr, sss, vvv}");
		ss.clear();
		ss.str(std::string());

	}

	SECTION("Test with FootballPlayer struct") {

		//creating some FootballPlayer objects
		FootballPlayer f1 {"Toni Kroos", 8};
		FootballPlayer f2 {"Cristiano Ronaldo", 7};
		FootballPlayer f3 {"Lionel Messi", 10};

		FootballPlayer f4 {"Robert Lewandowski", 9};
		FootballPlayer f5 {"Carles Puyol", 5};
		FootballPlayer f6 {"Petr Cech", 1};
		FootballPlayer f7 {"Bastian Schweinsteiger", 31};

		//testing default constructor
		Tree<FootballPlayer> t;

		//inserting some FootballPlayer objects into the tree and making sure they have been inserted
		std::vector<FootballPlayer> test_football_player = {f1, f2, f5, f6};

		for(FootballPlayer f: test_football_player) {

			t.insertElement(f);
			t.search(f);

		}

		//make sure number of nodes is 4
		REQUIRE( t.get_num_nodes() == 4);

		//check inorder traversal output- if correct, nodes have been inserted in correct positions
		std::stringstream ss;
		ss << t;
		REQUIRE(ss.str() == "{Petr Cech, Carles Puyol, Cristiano Ronaldo, Toni Kroos}");
		ss.clear();
		ss.str(std::string());

		//elements that have not been inserted should not be detected
		REQUIRE( t.search(f3) == false);
		REQUIRE( t.search(f4) == false);
		REQUIRE( t.search(f7) == false);

		//testing root deletion with this tree structure. make sure root element was deleted
		t.deleteElement(f1);
		REQUIRE( t.search(f1) == false);

		std::vector<FootballPlayer> test_football_players_t1 = {f2, f5, f6};

		//make sure the inserted non-root objects are still there
		for(FootballPlayer f: test_football_players_t1 ) {

			REQUIRE( t.search(f) == true);

		}

		//try deleting a node that was not present in the tree
		t.deleteElement(f7);

		//try inserting a duplicate element into the tree
		t.insertElement(f5);

		/*number of nodes should be 3 now, and inorder traversal should be as expected below. deletion of nonexistent element should not have
		affected this*/
		REQUIRE( t.get_num_nodes() == 3);

		ss << t;
		REQUIRE(ss.str() == "{Petr Cech, Carles Puyol, Cristiano Ronaldo}");
		ss.clear();
		ss.str(std::string());

		

	}

}

TEST_CASE ( "HashMap", "[test_hashmap]") {

	SECTION("Test with int") {

		//creating a vector of ints to initialize the hashmap with
		std::vector<int> vec_int = {5, 7, 3, 4, 2};

		HashMap<int> h(vec_int, 10);

		//testing search and checking if elements were inserted into hashmap properly
		REQUIRE( h.search(5) == true);
		REQUIRE( h.search(-5) == false);
		REQUIRE( h.search(2) == true);
		REQUIRE( h.search(-2) == false);
		REQUIRE( h.search(3) == true);
		REQUIRE( h.search(-3) == false);

		//inserting some elements, testing if insertion was successful
		h.insertElement(24);
		h.insertElement(57);
		h.insertElement(15);
		h.insertElement(10);
		h.insertElement(-7);

		REQUIRE( h.search(24) == true);
		REQUIRE( h.search(-7) == true);
		
		//testing deleteElement
		h.deleteElement(5);
		h.deleteElement(2);
		h.deleteElement(3);
		h.deleteElement(27); //trying with an element that isn't there

		//checking to see that deleted elements cannot be found, non-deleted elements can be
		REQUIRE( h.search(5) == false);
		REQUIRE( h.search(7) == true);
		REQUIRE( h.search(2) == false);
		REQUIRE( h.search(4) == true);
		REQUIRE( h.search(3) == false);

		//trying to insert an element that is already in the hashmap- there should be no duplicates
		//will test this by manually checking the hashmap with << operator, but will comment this out after use
		h.insertElement(4);

		/*std::stringstream ss;
		ss << h;
		std::cout << ss.str() << std::endl;
		ss.clear();
		ss.str(std::string());*/

		


	}

	SECTION("Test with double") {

		//creating a vector of doubles to initialize the hashmap with
		std::vector<double> vec_double = {-2.4543, 8.5, 3.3453, -13.342, 5.986};

		HashMap<double> h(vec_double, 5);

		//testing search and checking if elements were inserted into hashmap properly
		REQUIRE( h.search(-2.4543) == true);
		REQUIRE( h.search(-2.454) == false);
		REQUIRE( h.search(-13.342) == true);
		REQUIRE( h.search(-13.0) == false);
		REQUIRE( h.search( 3.3453) == true);
		REQUIRE( h.search( 3.3) == false);

		//inserting some elements, testing if insertion was successful
		h.insertElement(6.35);
		h.insertElement(9.2);

		REQUIRE( h.search(6.35) == true);
		REQUIRE( h.search(9.2) == true);
		
		//testing deleteElement
		h.deleteElement(8.5);
		h.deleteElement(5.986);
		h.deleteElement(-2.4543);
		h.deleteElement(-3.34); //trying with an element that isn't there

		//checking to see that deleted elements cannot be found, non-deleted elements can be
		REQUIRE( h.search(8.5) == false);
		REQUIRE( h.search(3.3453) == true);
		REQUIRE( h.search(5.986) == false);
		REQUIRE( h.search(-13.342) == true);
		REQUIRE( h.search(-2.4543) == false);


		//trying to insert an element that is already in the hashmap- there should be no duplicates
		//will test this by manually checking the hashmap with << operator, but will comment this out after use
		h.insertElement(-13.342);

		/*std::stringstream ss;
		ss << h;
		std::cout << ss.str() << std::endl;
		ss.clear();
		ss.str(std::string());*/


	}

	SECTION("Test with string") {

		//creating a vector of strings to initialize hashmap (it's empty- testing to see if simply starting with empty hashmap works
		std::vector<std::string> vec_string = {};

		HashMap<std::string> h(vec_string, 20);

		//inserting some elements, testing if insertion was successful
		h.insertElement("aaa");
		h.insertElement("zzz");

		//testing search and checking if elements were inserted into hashmap properly
		REQUIRE( h.search("aaa") == true);
		REQUIRE( h.search("aba") == false);
		REQUIRE( h.search("zzz") == true);
		REQUIRE( h.search("zaz") == false);
		
		//testing deleteElement
		h.deleteElement("aaa");
		h.deleteElement("aba"); //trying with an element that isn't there

		//checking to see that deleted elements cannot be found, non-deleted elements can be
		REQUIRE( h.search("aaa") == false);
		REQUIRE( h.search("zzz") == true);

		//trying to insert an element that is already in the hashmap- there should be no duplicates
		//will test this by manually checking the hashmap with << operator, but will comment this out after use
		h.insertElement("zzz");

		/*std::stringstream ss;
		ss << h;
		std::cout << ss.str() << std::endl;
		ss.clear();
		ss.str(std::string());*/


	}

	SECTION("Test with TechProduct") {

		//creating some TechProduct objects to insert into hashmap- we will be doing this with insertElement rather than constructor
		TechProduct t1{"Lenovo ThinkBook", "LT14G7"};
		TechProduct t2{"Corsair HS35 v2", "CHSV2GH"};

		TechProduct t3{"Logitech MX Master 3S", "LMXM3S"};
		TechProduct t4{"Dell Pro Smartcard Keyboard", "DPSKKB813"};
		TechProduct t5{"ASUS Vivobook 15", "ASV15"};

		//testing constructor with only size
		HashMap<TechProduct> h(7);

		//inserting an elements, testing if insertion was successful
		h.insertElement(t1);
		h.insertElement(t2);
		h.insertElement(t3);

		//testing search and checking if elements were inserted into hashmap properly
		REQUIRE( h.search(t1) == true);
		REQUIRE( h.search(t4) == false);
		REQUIRE( h.search(t2) == true);
		REQUIRE( h.search(t5) == false);
		REQUIRE( h.search(t3) == true);
		
		//testing deleteElement
		h.deleteElement(t1);
		h.deleteElement(t5); //trying with an element that isn't there

		//checking to see that deleted elements cannot be found, non-deleted elements can be
		REQUIRE( h.search(t1) == false);
		REQUIRE( h.search(t2) == true);
		REQUIRE( h.search(t3) == true);

		//trying to insert an element that is already in the hashmap- there should be no duplicates
		//will test this by manually checking the hashmap with << operator, but will comment this out after use
		h.insertElement(t2);

		/*std::stringstream ss;
		ss << h;
		std::cout << ss.str() << std::endl;
		ss.clear();
		ss.str(std::string());*/


	}

}

/*These are some tests I created for analysing the time complexity of search for each data structure. Alongside each test, I have written down my 
initial result expectations as comments. My observations are written as comments at the bottom of this file, after the tests. I have commented 
the tests out because they were causing my CI/CD pipeline to state that tests have failed, when I have intentionally left the failed checks in*/ 

/*
TEST_CASE( "Time Complexity for Integers", "[time_complexity_integer]") {

	//vector to hold the integers we read in
	std::vector<int> vec_integers;
		
	std::string filepath = "./data/integers.csv";
	std::ifstream file_open;
	file_open.open(filepath);

	//if file fails to open, fail test case
	if (file_open.fail()) {
		FAIL("The file could not be opened.");
	}
		
	std::string line;

	// while loop to read all lines in file, convert to int before pushing back
	while(getline(file_open, line)) {

		int i = std::stoi(line);
		vec_integers.push_back(i);
	}

	file_open.close();

	//delete the header because that seems to have been added as well
	vec_integers.erase(vec_integers.begin() + 0);


	//inserting the elements in vec_integers into each data structure
	Linear<int> linear_test;
	Tree<int> tree_test;
	HashMap<int> hashmap_test(vec_integers, 7907);

	for (int i: vec_integers) {
		linear_test.insertElement(i);
	}

	for (int i: vec_integers) {
		tree_test.insertElement(i);
	}


	SECTION("Testing with first value in input list") {

	//I expect the tree to outperform both the linear structure and hashmap, and for the 
	//linear structure to outperform the hashmap
	CHECK( tree_test.timeComplexity(807) < linear_test.timeComplexity(807));
	CHECK( tree_test.timeComplexity(807) < hashmap_test.timeComplexity(807));
	CHECK( linear_test.timeComplexity(807) < hashmap_test.timeComplexity(807));

	}

	SECTION("Testing with random value in input list") {

	//As the value is closer to the end of the input list, I expect the hashmap to outperform both the tree 
	//and linear structure here, and for the tree to outperform the linear structure
	CHECK( tree_test.timeComplexity(93305) < linear_test.timeComplexity(93305));
	CHECK( hashmap_test.timeComplexity(93305) < tree_test.timeComplexity(93305));
	CHECK( hashmap_test.timeComplexity(93305) < linear_test.timeComplexity(93305));

	}

	SECTION("Testing with last value in input list") {

	//I expect the hashmap to outperform both the tree and linear structure here, and for the tree to outperform
	//the linear structure
	CHECK( tree_test.timeComplexity(43028) < linear_test.timeComplexity(43028));
	CHECK( hashmap_test.timeComplexity(43028) < tree_test.timeComplexity(43028));
	CHECK( hashmap_test.timeComplexity(43028) < linear_test.timeComplexity(43028));

	}
	


}

TEST_CASE( "Time Complexity for Decimals", "[time_complexity_decimal]") {
	
	//vector to hold the decimal values we read in
	std::vector<double> vec_decimals;
		
	std::string filepath = "./data/decimals.csv";
	std::ifstream file_open;
	file_open.open(filepath);

	//if file fails to open, fail test case
	if (file_open.fail()) {
		FAIL("The file could not be opened.");
	}
		
	std::string line;

	// while loop to read all lines in file, convert to double before pushing back
	while(getline(file_open, line)) {

		double d = std::stod(line);
		vec_decimals.push_back(d);
	}

	file_open.close();

	//delete the header because that seems to have been added as well
	vec_decimals.erase(vec_decimals.begin() + 0);

	//inserting the elements in vec_decimals into each data structure
	Linear<double> linear_test;
	Tree<double> tree_test;
	HashMap<double> hashmap_test(vec_decimals, 7907);

	for (double d: vec_decimals) {
		linear_test.insertElement(d);
	}

	for (double d: vec_decimals) {
		tree_test.insertElement(d);
	}


	SECTION("Testing with first value in input list") {

	//I expect the tree to outperform both the linear structure and hashmap, and for the 
	//linear structure to outperform the hashmap
	CHECK( tree_test.timeComplexity(41.19) < linear_test.timeComplexity(41.19));
	CHECK( tree_test.timeComplexity(41.19) < hashmap_test.timeComplexity(41.19));
	CHECK( linear_test.timeComplexity(41.19) < hashmap_test.timeComplexity(41.19));

	}

	SECTION("Testing with random value in input list") {

	//As the value is closer to the end of the input list, I expect the hashmap to outperform both the tree 
	//and linear structure here, and for the tree to outperform the linear structure
	CHECK( tree_test.timeComplexity(144.24) < linear_test.timeComplexity(144.24));
	CHECK( hashmap_test.timeComplexity(144.24) < tree_test.timeComplexity(144.24));
	CHECK( hashmap_test.timeComplexity(144.24) < linear_test.timeComplexity(144.24));

	}

	SECTION("Testing with last value in input list") {

	//I expect the hashmap to outperform both the tree and linear structure here, and for the tree to outperform
	//the linear structure
	CHECK( tree_test.timeComplexity(637.79) < linear_test.timeComplexity(637.79));
	CHECK( hashmap_test.timeComplexity(637.79) < tree_test.timeComplexity(637.79));
	CHECK( hashmap_test.timeComplexity(637.79) < linear_test.timeComplexity(637.79));

	}


}

TEST_CASE( "Time Complexity for Strings", "[time_complexity_string]") {
	
	//vector to hold the strings we read in
	std::vector<std::string> vec_strings;
		
	std::string filepath = "./data/strings.csv";
	std::ifstream file_open;
	file_open.open(filepath);

	//if file fails to open, fail test case
	if (file_open.fail()) {
		FAIL("The file could not be opened.");
	}
		
	std::string line;

	//while loop to read all lines in file, push back to vector
	while(getline(file_open, line)) {
		
		vec_strings.push_back(line);
	}

	file_open.close();

	//delete the header because that seems to have been added as well
	vec_strings.erase(vec_strings.begin() + 0);

	//inserting the elements in vec_integers into each data structure
	Linear<std::string> linear_test;
	Tree<std::string> tree_test;
	HashMap<std::string> hashmap_test(vec_strings, 7907);

	for (std::string s: vec_strings) {
		linear_test.insertElement(s);
	}

	for (std::string s: vec_strings) {
		tree_test.insertElement(s);
	}


	SECTION("Testing with first value in input list") {

	//I expect the tree to outperform both the linear structure and hashmap, and for the 
	//linear structure to outperform the hashmap
	CHECK( tree_test.timeComplexity("zaftjrz") < linear_test.timeComplexity("zaftjrz"));
	CHECK( tree_test.timeComplexity("zaftjrz") < hashmap_test.timeComplexity("zaftjrz"));
	CHECK( linear_test.timeComplexity("zaftjrz") < hashmap_test.timeComplexity("zaftjrz"));

	}

	SECTION("Testing with random value in input list") {

	//As the value is closer to the end of the input list, I expect the hashmap to outperform both the tree 
	//and linear structure here, and for the tree to outperform the linear structure
	CHECK( tree_test.timeComplexity("ylmcs") < linear_test.timeComplexity("ylmcs"));
	CHECK( hashmap_test.timeComplexity("ylmcs") < tree_test.timeComplexity("ylmcs"));
	CHECK( hashmap_test.timeComplexity("ylmcs") < linear_test.timeComplexity("ylmcs"));

	}

	SECTION("Testing with last value in input list") {

	//I expect the hashmap to outperform both the tree and linear structure here, and for the tree to outperform
	//the linear structure
	CHECK( tree_test.timeComplexity("dfbdfhrty") < linear_test.timeComplexity("dfbdfhrty"));
	CHECK( hashmap_test.timeComplexity("dfbdfhrty") < tree_test.timeComplexity("dfbdfhrty"));
	CHECK( hashmap_test.timeComplexity("dfbdfhrty") < linear_test.timeComplexity("dfbdfhrty"));

	}


}

*/

/*ANALYSIS OF RESULTS

Before performing the tests for each type, my expectations were based on generally expected performance comparisons for each structure:

1.) For the first value in the input list, linear and tree will always outperform hashmap, with tree outperforming linear. This is because linear and tree
lack the overhead of hashing, and then the subsequent bucket search.

2.) For a random value in the input list, I expected the hashmap to outperform both the linear structure and the tree, with
the tree outperforming the linear structure.

3.) For the last value in the input list, I expected the hashmap to outperform both the linear structure and the tree, with
the tree outperforming the linear structure.

There were some unexpected results:

1.) When it came to testing strings, hashmap outperformed linear while searching for the first value in the list, on multiple runs. To be completely
honest, I am not very sure as to why this occurred for string and not for integer or double.

2.) Tree outperformed hashmap for every value. Initially, I was surprised by this, but then realized that while the hashmap I created had a large number of 
buckets, its load factor when taking the number of values into account was not ideal, probably resulting in many collisions. In addition to this, my hashKey function used the std::hash function and then modulo the bucket number as a hash key. We cannot be certain of uniformity with such a hash function (also,
std::hash may produce differing results across runs depending on the data type it's working with). The hash table may have had a large number of values
in some buckets.

My insertElement function for the hashmap also performed a linear search of the bucket beforehand, to prevent duplicates. This gives it a time complexity
of O(n), the same as the tree's worst case time complexity. It makes sense that the tree can outperform the hashmap to varying degrees.*/


