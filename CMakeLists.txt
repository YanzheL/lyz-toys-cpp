cmake_minimum_required(VERSION 3.5)

project(lyztoys)

set(CMAKE_CXX_STANDARD 14)

set(ALL_LYZ_SUBLIBS "" CACHE STRING "Names of all sub libraries" FORCE)

set(ALL_LYZ_OBJECTS "" CACHE STRING "" FORCE)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

function(add_lyz_test libname)
    if (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/main.cc")
        add_executable(${libname}-test main.cc)
        target_link_libraries(${libname}-test ${libname})
    endif ()
endfunction()

function(define_module module_name)
    set(LIB_NAME lyz-${module_name})
    set(ALL_LYZ_SUBLIBS ${ALL_LYZ_SUBLIBS} ${LIB_NAME} CACHE STRING "" FORCE)
    set(ALL_LYZ_OBJECTS ${ALL_LYZ_OBJECTS} $<TARGET_OBJECTS:${LIB_NAME}_object> CACHE STRING "" FORCE)
    add_library(${LIB_NAME}_object OBJECT ${SRCS})
    add_library(${LIB_NAME} SHARED $<TARGET_OBJECTS:${LIB_NAME}_object>)
    add_library(${LIB_NAME}_static STATIC $<TARGET_OBJECTS:${LIB_NAME}_object>)
    set_target_properties(${LIB_NAME}_static PROPERTIES OUTPUT_NAME ${LIB_NAME})
    add_lyz_test(${LIB_NAME})
endfunction()

macro(print_all_variables)
    message(STATUS "------------------------------------------print_all_variables------------------------------------------")
    get_cmake_property(_variableNames VARIABLES)
    foreach (_variableName ${_variableNames})
        message(STATUS "${_variableName}=${${_variableName}}")
    endforeach ()
    message(STATUS "------------------------------------------print_all_variables------------------------------------------")
endmacro()


add_subdirectory(factory)

add_library(lyztoys SHARED ${ALL_LYZ_OBJECTS})

add_library(lyztoys_static STATIC ${ALL_LYZ_OBJECTS})

set_target_properties(lyztoys_static PROPERTIES OUTPUT_NAME lyztoys)

add_lyz_test(lyztoys)


#print_all_variables()