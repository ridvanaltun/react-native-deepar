package com.reactnativedeepar;

import android.app.Activity;
import android.content.pm.ActivityInfo;
import android.util.DisplayMetrics;
import android.util.Size;
import android.view.Surface;

import androidx.annotation.NonNull;
import androidx.camera.core.CameraSelector;
import androidx.camera.core.ImageAnalysis;
import androidx.camera.core.ImageProxy;
import androidx.camera.core.Preview;
import androidx.camera.lifecycle.ProcessCameraProvider;
import androidx.core.content.ContextCompat;
import androidx.lifecycle.LifecycleOwner;

import com.google.common.util.concurrent.ListenableFuture;

import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.util.concurrent.ExecutionException;

import ai.deepar.ar.CameraResolutionPreset;
import ai.deepar.ar.DeepAR;
import ai.deepar.ar.DeepARImageFormat;

public class CameraService {
  private static final int NUMBER_OF_BUFFERS = 2;
  private static final boolean useExternalCameraTexture = true;
  private final Activity context;
  private final int defaultLensFacing = CameraSelector.LENS_FACING_FRONT;
  private ARSurfaceProvider surfaceProvider = null;
  private int lensFacing = defaultLensFacing;
  private final ImageAnalysis.Analyzer imageAnalyzer = new ImageAnalysis.Analyzer() {
    @Override
    public void analyze(@NonNull ImageProxy image) {
      byte[] byteData;
      ByteBuffer yBuffer = image.getPlanes()[0].getBuffer();
      ByteBuffer uBuffer = image.getPlanes()[1].getBuffer();
      ByteBuffer vBuffer = image.getPlanes()[2].getBuffer();

      int ySize = yBuffer.remaining();
      int uSize = uBuffer.remaining();
      int vSize = vBuffer.remaining();

      byteData = new byte[ySize + uSize + vSize];

      //U and V are swapped
      yBuffer.get(byteData, 0, ySize);
      vBuffer.get(byteData, ySize, vSize);
      uBuffer.get(byteData, ySize + vSize, uSize);

      buffers[currentBuffer].put(byteData);
      buffers[currentBuffer].position(0);
      if (frameReceiver != null) {
        frameReceiver.receiveFrame(buffers[currentBuffer],
          image.getWidth(), image.getHeight(),
          image.getImageInfo().getRotationDegrees(),
          lensFacing == CameraSelector.LENS_FACING_FRONT,
          DeepARImageFormat.YUV_420_888,
          image.getPlanes()[1].getPixelStride()
        );
      }
      currentBuffer = (currentBuffer + 1) % NUMBER_OF_BUFFERS;
      image.close();
    }
  };
  private ListenableFuture<ProcessCameraProvider> cameraProviderFuture;
  private ByteBuffer[] buffers;
  private int currentBuffer = 0;
  private int width = 0;
  private int height = 0;
  private DeepAR frameReceiver;

  public CameraService(Activity mContext) {
    context = mContext;
    setupCamera();
  }

  public void openCamera(DeepAR frameReceiver) {
    this.frameReceiver = frameReceiver;
    setupCamera();
  }

  public void closeCamera() {
    ProcessCameraProvider cameraProvider = null;
    try {
      cameraProvider = cameraProviderFuture.get();
      cameraProvider.unbindAll();
    } catch (ExecutionException e) {
      e.printStackTrace();
    } catch (InterruptedException e) {
      e.printStackTrace();
    }
    if (surfaceProvider != null) {
      surfaceProvider.stop();
      surfaceProvider = null;
    }
    frameReceiver.release();
    frameReceiver = null;
  }

  public void switchCamera() {
    lensFacing = lensFacing == CameraSelector.LENS_FACING_FRONT ? CameraSelector.LENS_FACING_BACK : CameraSelector.LENS_FACING_FRONT;
    //unbind immediately to avoid mirrored frame.
    ProcessCameraProvider cameraProvider = null;
    try {
      cameraProvider = cameraProviderFuture.get();
      cameraProvider.unbindAll();
    } catch (ExecutionException e) {
      e.printStackTrace();
    } catch (InterruptedException e) {
      e.printStackTrace();
    }
    setupCamera();
  }

  private void setupCamera() {
    cameraProviderFuture = ProcessCameraProvider.getInstance(this.context);
    cameraProviderFuture.addListener(new Runnable() {
      @Override
      public void run() {
        try {
          ProcessCameraProvider cameraProvider = cameraProviderFuture.get();
          bindImageAnalysis(cameraProvider);
        } catch (ExecutionException | InterruptedException e) {
          e.printStackTrace();
        }
      }
    }, ContextCompat.getMainExecutor(this.context));
  }

