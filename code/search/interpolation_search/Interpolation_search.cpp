/*
 Part of Cosmos by OpenGenus Foundation

 interpolation search synopsis

 warning: in order to follow the convention of STL, the interface is [begin, end) !!!

 // [begin, end)
template<typename _Random_Access_Iter,
         typename _Type = typename std::iterator_traits<_Random_Access_Iter>::value_type,
         typename _Compare>
_Random_Access_Iter
interpolation_search(_Random_Access_Iter begin,
                     _Random_Access_Iter end,
                     _Type const &find,
                     _Compare compare);

// [begin, end)
template<typename _Random_Access_Iter,
         typename _Type = typename std::iterator_traits<_Random_Access_Iter>::value_type>
_Random_Access_Iter
interpolation_search(_Random_Access_Iter begin, _Random_Access_Iter end, _Type const &find);
 */

#include <algorithm>

// [begin, end)
template<typename _Random_Access_Iter,
         typename _Type = typename std::iterator_traits<_Random_Access_Iter>::value_type,
         typename _Compare>
_Random_Access_Iter
interpolation_search(_Random_Access_Iter begin,
                     _Random_Access_Iter end,
                     _Type const &find,
                     _Compare compare)
{
    auto not_found = end;

    if (begin != end)
    {
        --end;

        // TODO: replace '<=' with '!=' or else to be more useful,
        // (e.g., allow input iterator can be passed)
        while (begin <= end)
        {
            // Now we will enquire the position keeping in mind the uniform distribution in mind
            auto pos = begin;
            if (*end - *begin)
            {
                auto len = (ptrdiff_t)std::distance(begin, end) * (find - *begin) / (*end - *begin);
                std::advance(pos, len);
            }

            if (pos < begin || pos > end)
                break;
            else if (compare(*pos, find))
                begin = ++pos;
            else if (compare(find, *pos))
                end = --pos;
            else
                return pos;
        }
    }

    return not_found;
}

// [begin, end)
template<typename _Random_Access_Iter,
         typename _Type = typename std::iterator_traits<_Random_Access_Iter>::value_type>
_Random_Access_Iter
interpolation_search(_Random_Access_Iter begin, _Random_Access_Iter end, _Type const &find)
{
    return interpolation_search(begin, end, find, std::less<_Type>());
}
