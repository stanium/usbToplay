aux_source_directory(. ed25519_src)
set(DIR_SRCS ${ed25519_src})
set(LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../../lib64s)
add_library( ed25519
        STATIC
        ${DIR_SRCS})