# CMake version
cmake_minimum_required(VERSION 3.14 FATAL_ERROR)
project(Chorizo VERSION 0.0.1 LANGUAGES C CXX)

option(BUILD_SHARED_LIBS "Build Shared Libraries" ON)
option(BUILD_TESTS "Build Tests" ON)
option(CODE_COVERAGE "Code Coverage" OFF)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Sets the install directories defined by GNU
include(GNUInstallDirs)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR})

# Add property to allow making project folders in IDEs
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Position-independent code
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# To build shared libraries in Windows, we set CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS to ON
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

# Under some compilers CMAKE_DEBUG_POSTFIX is set to "d", removed to clean dll names
set(CMAKE_DEBUG_POSTFIX "" CACHE STRING "Set Debug library postfix")
set(CMAKE_RELEASE_POSTFIX "" CACHE STRING "Set Release library postfix")
set(CMAKE_RELWITHDEBINFO_POSTFIX "" CACHE STRING "Set RelWithDebInfo library postfix")
# Removes any dll prefix name on windows, unix will keep a prefix set as "lib"
if (WIN32)
    set(CMAKE_SHARED_LIBRARY_PREFIX "")
endif ()

# Add module path
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/CMake")

if (CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_C_FLAGS_DEBUG "-g -ggdb -pg -O0 -fsanitize=undefined ${CMAKE_C_FLAGS_DEBUG}")
    set(CMAKE_C_FLAGS_RELEASE "-O2 ${CMAKE_C_FLAGS_RELEASE}")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -O0 -std=c++17 -fprofile-arcs -ftest-coverage ${CMAKE_CXX_FLAGS_DEBUG}")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -std=c++17 ${CMAKE_CXX_FLAGS_RELEASE} ")
endif ()

if (APPLE)
    set(CMAKE_EXE_LINKER_FLAGS
            "${CMAKE_EXE_LINKER_FLAGS} \
            -L/usr/local/lib \
            -lgtest")
endif ()

set(CMAKE_BUILD_TYPE Debug)

include(FetchContent)

# Find Threads
find_package(Threads REQUIRED)

add_subdirectory(Sources)

if (CHORIZO_INSTALL_RESOURCES)
    # Install resources for end-user usage
    # because many source files use these
    install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/Resources"
            DESTINATION "${CMAKE_INSTALL_DATADIR}/${PROJECT_NAME}")
endif ()

if (CMAKE_BUILD_TYPE MATCHES Debug)
    if (BUILD_TESTS)
        add_subdirectory(Tests)
    endif ()
endif ()