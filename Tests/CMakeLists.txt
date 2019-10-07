include(FetchContent)

FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.8.1
)

FetchContent_GetProperties(googletest)

if(NOT googletest_POPULATED)
    FetchContent_Populate(googletest)
    add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR})
    set_target_properties(gmock PROPERTIES FOLDER googletest)
    set_target_properties(gmock_main PROPERTIES FOLDER googletest)
    set_target_properties(gtest PROPERTIES FOLDER googletest)
    set_target_properties(gtest_main PROPERTIES FOLDER googletest)
endif()

file(GLOB_RECURSE TEST_HEADER_FILES
        "*.h"
        )

file(GLOB_RECURSE TEST_SOURCE_FILES
        "*.cpp"
        "*.rc"
        )

set(TEST_SOURCES
        ${TEST_HEADER_FILES}
        ${TEST_SOURCE_FILES}
        )

add_executable(UnitTests ${TEST_SOURCES})

target_compile_features(UnitTests
        PUBLIC cxx_std_17
        )

target_include_directories(UnitTests
        PRIVATE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        )

target_link_libraries(UnitTests PRIVATE Chorizo::Chorizo gtest_main)

set_target_properties(UnitTests PROPERTIES FOLDER "Chorizo")

if(UNIX AND APPLE)
    set_target_properties(UnitTests PROPERTIES
            MACOSX_BUNDLE_BUNDLE_NAME "Unit Tests"
            MACOSX_BUNDLE_SHORT_VERSION_STRING ${CHORIZO_VERSION}
            MACOSX_BUNDLE_LONG_VERSION_STRING ${CHORIZO_VERSION}
            MACOSX_BUNDLE_INFO_PLIST "../CMake/MacOSXBundleInfo.plist.in"
            )
endif()

add_test(NAME "Utils" COMMAND "UnitTests")

if(CHORIZO_INSTALL_EXAMPLES)
    install(TARGETS UnitTests
            RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
            ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
            )
endif()