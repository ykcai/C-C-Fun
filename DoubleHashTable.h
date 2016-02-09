#ifndef DOUBLE_HASH_TABLE_H
#define DOUBLE_HASH_TABLE_H
#include "Exception.h"
#include "ece250.h"

enum state { EMPTY, OCCUPIED, DELETED };

template<typename T>
class DoubleHashTable {
	private:
		int count;
		int power;
		int array_size;
		T *array;
		state *array_state;

		int h1( T const & ) const; // first hash function
		int h2( T const & ) const; // second hash function

	public:
		DoubleHashTable( int = 5 );
		~DoubleHashTable();
		int size() const;
		int capacity() const;		
		bool empty() const;
		bool member( T const & ) const;
		T bin( int ) const;

		void print() const;

		void insert( T const & );
		bool remove( T const & );
		void clear();
};

template<typename T >
DoubleHashTable<T >::DoubleHashTable( int m ):
count( 0 ), power( m ),
array_size( 1 << power ),
array( new T [array_size] ),
array_state( new state[array_size] ) {

	for ( int i = 0; i < array_size; ++i ) {
		array_state[i] = EMPTY;
	}
}

template<typename T >
DoubleHashTable<T >::~DoubleHashTable() {
	delete [] array;
	delete [] array_state;
}

template<typename T >
int DoubleHashTable<T >::size() const {
    return count;
}

template<typename T >
int DoubleHashTable<T >::capacity() const {
    return array_size;
}



template<typename T >
bool DoubleHashTable<T >::empty() const { 
	return (count == 0);
}

template<typename T >
int DoubleHashTable<T >::h1( T const &obj ) const {
    int index1 = 0;
    index1 =  static_cast<int>(obj) % array_size;
    if (index1 < 0){
        index1 += array_size;
    }
        
	return index1;
}

template<typename T >
int DoubleHashTable<T >::h2( T const &obj ) const {
    int index2 = 0;
    index2 = (static_cast<int>(obj)/array_size) % array_size;
    if(index2%2==0){
        ++index2;
    }
    if(index2 < 0){
        index2 += array_size;
    }
	return index2;
}

template<typename T >
bool DoubleHashTable<T >::member( T const &obj ) const {
    int probe = h1(obj);
    int offset = h2(obj);
    if ( !empty() ){
        while (array_state[probe] == OCCUPIED && array[probe] != obj){
            probe = (probe + offset)%array_size;
        }
    }   
    return( array[probe] == obj);
}

template<typename T >
T DoubleHashTable<T >::bin( int n ) const {
    if (array_state[n] = OCCUPIED)
	return array[n];
}

template<typename T >
void DoubleHashTable<T >::insert( T const &obj ) {
    int probe = h1(obj);
    int offset = h2(obj);
    if ( count == array_size ){
        throw overflow();
    }
    while (array_state[probe] == OCCUPIED){
        probe = (probe + offset)%array_size;
    }   
    array[probe] = obj;
    array_state[probe] = OCCUPIED;
    ++count;
}

template<typename T >
bool DoubleHashTable<T >::remove( T const &obj ) {
    int probe = h1(obj);
    int offset = h2(obj);
    if ( empty() ){
        throw overflow();
    }
    if (member(obj)){
        while (array_state[probe] == OCCUPIED && array[probe] != obj){
            probe = (probe + offset)%array_size;
        }
        array_state[probe] = DELETED;
        return true;
    }
	return false;
}

template<typename T >
void DoubleHashTable<T >::clear() {
    for (int i = 0; i < array_size; ++i){
        //array[i] = 0;
        array_state[i] = EMPTY;
    } 
    count = 0;
}

template<typename T >
void DoubleHashTable<T >::print() const {
      for (int i = 0; i < array_size; ++i){
        std::cout << "INDEX: " << i <<" ";
        std::cout << "KEY: " << array[i] <<" ";
        std::cout << "STATE: "<< array_state[i] << std::endl;
    } 	
	return;
}

#endif
