function(set_project_warnings project_name)
  option(WARNINGS_AS_ERRORS "Treat compiler warnings as errors" TRUE)

  set(MSVC_WARNINGS
      /W4     # Baseline reasonable warnings
      /permissive- # Standards conformance mode for MSVC
  )

  set(CLANG_WARNINGS
      -Wall
      -Wextra # Reasonable and standard
      -Wshadow # Warn if variable declaration shadows one from parent context
      -Wnon-virtual-dtor # Warn if class with virtual functions has non-virtual destructor
      -Wold-style-cast # Warn for C-style casts
      -Wcast-align # Warn for potential performance problem casts
      -Wunused # Warn on anything unused
      -Woverloaded-virtual # Warn if overload (not override) virtual function
      -Wpedantic # Warn if non-standard C++ used
      -Wconversion # Warn on type conversions that may lose data
      -Wsign-conversion # Warn on sign conversions
      -Wnull-dereference # Warn if null dereference detected
      -Wdouble-promotion # Warn if float implicitly promoted to double
      -Wformat=2 # Warn on security issues around format functions
  )

  set(GCC_WARNINGS
      ${CLANG_WARNINGS}
      -Wmisleading-indentation # Warn if indentation implies blocks where none exist
      -Wduplicated-cond # Warn if if/else chain has duplicated conditions
      -Wduplicated-branches # Warn if if/else branches have duplicated code
      -Wlogical-op # Warn about logical ops used where bitwise probably wanted
      -Wuseless-cast # Warn if cast to same type
  )

  if(MSVC)
    set(PROJECT_WARNINGS ${MSVC_WARNINGS})
  elseif(CMAKE_CXX_COMPILER_ID MATCHES ".*Clang")
    set(PROJECT_WARNINGS ${CLANG_WARNINGS})
  elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(PROJECT_WARNINGS ${GCC_WARNINGS})
  else()
    message(AUTHOR_WARNING "No compiler warnings set for '${CMAKE_CXX_COMPILER_ID}' compiler.")
  endif()

  if(WARNINGS_AS_ERRORS)
    list(APPEND PROJECT_WARNINGS -Werror)
  endif()

  target_compile_options(${project_name} INTERFACE ${PROJECT_WARNINGS})
endfunction()