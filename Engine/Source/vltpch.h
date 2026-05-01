// vltpch.h: This is a precompiled header file.
// Files listed below are compiled only once, improving build performance for future builds.
// This also affects IntelliSense performance, including code completion and many code browsing features.
// However, files listed here are ALL re-compiled if any one of them is updated between builds.
// Do not add files here that you will be updating frequently as this negates the performance advantage.
#pragma once

#include "Engine/Core/PlatformDetection.h"

#ifdef PLATFORM_WINDOWS
#include <windows.h>
#include <commdlg.h>
#undef APIENTRY
#else
#include <unistd.h>
#endif

// Core
#include <cstdint>
#include <cstddef>

// STL Utilities
#include <memory>
#include <utility>
#include <functional>
#include <optional>
#include <type_traits>

// Containers
#include <string>
#include <array>
#include <vector>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <deque>

// Algorithms
#include <algorithm>
#include <ranges>

// IO / Streams
#include <iostream>
#include <fstream>
#include <sstream>

// Multithreading
#include <thread>
#include <chrono>

// Misc
#include <cassert>
#include <limits>
#include <cstdlib>
#include <cstring>
#include <stdexcept>