find_package(Catch2 QUIET)

if (Catch2_FOUND)
    message("Found Catch2 test framework")

    add_executable(tests catch_main.cc operation_test.cc graph_test.cc conflict_graph_test.cc)
    target_link_libraries(tests Catch2::Catch2 serializability-checker-lib)

    message("Added target tests")

    include(CTest)
    include(Catch)
    catch_discover_tests(tests)
else ()
    message("Cannot find Catch2 test framework")
endif ()
