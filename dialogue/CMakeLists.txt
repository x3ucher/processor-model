
cmake_minimum_required(VERSION 3.16)
project(dialogue)

set(CMAKE_CXX_STANDARD 20)

option(THREADS "Enable threads" ON)

add_executable(dialogue dialogue.cpp)

if (THREADS)
    target_sources(dialogue PRIVATE ../asm/source/cleaner_thread.cpp)
else()
    target_sources(dialogue PRIVATE ../asm/source/cleaner_base.cpp)
endif()

target_link_libraries(dialogue asm cpu instr utils)

# cmake -DTHREADS=OFF ..
# cmake -DTHREADS=ON ..

# /home/urtoach/Desktop/proc_model/tests/testdata/valid_file.txt