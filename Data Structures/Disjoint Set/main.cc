#include <iostream>
#include <utility>

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include "disjoint-set.h"

/*
 * Given pairs of people, represented as integers, that denotes a friendship relation find the largest group of friends
 * e.g.
 * 1 and 2 are friends
 * 2 and 3 are friends
 * The largest group of friends consists of 3 people:  1, 2, and 3
 */
TEST_CASE("1. Friend Network", "[disjoint_set]")
{
    std::vector< std::pair<int, int> > friend_list {
        std::make_pair(1, 2)
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

    pvh::disjoint_set<int> ds(10);
    for(auto friends : friend_list)
    {
        ds.union_sets(friends.first, friends.second);
    }

    REQUIRE(ds.largest_set() == 7);
}

/*
 * Given pairs of computers, represented as integers, that denotes interconnection , determine if two given computers are currently connected.
 *
 * */
TEST_CASE("2. Network Connections", "[disjoint_set]")
{
    pvh::disjoint_set<int> ds(10);
    // connect computers 1 to 5 and 2 to 7.
    ds.union_sets(1, 5);
    ds.union_sets(2, 7);
    // are computers 7, and 1 connected?
    REQUIRE(ds.same_set(7, 1) == false);

    // connect computer 3 to 9
    ds.union_sets(3, 9);
    // are computers 9 and 6 connected?
    REQUIRE(ds.same_set(9, 6) == false);

    // connect computer 2 to 5
    ds.union_sets(2, 5);
    // are computers 7 and 5 connected?
    REQUIRE(ds.same_set(7, 5) == true);
}

/*
There are so many different religions in the world today
that it is difficult to keep track of them all. You are
interested in  finding out how many different religions
students in your university believe in.

You know that there are n students in your uni-
versity.  It is infeasible for you to
ask every student their religious beliefs. Furthermore,
many students are not comfortable expressing their be-
liefs.  

One way to avoid these problems is to ask m pairs of
students whether they believe in the same religion,
assuming they no each other.  From this data, you may 
not know what each person believes
in, but you can get an idea of the upper bound of how
many different religions can be possibly represented on
campus. You may assume that each student subscribes
to at most one religion.

Given a population of n and m pairs, each item in the
pair believe in the same religion (e.g. given pair (1, 2)
students 1 and 2 have the same religious beliefs.

The goal is to determine the number of different religions,
given the above as input.
*/

TEST_CASE("3. Unique Religions", "[disjoint_set]")
{
    {
        pvh::disjoint_set<int> ds1(10);
        ds1.union_sets(1, 2);
        ds1.union_sets(1, 3);
        ds1.union_sets(1, 4);
        ds1.union_sets(1, 5);
        ds1.union_sets(1, 6);
        ds1.union_sets(1, 7);
        ds1.union_sets(1, 8);
        ds1.union_sets(1, 9);
        ds1.union_sets(1, 10);
        REQUIRE(ds1.distinct_sets() == 1);
    }

    {
        pvh::disjoint_set<int> ds2(10);
        ds2.union_sets(2, 3);
        ds2.union_sets(4, 5);
        ds2.union_sets(4, 8);
        ds2.union_sets(5, 8);
        REQUIRE(ds2.distinct_sets() == 7);
    }
}
