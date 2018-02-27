cmake_minimum_required(VERSION 2.8)
project(lcm-crypt)
SET (BOOST_LIBRARYDIR "/usr/lib/x86_64-linux-gnu/")
SET (BOOST_INCLUDEDIR "/usr/include/boost/")

set (Boost_NO_BOOST_CMAKE ON)
FIND_PACKAGE(Boost COMPONENTS program_options REQUIRED)

if (NOT Boost_FOUND)
  message(FATAL_ERROR "Fatal error: Boost (version >= 1.55) required.")
else()
  message(STATUS "Setting up BOOST")
  message(STATUS " Includes - ${Boost_INCLUDE_DIRS}")
  message(STATUS " Library  - ${Boost_LIBRARY_DIRS}")
  include_directories(${Boost_INCLUDE_DIRS})
  add_executable(${PROJECT_NAME} "main.cpp")
  link_directories(${Boost_LIBRARY_DIRS})
  set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules/")
  find_package(LCM REQUIRED lcm)
  include_directories(${LCM_INCLUDE_DIRS})
  set(LIBS ${LIBS} ${LCM_LIBRARIES})
  target_link_libraries(lcm-crypt ${LIBS})
  TARGET_LINK_LIBRARIES( lcm-crypt LINK_PUBLIC ${Boost_LIBRARIES} )
endif (NOT Boost_FOUND)



