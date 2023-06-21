import React, { useRef, forwardRef, useImperativeHandle } from 'react';
import {
  UIManager,
  requireNativeComponent,
  findNodeHandle,
} from 'react-native';

import {
  IDeepARHandle,
  IDeepARProps,
  IRNTDeepARView,
  CameraPositions,
  ErrorTypes,
} from './index';

import Utils from './Utils';

const NATIVE_VIEW_KEY = 'RNTDeepARView';
const RNTDeepARView = requireNativeComponent<IRNTDeepARView>(NATIVE_VIEW_KEY);

const DeepARView = forwardRef<IDeepARHandle, IDeepARProps>(
  (
    {
      apiKey,
      position,
      videoWarmup,
      onEventSent,
      onInitialized,
      onEffectSwitched,
      onCameraSwitched,
      onScreenshotTaken,
      onVideoRecordingPrepared,
      onVideoRecordingStarted,
      onVideoRecordingFinished,
      onFaceVisibilityChanged,
      onImageVisibilityChanged,
      onFrameAvailable,
      onShutdownFinished,
      onError,
      ...props
    },
    ref
  ) => {
    const nativeRef = useRef(null);

    const nativeExecute = (name: string, params?: Array<any>) => {
      return UIManager.dispatchViewManagerCommand(
        findNodeHandle(nativeRef.current),
        UIManager.getViewManagerConfig(NATIVE_VIEW_KEY).Commands[name] || '',
        params
      );
    };

    useImperativeHandle(ref, () => ({
      switchEffect(params) {
        const { mask, slot } = params;
        nativeExecute('switchEffect', [mask, slot || 'effect']);
      },
      switchEffectWithPath(params) {
        const { path, slot } = params;
        nativeExecute('switchEffectWithPath', [path, slot || 'effect']);
      },
      fireTrigger(trigger) {
        nativeExecute('fireTrigger', [trigger]);
      },
      setFlashOn(enabled) {
        nativeExecute('setFlashOn', [enabled]);
      },
      startRecording(params) {
        nativeExecute('startRecording', [
          {
            width: params?.width || null,
            height: params?.height || null,
            bitrate: params?.bitrate || null,
            quality: params?.quality || null,
            recordAudio: params?.recordAudio === false ? false : true,
            maxKeyFrameInterval: params?.maxKeyFrameInterval || null,
            maxKeyFrameIntervalDuration:
              params?.maxKeyFrameIntervalDuration || null,
          },
        ]);
      },
      resumeRecording() {
        nativeExecute('resumeRecording');
      },
      pauseRecording() {
        nativeExecute('pauseRecording');
      },
      finishRecording() {
        nativeExecute('finishRecording');
      },
      setAudioMute(enabled) {
        nativeExecute('setAudioMute', [enabled]);
      },
      pause() {
        nativeExecute('pause');
      },
      resume() {
        nativeExecute('resume');
      },
      takeScreenshot() {
        nativeExecute('takeScreenshot');
      },
      setLiveMode(enabled) {
        nativeExecute('setLiveMode', [enabled]);
      },
      setFaceDetectionSensitivity(sensitivity) {
        nativeExecute('setFaceDetectionSensitivity', [sensitivity]);
      },
      showStats(enabled) {
        nativeExecute('showStats', [enabled]);
      },
      setTouchMode(enabled) {
        nativeExecute('setTouchMode', [enabled]);
      },
      changeParameterFloat(params) {
        const { gameObject, component, parameter, value } = params;
        const nativeParams = [gameObject, component, parameter, value];
        nativeExecute('changeParameterFloat', nativeParams);
      },
      changeParameterVec3(params) {
        const { gameObject, component, parameter, x, y, z } = params;
        const nativeParams = [gameObject, component, parameter, x, y, z];
        nativeExecute('changeParameterVec3', nativeParams);
      },
      changeParameterVec4(params) {
        const { gameObject, component, parameter, x, y, z, w } = params;
        const nativeParams = [gameObject, component, parameter, x, y, z, w];
        nativeExecute('changeParameterVec4', nativeParams);
      },
      changeParameterBool(params) {
        const { gameObject, component, parameter, value } = params;
        const nativeParams = [gameObject, component, parameter, value];
        nativeExecute('changeParameterBool', nativeParams);
      },
      changeParameterTexture(params) {
        const { gameObject, component, parameter, value, type } = params;
        const nativeParams = [gameObject, component, parameter, value, type];
        nativeExecute('changeParameterTexture', nativeParams);
      },
      changeParameterString(params) {
        const { gameObject, component, parameter, value } = params;
        const nativeParams = [gameObject, component, parameter, value];
        nativeExecute('changeParameterString', nativeParams);
      },
    }));

    return (
      <RNTDeepARView
        ref={nativeRef}
        apiKey={apiKey}
        cameraPosition={position || CameraPositions.FRONT}
        videoWarmup={videoWarmup ? 'true' : 'false'}
        onEventSent={({ nativeEvent }) => {
          if (onEventSent) onEventSent(nativeEvent);
          switch (nativeEvent.type) {
            case 'initialized':
              if (onInitialized) onInitialized();
              break;
            case 'effectSwitched':
              if (onEffectSwitched) onEffectSwitched(nativeEvent.value);
              break;
            case 'cameraSwitched':
              if (onCameraSwitched)
                onCameraSwitched(
                  nativeEvent.value === 'front'
                    ? CameraPositions.FRONT
                    : CameraPositions.BACK
                );
              break;
            case 'screenshotTaken':
              if (onScreenshotTaken) onScreenshotTaken(nativeEvent.value);
              break;
            case 'videoRecordingPrepared':
              if (onVideoRecordingPrepared) onVideoRecordingPrepared();
              break;
            case 'videoRecordingStarted':
              if (onVideoRecordingStarted) onVideoRecordingStarted();
              break;
            case 'videoRecordingFinished':
              if (onVideoRecordingFinished)
                onVideoRecordingFinished(nativeEvent.value);
              break;
            case 'faceVisibilityChanged':
              if (onFaceVisibilityChanged)
                onFaceVisibilityChanged(Utils.strToBool(nativeEvent.value));
              break;
            case 'imageVisibilityChanged':
              if (onImageVisibilityChanged)
                onImageVisibilityChanged(
                  Utils.strToBool(nativeEvent.value2),
                  nativeEvent.value
                );
              break;
            case 'frameAvailable':
              if (onFrameAvailable) onFrameAvailable();
              break;
            case 'shutdownFinished':
              if (onShutdownFinished) onShutdownFinished();
              break;
            case 'error':
              if (onError) {
                // @ts-ignore
                onError(nativeEvent.value, ErrorTypes[nativeEvent.value2]);
              }
              break;
            default:
              break;
          }
        }}
        {...props}
      />
    );
  }
);

export default DeepARView;
