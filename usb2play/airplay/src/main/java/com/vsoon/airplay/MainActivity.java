package com.vsoon.airplay;

import androidx.appcompat.app.AppCompatActivity;

import android.graphics.SurfaceTexture;
import android.os.Bundle;
import android.view.TextureView;


import java.net.HttpURLConnection;

import javax.jmdns.JmDNS;
import javax.jmdns.ServiceInfo;

public class MainActivity extends AppCompatActivity implements TextureView.SurfaceTextureListener {

    HttpURLConnection httpURLConnection;
    void httptest()
    {
        httpURLConnection.setRequestProperty("Server","AirTunes/220.68");
    }
    AirPlayView airPlayView;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

    }

    @Override
    public void onSurfaceTextureAvailable(SurfaceTexture surface, int width, int height) {

    }

    @Override
    public void onSurfaceTextureSizeChanged(SurfaceTexture surface, int width, int height) {

    }

    @Override
    public boolean onSurfaceTextureDestroyed(SurfaceTexture surface) {
        return false;
    }

    @Override
    public void onSurfaceTextureUpdated(SurfaceTexture surface) {

    }
}
