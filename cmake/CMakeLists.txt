cmake_minimum_required (VERSION 3.8)

project ("sharkcli")

add_executable (sharkc "app.cpp" "sar.cpp" "ps.cpp")
target_link_libraries(sharkc)
