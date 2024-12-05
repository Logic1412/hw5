#ifndef _QUICKSORT_H
#define _QUICKSORT_H

#include <vector>
#include <climits>

// So we don't need a separate function we have start and end set to INT_MIN
// for determining we need to start the sorting.
template <class T>
inline void quicksort(std::vector<T> &vin, int start = INT_MIN, int end = INT_MIN)
{
    (void) vin;
    (void) start;
    (void) end;

    if (start == INT_MIN) start = 0;
    if (end == INT_MIN) end = vin.size() - 1;
    if (start >= end) return;

    T Piv = vin[end];
    int i = start;
    for (int j = start; j < end; ++j)
    {
        if (vin[j] <= Piv)
        {
            std::swap(vin[i], vin[j]);
            i++;
        }
    }
    std::swap(vin[i], vin[end]);
    quicksort(vin, start, i - 1);
    quicksort(vin, i + 1, end);
}

#endif
