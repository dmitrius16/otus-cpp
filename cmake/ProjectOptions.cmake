include(cmake/StandardProjectSettings.cmake)

option(ENABLE_TESTING "Enable Test Builds" ON)
option(ENABLE_WARNINGS_SETTINGS "Allow target set standard" ON)

if(ENABLE_WARNINGS_SETTINGS)
  include(cmake/CompilerWarnings.cmake)
endif()

if(ENABLE_TESTING)
  enable_testing()
endif()