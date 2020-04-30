package com.vsoon.airplay;

import android.media.MediaCodec;
import android.widget.VideoView;

public class AirPlayView  {
    MediaCodec mediaCodec;
    static {
        System.loadLibrary("myairplay");
    }
}
