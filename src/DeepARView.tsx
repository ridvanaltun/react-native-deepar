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
  CameraFacing,
} from './index';

const NATIVE_VIEW_KEY = 'RNTDeepARView';
const RNTDeepARView = requireNativeComponent<IRNTDeepARView>(NATIVE_VIEW_KEY);

const DeepARView = forwardRef<IDeepARHandle, IDeepARProps>(
  (
    {
      apiKey,
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

    useImperativeHandle(ref, () => ({
      switchEffect(params) {
        let { mask, slot } = params;

        if (!!slot === false) {
          slot = 'effect';
        }

        UIManager.dispatchViewManagerCommand(
          findNodeHandle(nativeRef.current),
          UIManager.getViewManagerConfig(NATIVE_VIEW_KEY).Commands.switchEffect,
          [mask, slot]
        );
      },
      switchEffectWithPath(params) {
        let { path, slot } = params;

        if (!!slot === false) {
          slot = 'effect';
        }

        UIManager.dispatchViewManagerCommand(
          findNodeHandle(nativeRef.current),
          UIManager.getViewManagerConfig(NATIVE_VIEW_KEY).Commands
            .switchEffectWithPath,
          [path, slot]
        );
      },
      fireTrigger(trigger) {
        UIManager.dispatchViewManagerCommand(
          findNodeHandle(nativeRef.current),
          UIManager.getViewManagerConfig(NATIVE_VIEW_KEY).Commands.fireTrigger,
          [trigger]
        );
      },
      switchCamera() {
        UIManager.dispatchViewManagerCommand(
          findNodeHandle(nativeRef.current),
          UIManager.getViewManagerConfig(NATIVE_VIEW_KEY).Commands.switchCamera,
          undefined
        );
      },
      setFlashOn(enabled) {
        UIManager.dispatchViewManagerCommand(
          findNodeHandle(nativeRef.current),
          UIManager.getViewManagerConfig(NATIVE_VIEW_KEY).Commands.setFlashOn,
          [enabled]
        );
      },
      startRecording() {
        UIManager.dispatchViewManagerCommand(
          findNodeHandle(nativeRef.current),
          UIManager.getViewManagerConfig(NATIVE_VIEW_KEY).Commands
            .startRecording,
          undefined
        );
      },
      resumeRecording() {
        UIManager.dispatchViewManagerCommand(
          findNodeHandle(nativeRef.current),
          UIManager.getViewManagerConfig(NATIVE_VIEW_KEY).Commands
            .resumeRecording,
          undefined
        );
      },
      pauseRecording() {
        UIManager.dispatchViewManagerCommand(
          findNodeHandle(nativeRef.current),
          UIManager.getViewManagerConfig(NATIVE_VIEW_KEY).Commands
            .pauseRecording,
          undefined
        );
      },
      finishRecording() {
        UIManager.dispatchViewManagerCommand(
          findNodeHandle(nativeRef.current),
          UIManager.getViewManagerConfig(NATIVE_VIEW_KEY).Commands
            .finishRecording,
          undefined
        );
      },
      setAudioMute(enabled) {
        UIManager.dispatchViewManagerCommand(
          findNodeHandle(nativeRef.current),
          UIManager.getViewManagerConfig(NATIVE_VIEW_KEY).Commands.setAudioMute,
          [enabled]
        );
      },
      pause() {
        UIManager.dispatchViewManagerCommand(
          findNodeHandle(nativeRef.current),
          UIManager.getViewManagerConfig(NATIVE_VIEW_KEY).Commands.pause,
          undefined
        );
      },
      resume() {
        UIManager.dispatchViewManagerCommand(
          findNodeHandle(nativeRef.current),
          UIManager.getViewManagerConfig(NATIVE_VIEW_KEY).Commands.resume,
          undefined
        );
      },
      takeScreenshot() {
        UIManager.dispatchViewManagerCommand(
          findNodeHandle(nativeRef.current),
          UIManager.getViewManagerConfig(NATIVE_VIEW_KEY).Commands
            .takeScreenshot,
          undefined
        );
      },
      setLiveMode(enabled) {
        UIManager.dispatchViewManagerCommand(
          findNodeHandle(nativeRef.current),
          UIManager.getViewManagerConfig(NATIVE_VIEW_KEY).Commands.setLiveMode,
          [enabled]
        );
      },
      setFaceDetectionSensitivity(sensitivity) {
        UIManager.dispatchViewManagerCommand(
          findNodeHandle(nativeRef.current),
          UIManager.getViewManagerConfig(NATIVE_VIEW_KEY).Commands
            .setFaceDetectionSensitivity,
          [sensitivity]
        );
      },
      showStats(enabled) {
        UIManager.dispatchViewManagerCommand(
          findNodeHandle(nativeRef.current),
          UIManager.getViewManagerConfig(NATIVE_VIEW_KEY).Commands.showStats,
          [enabled]
        );
      },
      changeParameterFloat(params) {
        const { gameObject, component, parameter, value } = params;
        UIManager.dispatchViewManagerCommand(
          findNodeHandle(nativeRef.current),
          UIManager.getViewManagerConfig(NATIVE_VIEW_KEY).Commands
            .changeParameterFloat,
          [gameObject, component, parameter, value]
        );
      },
      changeParameterVec3(params) {
        const { gameObject, component, parameter, x, y, z } = params;
        UIManager.dispatchViewManagerCommand(
          findNodeHandle(nativeRef.current),
          UIManager.getViewManagerConfig(NATIVE_VIEW_KEY).Commands
            .changeParameterVec3,
          [gameObject, component, parameter, x, y, z]
        );
      },
      changeParameterVec4(params) {
        const { gameObject, component, parameter, x, y, z, w } = params;
        UIManager.dispatchViewManagerCommand(
          findNodeHandle(nativeRef.current),
          UIManager.getViewManagerConfig(NATIVE_VIEW_KEY).Commands
            .changeParameterVec4,
          [gameObject, component, parameter, x, y, z, w]
        );
      },
      changeParameterBool(params) {
        const { gameObject, component, parameter, value } = params;
        UIManager.dispatchViewManagerCommand(
          findNodeHandle(nativeRef.current),
          UIManager.getViewManagerConfig(NATIVE_VIEW_KEY).Commands
            .changeParameterBool,
          [gameObject, component, parameter, value]
        );
      },
      changeParameterTexture(params) {
        const { gameObject, component, parameter, value, type } = params;
        UIManager.dispatchViewManagerCommand(
          findNodeHandle(nativeRef.current),
          UIManager.getViewManagerConfig(NATIVE_VIEW_KEY).Commands
            .changeParameterTextureWithPath,
          [gameObject, component, parameter, value, type]
        );
      },
      changeParameterString(params) {
        const { gameObject, component, parameter, value } = params;
        UIManager.dispatchViewManagerCommand(
          findNodeHandle(nativeRef.current),
          UIManager.getViewManagerConfig(NATIVE_VIEW_KEY).Commands
            .changeParameterString,
          [gameObject, component, parameter, value]
        );
      },
    }));

    return (
      <RNTDeepARView
        ref={nativeRef}
        apiKey={apiKey}
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
                    ? CameraFacing.FRONT
                    : CameraFacing.BACK
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
                onFaceVisibilityChanged(nativeEvent.value === 'true');
              break;
            case 'imageVisibilityChanged':
              if (onImageVisibilityChanged)
                onImageVisibilityChanged(
                  nativeEvent.value2 === 'true',
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
              if (onError) onError(nativeEvent.value);
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
