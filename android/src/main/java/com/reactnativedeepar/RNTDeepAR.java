package com.reactnativedeepar;

import static androidx.core.app.ActivityCompat.requestPermissions;
import static androidx.core.content.ContextCompat.checkSelfPermission;

import android.Manifest;
import android.app.Activity;
import android.content.Context;
import android.content.ContextWrapper;
import android.content.pm.PackageManager;
import android.graphics.Bitmap;
import android.hardware.Camera;
import android.hardware.camera2.CameraManager;
import android.media.Image;
import android.os.Build;
import android.os.Environment;
import android.text.format.DateFormat;
import android.util.AttributeSet;
import android.util.Log;
import android.view.MotionEvent;
import android.view.SurfaceHolder;
import android.view.SurfaceView;
import android.view.View;
import android.widget.FrameLayout;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.lifecycle.LifecycleObserver;

import com.facebook.react.bridge.ReactContext;
import com.facebook.react.bridge.WritableMap;
import com.facebook.react.bridge.WritableNativeMap;
import com.facebook.react.uimanager.events.RCTEventEmitter;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.util.Date;

import ai.deepar.ar.ARErrorType;
import ai.deepar.ar.AREventListener;
import ai.deepar.ar.ARTouchInfo;
import ai.deepar.ar.ARTouchType;
import ai.deepar.ar.DeepAR;

public class RNTDeepAR extends FrameLayout implements AREventListener, SurfaceHolder.Callback, LifecycleObserver {

  private static final String TAG = "RNTDeepAR";
  SurfaceView surface;
  String tempVideoPath;
  private DeepAR deepAr;
  private CameraService cameraService;
  private final int defaultCameraDevice = Camera.CameraInfo.CAMERA_FACING_FRONT;
  private int cameraDevice = defaultCameraDevice;
  private CameraManager mCameraManager;
  private boolean started;

  public RNTDeepAR(Context context, DeepAR _deepAr) {
    super(context);
    deepAr = _deepAr;
    init();
  }

  public RNTDeepAR(@NonNull Context context, @Nullable AttributeSet attrs) {
    super(context, attrs);
        init();
  }

  public RNTDeepAR(Context context, AttributeSet attrs, int defStyle) {
    super(context, attrs, defStyle);
        init();
  }

  public void init() {
    View view = inflate(getContext(), R.layout.deeparview, null);
    addView(view);

    deepAr.initialize(this.getContext(), this);
    setupDeepAR();
  }

  @Override
  protected void onDetachedFromWindow() {
    super.onDetachedFromWindow();
    // deepAr.setAREventListener(null);
    // deepAr.release();
    // deepAr = null;
  }

  private void setupDeepAR() {

    if (started) {
      return;
    }

    started = true;

    surface = findViewById(R.id.surface);
    surface.getHolder().addCallback(this);

    // Surface might already be initialized, so we force the call to onSurfaceChanged
    surface.setVisibility(View.GONE);
    surface.setVisibility(View.VISIBLE);

    mCameraManager = (CameraManager) getContext().getSystemService(Context.CAMERA_SERVICE);
    cameraService = new CameraService(getActivity());
    if (cameraService != null) {
      if ((checkSelfPermission(getContext(), Manifest.permission.CAMERA) != PackageManager.PERMISSION_GRANTED) || (checkSelfPermission(getContext(), Manifest.permission.WRITE_EXTERNAL_STORAGE) != PackageManager.PERMISSION_GRANTED)) {
        Log.d(TAG, "No camera and storage permission");
        requestPermissions(getActivity(), new String[]{Manifest.permission.CAMERA, Manifest.permission.WRITE_EXTERNAL_STORAGE}, 50404);
      }

      cameraService.openCamera(deepAr);
    }

  }

  private Activity getActivity() {
    Context context = getContext();
    while (context instanceof ContextWrapper) {
      if (context instanceof Activity) {
        return (Activity) context;
      }
      context = ((ContextWrapper) context).getBaseContext();
    }
    return null;
  }

