#ifndef ARRAY_H
#define ARRAY_H
#include "Exception.h"
#include <math.h>

class Array
{
	private: 
		int array_capacity;
		int *internal_array;
		int array_size;

	public:
		//Member function declarations
		Array(int = 10); //default array size
        ~Array();

        //Accessors
        int capacity() const;
        bool empty() const;
        bool full() const;
        int size() const;
        int at(int) const;
        
        int sum() const;
        double average() const;
        double std_dev() const;
        double variance() const;
        //Mutators
         bool append ( int );
         void clear();
		 void swap (Array);
};

	//Member function definitions
	
	//The constructor
	// -create an instance of the array by
	/* 1. Initializing memory for an array of the given capacity, and 
	   2. Allocating memory for an array of the given capacity, and
	   3 Initializing the array size to 0 
	*/
	Array::Array(int n):
	array_capacity( std::max(1,n) ),
    internal_array( new int[array_capacity] ),
    array_size( 0 ) {
        if ( array_capacity <= 0)	{
        	array_capacity = 1;
		}
    }
    
    //The de-constructor
    //DELETE EVERYTHING AND BE FREE 
    Array::~Array(){
        delete [] internal_array;
    }
    //Return the number of entires in the array
    int Array::size() const{
        return array_size;
    }
    
    int Array::capacity() const{
        return array_capacity;
    }
    
    //Append a new entry into the array
    /* Note that 
    -when the array size is k, the next item should be appended in location k*
    and the size is then k+1 */
    bool Array::append( int obj ){
        if( full()){
            return false;
        }
        
        // currently, entries 0,...., arry_size - 1 are occupied
        internal_array[array_size] = obj;
        ++array_size;
        
        return true;
    }
    
    void Array::clear(){
        array_size = 0;
    }
    
    bool Array::empty() const {
        return (array_size == 0);
    }
    
    bool Array::full() const {
        return array_size == array_capacity;
    } 
    
    int Array::sum() const{
        int sum = 0;
        for (int i = 0; i < array_size; ++i){
            sum = sum + internal_array[i];
        }
        
        return sum;
    }
    
    double Array::average() const{
        if ( empty() ) {
            throw division_by_zero();
        }
        return (sum()*1.0/array_size);
    }
    
    double Array::variance() const{
        if ( size() <= 1 ) {
            throw underflow();
        }
        double diff = 0;
        double avg = average();
        for (int i = 0; i < array_size; ++i){
            diff += (internal_array[i] - avg)*(internal_array[i] - avg);
        }
        return (1.0/(array_size -1))*diff; 
    }
    
    int Array::at( int n ) const {
        if ( n < 0 || n >= size()){
            throw out_of_range();
        }
        return internal_array[n];
    }
    
    double Array::std_dev() const {
        return sqrt(variance());
    }
	
	void Array::swap(Array %other){
		std::swap( array_capacity, other.array_capacity);
		std::swap( internal_array, other.intern_array);
		std::swap( array_size, other.array_size);
	}
#endif  
