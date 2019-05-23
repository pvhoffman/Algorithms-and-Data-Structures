#ifndef __DISJOINT_SET_DISJOINT_SET_H__
#define __DISJOINT_SET_DISJOINT_SET_H__

#include <vector>

namespace pvh
{
/*---------------------------------------------------------------------------*/
template <typename T = int>
class DisjointSet
{
    public:
        using value_type = T;
        using size_type = typename std::vector<value_type>::size_type;

        struct SetNode
        {
            size_type m_parent;
            size_type m_size;
        };

        DisjointSet(size_type count) : m_set_nodes(count + 1), m_largest_set(1), m_distinct_sets(count)
        {
            for(size_type i = 1; i <= count; i++)
            {
                m_set_nodes[i].m_parent = i;
                m_set_nodes[i].m_size = 1;
            }
        }

        size_type find(size_type x) 
        {
            if(m_set_nodes[x].m_parent == x)
            {
                return x;
            }
            size_type p = find(m_set_nodes[x].m_parent);
            m_set_nodes[x].m_parent = p;
            return p;
        }

        size_type largest_set() const
        {
           return m_largest_set;
        }

        void union_sets(size_type x, size_type y)
        {
            auto l = find(x);
            auto r = find(y);

            if(l != r)
            {
                size_type s = 0;
                if(m_set_nodes[l].m_size >= m_set_nodes[r].m_size)
                {
                    m_set_nodes[l].m_size = s = m_set_nodes[l].m_size + m_set_nodes[r].m_size;
                    m_set_nodes[r].m_parent = l;
                }
                else
                {
                    m_set_nodes[r].m_size = s = m_set_nodes[r].m_size + m_set_nodes[l].m_size;
                    m_set_nodes[l].m_parent = r;
                }
                if(s > m_largest_set)
                {
                    m_largest_set = s;
                }
                --m_distinct_sets;
            }
        }

        bool same_set(size_type x, size_type y) 
        {
            return (find(x) == find(y));
        }

        size_type distinct_sets()
        {
            return m_distinct_sets;
        }

    private:
        std::vector<SetNode> m_set_nodes;
        size_type m_largest_set;
        size_type m_distinct_sets;
};
/*---------------------------------------------------------------------------*/
}
#endif /*!__DISJOINT_SET_DISJOINT_SET_H__*/

