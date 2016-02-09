#ifndef DEQUE_AS_ARRAY_H
#define DEQUE_AS_ARRAY_H
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cmath>        // std::abs
#include "Exception.h"
#include <math.h>
#include <algorithm>

class Deque_as_array {
	private:
		int array_size;
		int*array;
		int ihead;
		int itail;
		int count;

	public:
    //Member function declarations
		Deque_as_array( int = 10 ); //default array size
		~Deque_as_array(); //The de-constructor
        
        //Accessors
		int head() const;
		int tail() const;
		int size() const;
		bool empty() const;
		int capacity() const;

        //Mutators
		void enqueue_head( 
        int const & );
		void enqueue_tail( int const & );
		int dequeue_head();
		int dequeue_tail();
		void clear();
        void print();

	
};

 //The constructor
	// -create an instance of the deque by
	/* 1. Initializing memory for a deque of the given capacity, and 
	   2. Allocating memory for a deque of the given capacity, and
	   3 Initializing the deque size to 0 
	*/
Deque_as_array::Deque_as_array( int n ):
array_size( std::max( 1, n ) ), 
array( new int[array_size] ), 
count( 0 ) {
	if( array_size <= 0 ){
        array_size = 1;
    }
    ihead = -1;
    itail = ihead;
}

/* The de-constructor
    DELETE EVERYTHING AND BE FREE
    De-allocate the memory made for array */
Deque_as_array::~Deque_as_array() {
	delete [] array;
}

/*  Return the number of entires in the deque
 count is the number of objects in the deque */
int Deque_as_array::size() const {
	return count;
}

/*  Return the number of size in the deque
 array_size is the declared size for the deque */
int Deque_as_array::capacity() const {
	return array_size;
}

/* Return if is the deque is empty
See if there are no elements in the deque, then returns true. 
False if there are elements */
bool Deque_as_array::empty() const {
	return (count == 0);
}

/* Check if empty, if not, return the head element (an integer) in the deque
If the dequeu is empty, then head = -1, so an underflow error will be thrown */
int Deque_as_array::head() const {
	if ( empty() ){
        throw underflow();
    }
	return array[ihead];  
}    

/*  Checks if empty, if not, return the tail element (an integer) in the deque
 If the dequeu is empty, then tail = head = -1, 
 so an underflow error will be throw */
int Deque_as_array::tail() const {
	if ( empty() ){
        throw underflow();
    }
	return array[itail];
}    

/* This function will add an element to the head of the deque
To be consistent with constant time, a circle array is used
Head will initially be 0 then 9 and 8 and goes down
After the element has been added,count goes up by 1 (one new element is added)
If the count is equal to the array_size ( max capacity ) 
then my deque is full and an overflow will be thrown */
void Deque_as_array::enqueue_head( int const &obj ) {
	if ( count == (array_size) ){
        throw overflow();
    }
    if( empty() ){
        ihead = 0;
        itail = ihead;
    } else {
        ihead = (array_size + ihead - 1) % array_size;
    } 
    array[ihead] = obj;
    count++;
}

/* This function will add an element to the tail of the deque
To be consistent with constant time, a circle array is used
Head will initially be 0 then 1 and 2 and goes up
After the element has been added,count goes up by 1 (one new element is added)
If the count is equal to the array_size ( max capacity ) 
then my deque is full and an overflow will be thrown */
void Deque_as_array::enqueue_tail( int const &obj ) {
	if ( count >= (array_size) ){
        throw overflow();
    }
    if ( empty() ){
        ihead = 0;
        itail = ihead;
    } else {
        itail = (array_size + itail + 1) % array_size;
    } 
    array[itail] = obj;
    count++;
}

/* This function will remove an element from the head of the deque
To be consistent with constant time, a circle array is used
The head element will be store in a variable called removedHead
Then ihead is moved. Since enqueue_head decreases 0, 9, 8 ... then 
ihead will be added be ++ihead%mod array_size (eg. 6 then 7, 8...)
After the element has been removed,count down up by 1 (one element is added)
Then the removedHead is returned
If the count is equal to 0 
then my deque is empty and an underflow will be thrown */
int Deque_as_array::dequeue_head() {
    if ( count <= 0 ){
        throw underflow();
    }
	int removedHead = array[ihead];
    ihead = (++ihead) % array_size;
    --count;
    return removedHead;
}

/* This function will remove an element from the tail of the deque
To be consistent with constant time, a circle array is used
The tail element will be store in a variable called removedTail
Then itail is moved. Since enqueue_tail is increasing 0, 1, 2 ... then 
itail will be subtracted --itail%mod array_size eg. 6 then 5, 4...
To make sure we don't have a negative itail, I added array_size to itail
After the element has been removed,count down up by 1 (one element is added)
removedTail is returned
If the count is equal to 0 
then my deque is empty and an underflow will be thrown */
int Deque_as_array::dequeue_tail() {
    if ( count <= 0 ){
        throw underflow();
    }
	int removedTail = array[itail];
    itail = (array_size + itail - 1) % array_size;
    --count;
    return removedTail;
}

 
void Deque_as_array::print() {
    for (int x = 0; x < array_size; x++){
		std::cout << array[x] << std::endl;
	} 
}

/* This function will set all count ( number of elements in my deque to 0)
By setting count to 0, it is almost like saying that my deque is empty
However memory is still allocated
Making count to 0, this will not let my accessor access elements in my deque
because exception based on count will be thrown */
void Deque_as_array::clear() {
	count = 0;
    ihead = -1;
    ihead = itail;
}

#endif
