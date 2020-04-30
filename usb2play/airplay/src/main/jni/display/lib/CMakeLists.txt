cmake_minimum_required(VERSION 3.4.1)
#include_directories( curve25519 ed25519 playfair plist/plist )
include_directories( curve25519 ed25519 playfair)
include_directories(../include)
include_directories(../libplist/include )
include_directories(.)
link_directories(../../lib64s)
#aux_source_directory(. play_src)
SET(play_src
        byteutils.c
        crypto.c
        dnssd.c
        fairplay_playfair.c
        http_parser.c
        http_request.c
        http_response.c
        httpd.c
        logger.c
        mirror_buffer.c
        netutils.c
        pairing.c
        raop.c
        raop_buffer.c
        raop_ntp.c
        raop_rtp.c
        raop_rtp_mirror.c
        utils.c)

set(AIRPLAY_SRCS ${play_src})

add_library(airplay
        STATIC
        ${AIRPLAY_SRCS}
        )

target_link_libraries( airplay
        curve25519
        ed25519
        playfair
        plist
        crypto
      )

#if( UNIX AND NOT APPLE )
#if(1)
#  find_package(OpenSSL REQUIRED)
#  target_link_libraries( airplay OpenSSL::Crypto )
#  target_link_libraries( airplay dns_sd )
#else()
#  include_directories( /usr/local/opt/openssl@1.1/include/ )
#  target_link_libraries( airplay /usr/local/opt/openssl@1.1/lib/libcrypto.a )
#endif()
        