  private void sendEvent(String key, String value, String value2) {
    final Context context = getContext();
    if (context instanceof ReactContext) {
      WritableMap event = new WritableNativeMap();
      event.putString("type", key);
      event.putString("value", value);
      if (value2 != null) {
        event.putString("value2", value2);
      }
      ((ReactContext) context).getJSModule(RCTEventEmitter.class)
        .receiveEvent(getId(),
          "onEventSent", event);
    }
  }

  private String saveToInternalStorage(Bitmap bitmapImage) {
    ContextWrapper cw = new ContextWrapper(getContext().getApplicationContext());
    // path to /data/data/yourapp/app_data/imageDir
    File cacheDir = cw.getCacheDir();
    // Create imageDir
    CharSequence now = DateFormat.format("yyyy_MM_dd_hh_mm_ss", new Date());
    File tempPath = new File(cacheDir, "deepar_" + now + ".jpg");
    if (!tempPath.exists()) {
      try {
        tempPath.createNewFile();
      } catch (IOException e) {
        e.printStackTrace();
      }
    } else {
      tempPath.delete();
      try {
        tempPath.createNewFile();
      } catch (IOException e) {
        e.printStackTrace();
      }
    }

    FileOutputStream outputStream = null;
    try {
      outputStream = new FileOutputStream(tempPath);
      // Use the compress method on the BitMap object to write image to the OutputStream
      int quality = 100; // 0 to 100
      bitmapImage.compress(Bitmap.CompressFormat.JPEG, quality, outputStream);
    } catch (Exception e) {
      e.printStackTrace();
    } finally {
      try {
        outputStream.flush();
        outputStream.close();
      } catch (IOException e) {
        e.printStackTrace();
      }
    }

    return tempPath.getAbsolutePath();
  }

  //
  // Methods
  //

  public void switchCamera() {
    if (cameraService != null) {

      pause();

      cameraService.switchCamera();
      cameraService.openCamera(deepAr);

      cameraDevice = cameraDevice == Camera.CameraInfo.CAMERA_FACING_FRONT ? Camera.CameraInfo.CAMERA_FACING_BACK : Camera.CameraInfo.CAMERA_FACING_FRONT;
      String status = cameraDevice == Camera.CameraInfo.CAMERA_FACING_FRONT ? "front" : "back";

      sendEvent("cameraSwitched", status, null);

      resume();
    }
  }

  public void switchEffect(String effectName, String slot) {
    if (deepAr == null) {
      return;
    }

    if (slot == null || slot.isEmpty()) {
      slot = "effect";
    }

    if (!effectName.isEmpty() && !effectName.equalsIgnoreCase("me") && !effectName.equalsIgnoreCase("none")) {
      deepAr.switchEffect(slot, "file:///android_asset/custom/" + effectName);
    } else {
      deepAr.switchEffect(slot, "", 0);
    }
  }

  public void switchEffectWithPath(String path, String slot) {
    if (deepAr == null) {
      return;
    }

    if (slot == null || slot.isEmpty()) {
      slot = "effect";
    }

    deepAr.switchEffect(slot, path);
  }

  public void fireTrigger(String trigger) {
    if (deepAr == null) {
      return;
    }

    deepAr.fireTrigger(trigger);
  }

