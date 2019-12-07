#include <iostream>
#include "Rectangle.h"
#include "./containers/list.h"
#include <string.h>
#include <algorithm>
#include "my_allocator.h"

 

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE testList

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(testMemory) {
    containers::list<Rectangle<int>,myal::my_allocator<Rectangle<int>,330>> l;
    try {
        l.add(Rectangle<int>({0,0},{0,0},{0,0},{0,0}));  
    } catch(std::bad_alloc& e) {
    
    }
     try {
        l.add(Rectangle<int>({0,0},{0,0},{0,0},{0,0}));  
    } catch(std::bad_alloc& e) {
    
    }
 try {
        l.add(Rectangle<int>({0,0},{0,0},{0,0},{0,0}));  
    } catch(std::bad_alloc& e) {
    
    }
     try {
        l.add(Rectangle<int>({0,0},{0,0},{0,0},{0,0}));  
    } catch(std::bad_alloc& e) {
    
    }
     try {
        l.add(Rectangle<int>({0,0},{0,0},{0,0},{0,0}));  
    } catch(std::bad_alloc& e) {
    
    }
     try {
        l.add(Rectangle<int>({0,0},{0,0},{0,0},{0,0}));  
    } catch(std::bad_alloc& e) {
    
    }
     try {
        l.add(Rectangle<int>({0,0},{0,0},{0,0},{0,0}));  
    } catch(std::bad_alloc& e) {
    
    }
     try {
        l.add(Rectangle<int>({0,0},{0,0},{0,0},{0,0}));  
    } catch(std::bad_alloc& e) {
    
    }
    BOOST_CHECK_EQUAL(l.Size(), 5);

}

BOOST_AUTO_TEST_CASE(testFront) {
    containers::list<Rectangle<int>,myal::my_allocator<Rectangle<int>,330>> l;
    l.add(Rectangle<int>({0,3},{3,3},{0,0},{3,0}));
    l.add(Rectangle<int>({0,1},{1,1},{0,0},{1,0}));
    l.add(Rectangle<int>({0,2},{2,2},{0,0},{2,0}));

    BOOST_CHECK_EQUAL(l.front().getSquare(), 9);
}

BOOST_AUTO_TEST_CASE(testEnd) {
   containers::list<Rectangle<int>,myal::my_allocator<Rectangle<int>,330>> l;
    l.add(Rectangle<int>({0,3},{3,3},{0,0},{3,0}));
    l.add(Rectangle<int>({0,1},{1,1},{0,0},{1,0}));
    l.add(Rectangle<int>({0,2},{2,2},{0,0},{2,0}));

    BOOST_CHECK_EQUAL(l.End().getSquare(), 4);
}

