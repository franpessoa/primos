cmake_minimum_required(VERSION 3.28)
project(gen_primos)
set(PROJECT_VERSION 0.1)

find_package(fmt)

set(SOURCE_DIR)

set(CXX_STANDARD 23)
add_subdirectory(src)