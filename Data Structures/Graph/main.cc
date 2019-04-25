#include <iostream>
#include <utility>
#include <string>

/*
#define CATCH_CONFIG_MAIN
*/
#include <catch2/catch.hpp>
#include "graph.h"

int
main(int argc, char** argv)
{
    using graph_t = pvh::graph<std::string, pvh::adjacency_list_policy>;

    graph_t graph;

    graph.add_edge(graph_t::vertex_type("hello"), graph_t::vertex_type("world"));
    graph.add_edge(graph_t::vertex_type("hello"), graph_t::vertex_type("baz"));
    //graph.add_edge(graph_t::vertex_type(2), graph_t::vertex_type(3));
    //graph.add_edge(graph_t::vertex_type(3), graph_t::vertex_type(4));
    //graph.add_edge(graph_t::vertex_type(4), graph_t::vertex_type(5));

    const auto& s = graph["hello"];
    for(const auto& v : s.second)
    {
        std::cout << v.t.id << " -> ";
    }
    std::cout << std::endl;

   return 0;
}
