#ifndef __GRAPH_GRAPH_H__
#define __GRAPH_GRAPH_H__

#include <vector>

namespace pvh
{
/*---------------------------------------------------------------------------*/
class default_edge_node_type
{
    public:
        int y;
        int weight;
    private:
}
/*---------------------------------------------------------------------------*/
template <class edge_node_type = default_edge_node_type>
class adjacency_list_policy
{
    public:
        using value_type = edge_node_type
        using size_type = std::vector<value_type>::size_type;
        adjacency_list_policy(size_type vertex_count) : _adjacency_list(vertex_count)
        {
        }
    protected:
        std::vector< std::vector<value_type> > _adjacency_list;

        void _add_edge(edge_node_type from, edge_node_type to)
        {
            _adjacency_list[from.y].emplace_back( std::move(to) );
        }
}
/*---------------------------------------------------------------------------*/
template <class edge_node_type, template <class> adjacency_policy>
class graph : public adjacency_policy<edge_node_type>
{
    public:
        graph(size_type vertex_count, bool directed) : adjacency_policy(vertex_count), _directed(directed)
        {
        }
        void add_edge(const edge_node_type& from, const edge_node_type& to)
        {
            adjacency_policy::_add_edge(from, to);
            if(!_directed)
            {
                adjacency_policy::_add_edge(to, from);
            }
        }
    private:
        bool _directed;
};
/*---------------------------------------------------------------------------*/
}
#endif /*!__GRAPH_GRAPH_H__*/
