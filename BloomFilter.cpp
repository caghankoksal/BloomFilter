//HELLO Im CaghanKoksal my number is 20588 . This program designed to learn about data structure of BloomFilter and bitwise operations.

#include<iostream>
#include<string>
#include<sstream>
#include<ostream>


using namespace std;


template<class filterType, class elementType>
BloomFilter<filterType, elementType>::BloomFilter(int totalBits, int k, int* as, int* bs)// constructor
{// I stored these values as a private 
	// Also I would use initializer list in here to store parameters
	this->totalbits = totalBits;
	this->as = as;
	this->bs = bs;
	this->k = k;
	double size;

	//cout << sizeof(filterType) << endl;

	size = ceil((totalBits) / (double(sizeof(filterType) * 8)));//to understand how many object I should store in array// object = int or long long vs


	ptr = new filterType[size];// to make all elements zero;
	for (int j = 0; j < size; j++)
	{
		ptr[j] = 0;

	}

}


template<class filterType, class elementType>
int BloomFilter<filterType, elementType>::hash(string x_str, int index, int* as, int* bs) {
	unsigned int hash = 0;
	for (int i = 0; i < x_str.length(); i++) {
		hash ^= (x_str[i] * 899809363);
	}

	hash = (as[index] * hash) + bs[index];
	hash = hash % totalbits;
	return hash;
}




template<class filterType, class elementType>

void BloomFilter<filterType, elementType>::addElement(elementType element)// to add element
{

	string element2 = to_str(element);// to change string because element is templated so I want to make sure its string

	int place_at_array = 0;
	int modulo_place = 0;
	filterType place_changer = 1;
	for (int p = 0; p <= k - 1; p++)// to hash k-1 times
	{


		place_at_array = ceil((hash(element2, p, as, bs)) / (sizeof(filterType) * 8));// to understand the place of bits of the array 1. mi 2. mi 3.mü? size of 3 arrayin
		modulo_place = (hash(element2, p, as, bs)) % (sizeof(filterType) * 8);// to find modulo in order to place the bit
		ptr[place_at_array] = (ptr[place_at_array]) | ((place_changer << ((sizeof(filterType) * 8 - 1) - (modulo_place))));//to shift to the Most Left than goes right by modulo

	}



}




template<class filterType, class elementType>
bool BloomFilter<filterType, elementType>::checkExist(elementType element)
{
	string element2 = to_str(element);
	bool finisher = true;//bool to stop checking if & operation does not return 1 
	int place_at_array = 0;
	int modulo_place = 0;
	filterType place_changer = 1;

	for (int p = 0; p <= k - 1; p++)
	{
		place_at_array = ceil((hash(element2, p, as, bs)) / (sizeof(filterType) * 8));// to understand the place of bits of the array 1. mi 2. mi 3.mü? size of 3 arrayin
		modulo_place = (hash(element2, p, as, bs)) % (sizeof(filterType) * 8);
	

		if (!((ptr[place_at_array]) & ((place_changer << ((sizeof(filterType) * 8 - 1) - (modulo_place))))))//when this return 0 
		{
			finisher = false;// I made finisher false to say They are not in the same memory location
			
		}
	}
	return finisher;
}


template<class filterType, class elementType>
void BloomFilter<filterType, elementType>::printFilter()
{

	int size2 = ceil((totalbits) / (double(sizeof(filterType) * 8)));	//same as size at the top

	char * list = new char[size2 * sizeof(filterType) * 8];//to store datas that will be printed



	filterType*ptr_copy = new filterType[size2];

	for (int c = 0; c < size2; c++)//to copy inside of ptr to ptr_copy array
	{
		ptr_copy[c] = ptr[c];

	}


	list[(size2 * sizeof(filterType) * 8)] = '\0';// to showend the array



	for (int j = 0; j < size2; j++)
	{
		for (int i = 0; i < (sizeof(filterType) * 8); i++)
		{
			if ((ptr_copy[j] & 1) == 1)
			{
				list[((8 * sizeof(filterType))*(j + 1)) - i-1] = '1';//(J+1) to understand in which object and -1 is for not go beyond the list

			}
			else
			{
				//list[((8 * sizeof(filterType) - 1)*(j + 1)) - i] = '0';//FIXEDD BUG
				list[((8 * sizeof(filterType))*(j + 1)) - i-1] = '0';
			}

			ptr_copy[j] = ptr_copy[j] >> 1;

		}
	}
	
	cout << (to_str(list).substr(0, totalbits));//to hide the unnecesrrasy parts of the list //ex: total bit 50 but ı have 2 int(64 bits)


}

