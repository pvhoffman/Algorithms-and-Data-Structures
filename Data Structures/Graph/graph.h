#ifndef __GRAPH_GRAPH_H__
#define __GRAPH_GRAPH_H__

#include <unordered_map>
#include <vector>

/*


   G(V|E) -> 



class vertex
{
    public:
        int id;
};

class edge
{
    public:
        vertex src;
        vertex dst; 
        int weight;
};

class graph
{
    public:
        bool directed;
        std::map<vertex, std::vector<edge> > vs;

        add_edge(vertex from, vertex to, int weight)
        {
            vs[from].push_back(edge(from, to, weight));
            if(!directed)
            {
                vs[to].push_back(edge(to, from, weight));
            }
        }
};

*/
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
template <class ID>
class adjacency_list_policy
{
    public:
        using ident_type = ID;
        using vertex_type = vertex<ident_type>;
        using edge_type = edge<ident_type>;
        using vertex_hash_type = typename vertex_type::vertex_hash;
        using map_type = std::unordered_map<vertex_type, std::vector<edge_type>, vertex_hash_type>;

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
            return _edgenodes[i];
        }
        typename map_type::value_type& _get_vertex(ident_type i)
        {
            auto fi = _edgenodes.find(i);
            return *fi;
            //return _edgenodes.find(i);
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

        bool directed;

        void add_edge(vertex_type s, vertex_type t, int w = 0)
        {
            adjacency_type::_add_edge(s, t, w);
            if(!directed)
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

    private:

};
/*---------------------------------------------------------------------------*/
}
#endif /*!__GRAPH_GRAPH_H__*/
