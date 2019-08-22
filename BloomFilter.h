#include<iostream>
#include<string>
using namespace std;

template <typename T> string to_str(const T& obj) {
	ostringstream oss;
	oss << obj;
	return oss.str();
}

template<class filterType, class elementType>
class BloomFilter
{
private://private members
	filterType* ptr;
	int k;
	int * as;
	int * bs;
	int totalbits;

public://public memvers
	BloomFilter(int, int , int * , int *);
	bool checkExist(elementType element);
	void addElement(elementType element);
	int hash(string , int , int* , int* );
	void BloomFilter<filterType, elementType>::printFilter();

	
};

#include"BloomFilter.cpp"