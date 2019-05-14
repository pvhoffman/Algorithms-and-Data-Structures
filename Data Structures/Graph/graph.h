#ifndef __GRAPH_GRAPH_H__
#define __GRAPH_GRAPH_H__

#include <unordered_map>
#include <vector>
#include <stdexcept>

namespace pvh
{
/*---------------------------------------------------------------------------*/
template <class ID>
class vertex
{
    public:
        using ident_type = ID;

        ident_type id;
        vertex(ident_type i) : id(i)
        {
        }
        bool operator == (const vertex& rhs)
        {
            return id == rhs.id;
        }
        friend bool operator == (const vertex& lhs, const vertex& rhs)
        {
            return lhs.id == rhs.id;
        }
        struct vertex_hash
        {
            std::size_t operator()(const vertex& v) const
            {
                return std::hash<ident_type>()(v.id);
            }
        };
};
/*---------------------------------------------------------------------------*/
template <class ID>
class edge
{
    public:
        using ident_type = ID;
        using vertex_type = vertex<ident_type>;

        vertex_type s;
        vertex_type t;
        int weight;

        edge(vertex_type v1, vertex_type v2, int w = 0) : s(std::move(v1)), t(std::move(v2)), weight(w)
        {
        }
};
/*---------------------------------------------------------------------------*/
template <class ID>
class adjacency_list_policy
{
    public:
        using ident_type = ID;
        using vertex_type = vertex<ident_type>;
        using edge_type = edge<ident_type>;
        using vertex_hash_type = typename vertex_type::vertex_hash;
        using map_type = std::unordered_map<vertex_type, std::vector<edge_type>, vertex_hash_type>;

        class unknown_vertex_exception : public std::runtime_error
        {
            public:
                unknown_vertex_exception(const char* what) : std::runtime_error(what)
                {
                }
        };

    protected:
        map_type _edgenodes;

        void _add_edge(vertex_type& s, vertex_type& t, int w = 0)
        {
            if(_edgenodes.find(s) == _edgenodes.end())
            {
                _edgenodes.insert(std::make_pair(s, std::vector<edge_type>{edge_type(s, t, w)}));
            }
            else
            {
                _edgenodes[s].emplace_back(edge_type(s, t, w));
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
template <class ID, template <class> class adjacency_policy>
class graph : public adjacency_policy<ID>
{
    public:
        using ident_type = ID;
        using vertex_type = vertex<ident_type>;
        using edge_type = edge<ident_type>;
        using adjacency_type = adjacency_policy<ident_type>;
        using vertex_hash_type = typename vertex_type::vertex_hash;
        using map_type = std::unordered_map<vertex_type, std::vector<edge_type>, vertex_hash_type>;

        graph(bool directed) : _directed(directed)
        {
        }
        void add_edge(vertex_type s, vertex_type t, int w = 0)
        {
            adjacency_type::_add_edge(s, t, w);
            if(!_directed)
            {
                adjacency_type::_add_edge(t, s, w);
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
