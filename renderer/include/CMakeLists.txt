add_subdirectory(geometry)
add_subdirectory(math)

set(HEADER_FILES
    ${GEOMETRY_HEADER_FILES}
    ${MATH_HEADER_FILES}
    "${CMAKE_CURRENT_SOURCE_DIR}/const.h"
    PARENT_SCOPE
)
