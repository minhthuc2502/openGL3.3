cmake_minimum_required(VERSION 3.10)
project(Bras_robot_AL5D)

#Settings
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
# set(CMAKE_MODULE_PATH /usr/share/cmake-3.10/Modules/)

#Add dynamic library
find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)
pkg_search_module(GLEW REQUIRED glew)
pkg_search_module(GLM REQUIRED glm)

#Setting
include_directories(${CMAKE_SOURCE_DIR}/3Dgraphique/includes
                    ${GLEW_INCLUDE_DIRS}
                    ${GLM_INCLUDE_DIRS})

#file
file(GLOB_RECURSE ENGINE_SOURCES  ${CMAKE_SOURCE_DIR}/3Dgraphique/sources/*.cpp ${CMAKE_SOURCE_DIR}/3Dgraphique/sources/*.c)
file(GLOB_RECURSE ENGINE_HEADERS ${CMAKE_SOURCE_DIR}/3Dgraphique/includes/*.hpp ${CMAKE_SOURCE_DIR}/3Dgraphique/includes/*.h)

add_executable(bras3D ${ENGINE_SOURCES} ${ENGINE_HEADERS})
set_property(TARGET bras3D PROPERTY CXX_STANDARD 11)
target_link_libraries(bras3D 
                        glfw
                        dl
                        pthread
                        GL
                        Xrandr
                        assimp
                        ${GLEW_LIBRARIES}
                        ${GLM_LIBRARIES}
                        )
