cmake_minimum_required(VERSION 3.15)
project(LRU_cache C)

set(CMAKE_C_STANDARD 11)

add_executable(LRU_cache main.c hash_table.c cache.c input.c LRU_cache.h)
