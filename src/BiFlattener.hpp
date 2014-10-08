#ifndef BIFLATTENER_HPP
#define BIFLATTENER_HPP

#include <tuple>
#include <boost/type_traits/integral_promotion.hpp>


/** A bidirectional map (bijection) between
 * pairs of integers and a single (usually bigger) integer:
 *   (Int, Int) <--> Int
 * Uses a stride parameter to densely and efficiently pack all
 * possible (1..M, 1..N) pairs into exactly M times N consecutive integers.
 **/
template <typename T>
struct BiFlattener
{
    typedef T narrow_type;
    typedef typename boost::integral_promotion<T>::type wider_type;

    wider_type flatten(narrow_type i, narrow_type j) { return i + j * stride; }

    std::tuple<narrow_type, narrow_type>
        unflatten(wider_type k) { return std::make_tuple(k % stride, k / stride); }

    const narrow_type stride;
    BiFlattener(narrow_type d) : stride(d) {}
};

#endif // BIFLATTENER_HPP
