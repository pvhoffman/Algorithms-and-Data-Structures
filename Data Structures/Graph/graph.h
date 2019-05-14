#ifndef __GRAPH_GRAPH_H__
#define __GRAPH_GRAPH_H__

#include <unordered_map>
#include <vector>
#include <stdexcept>

namespace pvh
{
/*---------------------------------------------------------------------------*/
class vertex_base
{
    public:
        struct vertex_base_hash;

        using ident_type = unsigned int;
        using hash_type = vertex_base_hash;

        ident_type id;
        vertex_base(ident_type i) : id(i)
        {
        }
        bool operator == (const vertex_base& rhs)
        {
            return id == rhs.id;
        }
        friend bool operator == (const vertex_base& lhs, const vertex_base& rhs)
        {
            return lhs.id == rhs.id;
        }
        struct vertex_base_hash
        {
            std::size_t operator()(const vertex_base& v) const
            {
                return std::hash<ident_type>()(v.id);
            }
        };
};
/*---------------------------------------------------------------------------*/
template <class V>
class edge
{
    public:
        using vertex_type = V;
        using ident_type  = typename V::ident_type;

        vertex_type source;
        vertex_type destination;
        int weight;

        edge(vertex_type src, vertex_type dst, int w = 0) : source(std::move(src)), destination(std::move(dst)), weight(w)
        {
        }
};
/*---------------------------------------------------------------------------*/
template <class V>
class adjacency_list_policy
{
    public:
        using vertex_type      = V;
        using ident_type       = typename V::ident_type;
        using edge_type        = edge<vertex_type>;
        using vertex_hash_type = typename vertex_type::hash_type;
        using map_type         = std::unordered_map<vertex_type, std::vector<edge_type>, vertex_hash_type>;

        class unknown_vertex_exception : public std::runtime_error
        {
            public:
                unknown_vertex_exception(const char* what) : std::runtime_error(what)
                {
                }
        };

    protected:
        map_type _edgenodes;

        void _add_edge(vertex_type& source, vertex_type& destination, int w = 0)
        {
            if(_edgenodes.find(source) == _edgenodes.end())
            {
                _edgenodes.insert(std::make_pair(source, std::vector<edge_type>{edge_type(source, destination, w)}));
            }
            else
            {
                _edgenodes[source].emplace_back(edge_type(source, destination, w));
            }
        }
        const typename map_type::value_type& _get_vertex(ident_type i) const
        {
            auto fi = _edgenodes.find(i);
            if(fi != _edgenodes.end())
            {
                return *fi;
            }
            throw unknown_vertex_exception("unknown vertex");
        }
        typename map_type::value_type& _get_vertex(ident_type i)
        {
            auto fi = _edgenodes.find(i);
            if(fi != _edgenodes.end())
            {
                return *fi;
            }
            throw unknown_vertex_exception("unknown vertex");
        }
        typename map_type::size_type _vertex_count() const
        {
            return _edgenodes.size();
        }
 
};
/*---------------------------------------------------------------------------*/
template <class V, template <class> class adjacency_policy>
class graph : public adjacency_policy<V>
{
    public:
        using vertex_type      = V;
        using ident_type       = typename V::ident_type;
        using edge_type        = edge<vertex_type>;
        using vertex_hash_type = typename vertex_type::hash_type;
        using map_type         = std::unordered_map<vertex_type, std::vector<edge_type>, vertex_hash_type>;
        using adjacency_type   = adjacency_policy<vertex_type>;

        graph(bool directed) : _directed(directed)
        {
        }
        void add_edge(vertex_type source, vertex_type destination, int w = 0)
        {
            adjacency_type::_add_edge(source, destination, w);
            if(!_directed)
            {
                // add a back edge
                adjacency_type::_add_edge(destination, source, w);
            }
        }
        typename map_type::value_type& operator[] (const ident_type a)
        {
            return adjacency_type::_get_vertex(a);
        }
        const typename map_type::value_type& operator[] (const ident_type a) const
        {
            return adjacency_type::_get_vertex(a);
        }
        typename map_type::size_type vertex_count() const
        {
            return adjacency_type::_vertex_count();
        }
     private:
        bool _directed;
};
/*---------------------------------------------------------------------------*/
}
#endif /*!__GRAPH_GRAPH_H__*/
