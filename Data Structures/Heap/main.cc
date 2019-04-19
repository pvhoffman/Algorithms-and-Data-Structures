#include <iostream>
#include <cstdlib>
#include <ctime>
#include <climits>
#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include "heap.h"


static int random_heap_size()
{
    const int min_heap_size = 100;
    const int max_heap_size = 1000;
    std::srand(std::time(nullptr));
    int heap_size = min_heap_size + rand() % ((max_heap_size + 1) - min_heap_size);
    return heap_size;
}

TEST_CASE("1. Min heap sort order", "[minheap]")
{

    using IntegerMinHeap = pvh::heap<int, pvh::heap_compare_min>;
    IntegerMinHeap minheap;


    int heap_size = random_heap_size();
    for(int i = 0; i < heap_size; i++)
    {
        minheap.insert(std::rand());
    }

    int j = 0, last_j = 0;
    while(minheap.size() != 0)
    {
        j = minheap.top();
        REQUIRE(last_j <= j);
        last_j = j;
    }
}

TEST_CASE("2. Max heap sort order", "[maxheap]")
{

    using IntegerMaxHeap = pvh::heap<int, pvh::heap_compare_max>;
    IntegerMaxHeap maxheap;


    int heap_size = random_heap_size();
    for(int i = 0; i < heap_size; i++)
    {
        maxheap.insert(std::rand());
    }

    int j = 0, last_j = INT_MAX;
    while(maxheap.size() != 0)
    {
        j = maxheap.top();
        REQUIRE(last_j >= j);
        last_j = j;
    }
}

