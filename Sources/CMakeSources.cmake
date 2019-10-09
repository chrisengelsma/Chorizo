# All of these will be set as PUBLIC sources to Chorizo
set(_temp_chorizo_headers
        Astro/Season.h
        Astro/Meeus.h
        Const/CalendarConstants.h
        Date/Almanac.h
        Date/GregorianCalendar.h
        Utils/Maths.h
        Utils/AlmanacConverter.h
        )

# All of these will be set as PRIVATE sources to Chorizo
set(_temp_chorizo_sources
        Astro/Meeus.cpp
        Const/CalendarConstants.cpp
        Date/Almanac.cpp
        Date/GregorianCalendar.cpp
        Utils/AlmanacConverter.cpp
        )

# Adds the precompiled header
include(PrecompiledHeader)
add_precompiled_header(Chorizo
        StdAfx.h
        SOURCE_CXX
        StdAfx.cpp
        FORCEINCLUDE)

# Directory that Chorizo source resources can be found.
get_filename_component(CURRENT_PARENT_DIR ../Chorizo PATH)
set(CHORIZO_RESOURCES_DIR "${CURRENT_PARENT_DIR}/Resources")

# Adds a CMake generated config file
configure_file(Config.h.in ${CMAKE_CURRENT_SOURCE_DIR}/Config.h)

# Sets all headers as PUBLIC sources for Chorizo
# The BUILD/INSTALL interface generator expressions are for the EXPORT command
# Otherwise it wouldn't know where to look for them
foreach(_chorizo_header IN LISTS _temp_chorizo_headers)
    target_sources(Chorizo PUBLIC
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/${_chorizo_header}>
            $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}/${_chorizo_header}>
            )
endforeach()

# Sets all sources (cpp) as PRIVATE sources for Chorizo
# An INSTALL_INTERFACE isn't needed, as cpp files aren't installed
foreach(_chorizo_source IN LISTS _temp_chorizo_sources)
    target_sources(Chorizo
            PRIVATE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/${_chorizo_source}>
            )
endforeach()

