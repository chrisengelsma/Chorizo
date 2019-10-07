#pragma once

#include <algorithm>
#include <array>
#include <cassert>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <fstream>
#include <functional>
#include <future>
#include <iostream>
#include <iomanip>
#include <iterator>
#include <limits>
#include <map>
#include <memory>
#include <numeric>
#include <optional>
#include <ostream>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <string_view>
#include <thread>
#include <type_traits>
#include <unordered_map>
#include <utility>
#include <vector>

using namespace std::chrono_literals;

#if defined(CHORIZO_STATIC_DEFINE)
#  define CHORIZO_EXPORT
#  define CHORIZO_NO_EXPORT
#else
#  if defined(CHORIZO_BUILD_MSVC)
#    if defined(CHORIZO_EXPORTS)
#      define CHORIZO_EXPORT __declspec(dllexport)
#    else
#      define CHORIZO_EXPORT __declspec(dllimport)
#    endif
#    define CHORIZO_NO_EXPORT
#  else
#    define CHORIZO_EXPORT __attribute__((visibility("default")))
#    define CHORIZO_NO_EXPORT __attribute__((visibility("hidden")))
#  endif
#endif

#if defined(CHORIZO_BUILD_MSVC)
#  define CHORIZO_DEPRECATED __declspec(deprecated)
#  pragma section(".state", read, write)
#  define CHORIZO_STATE __declspec(allocate(".state"))
#else
#  define CHORIZO_DEPRECATED __attribute__ ((__deprecated__))
#  if defined(CHORIZO_BUILD_MACOS)
#    define CHORIZO_STATE __attribute__((used, section("__DATA,__state")))
#  else
#    pragma section(".state", read, write)
#    define CHORIZO_STATE __attribute__((section(".state")))
#  endif
#endif

