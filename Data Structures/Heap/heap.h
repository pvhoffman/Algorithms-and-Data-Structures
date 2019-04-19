#ifndef __HEAP_HEAP_H__
#define __HEAP_HEAP_H__

#include <vector>
#include <stdexcept>

namespace pvh
{
/*---------------------------------------------------------------------------*/
template <typename T>
class heap_compare_min
{
    public:
        using value_type = T;
        enum compare_result {lt = -1, eq = 0, gt = 1};
        compare_result compare(const value_type& lhs, const value_type& rhs)
        {
            if(lhs < rhs) return lt;
            if(lhs > rhs) return gt;
            return eq;
        }
};
/*---------------------------------------------------------------------------*/
template <typename T>
class heap_compare_max
{
    public:
        using value_type = T;
        enum compare_result {lt = -1, eq = 0, gt = 1};
        compare_result compare(const value_type& lhs, const value_type& rhs)
        {
            if(lhs < rhs) return gt;
            if(lhs > rhs) return lt;
            return eq;
        }
};

/*---------------------------------------------------------------------------*/
template <typename T, template <class> class compare_policy = heap_compare_min>
class heap : public compare_policy<T>
{
    public:
        using value_type = T;
        using size_type = typename std::vector<value_type>::size_type;
        using compare_type = compare_policy<value_type>;

        class heap_empty_exception : public std::runtime_error
        {
            public:
                heap_empty_exception() : std::runtime_error("heap empty")
                {
                }

        };


        void insert(value_type item)
        {
            _items.emplace_back(std::move(item));
            _heap_up(size() - 1);
        }
        value_type top()
        {
            if(!size())
            {
                throw heap_empty_exception();
            }
            value_type res = _items[0];
            std::swap(_items[0], _items[size() - 1]);
            _items.erase(_items.end() - 1);
            _heap_down(0);
            return res;
        }
        size_type size() const
        {
            return _items.size();
        }

    private:
        std::vector<value_type> _items;

        size_type _first_child(size_type n) const
        {
            return (n * 2) + 1;
        }
        size_type _second_child(size_type n) const
        {
            return (n * 2) + 2;
        }

        size_type _parent(size_type n) const
        {
            return (n - 1) / 2;
        }

        void _heap_up(size_type n)
        {
            if(n)
            {
                auto p  = _parent(n);
                if(compare_type::compare(_items[n], _items[p]) == compare_type::lt)
                {
                    std::swap(_items[n], _items[p]);
                    _heap_up(p);
                }
            }
        }
        void _heap_down(size_type n)
        {
            auto c = _first_child(n);
            auto m = n;

            for(size_type i = 0; i <= 1; i++)
            {
                if((c + i) < size())
                {
                    if(compare_type::compare(_items[m], _items[c + i]) == compare_type::gt)
                    {
                        m = c + i;
                    }
                }
            }
            if(m != n)
            {
                std::swap(_items[m], _items[n]);
                _heap_down(m);
            }
        }

};
/*---------------------------------------------------------------------------*/
} // namespace

#endif /*!__HEAP_HEAP_H__*/

