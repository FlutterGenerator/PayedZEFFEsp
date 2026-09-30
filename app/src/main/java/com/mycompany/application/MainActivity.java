package com.mycompany.application;

import android.annotation.SuppressLint;
import android.content.Context;
import android.graphics.PixelFormat;
import android.opengl.GLSurfaceView;
import android.os.Build;
import android.os.Handler;
import android.os.Looper;
import android.provider.Settings;
import android.util.Log;
import android.view.Gravity;
import android.view.MotionEvent;
import android.view.View;
import android.view.WindowManager;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

public class MainActivity {

    private static final String TAG = "UE4_Overlay";

    public static WindowManager manager;
    public static WindowManager.LayoutParams vParams;
    public static View vTouch;
    public static GLES3JNIView display;
    
    private static Handler handler;
    private static Runnable updateRunnable;
    private static boolean isLibraryLoaded = false;

    // 1. Безопасная подгрузка C++ библиотеки libMP.so
    static {
        try {
            System.loadLibrary("MP");
            isLibraryLoaded = true;
            Log.d(TAG, "libMP.so успешно загружена");
        } catch (UnsatisfiedLinkError e) {
            Log.e(TAG, "Ошибка загрузки libMP.so: " + e.getMessage());
        }
    }

    // 2. Главный метод запуска оверлея
    public static void Start(final Context context) {
        if (context == null) return;

        // Проверка разрешения на оверлей для Android 6.0+
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.M) {
            if (!Settings.canDrawOverlays(context)) {
                Log.e(TAG, "Разрешение SYSTEM_ALERT_WINDOW не предоставлено!");
                return;
            }
        }

        try {
            // Безопасное получение WindowManager без приведения к Activity
            manager = (WindowManager) context.getSystemService(Context.WINDOW_SERVICE);
            if (manager == null) return;

            vParams = getAttributes(false);
            WindowManager.LayoutParams wParams = getAttributes(true);

            display = new GLES3JNIView(context);
            vTouch = new View(context);

            // Добавляем View в оверлей
            manager.addView(vTouch, vParams);
            manager.addView(display, wParams);

            // Обработка касаний
            vTouch.setOnTouchListener(new View.OnTouchListener() {
                @SuppressLint("ClickableViewAccessibility")
                @Override
                public boolean onTouch(View v, MotionEvent event) {
                    int action = event.getAction();
                    if (action == MotionEvent.ACTION_DOWN || 
                        action == MotionEvent.ACTION_MOVE || 
                        action == MotionEvent.ACTION_UP) {

                        if (isLibraryLoaded) {
                            try {
                                GLES3JNIView.MotionEventClick(
                                        action != MotionEvent.ACTION_UP,
                                        event.getRawX(),
                                        event.getRawY()
                                );
                            } catch (Exception ignored) {}
                        }
                    }
                    return false;
                }
            });

            // Поток для динамического изменения размеров поля ввода/касания
            handler = new Handler(Looper.getMainLooper());
            updateRunnable = new Runnable() {
                @Override
                public void run() {
                    try {
                        if (isLibraryLoaded) {
                            String rectStr = GLES3JNIView.getWindowRect();
                            if (rectStr != null && !rectStr.isEmpty()) {
                                String[] rect = rectStr.split("\\|");
                                if (rect.length >= 4) {
                                    vParams.x = Integer.parseInt(rect[0]);
                                    vParams.y = Integer.parseInt(rect[1]);
                                    vParams.width = Integer.parseInt(rect[2]);
                                    vParams.height = Integer.parseInt(rect[3]);

                                    if (vTouch != null && vTouch.getParent() != null) {
                                        manager.updateViewLayout(vTouch, vParams);
                                    }
                                }
                            }
                        }
                    } catch (Exception ignored) {}

                    if (handler != null) {
                        handler.postDelayed(this, 20);
                    }
                }
            };

            handler.postDelayed(updateRunnable, 20);

        } catch (Exception e) {
            Log.e(TAG, "Ошибка при запуске оверлея: " + e.getMessage());
        }
    }

    // 3. Параметры окон WindowManager
    @SuppressLint({"RtlHardcoded", "ObsoleteSdkInt"})
    public static WindowManager.LayoutParams getAttributes(boolean isWindow) {
        int additionalFlags = 0;

        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.LOLLIPOP) {
            additionalFlags |= WindowManager.LayoutParams.FLAG_SPLIT_TOUCH;
            additionalFlags |= WindowManager.LayoutParams.FLAG_ALT_FOCUSABLE_IM;
        }

        int windowType;
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.O) {
            windowType = WindowManager.LayoutParams.TYPE_APPLICATION_OVERLAY;
        } else {
            windowType = WindowManager.LayoutParams.TYPE_PHONE;
        }

        WindowManager.LayoutParams params = new WindowManager.LayoutParams(
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
            params.flags |= WindowManager.LayoutParams.FLAG_NOT_TOUCH_MODAL;
            params.flags |= WindowManager.LayoutParams.FLAG_NOT_TOUCHABLE;
        }

        params.format = PixelFormat.RGBA_8888;

        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.P) {
            params.layoutInDisplayCutoutMode =
                    WindowManager.LayoutParams.LAYOUT_IN_DISPLAY_CUTOUT_MODE_SHORT_EDGES;
        }

        params.gravity = Gravity.LEFT | Gravity.TOP;
        params.x = 0;
        params.y = 0;

        if (isWindow) {
            params.width = WindowManager.LayoutParams.MATCH_PARENT;
            params.height = WindowManager.LayoutParams.MATCH_PARENT;
        } else {
            params.width = 0;
            params.height = 0;
        }

        return params;
    }

    // 4. Вложенный OpenGL-View класс
    public static class GLES3JNIView extends GLSurfaceView implements GLSurfaceView.Renderer {

        public GLES3JNIView(Context context) {
            super(context);
            setEGLConfigChooser(8, 8, 8, 8, 16, 0);
            getHolder().setFormat(PixelFormat.TRANSLUCENT);
            setEGLContextClientVersion(3);
            setRenderer(this);
            setRenderMode(GLSurfaceView.RENDERMODE_CONTINUOUSLY);
        }

        @Override
        public void onSurfaceCreated(GL10 gl, EGLConfig config) {
            if (isLibraryLoaded) {
                try { init(); } catch (Exception ignored) {}
            }
        }

        @Override
        public void onSurfaceChanged(GL10 gl, int width, int height) {
            if (isLibraryLoaded) {
                try { resize(width, height); } catch (Exception ignored) {}
            }
        }

        @Override
        public void onDrawFrame(GL10 gl) {
            if (isLibraryLoaded) {
                try { step(); } catch (Exception ignored) {}
            }
        }

        @Override
        protected void onDetachedFromWindow() {
            if (isLibraryLoaded) {
                try { imgui_Shutdown(); } catch (Exception ignored) {}
            }
            super.onDetachedFromWindow();
        }

        // Native методы C++
        public static native void init();
        public static native void resize(int width, int height);
        public static native void step();
        public static native void imgui_Shutdown();
        public static native void MotionEventClick(boolean down, float PosX, float PosY);
        public static native String getWindowRect();
    }
}
