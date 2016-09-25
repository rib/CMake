function(get_test_prerequirements found_var)
  # for now PGI compiler is not supported as it doesn't set --build-id
  # required by debuginfo rpm packages

  if(NOT CMAKE_CXX_COMPILER_ID STREQUAL "PGI")
    set(${found_var} true PARENT_SCOPE)
  endif()
endfunction()
