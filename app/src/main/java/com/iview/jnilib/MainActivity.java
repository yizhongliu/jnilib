package com.iview.jnilib;

import androidx.appcompat.app.AppCompatActivity;

import android.content.ComponentName;
import android.content.Context;
import android.content.Intent;
import android.content.ServiceConnection;
import android.os.Bundle;
import android.os.Handler;
import android.os.IBinder;
import android.util.Log;



public class MainActivity extends AppCompatActivity {

    private static String TAG = "MainActivity";

    private Handler handler;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

//        handler = new Handler();
//        final CommonManager commonManager = CommonManager.getInstance(this);
//        handler.postDelayed(new Runnable() {
//            @Override
//            public void run() {
//                commonManager.controlHorizontalMotor(0,0,0,true);
//            }
//        }, 5000);

//        Intent it = new Intent();
//        //  it.setClassName("com.iview.commonservice", "com.iview.commonservice.CommonService");
//
//        it.setAction("android.intent.action.CommonService");
//        it.setPackage("com.iview.commonservice");
//        bindService(it, sc, Context.BIND_AUTO_CREATE);
//        Log.e(TAG, "bind service");




}

    private ServiceConnection sc = new ServiceConnection() {
        @Override
        public void onServiceConnected(ComponentName componentName, IBinder iBinder) {
            Log.e(TAG, "onServiceConnected");
     //       commonService = ICommonService.Stub.asInterface(iBinder);
        }

        @Override
        public void onServiceDisconnected(ComponentName componentName) {

        }
    };
}