  public void setFlashOn(boolean enabled) {
    try {
      if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.M) {
        String mCameraId = mCameraManager.getCameraIdList()[0];
        mCameraManager.setTorchMode(mCameraId, enabled);
      }
    } catch (Exception e) {
      e.printStackTrace();
    }
  }

  public void pause() {
    if (deepAr == null) {
      return;
    }

    deepAr.setPaused(true);
  }

  public void resume() {
    if (deepAr == null) {
      return;
    }

    deepAr.setPaused(false);
  }

  public void takeScreenshot() {
    if (deepAr == null) {
      return;
    }

    new android.os.Handler().postDelayed(
      new Runnable() {
        public void run() {
          deepAr.takeScreenshot();
        }
      }, 100);
  }

  public void startRecording() {
    if (deepAr == null) {
      return;
    }

    int recordingWidth = 720;

    if (recordingWidth > deepAr.getMaxSupportedVideoWidth()) {
      recordingWidth = deepAr.getMaxSupportedVideoWidth();
    }

    float aspectRatio = (float) deepAr.getRenderWidth() / deepAr.getRenderHeight();

    int recordingHeight = (int) (recordingWidth / aspectRatio);

    if (recordingHeight > deepAr.getMaxSupportedVideoHeight()) {
      recordingHeight = deepAr.getMaxSupportedVideoHeight();
      recordingWidth = (int) (recordingHeight * aspectRatio);
    }


    tempVideoPath = Environment.getExternalStorageDirectory().toString() + File.separator + "video.mp4";
    deepAr.startVideoRecording(tempVideoPath, recordingWidth, recordingHeight);
  }

  public void resumeRecording() {
    if (deepAr == null) {
      return;
    }
    deepAr.resumeVideoRecording();
  }

  public void pauseRecording() {
    if (deepAr == null) {
      return;
    }
    deepAr.pauseVideoRecording();
  }

  public void finishRecording() {
    if (deepAr == null) {
      return;
    }
    deepAr.stopVideoRecording();
  }

  public void setAudioMute(boolean enabled) {
    if (deepAr == null) {
      return;
    }
    deepAr.setAudioMute(enabled);
  }

  public void setTouchMode(boolean enabled) {
    if (deepAr == null) {
      return;
    }

    if (enabled) {
      surface.setOnTouchListener((v, event) -> {
        switch (event.getAction()) {
          case MotionEvent.ACTION_DOWN:
            deepAr.touchOccurred(new ARTouchInfo(event.getX(), event.getY(), ARTouchType.Start));
            return true;
          case MotionEvent.ACTION_MOVE:
            deepAr.touchOccurred(new ARTouchInfo(event.getX(), event.getY(), ARTouchType.Move));
            return true;
          case MotionEvent.ACTION_UP:
            deepAr.touchOccurred(new ARTouchInfo(event.getX(), event.getY(), ARTouchType.End));
            return true;
        }

        return false;
      });
    } else {
      surface.setOnTouchListener(null);
    }
  }

  public void setLiveMode(boolean enabled) {
    if (deepAr == null) {
      return;
    }
    deepAr.changeLiveMode(enabled);
  }

  public void setFaceDetectionSensitivity(int sensitivity) {
    if (deepAr == null) {
      return;
    }
    deepAr.setFaceDetectionSensitivity(sensitivity);
  }

  public void showStats(boolean enabled) {
    if (deepAr == null) {
      return;
    }
    deepAr.showStats(enabled);
  }

  public void changeParameterFloat(String gameObject, String component, String parameter, float val) {
    if (deepAr == null) {
      return;
    }
    deepAr.changeParameterFloat(gameObject, component, parameter, val);
  }

  public void changeParameterVec4(String gameObject, String component, String parameter, float valX, float valY, float valZ, float valW) {
    if (deepAr == null) {
      return;
    }
    deepAr.changeParameterVec4(gameObject, component, parameter, valX, valY, valZ, valW);
  }

  public void changeParameterVec3(String gameObject, String component, String parameter, float valX, float valY, float valZ) {
    if (deepAr == null) {
      return;
    }
    deepAr.changeParameterVec3(gameObject, component, parameter, valX, valY, valZ);
  }

  public void changeParameterBool(String gameObject, String component, String parameter, boolean val) {
    if (deepAr == null) {
      return;
    }
    deepAr.changeParameterBool(gameObject, component, parameter, val);
  }

  public void changeParameterTexture(String gameObject, String component, String parameter, Bitmap image) {
    if (deepAr == null) {
      return;
    }
    deepAr.changeParameterTexture(gameObject, component, parameter, image);
  }

  public void changeParameterString(String gameObject, String component, String parameter, String value) {
    if (deepAr == null) {
      return;
    }

    // @todo: not exist in Android SDK
  }

  //
  // SurfaceHolder
  //

  @Override
  public void surfaceCreated(SurfaceHolder holder) {
    //
  }

  @Override
  public void surfaceChanged(SurfaceHolder holder, int format, int width, int height) {
    if (deepAr != null) {
      deepAr.setRenderSurface(holder.getSurface(), width, height);
    }
  }

  @Override
  public void surfaceDestroyed(SurfaceHolder holder) {
    if (deepAr != null) {
      deepAr.setRenderSurface(null, 0, 0);
    }
  }

  //
  // AREventListener
  //

  /**
   * Called when the DeepAR is initialized.
   * DeepAR methods should not be called before the initialization is completed.
   * */
  @Override
  public void initialized() {
    sendEvent("initialized", null, null);
  }

  /**
   * Called when an effect has been switched on a slot given by the slot parameter.
   * */
  @Override
  public void effectSwitched(String slot) {
    sendEvent("effectSwitched", slot, null);
  }

  /**
   * Called when the screen capture is finished.
   * The result is given as an Android Bitmap object.
   * */
  @Override
  public void screenshotTaken(Bitmap bitmap) {
    if (bitmap == null) {
      return;
    }
    String screenshotPath = saveToInternalStorage(bitmap);
    if (!screenshotPath.isEmpty()) {
      sendEvent("screenshotTaken", screenshotPath, null);
    }
  }

  /**
   * Called when the video recording is prepared.
   * */
  @Override
  public void videoRecordingPrepared() {
    sendEvent("videoRecordingPrepared", null, null);
  }

  /**
   * The start of the video recording process is not synchronous,
   * so this method will be called when the video recording is started.
   * */
  @Override
  public void videoRecordingStarted() {
    sendEvent("videoRecordingStarted", null, null);
  }

  /**
   * Called when the video recording is finished.
   * */
  @Override
  public void videoRecordingFinished() {
    sendEvent("videoRecordingFinished", tempVideoPath, null);
  }

  /**
   * Called if the video recording fails.
   * */
  @Override
  public void videoRecordingFailed() {
    sendEvent("error", "Video Recording Failed", null);
  }

  /**
   * Called when the user's face becomes visible or invisible.
   * This event can be used to show a hint to the user to position the face in the camera field of view.
   * */
  @Override
  public void faceVisibilityChanged(boolean faceVisible) {
    String faceVisibleStr = faceVisible == true ? "true" : "false";
    sendEvent("faceVisibilityChanged", faceVisibleStr, null);
  }

  /**
   * Called when a natural image is being tracked and the visibility has changed.
   * The gameObjectName contains the name of the game object with the Natural image position component attached and the current visibility is given by the imageVisible parameter.
   * */
  @Override
  public void imageVisibilityChanged(String gameObject, boolean visible) {
    String visibleStr = visible ? "true" : "false";
    sendEvent("imageVisibilityChanged", gameObject, visibleStr);
  }

  /**
   * Each processed frame will be available here as an Image object.
   * Make sure to call startCapture on DeepAR object otherwise this method will not be called.
   * */
  @Override
  public void frameAvailable(Image image) {
    sendEvent("frameAvailable", null, null);
  }

  /**
   * Called when engine shutdown is finished after calling release().
   * */
  @Override
  public void shutdownFinished() {
    sendEvent("shutdownFinished", null, null);
  }

  /**
   * Called when an error occurs - like the model path not found or the effect file failed to load.
   * */
  @Override
  public void error(ARErrorType arErrorType, String errorText) {
    sendEvent("error", errorText, null);
  }
}
