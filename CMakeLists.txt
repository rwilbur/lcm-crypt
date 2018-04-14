cmake_minimum_required(VERSION 2.8)
project(lcm-crypt)
#SET (BOOST_LIBRARYDIR "/usr/lib/x86_64-linux-gnu/")
SET (BOOST_INCLUDEDIR "/usr/include/boost/")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/lcm-cmake/")
message(STATUS ${CMAKE_MODULE_PATH})
set (Boost_NO_BOOST_CMAKE ON)
FIND_PACKAGE(Boost COMPONENTS program_options REQUIRED)
FIND_PACKAGE(lcm REQUIRED)

if (NOT Boost_FOUND)
  message(FATAL_ERROR "Fatal error: Boost (version >= 1.55) required.")
else()
  message(STATUS "Setting up BOOST")
  message(STATUS " Includes - ${Boost_INCLUDE_DIRS}")
  message(STATUS " Library  - ${Boost_LIBRARY_DIRS}")
  include_directories(${Boost_INCLUDE_DIRS})
  add_executable(${PROJECT_NAME} "main.cpp")

  message(STATUS "LCM ${LCM}")
  message(STATUS ${Boost_LIBRARY_DIRS})

  TARGET_LINK_LIBRARIES( lcm-crypt LINK_PUBLIC ${Boost_LIBRARIES} ${LCM} ${CMAKE_THREAD_LIBS_INIT} -lglib-2.0 -lpthread -lm )
  message(STATUS "Linking done")

endif (NOT Boost_FOUND)


