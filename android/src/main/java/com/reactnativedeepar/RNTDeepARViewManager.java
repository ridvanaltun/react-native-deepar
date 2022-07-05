package com.reactnativedeepar;

import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.util.Base64;
import android.widget.FrameLayout;

import com.facebook.infer.annotation.Assertions;
import com.facebook.react.bridge.ReactContext;
import com.facebook.react.bridge.ReadableArray;
import com.facebook.react.common.MapBuilder;
import com.facebook.react.module.annotations.ReactModule;
import com.facebook.react.uimanager.SimpleViewManager;
import com.facebook.react.uimanager.ThemedReactContext;
import com.facebook.react.uimanager.annotations.ReactProp;

import java.net.URL;
import java.util.HashMap;
import java.util.Map;

import ai.deepar.ar.DeepAR;

import javax.annotation.Nullable;

@ReactModule(name = RNTDeepARViewManager.REACT_CLASS)
public class RNTDeepARViewManager extends SimpleViewManager<RNTDeepAR> {

  public static final String REACT_CLASS = "RNTDeepARView";
  private DeepAR deepAr;
  private ReactContext context;

  /**
   * General
   */
  private static final int SWITCH_EFFECT = 1;
  private static final int SWITCH_EFFECT_WITH_PATH = 2;
  private static final int FIRE_TRIGGER = 3;
  private static final int TAKE_SCREENSHOT = 4;
  private static final int SET_TOUCH_MODE = 5;

  /**
   * Camera
   */
  private static final int SWITCH_CAMERA = 10;
  private static final int SET_FLASH_ON = 11;


  /**
   * Video Recording
   */
  private static final int START_RECORDING = 20;
  private static final int RESUME_RECORDING = 21;
  private static final int PAUSE_RECORDING = 22;
  private static final int FINISH_RECORDING = 23;
  private static final int SET_AUDIO_MUTE = 24;

  /**
   * Change Parameter
   */
  private static final int CHANGE_PARAMETER_FLOAT = 30;
  private static final int CHANGE_PARAMETER_VEC4 = 31;
  private static final int CHANGE_PARAMETER_VEC3 = 32;
  private static final int CHANGE_PARAMETER_BOOL = 33;
  private static final int CHANGE_PARAMETER_TEXTURE = 34;
  private static final int CHANGE_PARAMETER_STRING = 35;

  /**
   * Core
   */
  private static final int PAUSE = 90;
  private static final int RESUME = 91;
  private static final int SET_LIVE_MODE = 92;
  private static final int SET_FACE_DETECTION_SENSITIVITY = 93;
  private static final int SHOW_STATS = 94;

  @Override
  public String getName() {
    return REACT_CLASS;
  }

  @Override
  protected RNTDeepAR createViewInstance(ThemedReactContext reactContext) {
    context = reactContext;
    deepAr = new DeepAR(reactContext);

    return new RNTDeepAR(reactContext, deepAr);
  }

  @Override
  public @Nullable
  Map<String, Integer> getCommandsMap() {

    return new HashMap<String, Integer>() {
      private static final long serialVersionUID = 6422000319397326714L;

      {
        put("switchCamera", SWITCH_CAMERA);
        put("switchEffect", SWITCH_EFFECT);
        put("switchEffectWithPath", SWITCH_EFFECT_WITH_PATH);
        put("fireTrigger", FIRE_TRIGGER);
        put("setFlashOn", SET_FLASH_ON);
        put("pause", PAUSE);
        put("resume", RESUME);
        put("takeScreenshot", TAKE_SCREENSHOT);
        put("startRecording", START_RECORDING);
        put("resumeRecording", RESUME_RECORDING);
        put("pauseRecording", PAUSE_RECORDING);
        put("finishRecording", FINISH_RECORDING);
        put("setAudioMute", SET_AUDIO_MUTE);
        put("setLiveMode", SET_LIVE_MODE);
        put("setFaceDetectionSensitivity", SET_FACE_DETECTION_SENSITIVITY);
        put("showStats", SHOW_STATS);
        put("setTouchMode", SET_TOUCH_MODE);
        put("changeParameterFloat", CHANGE_PARAMETER_FLOAT);
        put("changeParameterVec4", CHANGE_PARAMETER_VEC4);
        put("changeParameterVec3", CHANGE_PARAMETER_VEC3);
        put("changeParameterBool", CHANGE_PARAMETER_BOOL);
        put("changeParameterTexture", CHANGE_PARAMETER_TEXTURE);
        put("changeParameterString", CHANGE_PARAMETER_STRING);
      }
    };
  }

