cmake_minimum_required(VERSION 3.12)

project(task06 VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})

set(CMAKE_PREFIX_PATH_EXT "" CACHE PATH "pathes for find_package")
list(APPEND CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH_EXT})
set(Boost_USE_STATIC_LIBS OFF)
find_package(Boost COMPONENTS unit_test_framework REQUIRED)

configure_file(version.h.in ${PROJECT_SOURCE_DIR}/version.h)

add_executable(matrix "matrix.cpp")

add_executable(test_matrix "test_matrix.cpp")

set_target_properties(
	matrix test_matrix
    PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

set_target_properties(
	test_matrix PROPERTIES
    COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
    INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR}
)

target_link_libraries(
	test_matrix
    ${Boost_LIBRARIES}
)

install(TARGETS matrix RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT cheshirskiy-kot-courses@yandex.com)

set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)

include(CPack)

enable_testing()

add_test(
    NAME matrix_tests
    COMMAND test_matrix
    WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
)