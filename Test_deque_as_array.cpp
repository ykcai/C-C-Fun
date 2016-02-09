#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Deque_as_array.h"
#include "Exception.h"
using namespace std;

int main() {
    Deque_as_array foo(15);
    
    assert(foo.empty());
    assert(foo.empty() != 0);
    assert(foo.size() == 0);
    
    foo.enqueue_head(1);
    foo.enqueue_head(2);
    foo.enqueue_head(3);
    foo.enqueue_head(334);
    foo.enqueue_head(35);
    foo.enqueue_tail(12);
    foo.enqueue_tail(11);
    foo.enqueue_tail(13);
    foo.enqueue_tail(14);
    foo.enqueue_tail(90);
    assert(foo.head() == 35);
    assert(foo.size() == 10);
    assert(foo.capacity() == 15);
    assert(foo.tail() != 14);
    assert(foo.tail() == 90);
    assert(foo.empty() != 1);
    foo.enqueue_head(10);
    assert(foo.dequeue_head() == 10);
    assert(foo.dequeue_tail() == 90);
    assert(foo.dequeue_tail() == 14);
    assert(foo.head() == 35);
    assert(foo.dequeue_head() == 35);
    assert(foo.head() == 334);
    assert(foo.tail() == 13);
    foo.enqueue_head(111);
    foo.enqueue_head(121);
    foo.enqueue_tail(122);
    foo.enqueue_head(129);
    foo.enqueue_tail(127);
    foo.enqueue_head(137);
    foo.enqueue_head(147);
    foo.enqueue_tail(177);
    assert(foo.size() == 15);
    assert(foo.head() == 147);
    assert(foo.tail() == 177);
    
    try{
        foo.enqueue_tail(12);
    }
    catch ( overflow ) {
        assert(true);
    }
    
    foo.clear();

    cout<< " YOU PASSED MY TESTS";
return 0;
}
    