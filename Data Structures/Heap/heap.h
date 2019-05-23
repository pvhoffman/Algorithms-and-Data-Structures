#ifndef __HEAP_HEAP_H__
#define __HEAP_HEAP_H__

#include <vector>
#include <stdexcept>

namespace pvh
{
/*---------------------------------------------------------------------------*/
template <typename T>
class HeapCompareMin
{
    public:
        using value_type = T;
        enum CompareResult {lt = -1, eq = 0, gt = 1};
        CompareResult compare(const value_type& lhs, const value_type& rhs)
        {
            if(lhs < rhs) return lt;
            if(lhs > rhs) return gt;
            return eq;
        }
};
/*---------------------------------------------------------------------------*/
template <typename T>
class HeapCompareMax
{
    public:
        using value_type = T;
        enum CompareResult {lt = -1, eq = 0, gt = 1};
        CompareResult compare(const value_type& lhs, const value_type& rhs)
        {
            if(lhs < rhs) return gt;
            if(lhs > rhs) return lt;
            return eq;
        }
};

/*---------------------------------------------------------------------------*/
template <typename T, template <class> class ComparePolicy = HeapCompareMin>
class Heap : public ComparePolicy<T>
{
    public:
        using value_type = T;
        using size_type = typename std::vector<value_type>::size_type;
        using compare_type = ComparePolicy<value_type>;

        class HeapEmptyException : public std::runtime_error
        {
            public:
                HeapEmptyException() : std::runtime_error("heap empty")
                {
                }

        };


        void insert(value_type item)
        {
            m_items.emplace_back(std::move(item));
            heap_up(size() - 1);
        }
        value_type top()
        {
            if(!size())
            {
                throw HeapEmptyException();
            }
            value_type res = m_items[0];
            std::swap(m_items[0], m_items[size() - 1]);
            m_items.erase(m_items.end() - 1);
            heap_down(0);
            return res;
        }
        size_type size() const
        {
            return m_items.size();
        }

    private:
        std::vector<value_type> m_items;

        size_type first_child(size_type n) const
        {
            return (n * 2) + 1;
        }
        size_type second_child(size_type n) const
        {
            return (n * 2) + 2;
        }

        size_type parent(size_type n) const
        {
            return (n - 1) / 2;
        }

        void heap_up(size_type n)
        {
            if(n)
            {
                auto p  = parent(n);
                if(compare_type::compare(m_items[n], m_items[p]) == compare_type::lt)
                {
                    std::swap(m_items[n], m_items[p]);
                    heap_up(p);
                }
            }
        }
        void heap_down(size_type n)
        {
            auto c = first_child(n);
            auto m = n;

            for(size_type i = 0; i <= 1; i++)
            {
                if((c + i) < size())
                {
                    if(compare_type::compare(m_items[m], m_items[c + i]) == compare_type::gt)
                    {
                        m = c + i;
                    }
                }
            }
            if(m != n)
            {
                std::swap(m_items[m], m_items[n]);
                heap_down(m);
            }
        }
};
/*---------------------------------------------------------------------------*/
} // namespace

#endif /*!__HEAP_HEAP_H__*/

