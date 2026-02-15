cmake_minimum_required(VERSION 3.16)

project(ip_filter VERSION 0.0.1)

include(cmake/ProjectOptions.cmake)

add_subdirectory(src/lib)
add_subdirectory(src/ip_filter)

if(ENABLE_TESTING)
  add_subdirectory(test)
endif()

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT example@example.com)
include(CPack)