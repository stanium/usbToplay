//
// Created by Administrator on 2020/3/11.
//
#include <stddef.h>
#include <cstring>
#include <signal.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <fstream>
#include <linux/fb.h>
#include <sys/ioctl.h>
#include <fcntl.h>

//#include "log.h"
#include <android/native_window_jni.h>
#include <android/native_window.h>
#include <android/surface_texture.h>
#include <android/surface_texture_jni.h>
#include <android/surface_control.h>
//#include <gui/Surface.h>

#include "lib/stream.h"
#include "lib/logger.h"
#include "lib/dnssd.h"
#include "lib/dnssd.h"
#include "lib/raop.h"
#include "VsDisplay.h"
#if 0
#include "renderers/video_renderer.h"
#include "renderers/audio_renderer.h"
#define DEFAULT_DEBUG_LOG false
#define DEFAULT_ROTATE 0
static dnssd_t *dnssd = NULL;
static raop_t *raop = NULL;
#define DEFAULT_NAME "VSPlay"
#define DEFAULT_HW_ADDRESS { (char) 0x48, (char) 0x5d, (char) 0x60, (char) 0x7c, (char) 0xee, (char) 0x22 }
bool debug_log = DEFAULT_DEBUG_LOG;

static video_renderer_t *video_renderer = NULL;
static audio_renderer_t *audio_renderer = NULL;

#endif
//SurfaceComposerClient surfaceComposerClient;
#define DEFAULT_NAME "VSPlay"
#define DEFAULT_HW_ADDRESS { (char) 0x48, (char) 0x5d, (char) 0x60, (char) 0x7c, (char) 0xee, (char) 0x22 }
//bool debug_log = DEFAULT_DEBUG_LOG;

/*保存mac地址*/
static int parse_hw_addr(std::string str, std::vector<char> &hw_addr) {
    for (int i = 0; i < str.length(); i += 3) {
        hw_addr.push_back((char) stol(str.substr(i), NULL, 16));
    }
    return 0;
}

/*获取mac地址*/
std::string vs_find_mac() {
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

#if 0
extern "C" void log_callback(void *cls, int level, const char *msg) {
    switch (level) {
        case LOGGER_DEBUG: {
            LOGD("%s", msg);
            break;
        }
        case LOGGER_WARNING: {
            LOGW("%s", msg);
            break;
        }
        case LOGGER_INFO: {
            LOGI("%s", msg);
            break;
        }
        case LOGGER_ERR: {
            LOGE("%s", msg);
            break;
        }
        default:
            break;
    }

}
#endif
// Server callbacks
extern "C" void conn_init(void *cls) {
//     video_renderer_update_background(video_renderer, 1);
}

extern "C" void conn_destroy(void *cls) {
//     video_renderer_update_background(video_renderer, -1);
}



int main()
{
#if 0
    ANativeWindow_Buffer buffer;
   // FILE file=open("/data/test.rgb",);
    //if(file== NULL){
    //    printf("open fail\n");
    }
    ANativeWindow* window = ANativeWindow_fromSurface(env, surface);//surface是传到jni的jobject
    ANativeWindow_setBuffersGeometry(window,640,640,WINDOW_FORMAT_RGBA_8888);
    if (ANativeWindow_lock(window, &buffer, NULL) == 0) {
        //在这里将要显示的内容以对应的format填充到buffer.bits
        ANativeWindow_unlockAndPost(window);
        ANativeWindow_release(window);
    }
#endif
    std::string server_name = DEFAULT_NAME;
    std::vector<char> server_hw_addr = DEFAULT_HW_ADDRESS;
    std::string mac_address = vs_find_mac();
    if (!mac_address.empty()) {
        server_hw_addr.clear();
        parse_hw_addr(mac_address, server_hw_addr);
    }
    VsDisplay *vsDisplay=new VsDisplay();

    vsDisplay->start_server(server_hw_addr,server_name);
    while (1) {
    }

}
