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
    std::cout << "Currently no test cases for graph data structure." << std::endl;
#if 0
    using graph_t = pvh::graph<std::string, pvh::adjacency_list_policy>;

    graph_t graph(false);

    graph.add_edge(graph_t::vertex_type("paul"), graph_t::vertex_type("kendra"));
    graph.add_edge(graph_t::vertex_type("kendra"), graph_t::vertex_type("quinn"));
    graph.add_edge(graph_t::vertex_type("kendra"), graph_t::vertex_type("riley"));
    graph.add_edge(graph_t::vertex_type("riley"), graph_t::vertex_type("allie"));
    graph.add_edge(graph_t::vertex_type("allie"), graph_t::vertex_type("crystal"));
    graph.add_edge(graph_t::vertex_type("quinn"), graph_t::vertex_type("judd"));

    // bfs -- start with paul
    std::queue<graph_t::vertex_type> qu;
    std::unordered_set<std::string> visited;
    std::unordered_map<std::string, std::string> ps;

    qu.push(graph["judd"].first);
    while(!qu.empty())
    {
        auto v = qu.front();
        std::cout << "processing vertex: " << v.id << std::endl;
        qu.pop();
        visited.insert(v.id);
        for(const auto& ns : graph[v.id].second)
        {
            if(visited.find(ns.t.id) == visited.end())
            {
                ps[ns.t.id] = v.id;
                qu.push(ns.t);
            }
        }
    }

    // follow judd's network of friends up
    auto pi = ps.find("paul");
    if(pi != ps.end())
    {
        std::cout << (*pi).first << " <- ";
        while(pi != ps.end())
        {
            std::cout << (*pi).second << " <- ";
            auto p = (*pi).second;
            pi = ps.find(p);
        }
    }
    std::cout << std::endl;
#endif
    return 0;

}
