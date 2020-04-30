cmake_minimum_required(VERSION 3.10)
add_subdirectory(renderers/h264-bitstream)
add_subdirectory(lib/curve25519)
add_subdirectory(lib/ed25519)
add_subdirectory(lib/playfair)
add_subdirectory(lib)


include_directories(lib)

include_directories(include)
link_directories(../lib64s)
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/output/bin)
#find_library(binder-lib binder)
#find_library(cutils-lib cutils)
#find_library(log-lib log)
#find_library(gui-lib gui)
#find_library(media-lib media)
#find_library(stagefright-lib stagefright)
#find_library(stagefright_foundation-lib stagefright_foundation)
#find_library(ui-lib ui)
#find_library(utils-lib utils)

SET(LIBRARY_OUTPUT_PATH  ${PROJECT_SOURCE_DIR}/../../libs)

add_executable(test1 test.cpp VsDisplay.cpp)

target_link_libraries(test1  airplay dns_sd h264-bitstream android log)
add_library(myairplay com_vsoon_ui_VsoonPlay.cpp)
