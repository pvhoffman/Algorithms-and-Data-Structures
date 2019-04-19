#include <iostream>
#include <utility>

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include "disjoint-set.h"

#if 0
int
main(int argc, char** argv)
{
    pvh::disjoint_set<int> ds(10);
    std::vector< std::pair< int, int> > edges {
        std::make_pair(1,2)
        , std::make_pair(3, 1)
        , std::make_pair(3, 4)
        , std::make_pair(5, 4)
        , std::make_pair(3, 5)
        , std::make_pair(4, 6)
        , std::make_pair(5, 2)
        , std::make_pair(2, 1)
        , std::make_pair(7, 1)
        , std::make_pair(1, 2)
        , std::make_pair(9, 10)
        , std::make_pair(8, 9)
    };

    for(auto edge : edges)
    {
        ds.union_sets(edge.first, edge.second);
    }

    std::cout << ds.largest_set() << std::endl;


    return 0;
}
#endif

