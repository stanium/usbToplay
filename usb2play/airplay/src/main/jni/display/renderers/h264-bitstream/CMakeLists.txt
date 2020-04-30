aux_source_directory(. h264_bitstream_src)
set(DIR_SRCS ${h264_bitstream_src})
set(LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../../lib64s)
add_library(h264-bitstream
        STATIC
        ${DIR_SRCS})

