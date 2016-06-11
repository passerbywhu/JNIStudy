package com.passerbywhu.jnistudy;

import android.os.Bundle;
import android.support.annotation.Nullable;
import android.support.v7.app.AppCompatActivity;
import android.widget.TextView;

/**
 * Created by passe on 2016/6/11.
 */
public class MainActivity extends AppCompatActivity {
    static {
        System.loadLibrary("native");
    }

    public native String getText();

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        ((TextView) findViewById(R.id.text)).setText(getText());
    }
}
