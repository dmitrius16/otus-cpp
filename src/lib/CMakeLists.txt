add_library(str_utils_lib string_utils.cpp)

set_target_properties(str_utils_lib PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

target_include_directories(str_utils_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

set_project_warnings(str_utils_lib)
