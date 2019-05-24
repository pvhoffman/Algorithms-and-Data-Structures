#ifndef __GRAPH_GRAPH_H__
#define __GRAPH_GRAPH_H__

#include <unordered_map>
#include <vector>
#include <stdexcept>

namespace pvh
{
/*---------------------------------------------------------------------------*/
class VertexBase
{
    public:
        struct VertexBaseHash;

        using ident_type = unsigned int;
        using hash_type = VertexBaseHash;

        ident_type m_id;
        VertexBase(ident_type i) : m_id(i)
        {
        }
        bool operator == (const VertexBase& rhs)
        {
            return m_id == rhs.m_id;
        }
        friend bool operator == (const VertexBase& lhs, const VertexBase& rhs)
        {
            return lhs.m_id == rhs.m_id;
        }
        struct VertexBaseHash
        {
            std::size_t operator()(const VertexBase& v) const
            {
                return std::hash<ident_type>()(v.m_id);
            }
        };
};
/*---------------------------------------------------------------------------*/
template <class V>
class GraphEdge
{
    public:
        using vertex_type = V;
        using ident_type  = typename V::ident_type;

        vertex_type m_source;
        vertex_type m_destination;
        int m_weight;

        GraphEdge(vertex_type src, vertex_type dst, int w = 0) : m_source(std::move(src)), m_destination(std::move(dst)), m_weight(w)
        {
        }
};
/*---------------------------------------------------------------------------*/
template <class V>
class AdjacencyListPolicy 
{
    public:
        using vertex_type      = V;
        using ident_type       = typename V::ident_type;
        using edge_type        = GraphEdge<vertex_type>;
        using vertex_hash_type = typename vertex_type::hash_type;
        using map_type         = std::unordered_map<vertex_type, std::vector<edge_type>, vertex_hash_type>;

        class UnknownVertexException : public std::runtime_error
        {
            public:
                UnknownVertexException(const char* what) : std::runtime_error(what)
                {
                }
        };

    protected:
        map_type m_edgenodes;

        void add_edge(vertex_type& source, vertex_type& destination, int w = 0)
        {
            if(m_edgenodes.find(source) == m_edgenodes.end())
            {
                m_edgenodes.insert(std::make_pair(source, std::vector<edge_type>{edge_type(source, destination, w)}));
            }
            else
            {
                m_edgenodes[source].emplace_back(edge_type(source, destination, w));
            }
        }
        const typename map_type::value_type& get_vertex(ident_type i) const
        {
            auto fi = m_edgenodes.find(i);
            if(fi != m_edgenodes.end())
            {
                return *fi;
            }
            throw UnknownVertexException("unknown vertex");
        }
        typename map_type::value_type& get_vertex(ident_type i)
        {
            auto fi = m_edgenodes.find(i);
            if(fi != m_edgenodes.end())
            {
                return *fi;
            }
            throw UnknownVertexException("unknown vertex");
        }
        typename map_type::size_type vertex_count() const
        {
            return m_edgenodes.size();
        }
 
};
/*---------------------------------------------------------------------------*/
template <class V, template <class> class AdjacencyPolicy>
class Graph : public AdjacencyPolicy<V>
{
    public:
        using vertex_type      = V;
        using ident_type       = typename V::ident_type;
        using edge_type        = GraphEdge<vertex_type>;
        using vertex_hash_type = typename vertex_type::hash_type;
        using map_type         = std::unordered_map<vertex_type, std::vector<edge_type>, vertex_hash_type>;
        using adjacency_type   = AdjacencyPolicy<vertex_type>;

        Graph(bool directed) : m_directed(directed)
        {
        }
        void add_edge(vertex_type source, vertex_type destination, int w = 0)
        {
            adjacency_type::add_edge(source, destination, w);
            if(!m_directed)
            {
                // add a back edge
                adjacency_type::add_edge(destination, source, w);
            }
        }
        typename map_type::value_type& operator[] (const ident_type a)
        {
            return adjacency_type::get_vertex(a);
        }
        const typename map_type::value_type& operator[] (const ident_type a) const
        {
            return adjacency_type::get_vertex(a);
        }
        typename map_type::size_type vertex_count() const
        {
            return adjacency_type::vertex_count();
        }
     private:
        bool m_directed;
};
/*---------------------------------------------------------------------------*/
}
#endif /*!__GRAPH_GRAPH_H__*/
