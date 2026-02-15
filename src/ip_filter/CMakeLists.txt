add_library(ip_storage ip_storage.cpp)

set_target_properties(ip_storage PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

target_include_directories(ip_storage PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(ip_storage PRIVATE str_utils_lib)

set_project_warnings(ip_storage)

add_executable(ip_filter main.cpp)

set_target_properties(ip_filter PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

target_link_libraries(ip_filter PRIVATE
    ip_storage
)

set_project_warnings(ip_filter)
