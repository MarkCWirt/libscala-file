# This creates the scala-scale library. We'll link main to it.

set(BUILD_SHARED_LIBS OFF)

add_library (scala-file scala_file.cpp)

# This is kind of fun: We tell the build system that anything linking
# with this has to include this directory for includes. We don't have 
# to do it for each thing that links to it. That's what the INTERFACE
# keyword means.

target_include_directories(scala-file INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

# Install stuff

install(TARGETS scala-file DESTINATION lib)
install(FILES scala_file.hpp DESTINATION include)
