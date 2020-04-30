//
// Created by Administrator on 2020/4/23.
//

#ifndef VSUSBMUX3_VSDISPLAY_H
#define VSUSBMUX3_VSDISPLAY_H
#include <android/native_window_jni.h>
#include <android/native_window.h>
#include "lib/raop.h"
#include <string>
#include <assert.h>
#include <cstring>
#include <vector>
#include <jni.h>
#include "objectarray.h"

typedef struct Vframe{

}vframe;
class VsDisplay {
public:
    VsDisplay();
    ~VsDisplay();
    raop_callbacks_t *raop_cbs;
    unsigned short port;
    ANativeWindow *mPreviewWindow;
    dnssd_t *dnssd;
    raop_t *raop;
    ObjectArray<Vframe *> previewFrames;
    pthread_t dis_thread;
    pthread_mutex_t dis_mutex;
    pthread_cond_t dis_sync;
    void setVideoPlay();
    vframe * getframe(); //获取帧

    /*帧缓冲池*/
    void init_pool();
    void free_pool();
    int start_server(std::vector<char> hw_addr,std::string name);
    int stop_server();

private:


};


#endif //VSUSBMUX3_VSDISPLAY_H
