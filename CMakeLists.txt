######################################################################
# configuration ######################################################
######################################################################

cmake_minimum_required(VERSION 3.17)
project(exqudens_cpp_cmake_windows)

if(NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/extension.cmake")
    file(
        DOWNLOAD
            "https://raw.githubusercontent.com/exqudens/exqudens-cmake/6.1.1/src/main/cmake/extension.cmake"
            "${CMAKE_CURRENT_SOURCE_DIR}/extension.cmake"
        EXPECTED_MD5
            "6c01fe309bb9a6d444b89f0160dce46c"
    )
endif()
include(extension.cmake)

set(RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/lib)
set(RESOURCE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/res)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${RUNTIME_OUTPUT_DIRECTORY})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${LIBRARY_OUTPUT_DIRECTORY})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${LIBRARY_OUTPUT_DIRECTORY})
set(CMAKE_CXX_STANDARD 20)
#set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS TRUE)

######################################################################
# copy ###############################################################
######################################################################

get_filename_component(CXX_COMPILER_DIR ${CMAKE_CXX_COMPILER} DIRECTORY)

set_copy_file_command_arguments(CFCA_LIB_STDCPP_6 ${CXX_COMPILER_DIR} ${RUNTIME_OUTPUT_DIRECTORY}
    "libstdc++-6.dll"
)
set_copy_file_command_arguments(CFCA_LIB_GCC_S_SEH_1 ${CXX_COMPILER_DIR} ${RUNTIME_OUTPUT_DIRECTORY}
    "libgcc_s_seh-1.dll"
)
set_copy_file_command_arguments(CFCA_LIB_WINPTHREAD_1 ${CXX_COMPILER_DIR} ${RUNTIME_OUTPUT_DIRECTORY}
    "libwinpthread-1.dll"
)

add_custom_target(copyRuntimeBinaries
    COMMAND ${CMAKE_COMMAND} -E make_directory ${RUNTIME_OUTPUT_DIRECTORY}
    COMMAND ${CMAKE_COMMAND} ${CFCA_LIB_STDCPP_6}
    COMMAND ${CMAKE_COMMAND} ${CFCA_LIB_GCC_S_SEH_1}
    COMMAND ${CMAKE_COMMAND} ${CFCA_LIB_WINPTHREAD_1}
)

######################################################################
# main ###############################################################
######################################################################

add_executable(main_1 src/main/cpp/main_1.cpp)
add_dependencies(main_1 copyRuntimeBinaries)

add_executable(main_2 src/main/cpp/main_2.cpp)
add_dependencies(main_2 copyRuntimeBinaries)

add_executable(main_3 src/main/cpp/main_3.cpp)
add_dependencies(main_3 copyRuntimeBinaries)

add_executable(main_4 src/main/cpp/main_4.cpp)
add_dependencies(main_4 copyRuntimeBinaries)

add_executable(main_5 src/main/cpp/main_5.cpp)
add_dependencies(main_5 copyRuntimeBinaries)

add_executable(main_99 src/main/cpp/main_99.cpp)
add_dependencies(main_99 copyRuntimeBinaries)

enable_testing()

add_test(
    NAME test_main_1
    WORKING_DIRECTORY ${RUNTIME_OUTPUT_DIRECTORY}
    COMMAND main_1 --read-png
)
set_tests_properties(test_main_1 PROPERTIES ENVIRONMENT "PATH=${RUNTIME_OUTPUT_DIRECTORY}")
