/*
 *
 *      A few functions I wrote and decided to keep.
 * 
 *      binary_search():
 *          > useful for searching through a large vector.
 *          > this code is an implementation of pseudo-code
 *          found here: https://en.wikipedia.org/wiki/Binary_search_algorithm#Procedure
 * 
 * 
 *      lin_growth():
 *          > simple linear growth function
 * 
 *      percent():
 *          > converts a number to a percentage 
 * 
 * 
 */

#ifndef     FUNCTIONS
#define     FUNCTIONS

#include    <algorithm>

/**
 * 
 * @brief   Efficient vector search algorithm.
 *          Useful for finding values in large vectors quickly.
 *          Vector is divided into Left and Right sides, and half the vector is discarded each check until the correct value is found.
 *          This algorithm allows for the value to be quickly found not matter the size of the vector.
 * 
 * @tparam  T
 *          Vector type and target type.
 * 
 * @param   __vec
 *          Vector to search.
 *          Passed by reference into function as the vector must be sorted ascending.
 * 
 * @param   __t
 *          Target value to find.
 * 
 * @return  Either vector index or -1 as int.
 *          A return value of -1 indicates that the target value was not found.
 *          The vector will be modified by the function to be sorted ascending, this is necessary for the correct indexing of the target.
 * 
*/
template <typename T> int binary_search(std::vector<T>& __vec, T __t)
{
    std::sort(__vec.begin(), __vec.end());
    int L = 0; int R = __vec.size() - 1;
    while (L <= R)
    {
        int __M = static_cast<int>((L + R) / 2);
        if      (__vec[__M] < __t)  {L = __M + 1;}
        else if (__vec[__M] > __t)  {R = __M - 1;}
        else                        {return __M;}
    }
    return -1;
}

double  lin_growth(double base, double multiplier)
{
    return base * multiplier;
}

template <typename T>
double percent(T x)
{
    if (typeid(x) == typeid(double)) return x / 100;
    double y = static_cast<double>(x);
    return y / 100;
}

#endif
