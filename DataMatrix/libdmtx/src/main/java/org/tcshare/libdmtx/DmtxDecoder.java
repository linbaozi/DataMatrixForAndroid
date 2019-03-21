package org.tcshare.libdmtx;

import android.graphics.Bitmap;

public class DmtxDecoder {

    /**
     * 一次识别一张DataMatrix 图片
     */
    public native String getDMListFromBitmap(Bitmap bitmap, long timeout);
}