  @ReactProp(name = "apiKey")
  public void setApiKey(FrameLayout view, String apiKey) {
    deepAr.setLicenseKey(apiKey);
  }

  @Override
  public void receiveCommand(RNTDeepAR deepARView, int commandId, @Nullable ReadableArray args) {
    Assertions.assertNotNull(deepARView);
    switch (commandId) {
      case SWITCH_CAMERA: {
        deepARView.switchCamera();
        return;
      }
      case SWITCH_EFFECT: {
        if (args != null) {
          String maskName = args.getString(0);
          String slot = args.getString(1);
          deepARView.switchEffect(maskName, slot);
        }
        return;
      }
      case SWITCH_EFFECT_WITH_PATH: {
        if (args != null) {
          String path = args.getString(0);
          String slot = args.getString(1);
          deepARView.switchEffectWithPath(path, slot);
        }
        return;
      }
      case FIRE_TRIGGER: {
        if (args != null) {
          String trigger = args.getString(0);
          deepARView.fireTrigger(trigger);
        }
        return;
      }
      case SET_FLASH_ON: {
        if (args != null) {
          boolean enabled = args.getBoolean(0);
          deepARView.setFlashOn(enabled);
        }
        return;
      }
      case PAUSE: {
        deepARView.pause();
        return;
      }
      case RESUME: {
        deepARView.resume();
        return;
      }
      case TAKE_SCREENSHOT: {
        deepARView.takeScreenshot();
        return;
      }
      case START_RECORDING: {
        deepARView.startRecording();
        return;
      }
      case RESUME_RECORDING: {
        deepARView.resumeRecording();
        return;
      }
      case PAUSE_RECORDING: {
        deepARView.pauseRecording();
        return;
      }
      case FINISH_RECORDING: {
        deepARView.finishRecording();
        return;
      }
      case SET_AUDIO_MUTE: {
        boolean enabled = args.getBoolean(0);
        deepARView.setAudioMute(enabled);
        return;
      }
      case SET_LIVE_MODE: {
        boolean enabled = args.getBoolean(0);
        deepARView.setLiveMode(enabled);
        return;
      }
      case SET_FACE_DETECTION_SENSITIVITY: {
        Integer sensitivity = args.getInt(0);
        deepARView.setFaceDetectionSensitivity(sensitivity);
        return;
      }
      case SHOW_STATS: {
        boolean enabled = args.getBoolean(0);
        deepARView.showStats(enabled);
        return;
      }
      case SET_TOUCH_MODE: {
        boolean enabled = args.getBoolean(0);
        deepARView.setTouchMode(enabled);
        return;
      }
      case CHANGE_PARAMETER_FLOAT: {
        if (args != null) {
          String gameObject = args.getString(0);
          String component = args.getString(1);
          String parameter = args.getString(2);
          float val = Float.parseFloat(args.getString(3));
          deepARView.changeParameterFloat(gameObject, component, parameter, val);
        }
        return;
      }
      case CHANGE_PARAMETER_VEC4: {
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
      case CHANGE_PARAMETER_VEC3: {
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
      case CHANGE_PARAMETER_BOOL: {
        if (args != null) {
          String gameObject = args.getString(0);
          String component = args.getString(1);
          String parameter = args.getString(2);
          boolean val = args.getBoolean(3);
          deepARView.changeParameterBool(gameObject, component, parameter, val);
        }
        return;
      }
      case CHANGE_PARAMETER_TEXTURE: {
        if (args != null) {
          String gameObject = args.getString(0);
          String component = args.getString(1);
          String parameter = args.getString(2);
          String value = args.getString(3);
          String type = args.getString(4);
          switch (type) {
            case "URL":
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
            case "BASE64":
              byte[] decodedString = Base64.decode(value, Base64.DEFAULT);
              Bitmap image = BitmapFactory.decodeByteArray(decodedString, 0, decodedString.length);
              deepARView.changeParameterTexture(gameObject, component, parameter, image);
              break;
            case "PATH":
              Bitmap pathImage = BitmapFactory.decodeFile(value);
              deepARView.changeParameterTexture(gameObject, component, parameter, pathImage);
              break;
          }
        }
        return;
      }
      case CHANGE_PARAMETER_STRING: {
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
