package com.reactnativedeepar;

import android.Manifest;
import android.app.Activity;
import android.content.pm.PackageManager;
import android.os.Build;

import androidx.annotation.NonNull;
import androidx.core.content.ContextCompat;

import com.facebook.react.bridge.Promise;
import com.facebook.react.bridge.ReactApplicationContext;
import com.facebook.react.bridge.ReactContextBaseJavaModule;
import com.facebook.react.bridge.ReactMethod;
import com.facebook.react.module.annotations.ReactModule;
import com.facebook.react.modules.core.PermissionAwareActivity;

@ReactModule(name = RNTCameraModule.NAME)
public class RNTCameraModule extends ReactContextBaseJavaModule {
    public static final String NAME = "RNTCameraModule";

    public Integer RequestCode = 10;

    public RNTCameraModule(ReactApplicationContext reactContext) {
      super(reactContext);
    }

    @Override
    @NonNull
    public String getName() {
      return NAME;
    }

    public String parsePermissionStatus(Integer status) {
      if (status == PackageManager.PERMISSION_DENIED) return "denied";
      if (status == PackageManager.PERMISSION_GRANTED) return "authorized";

      return "not-determined";
    }

    @ReactMethod
    public void getCameraPermissionStatus(Promise promise) {
      ReactApplicationContext reactContext = getReactApplicationContext();
      Integer status = ContextCompat.checkSelfPermission(reactContext, Manifest.permission.CAMERA);
      promise.resolve(parsePermissionStatus(status));
    }

    @ReactMethod
    public void getMicrophonePermissionStatus(Promise promise) {
      ReactApplicationContext reactContext = getReactApplicationContext();
      Integer status = ContextCompat.checkSelfPermission(reactContext, Manifest.permission.RECORD_AUDIO);
      promise.resolve(parsePermissionStatus(status));
    }

    @ReactMethod
    public void requestCameraPermission(Promise promise) {
      if (Build.VERSION.SDK_INT < Build.VERSION_CODES.M) {
        // API 21 and below always grants permission on app install
        promise.resolve("authorized");
      }

      String[] PERMISSIONS = {Manifest.permission.CAMERA};

      Activity activity = getReactApplicationContext().getCurrentActivity();

      if (activity instanceof PermissionAwareActivity) {
        Integer currentRequestCode = RequestCode++;

        ((PermissionAwareActivity) this.getCurrentActivity()).requestPermissions(PERMISSIONS, currentRequestCode, (requestCode, permissions, grantResults) -> {
          if (requestCode == currentRequestCode) {
            Integer permissionStatus;
            if (grantResults.length > 0) {
              permissionStatus = grantResults[0];
            }  else {
              permissionStatus = PackageManager.PERMISSION_DENIED;
            }

            promise.resolve(parsePermissionStatus(permissionStatus));

            return true;
          }

          return false;
        });
      }
    }

    @ReactMethod
    public void requestMicrophonePermission(Promise promise) {
      if (Build.VERSION.SDK_INT < Build.VERSION_CODES.M) {
        // API 21 and below always grants permission on app install
        promise.resolve("authorized");
      }

      String[] PERMISSIONS = {Manifest.permission.RECORD_AUDIO};

      Activity activity = getReactApplicationContext().getCurrentActivity();

      if (activity instanceof PermissionAwareActivity) {
        Integer currentRequestCode = RequestCode++;

        ((PermissionAwareActivity) this.getCurrentActivity()).requestPermissions(PERMISSIONS, currentRequestCode, (requestCode, permissions, grantResults) -> {
          if (requestCode == currentRequestCode) {
            Integer permissionStatus;
            if (grantResults.length > 0) {
              permissionStatus = grantResults[0];
            }  else {
              permissionStatus = PackageManager.PERMISSION_DENIED;
            }

            promise.resolve(parsePermissionStatus(permissionStatus));

            return true;
          }

          return false;
        });
      }
    }
}
