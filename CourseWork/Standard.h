#pragma once
#include <vector>
template <class T, class F>
decltype(auto) map(const std::vector<T> a, const F fn) {
    std::vector<decltype(fn(a[0]) > result = {});
    std::transform(a.cbegin(), a.cend(), std::back_inserter(result), fn);
    return result;
}