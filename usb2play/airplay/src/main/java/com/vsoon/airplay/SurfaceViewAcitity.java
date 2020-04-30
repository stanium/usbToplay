package com.vsoon.airplay;

import androidx.appcompat.app.AppCompatActivity;

import android.graphics.Canvas;
import android.graphics.Region;
import android.media.MediaPlayer;
import android.os.Bundle;
import android.view.SurfaceControl;
import android.view.SurfaceHolder;
import android.view.SurfaceView;
import android.widget.VideoView;

import java.io.BufferedInputStream;
import java.io.FileOutputStream;
import java.io.InputStream;
import java.net.HttpURLConnection;
import java.net.MalformedURLException;
import java.net.URL;

public class SurfaceViewAcitity extends AppCompatActivity implements MediaPlayer.OnBufferingUpdateListener,
        SurfaceHolder.Callback {
    MediaPlayer mediaPlayer;
    SurfaceView surfaceView;
    HttpURLConnection httpURLConnection;
    VideoView videoView;

    void init_play(){

    }

/*
    void http_test(){
        String testUrl="";

        try {

            URL url = new URL(testUrl);
            try {
                HttpURLConnection httpURLConnection = (HttpURLConnection) url.openConnection();
                httpURLConnection.setRequestMethod("GET");
                httpURLConnection.setConnectTimeout(1000*5);
                httpURLConnection.setReadTimeout(1000*5);
                httpURLConnection.setDoInput(true);
                httpURLConnection.connect();

                httpURLConnection.setRequestProperty();

                //代表请求成功
                if (httpURLConnection.getResponseCode() == 200) {
                    InputStream in = httpURLConnection.getInputStream();
                    bufferedInputStream = new BufferedInputStream(in);//文件输入流
                    outputStream = new FileOutputStream(savePath);
                    byte[] buffer = new byte[1024];
                    int length = 0;
                    while ((length = bufferedInputStream.read(buffer)) != -1) {
                        outputStream.write(buffer, 0, length);//写入文件
                    }
                    outputStream.flush();//强制把数据写入磁盘
                    final Bitmap bitmap = BitmapFactory.decodeFile(savePath);
                    runOnUiThread(new Runnable() {
                        @Override
                        public void run() {
                            imageView.setImageBitmap(bitmap);
                        }
                    });
                }

            } catch (IOException e) {
                e.printStackTrace();
            }
        catch (MalformedURLException e){

        }

    }

*/

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_surface_view_acitity);
        surfaceView=findViewById(R.id.surfaceView1);
    }


    @Override
    public void surfaceCreated(SurfaceHolder holder) {

    }

    @Override
    public void surfaceChanged(SurfaceHolder holder, int format, int width, int height) {

    }

    @Override
    public void surfaceDestroyed(SurfaceHolder holder) {

    }

    @Override
    public void onBufferingUpdate(MediaPlayer mp, int percent) {

    }
}
