cmake_minimum_required(VERSION 3.20)
project(Huffman_Files C)

set(CMAKE_C_STANDARD 11)

add_executable(Huffman_Files main.c tree_queue.c tree_queue.h encode.c encode.h bits.c bits.h decode.c decode.h console_interface.c console_interface.h progress_bar.c progress_bar.h logs.c logs.h)
