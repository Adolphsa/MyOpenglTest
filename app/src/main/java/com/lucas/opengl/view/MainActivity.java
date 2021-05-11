package com.lucas.opengl.view;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.widget.TextView;

import com.lucas.opengl.MyNativeRender;
import com.lucas.opengl.R;

public class MainActivity extends AppCompatActivity {



    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        MyNativeRender myNativeRender = new MyNativeRender();

        // Example of a call to a native method
        TextView tv = findViewById(R.id.sample_text);
        tv.setText(myNativeRender.native_StringFromJNI());
    }


}