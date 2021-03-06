cmake_minimum_required(VERSION 3.0)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

project(coer)
set(project_name coer)

set(coer_VERSION_MAJOR 0)
set(coer_VERSION_MINOR 0)
set(coer_VERSION_PATCH 1)

option(BuildCoerDocumentation "BuildDocumentation" OFF)
option(BuildCoerTest "BuildTest" ON)
option(BuildCoerLibrary "Build the coer library for embedding or linking" ON)

if(CMAKE_BUILD_TYPE)
  if (${CMAKE_BUILD_TYPE} STREQUAL "release")
    set(BuildDocumentation ON)
  else()
    set(CMAKE_BUILD_TYPE "debug")
  endif()
else()
  set(CMAKE_BUILD_TYPE "debug")
endif()

if(${BuildCoerTest})
  add_subdirectory("test")
endif()

if(${have_r4_environment})
  message("Building within r4 lib structure.")
else()

 #find_package(Libcoer)
 # if( coer_FOUND)
 #   add_definitions(-Dcoer_ENABLE_coer)
 #endif()

  find_package(LibGLFW )
  include_directories(${LibGLFW_INCLUDE_DIRS})
  set(LIBS ${LIBS} ${LibGLFW_LIBRARIES})

  IF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    SET(OperatingSystem "macos")
    set(contrib_lib_dir ${CMAKE_SOURCE_DIR}/contrib/platform/darwin)
  ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")

  IF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    SET(OperatingSystem "linux")
  ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")

  IF(WIN32)
    SET(OperatingSystem "windows")
  ENDIF()

  macro(use_c99)
    if(CMAKE_VERSION VERSION_LESS "3.1")
      if(CMAKE_C_COMPILER_ID STREQUAL "GNU")
        set(CMAKE_C_FLAGS "-std=gnu99 ${CMAKE_C_FLAGS}")
      endif()
    else()
      set(CMAKE_C_STANDARD 99)
    endif()
  endmacro(use_c99)

  find_package(Doxygen)
  option(
    BUILD_DOCUMENTATION
    "Create and install the HTML based API
	documentation (requires Doxygen)"
    ${DOXYGEN_FOUND})

  if(BUILD_DOCUMENTATION)
    if(${CMAKE_BUILD_TYPE} STREQUAL "release")
      set(build_doc YES)
    endif()
  endif()
endif()

if(${build_doc})
  message("DOCS!?")

  set(doxyfile_in ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile)
  set(doxyfile ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

  configure_file(${doxyfile_in} ${doxyfile} @ONLY)

  message("Doxygen build started.")
  add_custom_target(doc ALL
                    COMMAND ${DOXYGEN_EXECUTABLE} ${doxyfile_in}
                    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                    COMMENT "Generating API documentation with Doxygen"
                            VERBATIM)

endif()

macro(build_plugin)

  file(GLOB_RECURSE sources ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c)

  IF(${OperatingSystem} MATCHES "macos") # Mac OS X specific code
    SET(lib_extension dylib)
  endif()

  IF(${OperatingSystem} MATCHES "linux") # Linux specific code
    SET(lib_extension so)

  endif()

  IF({OperatingSystem} MATCHES "windows")
    SET(lib_extension dll)
  ENDIF()
 link_directories(${CMAKE_BINARY_DIR}
                   ${CMAKE_SOURCE_DIR}/../coer/build)

  add_library(${project_name} SHARED ${sources})

  target_include_directories(
    ${project_name} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/../../../../contrib/include
  	${CMAKE_CURRENT_SOURCE_DIR}/../../../../contrib
 	  ${CMAKE_CURRENT_SOURCE_DIR}/../../../../..
 	  ${CMAKE_CURRENT_SOURCE_DIR}/../../../../../..
    ${CMAKE_SOURCE_DIR}/..
    ${CMAKE_SOURCE_DIR}/libs
 	)

  message(${CMAKE_CURRENT_SOURCE_DIR})

  target_link_libraries(${project_name} m coer)

  if(${OperatingSystem} MATCHES "macos")
    set(plugin_path $ENV{HOME}/Library/Application\ Support)
  endif()

  if(${OperatingSystem} MATCHES "linux")
    set(plugin_path $ENV{HOME}/.config/space.ruminant)
  endif()

  if(InstallPlugins)
    execute_process(COMMAND ${CMAKE_COMMAND} -E make_directory ${plugin_path})

    set(lib_name "lib${project_name}.${lib_extension}")
    set(plugin_name ${project_name}.plugin)
    set(plugin_dir ${plugin_path}/wash/plugins/${plugin_name})
    set(lib_dest ${plugin_dir}/lib${project_name}.${lib_extension})

    #file(MAKE_DIRECTORY ${plugin_dir})
    set(full_plugin_install_path )
    add_custom_command(
      TARGET ${project_name} POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy
              ${CMAKE_CURRENT_BINARY_DIR}/lib${project_name}.${lib_extension}
              ${lib_dest})

    message("Installing plugin to ${lib_dest}")
  else()
    message("Not installing plugin.")
  endif()
endmacro()


if(BuildLibrary)
  file(GLOB sources coer.c src/*.c src/geo/*.c src/util/*.c)

  add_library(coer STATIC ${sources})

  target_include_directories(coer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/..)
  target_include_directories(coer PUBLIC
                             ${CMAKE_CURRENT_SOURCE_DIR}/../../contrib/include)
  target_include_directories(coer PUBLIC
                             ${CMAKE_CURRENT_SOURCE_DIR}/../../contrib)
  target_include_directories(coer PUBLIC
                             ${CMAKE_CURRENT_SOURCE_DIR}/../../contrib/deps)


endif()
