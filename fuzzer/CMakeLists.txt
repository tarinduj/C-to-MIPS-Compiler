set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address,fuzzer -g")

add_executable(c-to-mips-fuzzer
  fuzzer.cpp
)
target_link_libraries(c-to-mips-fuzzer PRIVATE compiler)
