add_library(Chorizo)
add_library(Chorizo::Chorizo ALIAS Chorizo)

# This file is quite big, so for readability we include instead...
# This uses target_sources(Chorizo) to define its headers & source files
include(CMakeSources.cmake)

target_compile_features(Chorizo PUBLIC cxx_std_17)

if (BUILD_SHARED_LIBS)
    target_compile_definitions(Chorizo PRIVATE CHORIZO_EXPORTS)
else()
    target_compile_definitions(Chorizo PRIVATE CHORIZO_STATI_DEFINE)
endif()

target_compile_definitions(Chorizo
        PUBLIC
        # If the CONFIG is Debug or RelWithDebInfo, define CHORIZO_VERBOSE
        # Works on both single and mutli configuration
        CHORIZO_VERBOSE # $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:CHORIZO_VERBOSE>
        # 32-bit
        $<$<EQUAL:4,${CMAKE_SIZEOF_VOID_P}>:CHORIZO_BUILD_32BIT>
        # 64-bit
        $<$<EQUAL:8,${CMAKE_SIZEOF_VOID_P}>:CHORIZO_BUILD_64BIT>
        # Windows
        $<$<PLATFORM_ID:Windows>:CHORIZO_BUILD_WINDOWS WIN32_LEAN_AND_MEAN NOMINMAX>
        # Linux
        $<$<PLATFORM_ID:Linux>:CHORIZO_BUILD_LINUX>
        # macOS
        $<$<PLATFORM_ID:Darwin>:CHORIZO_BUILD_MACOS>
        # MSVC
        $<$<CXX_COMPILER_ID:MSVC>:CHORIZO_BUILD_MSVC _SCL_SECURE_NO_WARNINGS _CRT_SECURE_NO_WARNINGS _WINSOCK_DEPRECATED_NO_WARNINGS>
        # Clang/AppleClang
        $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>>:CHORIZO_BUILD_CLANG>
        # GNU/GCC
        $<$<CXX_COMPILER_ID:GNU>:CHORIZO_BUILD_GNU __USE_MINGW_ANSI_STDIO=0>
        )
target_compile_options(Chorizo
        PUBLIC
        # Disables symbol warnings.
        $<$<CXX_COMPILER_ID:MSVC>:/wd4251 /wd4592>
        PRIVATE
        # Enables SSE4.1, it is also possible to use SSE2 with -msse2
        $<$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>:-msse4.1>
        # Enabled SSE2 for MSVC for 32-bit.
        $<$<AND:$<CXX_COMPILER_ID:MSVC>,$<EQUAL:4,${CMAKE_SIZEOF_VOID_P}>>:/arch:SSE2>
        )
target_include_directories(Chorizo
        PUBLIC
        # Helps the includes find what they need at build-time
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        # Helps the includes find what they need at runtime
        # Although this also allows people to not prefix "Chorizo" before includes as well
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}>
        )
target_link_libraries(Chorizo
        PUBLIC
        # All IMPORTED targets, which automatically handles includes
        Threads::Threads
        # Unix
        ${CMAKE_DL_LIBS}
        # Windows
        $<$<PLATFORM_ID:Windows>:ws2_32>
        $<$<PLATFORM_ID:Windows>:dbghelp>
        PRIVATE
        # More IMPORTED
        "-L/usr/local/lib"
        # Not IMPORTED targets, requires manual includes handling
        # When built locally from submodules, these are merely the names..
        # of the library targets that exist in-scope, else they're set..
        # from find_package() calls
        )

set_target_properties(Chorizo PROPERTIES
        INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR}
        FOLDER "Chorizo"
        )

# Installs all headers, preserving their file structure
install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/"
        DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}"
        FILES_MATCHING
        PATTERN "*.h"
        )
# If strictly using system libs, we can generate an export & install it
if(_CHORIZO_ALL_SYSTEM_LIBS)
    install(TARGETS Chorizo
            # Auto-generates an export to install
            EXPORT
            ChorizoTargets
            LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
            ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
            )
    # Install the auto-generated export
    install(EXPORT ChorizoTargets
            # Makes the end-user imported library Chorizo::Chorizo instead of just Chorizo
            NAMESPACE Chorizo::
            DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}"
            )
    # Defines write_basic_package_version_file
    include(CMakePackageConfigHelpers)
    # Dynamically writes the path to the resources dir (if installed) into the ChorizoConfig.cmake file
    configure_package_config_file("${CMAKE_CURRENT_SOURCE_DIR}/ChorizoConfig.cmake.in"
            "${PROJECT_BINARY_DIR}/ChorizoConfig.cmake"
            INSTALL_DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}"
            PATH_VARS CMAKE_INSTALL_DATADIR
            NO_CHECK_REQUIRED_COMPONENTS_MACRO
            )
    # Auto-generates a version file based on the current version specified in project()
    write_basic_package_version_file("${PROJECT_BINARY_DIR}/ChorizoConfigVersion.cmake"
            COMPATIBILITY SameMajorVersion
            )
    # Install the auto-generated version file and ChorizoConfig
    install(FILES
            "${PROJECT_BINARY_DIR}/ChorizoConfig.cmake"
            "${PROJECT_BINARY_DIR}/ChorizoConfigVersion.cmake"
            DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}"
            )
else()
    # Install without an export since we're using 1 (or more) non-system libs
    install(TARGETS Chorizo
            LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
            ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
            RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
            )
endif()
