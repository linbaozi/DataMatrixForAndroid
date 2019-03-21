package org.tcshare.cv.datamatrix;

import android.app.Activity;
import android.graphics.BitmapFactory;
import android.os.Bundle;
import android.util.Log;

import org.tcshare.libdmtx.DmtxDecoder;

public class MainActivity extends Activity {

    static {
        System.loadLibrary("libdmtx");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        // Example of a call to a native method
        new Thread(){
            @Override
            public void run() {
                super.run();
                DmtxDecoder decoder = new DmtxDecoder();
                for(int i = 0; i < 50; i++) {
                    // 识别一张dm
                    String result = decoder.getDMListFromBitmap(BitmapFactory.decodeResource(getResources(),R.mipmap.test1), 2000);
                    Log.e("tmp", i+"result:" + result);
                }
            }
        }.start();

    }

}
