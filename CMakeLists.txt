cmake_minimum_required(VERSION 3.22)
message("starting cmake compiling apples")
#set(CMAKE_CXX_STANDARD C17)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20")
# создаём новый проект
project(rpggame)
#add_subdirectory (src)
set("${PROJECT}_BINARY_DIR" bin)
#set ("${PROJECT}_SOURCE_DIR" src:include)
set("${PROJECT}_LIB_DIR" lib)
set(CMAKE_INCLUDE_PATH ${${PROJECT}_SOURCE_DIR})
#set (CMAKE_LIBRARY_PATH ${${PROJECT}_LIB_DIR})
#set (EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/${${PROJECT}_BINARY_DIR})
set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_BUILD_TYPE Debug)
set(ERR_NO_UNIX "Cannot build on non Unix systems")
if (WITH_DEBUG_MODE)
    ADD_DEFINITIONS(-DMY_DEBUG_MODE=1)
endif ()
if (CMAKE_COMPILER_IS_GNUCXX)
    set(MY_CXX_FLAGS "-Wall -std=c++20 -fmessage-length=0 -v -L/usr/local/lib -L/usr/lib -lsfml-graphics -lsfml-window -lsfml-network -lsfml-audio -lsfml-system")
    set(CMAKE_CXX_FLAGS "-O0 ${MY_CXX_FLAGS}")
    # я отключил настройку разных флагов для релиза и отладки. Пока что не нужно.
    #set(CMAKE_CXX_FLAGS_DEBUG "-g -O0 -fno-reorder-blocks -fno-schedule-insns -fno-inline")
    #set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")
else ()
    message(FATAL_ERROR ${ERR_NO_UNIX})
endif ()

find_package(SFML COMPONENTS graphics window system)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_executable(rpggame
        Define.h
        Resources/Audio.h
        Resources/Font.h
        Resources/Texture.h
        Game/Game.h
        Game/Game.cpp
        Base.cpp
        Base.h)


find_package(SFML 2.6 COMPONENTS graphics audio network REQUIRED)

# в текущем проекте ничего не нужно дополнительно компилировать
#set (LIBRARIES)
# следующий код нужен для компиляции и подключения сторонних библиотек 
#    foreach (LIBRARY ${LIBRARIES})
#        find_library("${LIBRARY}_FOUND" ${LIBRARY})
#        message(STATUS "Check the ${LIBRARY} is installed: " ${${LIBRARY}_FOUND})
#        if ( "${${LIBRARY}_FOUND}" STREQUAL "${LIBRARY}_FOUND-NOTFOUND" )
#            message(STATUS "Adding library sources")
#            add_subdirectory (../${LIBRARY} lib/${LIBRARY})
#        endif ()
#    endforeach ()

# никаких дополнительных целей нет
#set (TARGETS "")
#CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/src/ ${CMAKE_CURRENT_BINARY_DIR}/bin/)
#find_package(OpenGL)
#find_package(GLEW)
#find_package(glfw3 3.3 REQUIRED)
#option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

#include(FetchContent)
#FetchContent_Declare(SFML
#    GIT_REPOSITORY https://github.com/SFML/SFML.git
#    GIT_TAG 2.6.x)
#FetchContent_MakeAvailable(SFML)
#add_executable(CMakeSFMLProject src/main.cpp)
#add_executable(${PROJECT_NAME} main.cpp Apple.cpp Apple.h config.h Constants.h Game.cpp Game.h Math.h Math.cpp Player.cpp Player.h Rock.cpp Rock.h)
#target_link_libraries(CMakeSFMLProject PRIVATE sfml-graphics)

#target_link_libraries (${PROJECT_NAME} PUBLIC sfml-system sfml-graphics sfml-audio sfml-network)
#target_link_libraries(${PROJECT_NAME} OpenGL::OpenGL GLEW::GLEW glfw sfml-graphics sfml-window sfml-system)
#target_compile_features(CMakeSFMLProject PRIVATE cxx_std_20)


