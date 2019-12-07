#include <iostream>
#include "Rectangle.h"
#include "./containers/list.h"
#include <string.h>
#include <algorithm>
#include "my_allocator.h"

 

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE testListDelete

#include <boost/test/unit_test.hpp>


BOOST_AUTO_TEST_CASE(testDeleteMiddle) {
   containers::list<Rectangle<int>,myal::my_allocator<Rectangle<int>,330>> l;
    l.add(Rectangle<int>({0,3},{3,3},{0,0},{3,0}));
    l.add(Rectangle<int>({0,1},{1,1},{0,0},{1,0}));
    l.add(Rectangle<int>({0,2},{2,2},{0,0},{2,0}));
    l.erase(l.begin()+1);
    BOOST_CHECK_EQUAL(l[1].getSquare(), 4);
}
BOOST_AUTO_TEST_CASE(testDeleteFront) {
   containers::list<Rectangle<int>,myal::my_allocator<Rectangle<int>,330>> l;
    l.add(Rectangle<int>({0,3},{3,3},{0,0},{3,0}));
    l.add(Rectangle<int>({0,1},{1,1},{0,0},{1,0}));
    l.add(Rectangle<int>({0,2},{2,2},{0,0},{2,0}));
    l.erase(l.begin());
    BOOST_CHECK_EQUAL(l[0].getSquare(), 1);
}