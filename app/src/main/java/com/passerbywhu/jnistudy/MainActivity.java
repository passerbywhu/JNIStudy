package com.passerbywhu.jnistudy;

import android.os.Bundle;
import android.support.annotation.Nullable;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.widget.TextView;

/**
 * Created by passe on 2016/6/11.
 * D:\Android\workspace\JNIStudy\app\src\main\java>javah -encoding utf-8 com.passerbywhu.jnistudy.MainActivity
 */
public class MainActivity extends AppCompatActivity {
    private static final String TAG = "JNIStudy";
    static {
        System.loadLibrary("native");
    }

    public native String getText();

    private native String show();

    private void callback() {
        Log.d(TAG, "call back from native");
        throw new NullPointerException();
    }

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        ((TextView) findViewById(R.id.text)).setText(getText() + "\n" + show());
    }
}
