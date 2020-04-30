aux_source_directory(. curve25519_src)
set(DIR_SRCS ${curve25519_src})

set(LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../../lib64s)

add_library(curve25519
        STATIC
        ${DIR_SRCS})
