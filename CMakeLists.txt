cmake_minimum_required(VERSION 3.29)
project(10_Million_Passwords)

set(CMAKE_CXX_STANDARD 14)

set(SFML_DIR "${CMAKE_SOURCE_DIR}/SFML-2.5.1/lib/cmake/SFML")

find_package(SFML 2.5 REQUIRED graphics window system)

add_executable(10_Million_Passwords
        src/main.cpp
        src/Trie.h
        src/Trie.cpp
        src/Test.h
        src/Test.cpp
        src/GUI.cpp
        src/GUI.h
        src/Hash_Table_LL_Chaining.cpp
        src/Hash_Table_LL_Chaining.h)

target_link_libraries(10_Million_Passwords sfml-graphics sfml-window sfml-system)

include_directories(10_Million_Passwords PRIVATE
        ${CMAKE_SOURCE_DIR}/src
        ${CMAKE_SOURCE_DIR}/SFML-2.5.1/include
)

link_directories("${CMAKE_SOURCE_DIR}/SFML-2.5.1/lib")

add_custom_command(TARGET 10_Million_Passwords POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_SOURCE_DIR}/SFML-2.5.1/bin/sfml-graphics-d-2.dll" $<TARGET_FILE_DIR:10_Million_Passwords>
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_SOURCE_DIR}/SFML-2.5.1/bin/sfml-window-d-2.dll" $<TARGET_FILE_DIR:10_Million_Passwords>
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_SOURCE_DIR}/SFML-2.5.1/bin/sfml-system-d-2.dll" $<TARGET_FILE_DIR:10_Million_Passwords>
)
