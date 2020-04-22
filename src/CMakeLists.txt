add_executable(serializability-checker main.cc)
add_library(serializability-checker-lib STATIC operation.cc operation.h graph.h conflict_graph.h)
target_link_libraries(serializability-checker serializability-checker-lib)
