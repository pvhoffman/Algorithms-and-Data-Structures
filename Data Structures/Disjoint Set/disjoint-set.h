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

        disjoint_set(size_type count) : _set_nodes(count + 1)
        {
            for(size_type i = 1; i <= count; i++)
            {
                _set_nodes[i].parent = i;
                _set_nodes[i].size = 1;
            }
        }
        size_type find(size_type x) const
        {
            if(_set_nodes[x].parent == x)
            {
                return x;
            }
            else
            {
                return find(_set_nodes[x].parent);
            }
        }

        size_type largest_set() const
        {
            size_type r = 0;
            for(const auto& node : _set_nodes)
            {
                if(node.size > r)
                {
                    r = node.size;
                }
            }
            return r;
        }

        void union_sets(size_type x, size_type y)
        {
            auto l = find(x);
            auto r = find(y);

            if(l != r)
            {
                if(_set_nodes[l].size >= _set_nodes[r].size)
                {
                    _set_nodes[l].size = _set_nodes[l].size + _set_nodes[r].size;
                    _set_nodes[r].parent = l;
                }
                else
                {
                    _set_nodes[r].size = _set_nodes[r].size + _set_nodes[l].size;
                    _set_nodes[l].parent = r;
                }
            }
        }

        bool same_set(size_type x, size_type y) const
        {
            return (find(x) == find(y));
        }

    private:
        std::vector<set_node> _set_nodes;


};
/*---------------------------------------------------------------------------*/
}

#endif /*!__DISJOINT_SET_DISJOINT_SET_H__*/
