find_package(Boost COMPONENTS unit_test_framework REQUIRED)

add_executable(test_string_utils test_string_utils.cpp)
add_executable(test_ip_storage test_ip_storage.cpp)

set_target_properties(test_string_utils test_ip_storage PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

set_target_properties(test_string_utils test_ip_storage PROPERTIES
    COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
    INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR}
)

target_link_libraries(test_string_utils
    ${Boost_LIBRARIES}
    str_utils_lib
)
target_link_libraries(test_ip_storage
    ${Boost_LIBRARIES}
    ip_storage
)

set_project_warnings(test_string_utils)
set_project_warnings(test_ip_storage)

add_test(test_string_utils test_string_utils)
add_test(test_ip_storage test_ip_storage)
