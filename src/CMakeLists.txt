add_library(
    primos
    lib/primos.cc
    lib/benchmark.cc
)

target_link_libraries(primos)
target_include_directories(primos PRIVATE ${CMAKE_SOURCE_DIR}/include/private/)
target_include_directories(primos PUBLIC ${CMAKE_SOURCE_DIR}/include/public/)
set_target_properties(primos PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(primos PROPERTIES PUBLIC_HEADER  ${CMAKE_SOURCE_DIR}/include/public/primos.h)


add_executable(
    primos_cli
    cli/main.cc
)

target_link_libraries(primos_cli primos)

find_package(fmt)
target_link_libraries(primos_cli fmt::fmt)
target_include_directories(primos_cli PRIVATE ../include/public/)
target_include_directories(primos_cli PRIVATE ../include/private/)
