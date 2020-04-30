package com.vsoon.ui;

import android.graphics.SurfaceTexture;
import android.view.Surface;
import android.view.SurfaceHolder;

public class VsoonPlay   {
    static private  boolean isLoaded;
    static {
        if (!isLoaded) {
            System.loadLibrary("jpeg-turbo1500");
            isLoaded = true;
        }
    }

    /**
     * set preview surface with SurfaceHolder</br>
     * you can use SurfaceHolder came from SurfaceView/GLSurfaceView
     * @param holder
     */
    public synchronized void setVideoDisplay(final SurfaceHolder holder) {
       // nativeSetDisplay(mNativePtr, holder.getSurface());
    }

    /**
     * set preview surface with SurfaceTexture.
     * this method require API >= 14
     * @param texture
     */
    public synchronized void setVideoTexture(final SurfaceTexture texture) {	// API >= 11
        final Surface surface = new Surface(texture);	// XXX API >= 14
       // nativeSetDisplay(mNativePtr, surface);
    }

    /**
     * set preview surface with Surface
     * @param surface
     */
    public synchronized void setVideoDisplay(final Surface surface) {
        //nativeSetDisplay(mNativePtr, surface);
    }
}
