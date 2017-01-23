# CMakeLists file for all unit tests.

# Add GoogleTest as an external project and build.
include(ExternalProject)
set_directory_properties(PROPERTIES EP_PREFIX ${CMAKE_BINARY_DIR}/ThirdParty)
ExternalProject_Add(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG master
    # Force separate output paths for debug and release builds to allow easy
    # identification of correct lib in subsequent TARGET_LINK_LIBRARIES commands
    CMAKE_ARGS -DCMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG:PATH=DebugLibs
               -DCMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE:PATH=ReleaseLibs
               -Dgtest_force_shared_crt=ON
               # For now we only build GoogleTest, add GoogleMock when needed.
               -DBUILD_GTEST=ON
               -DBUILD_GMOCK=OFF
    # Disable install step
    INSTALL_COMMAND ""
    LOG_DOWNLOAD ON
    LOG_CONFIGURE ON
    LOG_BUILD ON)
ExternalProject_Get_Property(googletest SOURCE_DIR)
set(GTEST_INCLUDE_DIR "${SOURCE_DIR}/googletest/include")
ExternalProject_Get_Property(googletest BINARY_DIR)
set(GTEST_BINARY_DIR "${BINARY_DIR}/googletest")

# Set environment specific varaibles.
if(MSVC)
  set(LIB_SUFFIX ".lib")
else()
  set(LIB_SUFFIX ".a")
  set(PTHREAD "-pthread")
endif()

# Add include directories and test source files directories.
include_directories(
    ../include
    ${GTEST_INCLUDE_DIR}
)
add_subdirectory(math)
set(TEST_FILES
    ${MATH_TEST_FILES}
    test_main.cpp
)
set(PROJ_TEST_NAME "${PROJ_NAME}_test")

message("Compiling ${PROJ_TEST_NAME}...")
foreach(file ${TEST_FILES})
    message(STATUS "Test file: ${file}")
endforeach(file ${TEST_FILES})

# Build executables and add dependencies.
add_executable(${PROJ_TEST_NAME} ${CORELIBS} ${TEST_FILES})
add_dependencies(${PROJ_TEST_NAME} googletest)

target_link_libraries(${PROJ_TEST_NAME}
    "${PROJ_NAME}_lib"    
    debug ${GTEST_BINARY_DIR}/DebugLibs/${CMAKE_FIND_LIBRARY_PREFIXES}gtest${LIB_SUFFIX}
    optimized ${GTEST_BINARY_DIR}/ReleaseLibs/${CMAKE_FIND_LIBRARY_PREFIXES}gtest${LIB_SUFFIX}
    ${PTHREAD}
)
