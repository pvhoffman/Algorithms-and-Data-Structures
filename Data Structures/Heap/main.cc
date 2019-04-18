#include <iostream>

//#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include "heap.h"

int
main(int argc, char** argv)
{

    using IntegerMinHeap = pvh::heap<int, pvh::heap_compare_min>;

    IntegerMinHeap minheap;

    minheap.insert(10);
    minheap.insert(8);
    minheap.insert(6);
    minheap.insert(9);
    minheap.insert(7);
    minheap.insert(2);
    minheap.insert(1);
    minheap.insert(5);
    minheap.insert(4);
    minheap.insert(3);
    minheap.insert(0);
    minheap.insert(-5);


    while(minheap.size() != 0)
    {
        std::cout << minheap.top() << " -> ";
    }
    std::cout << std::endl;
    return 0;
}


