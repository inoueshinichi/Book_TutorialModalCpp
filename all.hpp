#ifndef __ALL_HPP__
#define __ALL_HPP__

#include <iostream>
#include <cstddef>
#include <limits>
#include <cfloat>
#include <cstdint>
#include <cstdlib>
#include <new>
#include <typeinfo>
#include <exception>
#include <initializer_list>

#if __has_include(<cstdalign>)
    #include <cstdalign
#endif

#include <stdexcept>
#include <cassert>
#include <cerrno>
#include <system_error>
#include <string>

#if __has_include(<string_view>)
#   include <string_view>
#endif

#include <deque>
#include <forward_list>
#include <list>
#include <vector>
#include <array>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <stack>
#include <iterator>
#include <algorithm>
#include <cfenv>
#include <random>
#include <numeric>

#if __has_include(<numbers>)
#   include <numbers>
#endif

#include <cmath>
#include <iosfwd>
#include <ios>
#include <streambuf>
#include <istream>
#include <ostream>
#include <iomanip>
#include <sstream>
#include <fstream>

#if __has_include(<filesystem>)
#   include <filesystem>
#endif

#if __has_include (<cxxabi.h>)
#   include <cxxabi.h>
#endif

#include <cstdio>
#include <cinttypes>

#include <regex>
#include <atomic>
#include <thread>
#include <mutex>
#include <shared_mutex>
#include <condition_variable>
#include <future>

using namespace std::literals;

#endif