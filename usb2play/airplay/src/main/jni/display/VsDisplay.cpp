//
// Created by Administrator on 2020/4/23.
//

#include "VsDisplay.h"
#include "lib/raop.h"
#include <stdio.h>
#include <stdlib.h>
#include <linux/time.h>
#include <unistd.h>
#include <fstream>
#include "string.h"


/*保存mac地址*/
static int parse_hw_addr(std::string str, std::vector<char> &hw_addr) {
    for (int i = 0; i < str.length(); i += 3) {
        hw_addr.push_back((char) stol(str.substr(i), NULL, 16));
    }
    return 0;
}

/*获取mac地址*/
std::string find_mac() {
    std::ifstream iface_stream("/sys/class/net/eth0/address");
    if (!iface_stream) {
        iface_stream.open("/sys/class/net/wlan0/address");
    }
    if (!iface_stream) return "";

    std::string mac_address;
    iface_stream >> mac_address;
    iface_stream.close();
    return mac_address;
}

VsDisplay::VsDisplay() {

}

VsDisplay::~VsDisplay() {

};
#if 0
static void copyFrame(const uint8_t *src, uint8_t *dest, const int width, int height, const int stride_src, const int stride_dest) {
    const int h8 = height % 8;
    for (int i = 0; i < h8; i++) {
        memcpy(dest, src, width);
        dest += stride_dest; src += stride_src;
    }
    for (int i = 0; i < height; i += 8) {
        memcpy(dest, src, width);
        dest += stride_dest; src += stride_src;
        memcpy(dest, src, width);
        dest += stride_dest; src += stride_src;
        memcpy(dest, src, width);
        dest += stride_dest; src += stride_src;
        memcpy(dest, src, width);
        dest += stride_dest; src += stride_src;
        memcpy(dest, src, width);
        dest += stride_dest; src += stride_src;
        memcpy(dest, src, width);
        dest += stride_dest; src += stride_src;
        memcpy(dest, src, width);
        dest += stride_dest; src += stride_src;
        memcpy(dest, src, width);
        dest += stride_dest; src += stride_src;
    }
}


int copyToSurface(vframe *frame, ANativeWindow **window) {
    // ENTER();
    int result = 0;
    if (LIKELY(*window)) {
        ANativeWindow_Buffer buffer;
        if (LIKELY(ANativeWindow_lock(*window, &buffer, NULL) == 0)) {
            // source = frame data
            const uint8_t *src = (uint8_t *)frame->data;
            const int src_w = frame->width * PREVIEW_PIXEL_BYTES;
            const int src_step = frame->width * PREVIEW_PIXEL_BYTES;
            // destination = Surface(ANativeWindow)
            uint8_t *dest = (uint8_t *)buffer.bits;
            const int dest_w = buffer.width * PREVIEW_PIXEL_BYTES;
            const int dest_step = buffer.stride * PREVIEW_PIXEL_BYTES;
            // use lower transfer bytes
            const int w = src_w < dest_w ? src_w : dest_w;
            // use lower height
            const int h = frame->height < buffer.height ? frame->height : buffer.height;
            // transfer from frame data to the Surface
            copyFrame(src, dest, w, h, src_step, dest_step);
            ANativeWindow_unlockAndPost(*window);
        } else {
            result = -1;
        }
    } else {
        result = -1;
    }
    return result; //RETURN(result, int);
}

#endif

void conn_init(void *cls) {
//     video_renderer_update_background(video_renderer, 1);
}

void conn_destroy(void *cls) {
//     video_renderer_update_background(video_renderer, -1);
}

int VsDisplay::start_server(std::vector<char> hw_addr,std::string name) {
    //raop_callbacks_t raop_cbs;

    raop_cbs=(raop_callbacks_t *)calloc(1, sizeof(raop_callbacks_t));
  //  memset(&raop_cbs, 0, sizeof(raop_cbs));


    raop_cbs->conn_init = conn_init;
    raop_cbs->conn_destroy = conn_destroy;

#if 0
    raop_cbs.audio_process = audio_process;
    raop_cbs.video_process = video_process;
    raop_cbs.audio_flush = audio_flush;
    raop_cbs.video_flush = video_flush;
    raop_cbs.audio_set_volume = audio_set_volume;
#else
    raop_cbs->audio_process = NULL;
    raop_cbs->video_process = NULL;
    raop_cbs->audio_flush = NULL;
    raop_cbs->video_flush = NULL;
    raop_cbs->audio_set_volume = NULL;
#endif

    raop = raop_init(10, raop_cbs);
    if (raop == NULL) {
        printf("Error initializing raop!");
        return -1;
    }
#if 0
    raop_set_log_callback(raop, log_callback, NULL);
    raop_set_log_level(raop, debug_log ? RAOP_LOG_DEBUG : LOGGER_INFO);

    logger_t *render_logger = logger_init();
    logger_set_callback(render_logger, log_callback, NULL);
    logger_set_level(render_logger, debug_log ? LOGGER_DEBUG : LOGGER_INFO);
#endif
#if 0
    if (low_latency) logger_log(render_logger, LOGGER_INFO, "Using low-latency mode");

    if ((video_renderer = video_renderer_init(render_logger, background_mode, low_latency, rotation)) == NULL) {
        LOGE("Could not init video renderer");
        return -1;
    }

    if (audio_device == AUDIO_DEVICE_NONE) {
        LOGI("Audio disabled");
    } else if ((audio_renderer = audio_renderer_init(render_logger, video_renderer, audio_device, low_latency)) ==
               NULL) {
        LOGE("Could not init audio renderer");
        return -1;
    }

    if (video_renderer) video_renderer_start(video_renderer);
    if (audio_renderer) audio_renderer_start(audio_renderer);
#endif

    port = 0;
    raop_start(raop, &port);
    raop_set_port(raop, port);

    int error;
    dnssd = dnssd_init(name.c_str(), strlen(name.c_str()), hw_addr.data(), hw_addr.size(), &error);
    if (error) {
        printf("Could not initialize dnssd library!");
        return -2;
    }

    raop_set_dnssd(raop, dnssd);
    // dnssd->DNSServiceRegister注册dns服务器
    dnssd_register_raop(dnssd, port);
    //dnssd->DNSServiceRegister注册dns服务器
    dnssd_register_airplay(dnssd, port + 1);

    return 0;
}

int VsDisplay::stop_server() {
    raop_destroy(raop);
    dnssd_unregister_raop(dnssd);
    dnssd_unregister_airplay(dnssd);
    // If we don't destroy these two in the correct order, we get a deadlock from the ilclient library
    //audio_renderer_destroy(audio_renderer);
    //video_renderer_destroy(video_renderer);
    return 0;
}

//============h264===========

bool checkHead(void *buf ,int offset)
{
    return true;
}

void findHead()
{}
