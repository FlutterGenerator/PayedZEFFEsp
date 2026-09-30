package com.mycompany.application;

import android.annotation.SuppressLint;
import android.app.Activity;
import android.content.Context;
import android.graphics.PixelFormat;
import android.os.Build;
import android.os.Bundle;
import android.os.Handler;
import android.os.Looper;
import android.provider.Settings;
import android.view.Gravity;
import android.view.MotionEvent;
import android.view.View;
import android.view.WindowManager;

public class MainActivity extends Activity {

    public static WindowManager manager;
    public static WindowManager.LayoutParams vParams;

    @SuppressLint("StaticFieldLeak")
    public static View vTouch;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.M) {
            // Запускаем overlay только если разрешение уже выдано
            if (Settings.canDrawOverlays(this)) {
                Start(this);
            }
        } else {
            Start(this);
        }
    }

    public static void Start(Context context) {
        try {
            // Загружаем native-библиотеку
            System.loadLibrary("MP");

            Activity activity = (Activity) context;
            manager = activity.getWindowManager();

            vParams = getAttributes(false);
            WindowManager.LayoutParams wParams = getAttributes(true);

            GLES3JNIView display = new GLES3JNIView(context);

            vTouch = new View(context);

            manager.addView(vTouch, vParams);
            manager.addView(display, wParams);

            vTouch.setOnTouchListener(new View.OnTouchListener() {
                @SuppressLint("ClickableViewAccessibility")
                @Override
                public boolean onTouch(View v, MotionEvent event) {

                    int action = event.getAction();

                    switch (action) {
                        case MotionEvent.ACTION_DOWN:
                        case MotionEvent.ACTION_MOVE:
                        case MotionEvent.ACTION_UP:

                            GLES3JNIView.MotionEventClick(
                                    action != MotionEvent.ACTION_UP,
                                    event.getRawX(),
                                    event.getRawY()
                            );
                            break;
                    }

                    return false;
                }
            });

            final Handler handler = new Handler(Looper.getMainLooper());

            handler.postDelayed(new Runnable() {
                @Override
                public void run() {

                    try {
                        String[] rect =
                                GLES3JNIView.getWindowRect().split("\\|");

                        if (rect.length >= 4) {

                            vParams.x = Integer.parseInt(rect[0]);
                            vParams.y = Integer.parseInt(rect[1]);

                            vParams.width =
                                    Integer.parseInt(rect[2]);

                            vParams.height =
                                    Integer.parseInt(rect[3]);

                            if (vTouch != null && vTouch.getParent() != null) {
                                manager.updateViewLayout(
                                        vTouch,
                                        vParams
                                );
                            }
                        }

                    } catch (Exception ignored) {
                    }

                    handler.postDelayed(this, 20);
                }
            }, 20);

        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    @SuppressLint({"RtlHardcoded", "ObsoleteSdkInt"})
    public static WindowManager.LayoutParams getAttributes(boolean isWindow) {

        int additionalFlags = 0;

        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.LOLLIPOP) {
            additionalFlags |=
                    WindowManager.LayoutParams.FLAG_SPLIT_TOUCH;

            additionalFlags |=
                    WindowManager.LayoutParams.FLAG_ALT_FOCUSABLE_IM;
        }

        int windowType;

        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.O) {
            // Android 8.0+
            windowType =
                    WindowManager.LayoutParams.TYPE_APPLICATION_OVERLAY;
        } else if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.M) {
            // Android 6.0 - 7.1
            windowType =
                    WindowManager.LayoutParams.TYPE_PHONE;
        } else {
            windowType =
                    WindowManager.LayoutParams.TYPE_PHONE;
        }

        WindowManager.LayoutParams params =
                new WindowManager.LayoutParams(
                        WindowManager.LayoutParams.MATCH_PARENT,
                        WindowManager.LayoutParams.MATCH_PARENT,

                        windowType,

                        WindowManager.LayoutParams.FLAG_NOT_FOCUSABLE
                                | WindowManager.LayoutParams.FLAG_LAYOUT_IN_OVERSCAN
                                | WindowManager.LayoutParams.FLAG_LAYOUT_IN_SCREEN
                                | WindowManager.LayoutParams.FLAG_SPLIT_TOUCH
                                | additionalFlags,

                        PixelFormat.TRANSLUCENT
                );

        if (isWindow) {
            params.flags |=
                    WindowManager.LayoutParams.FLAG_NOT_TOUCH_MODAL;

            params.flags |=
                    WindowManager.LayoutParams.FLAG_NOT_TOUCHABLE;
        }

        params.format = PixelFormat.RGBA_8888;

        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.P) {
            params.layoutInDisplayCutoutMode =
                    WindowManager.LayoutParams
                            .LAYOUT_IN_DISPLAY_CUTOUT_MODE_SHORT_EDGES;
        }

        params.gravity =
                Gravity.LEFT | Gravity.TOP;

        params.x = 0;
        params.y = 0;

        if (isWindow) {
            params.width =
                    WindowManager.LayoutParams.MATCH_PARENT;

            params.height =
                    WindowManager.LayoutParams.MATCH_PARENT;
        } else {
            // Размер touch-области первоначально 0x0.
            // Далее он обновляется через getWindowRect().
            params.width = 0;
            params.height = 0;
        }

        return params;
    }
}