cmake_minimum_required(VERSION 3.13)
set (CMAKE_CXX_STANDARD 11)
project(exiv2json)

## Add Exiv2
find_package(exiv2lib REQUIRED CONFIG NAMES exiv2)
# include_directories(${exiv2lib_INCLUDE_DIRS})
link_libraries(exiv2lib)

## Add boost
set(Boost_USE_STATIC_LIBS ON) 
set(Boost_USE_MULTITHREADED ON)  
set(Boost_USE_STATIC_RUNTIME OFF) 
find_package(Boost 1.74.0) 
include_directories(${Boost_INCLUDE_DIRS})

## Add other dependencies
include_directories(include)

## Add executable

add_executable(exiv2json
    main.cpp)
target_compile_features(exiv2json PUBLIC cxx_std_11)

## Link static with SDKs

target_link_libraries(exiv2json PRIVATE
    ${Boost_LIBRARIES}
)
