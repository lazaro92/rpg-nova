cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

# Set project name and version
project(RpgNova VERSION 0.1 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

## If you want to link SFML statically
# set(SFML_STATIC_LIBRARIES TRUE)

# Enable debug symbols by default
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug 
    CACHE STRING 
      "Choose the type of build (Debug or Release)" FORCE)
endif()

# Export compile commands for completion engines (optional)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Set option to control setting the resource path variable
option(USE_INSTALL_RESOURCE_PATH "Set resource path to install location" OFF)

if(NOT USE_INSTALL_RESOURCE_PATH)
  set(RESOURCE_PATH "${PROJECT_SOURCE_DIR}/content/")
else()
  set(RESOURCE_PATH "${CMAKE_INSTALL_PREFIX}/share/${CMAKE_PROJECT_NAME}/content/")
endif()

# Generate config.h TODO see if it is util
#configure_file(include/config.h.in config.h)

# Find SFML shared libraries
find_package(SFML 2.5 COMPONENTS system window graphics audio REQUIRED)

include(Source/CMakeLists.txt)

# Compile executable
message(${source_files})
add_executable(RpgNova Source/Main.cpp ${source_files})

# Set include directory search paths
target_include_directories(RpgNova 
  PRIVATE
    "${PROJECT_BINARY_DIR}"
    "${CMAKE_CURRENT_SOURCE_DIR}/Include"
  )

# Set executable RPATH
set_target_properties(RpgNova
  PROPERTIES
      INSTALL_RPATH
        "${CMAKE_INSTALL_PREFIX}/lib"
  )

if(MSVC)
  target_compile_options(RpgNova PRIVATE /W4 /WX)
else()
  target_compile_options(RpgNova PRIVATE -Wall -Wextra -pedantic)
endif()

# Link executable to required SFML modules
target_link_libraries(RpgNova sfml-graphics sfml-audio)

# Set executable install location (/usr/local/bin)
install(TARGETS RpgNova DESTINATION bin)

# Set install location for resources
install(DIRECTORY Media
  DESTINATION "${CMAKE_INSTALL_PREFIX}/share/${CMAKE_PROJECT_NAME}"
)
