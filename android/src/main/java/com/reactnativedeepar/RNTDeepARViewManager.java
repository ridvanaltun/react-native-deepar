package com.reactnativedeepar;

import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.util.Base64;

import androidx.camera.core.CameraSelector;

import com.facebook.infer.annotation.Assertions;
import com.facebook.react.bridge.ReadableArray;
import com.facebook.react.bridge.ReadableMap;
import com.facebook.react.common.MapBuilder;
import com.facebook.react.module.annotations.ReactModule;
import com.facebook.react.uimanager.SimpleViewManager;
import com.facebook.react.uimanager.ThemedReactContext;
import com.facebook.react.uimanager.annotations.ReactProp;

import com.reactnativedeepar.enums.Methods;
import com.reactnativedeepar.enums.TextureTypes;
import com.reactnativedeepar.enums.CameraPositions;

import java.net.URL;
import java.util.HashMap;
import java.util.Map;

import javax.annotation.Nullable;

@ReactModule(name = RNTDeepARViewManager.REACT_CLASS)
public class RNTDeepARViewManager extends SimpleViewManager<RNTDeepAR> {
  public static final String REACT_CLASS = "RNTDeepARView";

  @Override
  public String getName() {
    return REACT_CLASS;
  }

  @Override
  protected RNTDeepAR createViewInstance(ThemedReactContext reactContext) {
    return new RNTDeepAR(reactContext);
  }

  @Override
  public @Nullable
  Map<String, Integer> getCommandsMap() {
    return new HashMap<String, Integer>() {
      private static final long serialVersionUID = 6422000319397326714L;
      {
        put("switchEffect", Methods.SWITCH_EFFECT);
        put("switchEffectWithPath", Methods.SWITCH_EFFECT_WITH_PATH);
        put("fireTrigger", Methods.FIRE_TRIGGER);
        put("setFlashOn", Methods.SET_FLASH_ON);
        put("pause", Methods.PAUSE);
        put("resume", Methods.RESUME);
        put("takeScreenshot", Methods.TAKE_SCREENSHOT);
        put("startRecording", Methods.START_RECORDING);
        put("resumeRecording", Methods.RESUME_RECORDING);
        put("pauseRecording", Methods.PAUSE_RECORDING);
        put("finishRecording", Methods.FINISH_RECORDING);
        put("setAudioMute", Methods.SET_AUDIO_MUTE);
        put("setLiveMode", Methods.SET_LIVE_MODE);
        put("setFaceDetectionSensitivity", Methods.SET_FACE_DETECTION_SENSITIVITY);
        put("showStats", Methods.SHOW_STATS);
        put("setTouchMode", Methods.SET_TOUCH_MODE);
        put("changeParameterFloat", Methods.CHANGE_PARAMETER_FLOAT);
        put("changeParameterVec4", Methods.CHANGE_PARAMETER_VEC4);
        put("changeParameterVec3", Methods.CHANGE_PARAMETER_VEC3);
        put("changeParameterBool", Methods.CHANGE_PARAMETER_BOOL);
        put("changeParameterTexture", Methods.CHANGE_PARAMETER_TEXTURE);
        put("changeParameterString", Methods.CHANGE_PARAMETER_STRING);
      }
    };
  }

  @ReactProp(name = "apiKey")
  public void setApiKey(RNTDeepAR deepARView, String apiKey) {
    deepARView.setLicenseKey(apiKey);
  }

  @ReactProp(name = "videoWarmup")
  public void setVideoWarmup(RNTDeepAR deepARView, String enabled) {
    // ..
  }

  @ReactProp(name = "cameraPosition")
  public void setCameraPosition(RNTDeepAR deepARView, String cameraPosition) {
    int position = CameraSelector.LENS_FACING_FRONT;

    switch (cameraPosition) {
      case CameraPositions.BACK:
        position = CameraSelector.LENS_FACING_BACK;
        break;
      case CameraPositions.FRONT:
        position = CameraSelector.LENS_FACING_FRONT;
        break;
    }

    deepARView.switchCamera(position);
  }

