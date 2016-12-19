cmake_minimum_required(VERSION 3.0)
project(pencil)

#############################################
# Directory structure macros
#############################################

# Set pencil root dir
set(PENCIL_ROOT_DIR ${PROJECT_SOURCE_DIR})

# Source directory
set(PENCIL_SRC_DIR ${PENCIL_ROOT_DIR}/src)
# Dependencies directory (GLFW, compiled libs etc...)
set(PENCIL_DEP_DIR ${PENCIL_ROOT_DIR}/deps)

# Directories for static libraries
set(PENCIL_LIB_DIR ${PENCIL_DEP_DIR}/lib})
set(PENCIL_INCLUDE_DIR ${PENCIL_DEP_DIR}/include})

#############################################

# Set SRCS macro - place source files you want to compile here (.cpp or .c, not
# h or hpp!)
set(PENCIL_SRCS 
	${PENCIL_SRC_DIR}/main.cpp
	${PENCIL_SRC_DIR}/renderer.cpp
	${PENCIL_SRC_DIR}/state.cpp
	)

# Set to build pencil project
add_executable(pencil ${PENCIL_SRCS})

target_include_directories(pencil PUBLIC ${PENCIL_SRC_DIR})


#############################################
# Dependencies
#############################################

# OpenGL ###########################################
# For GNU Linux, should only need to link to this... windows might be a bit
# different.
target_link_libraries(pencil GL)
####################################################

# GLFW #############################################
# Make sure GLFW doesn't build examples / tests / docs
set (GLFW_BUILD_EXAMPLES OFF)
set (GLFW_BUILD_TESTS OFF)
set (GLFW_BUILD_DOCS OFF)
# Make sure GLFW doesn't build vulkan
set (GLFW_VULKAN_STATIC OFF)
add_subdirectory(${PENCIL_DEP_DIR}/glfw)
target_link_libraries(pencil glfw)
target_include_directories(pencil PUBLIC ${PENCIL_DEP_DIR}/glfw/include)
####################################################

#############################################
# COMPILER FLAGS
#############################################
if ("${CMAKE_C_COMPILER_ID}" STREQUAL "MSVC")
	SET_TARGET_PROPERTIES(pencil
		PROPERTIES COMPILE_FLAGS "/W4 /Wall")
elseif ("${CMAKE_C_COMPILER_ID}" STREQUAL "GNU")
	SET_TARGET_PROPERTIES(pencil
		PROPERTIES COMPILE_FLAGS "-Wall -Wpedantic -g -std=c++11")
endif()
