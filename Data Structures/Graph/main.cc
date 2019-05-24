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


/* the vertex type can be any user defined type, not just a primative
 *
 *
 * */

struct FriendStreetAddress
{
    std::string street_number;
    std::string unit_number;
    std::string street_name;
    FriendStreetAddress(std::string street_num, std::string unit_num, std::string name) :
        street_number(std::move(street_num))
        , unit_number(std::move(unit_num))
        , street_name(std::move(name))
    {
    }
    FriendStreetAddress()
    {
    }
};

struct FriendStreetAddressVertex
{

    struct FriendStreetAddressVertexHash;
    using ident_type = FriendStreetAddress;
    using hash_type  = FriendStreetAddressVertexHash;

    ident_type id;

    FriendStreetAddressVertex(ident_type i) : id(i)
    {
    }

    bool operator == (const FriendStreetAddressVertex& rhs)
    {
        return false;
    }

    friend bool operator == (const FriendStreetAddress& lhs, const FriendStreetAddress& rhs)
    {
        return lhs.street_number == rhs.street_number
            && lhs.unit_number == rhs.unit_number
            && lhs.street_name == rhs.street_name;
    }
    struct FriendStreetAddressHash
    {
        std::size_t operator()(const FriendStreetAddress& f)
        {
            return ((std::hash<std::string>()(f.street_number) 
                    ^ (std::hash<std::string>()(f.unit_number) << 5)
                    ^ (std::hash<std::string>()(f.street_name) << 13)));
        }
    };
};

int
main(int argc, char** argv)
{
    using graph_t = pvh::Graph< pvh::VertexBase, pvh::AdjacencyListPolicy>;
    //using graph1_t = pvh::graph< FriendStreetAddressVertex, pvh::adjacency_list_policy>;

    //graph1_t(false);
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
                    if(visited.find(adj_vs.m_destination.m_id) == visited.end())
                    {
                        std::cout << "\tfound " << adj_vs.m_destination.m_id << std::endl;
                        qu.push(adj_vs.m_destination.m_id);
                    }
                }
                processed.insert(v);
            }
        }
    }
    catch(graph_t::adjacency_type::UnknownVertexException &uvex)
    {
        std::cout << "unknown vertex" << std::endl;
    }

    return 0;
}