  @Override
  public void receiveCommand(RNTDeepAR deepARView, int commandId, @Nullable ReadableArray args) {
    Assertions.assertNotNull(deepARView);
    switch (commandId) {
      case Methods.SWITCH_EFFECT: {
        if (args != null) {
          String maskName = args.getString(0);
          String slot = args.getString(1);
          deepARView.switchEffect(maskName, slot);
        }
        return;
      }
      case Methods.SWITCH_EFFECT_WITH_PATH: {
        if (args != null) {
          String path = args.getString(0);
          String slot = args.getString(1);
          deepARView.switchEffectWithPath(path, slot);
        }
        return;
      }
      case Methods.FIRE_TRIGGER: {
        if (args != null) {
          String trigger = args.getString(0);
          deepARView.fireTrigger(trigger);
        }
        return;
      }
      case Methods.SET_FLASH_ON: {
        if (args != null) {
          boolean enabled = args.getBoolean(0);
          deepARView.setFlashOn(enabled);
        }
        return;
      }
      case Methods.PAUSE: {
        deepARView.pause();
        return;
      }
      case Methods.RESUME: {
        deepARView.resume();
        return;
      }
      case Methods.TAKE_SCREENSHOT: {
        deepARView.takeScreenshot();
        return;
      }
      case Methods.START_RECORDING: {
        ReadableMap settings = args.getMap(0);
        deepARView.startRecording(settings);
        return;
      }
      case Methods.RESUME_RECORDING: {
        deepARView.resumeRecording();
        return;
      }
      case Methods.PAUSE_RECORDING: {
        deepARView.pauseRecording();
        return;
      }
      case Methods.FINISH_RECORDING: {
        deepARView.finishRecording();
        return;
      }
      case Methods.SET_AUDIO_MUTE: {
        boolean enabled = args.getBoolean(0);
        deepARView.setAudioMute(enabled);
        return;
      }
      case Methods.SET_LIVE_MODE: {
        boolean enabled = args.getBoolean(0);
        deepARView.setLiveMode(enabled);
        return;
      }
      case Methods.SET_FACE_DETECTION_SENSITIVITY: {
        Integer sensitivity = args.getInt(0);
        deepARView.setFaceDetectionSensitivity(sensitivity);
        return;
      }
      case Methods.SHOW_STATS: {
        boolean enabled = args.getBoolean(0);
        deepARView.showStats(enabled);
        return;
      }
      case Methods.SET_TOUCH_MODE: {
        boolean enabled = args.getBoolean(0);
        deepARView.setTouchMode(enabled);
        return;
      }
      case Methods.CHANGE_PARAMETER_FLOAT: {
        if (args != null) {
          String gameObject = args.getString(0);
          String component = args.getString(1);
          String parameter = args.getString(2);
          float val = Float.parseFloat(args.getString(3));
          deepARView.changeParameterFloat(gameObject, component, parameter, val);
        }
        return;
      }
      case Methods.CHANGE_PARAMETER_VEC4: {
        if (args != null) {
          String gameObject = args.getString(0);
          String component = args.getString(1);
          String parameter = args.getString(2);
          float valX = Float.parseFloat(args.getString(3));
          float valY = Float.parseFloat(args.getString(4));
          float valZ = Float.parseFloat(args.getString(5));
          float valW = Float.parseFloat(args.getString(6));
          deepARView.changeParameterVec4(gameObject, component, parameter, valX, valY, valZ, valW);
        }
        return;
      }
      case Methods.CHANGE_PARAMETER_VEC3: {
        if (args != null) {
          String gameObject = args.getString(0);
          String component = args.getString(1);
          String parameter = args.getString(2);
          float valX = Float.parseFloat(args.getString(3));
          float valY = Float.parseFloat(args.getString(4));
          float valZ = Float.parseFloat(args.getString(5));
          deepARView.changeParameterVec3(gameObject, component, parameter, valX, valY, valZ);
        }
        return;
      }
      case Methods.CHANGE_PARAMETER_BOOL: {
        if (args != null) {
          String gameObject = args.getString(0);
          String component = args.getString(1);
          String parameter = args.getString(2);
          boolean val = args.getBoolean(3);
          deepARView.changeParameterBool(gameObject, component, parameter, val);
        }
        return;
      }
      case Methods.CHANGE_PARAMETER_TEXTURE: {
        if (args != null) {
          String gameObject = args.getString(0);
          String component = args.getString(1);
          String parameter = args.getString(2);
          String value = args.getString(3);
          String type = args.getString(4);
          switch (type) {
            case TextureTypes.URL:
              new Thread(new Runnable(){
                @Override
                public void run() {
                  try {
                    URL url = new URL(value);
                    Bitmap image = BitmapFactory.decodeStream(url.openConnection().getInputStream());
                    deepARView.changeParameterTexture(gameObject, component, parameter, image);
                  }
                  catch (Exception ex) {
                    ex.printStackTrace();
                  }
                }
              }).start();
              break;
            case TextureTypes.BASE64:
              byte[] decodedString = Base64.decode(value, Base64.DEFAULT);
              Bitmap image = BitmapFactory.decodeByteArray(decodedString, 0, decodedString.length);
              deepARView.changeParameterTexture(gameObject, component, parameter, image);
              break;
            case TextureTypes.PATH:
              Bitmap pathImage = BitmapFactory.decodeFile(value);
              deepARView.changeParameterTexture(gameObject, component, parameter, pathImage);
              break;
          }
        }
        return;
      }
      case Methods.CHANGE_PARAMETER_STRING: {
        if (args != null) {
          String gameObject = args.getString(0);
          String component = args.getString(1);
          String parameter = args.getString(2);
          String val = args.getString(3);
          deepARView.changeParameterString(gameObject, component, parameter, val);
        }
        return;
      }
      default:
        throw new IllegalArgumentException(String.format(
          "Unsupported command %d received by %s.",
          commandId,
          deepARView.getClass().getSimpleName()));
    }
  }

  @Nullable
  @Override
  public Map<String, Object> getExportedCustomDirectEventTypeConstants() {
    return MapBuilder.<String, Object>builder()
      .put("onEventSent",
        MapBuilder.of("registrationName", "onEventSent"))
      .build();
  }
}
