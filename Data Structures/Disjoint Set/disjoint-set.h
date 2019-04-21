#ifndef __DISJOINT_SET_DISJOINT_SET_H__
#define __DISJOINT_SET_DISJOINT_SET_H__

#include <vector>

namespace pvh
{
/*---------------------------------------------------------------------------*/
template <typename T = int>
class disjoint_set
{
    public:
        using value_type = T;
        using size_type = typename std::vector<value_type>::size_type;

        struct set_node
        {
            size_type parent;
            size_type size;
        };

        disjoint_set(size_type count) : _set_nodes(count + 1), _largest_set(1), _distinct_sets(count)
        {
            for(size_type i = 1; i <= count; i++)
            {
                _set_nodes[i].parent = i;
                _set_nodes[i].size = 1;
            }
        }

        size_type find(size_type x) 
        {
            if(_set_nodes[x].parent == x)
            {
                return x;
            }
            else
            {
                size_type p = find(_set_nodes[x].parent);
                _set_nodes[x].parent = p;
                return p;
            }
        }

        size_type largest_set() const
        {
           return _largest_set;
        }

        void union_sets(size_type x, size_type y)
        {
            auto l = find(x);
            auto r = find(y);

            if(l != r)
            {
                size_type s = 0;
                if(_set_nodes[l].size >= _set_nodes[r].size)
                {
                    _set_nodes[l].size = s = _set_nodes[l].size + _set_nodes[r].size;
                    _set_nodes[r].parent = l;
                }
                else
                {
                    _set_nodes[r].size = s = _set_nodes[r].size + _set_nodes[l].size;
                    _set_nodes[l].parent = r;
                }
                if(s > _largest_set)
                {
                    _largest_set = s;
                }
                --_distinct_sets;
            }
        }

        bool same_set(size_type x, size_type y) 
        {
            return (find(x) == find(y));
        }

        size_type distinct_sets()
        {
            return _distinct_sets;
        }

    private:
        std::vector<set_node> _set_nodes;
        size_type _largest_set;
        size_type _distinct_sets;
        


};
/*---------------------------------------------------------------------------*/
}

#endif /*!__DISJOINT_SET_DISJOINT_SET_H__*/
