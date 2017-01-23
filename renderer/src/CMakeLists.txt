include_directories(../include)

add_subdirectory(math)

set(SOURCE_FILES
    ${MATH_SOURCE_FILES}
    main.cpp
)

set(PROJ_LIB_NAME "${PROJ_NAME}_lib")

message("Compiling ${PROJ_LIB_NAME}...")
foreach(file ${SOURCE_FILES})
    message(STATUS "Source file: ${file}")
endforeach(file ${SOURCE_FILES})

add_library(${PROJ_LIB_NAME} ${SOURCE_FILES})
add_executable(${PROJ_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJ_NAME}
    "${PROJ_NAME}_lib"
)