  private void bindImageAnalysis(@NonNull ProcessCameraProvider cameraProvider) {
    CameraResolutionPreset cameraResolutionPreset = CameraResolutionPreset.P1920x1080;
    int width;
    int height;
    int orientation = getScreenOrientation();
    if (orientation == ActivityInfo.SCREEN_ORIENTATION_REVERSE_LANDSCAPE || orientation == ActivityInfo.SCREEN_ORIENTATION_LANDSCAPE) {
      width = cameraResolutionPreset.getWidth();
      height = cameraResolutionPreset.getHeight();
    } else {
      width = cameraResolutionPreset.getHeight();
      height = cameraResolutionPreset.getWidth();
    }

    Size cameraResolution = new Size(width, height);
    CameraSelector cameraSelector = new CameraSelector.Builder().requireLensFacing(lensFacing).build();

    if (useExternalCameraTexture) {
      Preview preview = new Preview.Builder()
        .setTargetResolution(cameraResolution)
        .build();

      cameraProvider.unbindAll();
      cameraProvider.bindToLifecycle((LifecycleOwner) this.context, cameraSelector, preview);
      if (surfaceProvider == null) {
        surfaceProvider = new ARSurfaceProvider(this.context, frameReceiver);
      }
      preview.setSurfaceProvider(surfaceProvider);
      surfaceProvider.setMirror(lensFacing == CameraSelector.LENS_FACING_FRONT);
    } else {
      buffers = new ByteBuffer[NUMBER_OF_BUFFERS];
      for (int i = 0; i < NUMBER_OF_BUFFERS; i++) {
        buffers[i] = ByteBuffer.allocateDirect(width * height * 3);
        buffers[i].order(ByteOrder.nativeOrder());
        buffers[i].position(0);
      }
      ImageAnalysis imageAnalysis = new ImageAnalysis.Builder()
        .setTargetResolution(cameraResolution)
        .setBackpressureStrategy(ImageAnalysis.STRATEGY_KEEP_ONLY_LATEST)
        .build();
      imageAnalysis.setAnalyzer(ContextCompat.getMainExecutor(this.context), imageAnalyzer);
      cameraProvider.unbindAll();
      cameraProvider.bindToLifecycle((LifecycleOwner) this, cameraSelector, imageAnalysis);
    }
  }

  private String getFilterPath(String filterName) {
    if (filterName.equals("none")) {
      return null;
    }
    return "file:///android_asset/" + filterName;
  }

  private int getScreenOrientation() {
    int rotation = context.getWindowManager().getDefaultDisplay().getRotation();
    DisplayMetrics dm = new DisplayMetrics();
    context.getWindowManager().getDefaultDisplay().getMetrics(dm);
    width = dm.widthPixels;
    height = dm.heightPixels;
    int orientation;
    // if the device's natural orientation is portrait:
    if ((rotation == Surface.ROTATION_0
      || rotation == Surface.ROTATION_180) && height > width ||
      (rotation == Surface.ROTATION_90
        || rotation == Surface.ROTATION_270) && width > height) {
      switch (rotation) {
        case Surface.ROTATION_0:
          orientation = ActivityInfo.SCREEN_ORIENTATION_PORTRAIT;
          break;
        case Surface.ROTATION_90:
          orientation = ActivityInfo.SCREEN_ORIENTATION_LANDSCAPE;
          break;
        case Surface.ROTATION_180:
          orientation =
            ActivityInfo.SCREEN_ORIENTATION_REVERSE_PORTRAIT;
          break;
        case Surface.ROTATION_270:
          orientation =
            ActivityInfo.SCREEN_ORIENTATION_REVERSE_LANDSCAPE;
          break;
        default:
          orientation = ActivityInfo.SCREEN_ORIENTATION_PORTRAIT;
          break;
      }
    }
    // if the device's natural orientation is landscape or if the device
    // is square:
    else {
      switch (rotation) {
        case Surface.ROTATION_0:
          orientation = ActivityInfo.SCREEN_ORIENTATION_LANDSCAPE;
          break;
        case Surface.ROTATION_90:
          orientation = ActivityInfo.SCREEN_ORIENTATION_PORTRAIT;
          break;
        case Surface.ROTATION_180:
          orientation =
            ActivityInfo.SCREEN_ORIENTATION_REVERSE_LANDSCAPE;
          break;
        case Surface.ROTATION_270:
          orientation =
            ActivityInfo.SCREEN_ORIENTATION_REVERSE_PORTRAIT;
          break;
        default:
          orientation = ActivityInfo.SCREEN_ORIENTATION_LANDSCAPE;
          break;
      }
    }

    return orientation;
  }
}
