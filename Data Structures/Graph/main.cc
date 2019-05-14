#include <iostream>
#include <utility>
#include <string>
#include <queue>
#include <unordered_set>

/*
#define CATCH_CONFIG_MAIN
*/
#include <catch2/catch.hpp>
#include "graph.h"

int
main(int argc, char** argv)
{
    using graph_t = pvh::graph< pvh::vertex_base, pvh::adjacency_list_policy>;

    graph_t g(false);
    g.add_edge(graph_t::vertex_type(1), graph_t::vertex_type(2));
    g.add_edge(graph_t::vertex_type(2), graph_t::vertex_type(3));
    g.add_edge(graph_t::vertex_type(3), graph_t::vertex_type(4));
    g.add_edge(graph_t::vertex_type(4), graph_t::vertex_type(5));
    g.add_edge(graph_t::vertex_type(5), graph_t::vertex_type(1));
    g.add_edge(graph_t::vertex_type(2), graph_t::vertex_type(5));
    g.add_edge(graph_t::vertex_type(1), graph_t::vertex_type(6));

    // bfs
    std::queue<graph_t::ident_type> qu;
    std::unordered_set<graph_t::ident_type> visited;
    std::unordered_set<graph_t::ident_type> processed;

    qu.push(11);
    try
    {
        while(!qu.empty())
        {
            auto v = qu.front();
            qu.pop();

            if(processed.find(v) == processed.end())
            {
                std::cout << "processing vertex: " << v << std::endl;
                visited.insert(v);
                for(const auto& adj_vs : g[v].second)
                {
                    if(visited.find(adj_vs.destination.id) == visited.end())
                    {
                        std::cout << "\tfound " << adj_vs.destination.id << std::endl;
                        qu.push(adj_vs.destination.id);
                    }
                }
                processed.insert(v);
            }
        }
    }
    catch(graph_t::adjacency_type::unknown_vertex_exception &uvex)
    {
        std::cout << "unknown vertex" << std::endl;
    }

    return 0;
}
