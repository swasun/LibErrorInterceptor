## @brief LibErrorInteceptor
## @author Charly Lamothe


# --- PROJECT ---

PROJECT(libei C)
cmake_minimum_required(VERSION 3.8)


# --- GLOBAL OPTIONS ---

set(CMAKE_VERBOSE_MAKEFILE on)

# --- PATH ---

set(${CMAKE_CURRENT_SOURCE_DIR} ..)
set(SRC_PATH "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(EXAMPLES_PATH "${CMAKE_CURRENT_SOURCE_DIR}/examples")

if (CMAKE_BUILD_TYPE STREQUAL "Release")
	set(LIBRARY_OUTPUT_PATH "${CMAKE_CURRENT_SOURCE_DIR}/bin/release")
	set(EXAMPLES_OUTPUT_PATH "${CMAKE_CURRENT_SOURCE_DIR}/bin/release/examples")
elseif (CMAKE_BUILD_TYPE STREQUAL "Debug")
	set(LIBRARY_OUTPUT_PATH "${CMAKE_CURRENT_SOURCE_DIR}/bin/debug")
	set(EXAMPLES_OUTPUT_PATH "${CMAKE_CURRENT_SOURCE_DIR}/bin/debug/examples")
endif ()


# --- COMPILE OPTIONS ---

if(NOT CMAKE_BUILD_TYPE STREQUAL "Debug")     ## (not debug)
   if(CMAKE_COMPILER_IS_GNUCXX)               ## (GNU COMMAND)
      add_compile_options("-O3")              ### No Optimization
      set(CMAKE_EXE_LINKER_FLAGS "-s")        ### Strip binary (only in release mode)
   endif ()
else ()
	add_compile_options("-g")
endif ()

if (UNIX)
	add_compile_options("-std=gnu99" "-pthread" "-ldl")
elseif (WIN32)
        add_compile_options("-std=c99" "-lkernel32" "-lntdll")
        if (CMAKE_BUILD_TYPE STREQUAL "Debug")
            add_compile_options("-static-libgcc" "-ggdb")
        endif ()
else ()
        add_compile_options("-std=c99")
endif ()

add_compile_options("-Wall" "-Werror" "-pedantic" "-fno-builtin")

if (WIN32)
    macro(get_WIN32_WINNT version)
        if (WIN32 AND CMAKE_SYSTEM_VERSION)
            set(ver ${CMAKE_SYSTEM_VERSION})
            string(REPLACE "." "" ver ${ver})
            string(REGEX REPLACE "([0-9])" "0\\1" ver ${ver})

            set(${version} "0x${ver}")
        endif()
    endmacro()

    get_WIN32_WINNT(ver)
    add_definitions(-D_WIN32_WINNT=${ver})
endif ()

# CCache

find_program(CCACHE_FOUND "ccache")
if(CCACHE_FOUND)
        set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE "ccache")
        set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK "ccache")
endif(CCACHE_FOUND)

# --- SEARCH LIB ---

# Search pthread

if (UNIX)
	find_package (Threads)
endif ()


# --- BUILD LIBERRORINTERCEPTOR ---

# Options
set(PROJECT_NAME_STATIC "${PROJECT_NAME}_static")
set(PROJECT_NAME_SHARED "${PROJECT_NAME}_shared")

# Load source files
file(GLOB_RECURSE PROGRAM_TARGET_SRC_FILES "${SRC_PATH}/*.*")

# Build shared library
add_library(${PROJECT_NAME_SHARED} SHARED ${PROGRAM_TARGET_SRC_FILES})
target_include_directories(${PROJECT_NAME_SHARED} PUBLIC "${SRC_PATH}")
set_target_properties(${PROJECT_NAME_SHARED} PROPERTIES OUTPUT_NAME libei)
target_link_libraries(${PROJECT_NAME_SHARED} ${CMAKE_THREAD_LIBS_INIT})

# Build static library
add_library(${PROJECT_NAME_STATIC} STATIC ${PROGRAM_TARGET_SRC_FILES})
target_include_directories(${PROJECT_NAME_STATIC} PUBLIC "${SRC_PATH}")
set_target_properties(${PROJECT_NAME_STATIC} PROPERTIES OUTPUT_NAME libei)
target_link_libraries(${PROJECT_NAME_STATIC} ${CMAKE_THREAD_LIBS_INIT})


# --- INSTALL ---

if (UNIX)
    # Copy includes
    install(DIRECTORY ${CMAKE_SOURCE_DIR}/src/ DESTINATION /usr/include
              FILES_MATCHING PATTERN "*.h")

    # Copy static library
    install (TARGETS ${PROJECT_NAME_STATIC} ARCHIVE DESTINATION "/usr/lib")

    # Copy shared library
    install (TARGETS ${PROJECT_NAME_SHARED} LIBRARY DESTINATION "/usr/lib")
endif ()

# Build examples
file(GLOB files "${EXAMPLES_PATH}/*.c")
foreach (filePath ${files} )
	get_filename_component(executableName ${filePath} NAME_WE)
	message(STATUS "Build Program : ${executableName}")
	add_executable(${executableName} ${filePath})
    target_link_libraries(${executableName} ${PROJECT_NAME_STATIC})
    set_target_properties(${executableName} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${EXAMPLES_OUTPUT_PATH})
endforeach ()
