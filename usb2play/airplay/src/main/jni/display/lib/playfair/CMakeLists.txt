
aux_source_directory(. playfair_src)
set(DIR_SRCS ${playfair_src})
include_directories(.)


set(LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../../lib64s)
add_library( playfair
        STATIC
        ${DIR_SRCS})