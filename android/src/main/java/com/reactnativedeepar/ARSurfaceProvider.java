package com.reactnativedeepar;

import android.content.Context;
import android.graphics.SurfaceTexture;
import android.opengl.EGL14;
import android.util.Log;
import android.util.Size;
import android.view.Surface;

import androidx.annotation.NonNull;
import androidx.camera.core.Preview;
import androidx.camera.core.SurfaceRequest;
import androidx.core.content.ContextCompat;

import java.util.Timer;
import java.util.TimerTask;

import ai.deepar.ar.DeepAR;

/**
 * Surface provider used for CameraX preview use-case that provides DeepAR's external GL texture
 * wrapped in SurfaceTexture.
 */
public class ARSurfaceProvider implements Preview.SurfaceProvider {
  private static final String TAG = ARSurfaceProvider.class.getSimpleName();

  private final DeepAR deepAR;
  private final Context context;
  private boolean isNotifyDeepAR = true;
  private boolean stop = false;
  private boolean mirror = true;
  private int orientation = 0;
  private SurfaceTexture surfaceTexture;
  private Surface surface;
  private int nativeGLTextureHandle = 0;

  ARSurfaceProvider(Context context, DeepAR deepAR) {
    this.context = context;
    this.deepAR = deepAR;
  }

  private void printEglState() {
    Log.d(TAG, "display: " + EGL14.eglGetCurrentDisplay().getNativeHandle() + ", context: " + EGL14.eglGetCurrentContext().getNativeHandle());
  }

  @Override
  public void onSurfaceRequested(@NonNull SurfaceRequest request) {
    Log.d(TAG, "Surface requested");
    printEglState();

    // request the external gl texture from DeepAR
    if (nativeGLTextureHandle == 0) {
      nativeGLTextureHandle = deepAR.getExternalGlTexture();
      Log.d(TAG, "request new external GL texture");
      printEglState();
    }

    // if external gl texture could not be provided
    if (nativeGLTextureHandle == 0) {
      request.willNotProvideSurface();
      return;
    }

    // if external GL texture is provided create SurfaceTexture from it
    // and register onFrameAvailable listener to
    Size resolution = request.getResolution();
    if (surfaceTexture == null) {
      surfaceTexture = new SurfaceTexture(nativeGLTextureHandle);
      surfaceTexture.setOnFrameAvailableListener(__ -> {
        if (stop) {
          return;
        }
        surfaceTexture.updateTexImage();
        if (isNotifyDeepAR) {
          deepAR.receiveFrameExternalTexture(resolution.getWidth(), resolution.getHeight(), orientation, mirror, nativeGLTextureHandle);
        }
      });
    }
    surfaceTexture.setDefaultBufferSize(resolution.getWidth(), resolution.getHeight());

    if (surface == null) {
      surface = new Surface(surfaceTexture);
    }

    // register transformation listener to listen for screen orientation changes
    request.setTransformationInfoListener(ContextCompat.getMainExecutor(context), transformationInfo -> orientation = transformationInfo.getRotationDegrees());

    request.provideSurface(surface, ContextCompat.getMainExecutor(context), result -> {
      switch (result.getResultCode()) {
        case SurfaceRequest.Result.RESULT_SURFACE_USED_SUCCESSFULLY:
          Log.i(TAG, "RESULT_SURFACE_USED_SUCCESSFULLY");
          break;
        case SurfaceRequest.Result.RESULT_INVALID_SURFACE:
          Log.i(TAG, "RESULT_INVALID_SURFACE");
          break;
        case SurfaceRequest.Result.RESULT_REQUEST_CANCELLED:
          Log.i(TAG, "RESULT_REQUEST_CANCELLED");
          break;
        case SurfaceRequest.Result.RESULT_SURFACE_ALREADY_PROVIDED:
          Log.i(TAG, "RESULT_SURFACE_ALREADY_PROVIDED");
          break;
        case SurfaceRequest.Result.RESULT_WILL_NOT_PROVIDE_SURFACE:
          Log.i(TAG, "RESULT_WILL_NOT_PROVIDE_SURFACE");
          break;
      }
    });
  }

  /**
   * Get the mirror flag. Mirror flag tells the DeepAR weather to mirror the camera frame.
   * Usually this is set when using front camera.
   *
   * @return mirror flag
   */
  public boolean isMirror() {
    return mirror;
  }

  /**
   * Set the mirror flag. Mirror flag tells the DeepAR weather to mirror the camera frame.
   * Usually this is set when using front camera.
   *
   * @param mirror mirror flag
   */
  public void setMirror(boolean mirror) {
    this.mirror = mirror;
    if (surfaceTexture == null || surface == null) {
      return;
    }

    // when camera changes from front to back, we don't know
    // when exactly it will happen so we pause feeding the frames
    // to DeepAR for 1 second to avoid mirroring image before
    // the camera actually changed
    isNotifyDeepAR = false;
    new Timer().schedule(new TimerTask() {
      @Override
      public void run() {
        isNotifyDeepAR = true;
      }
    }, 1000);
  }

  /**
   * Tell the surface provider to stop feeding frames to DeepAR.
   * Should be called in...
   */
  public void stop() {
    stop = true;
  }
}

