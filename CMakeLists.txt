cmake_minimum_required(VERSION 3.21)
project(Huffman_Files C)

set(CMAKE_C_STANDARD 11)

add_executable(Huffman_Files main.c tree_queue.c tree_queue.h encode.c encode.h)
