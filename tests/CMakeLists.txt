# Load a 12-TET with messy formatting
add_executable (test-tet-12 tet-12.cpp)
target_link_libraries(test-tet-12 PUBLIC scala-file)
add_test(NAME "TET-12" COMMAND test-tet-12)

# Make sure the description can be blank
add_executable (test-blank-desc blank-desc.cpp)
target_link_libraries(test-blank-desc PUBLIC scala-file)
add_test(NAME "Blank-Description" COMMAND test-blank-desc)

# Load a justly-intoned scale
add_executable (test-just just.cpp)
target_link_libraries(test-just PUBLIC scala-file)
add_test(NAME "Just-Intonation" COMMAND test-just)

# Load a mixed scale
add_executable (test-mixed mixed.cpp)
target_link_libraries(test-mixed PUBLIC scala-file)
add_test(NAME "Mixed-Scale" COMMAND test-mixed)

# Check that bare numbers are interpreted as ratios.
add_executable (test-implicit implicit.cpp)
target_link_libraries(test-implicit PUBLIC scala-file)
add_test(NAME "Implicit-Denominators" COMMAND test-implicit)

# Check meantone scale on the Scala site
add_executable (test-meanquar meanquar.cpp)
target_link_libraries(test-meanquar PUBLIC scala-file)
add_test(NAME "Quarter-meantone" COMMAND test-meanquar)

# A random collection of valid intervals from the scala site
add_executable (test-valid valid.cpp)
target_link_libraries(test-valid PUBLIC scala-file)
add_test(NAME "Random-valid-intervals" COMMAND test-valid)

# Test the KBM mapping parser
add_executable (test-kbm kbm.cpp)
target_link_libraries(test-kbm PUBLIC scala-file)
add_test(NAME "Keyboard-mapping" COMMAND test-kbm)

# Ensure the KBM parser honors x's.
add_executable (test-kbm-xs kbm-xs.cpp)
target_link_libraries(test-kbm-xs PUBLIC scala-file)
add_test(NAME "Keyboard-mapping-with-non-entries" COMMAND test-kbm-xs)

# This copies our test data into our build directory, so that our tests 
# have access to it.
file(COPY scales DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY kbm DESTINATION ${CMAKE_CURRENT_BINARY_DIR})