#pragma once
#include "Mem.h"
#include "Set.h"
using namespace std;

class Set_Test {
private:
	Set* main_set;
	Mem* _memory;
public:
	Set_Test(size_t size);
	~Set_Test();

	void fill_array(size_t count_elem); //test insert
	int check_insert(int index); //check insert
	void print_elements(); //print all elements

	void test_remove_find(size_t count_elem); //
	void test_removing_all_elem(size_t count_elem); //test empty
	//int Test_two_Iterators(size_t count_elem); //***
	void Test_void_insert(); //
	void Test_rehash_function(size_t count_elem); //

	//insert, remove, find +
	//newIterator clear empty size +
	//getElement gotoNext hasNext +
};
