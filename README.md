# DataMatrixForAndroid
在Android上检测DM码，返回识别的内容<br/><br/>

```
使用方法：
        参数1： Bitmap
        参数2： 超时时间
        String result = decoder.getDMListFromBitmap(bitmap, 2000);

示例：
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

注意事项：
   示例中使用了getResources() 来读取mipmap， 这种情况在不同的机型安卓会自动缩放图片， 导致识别失败； 建议通过InputStream的方式来加载Bitmap
   ```
   
