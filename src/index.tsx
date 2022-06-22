import DeepARView from './DeepARView';

import type {ViewProps} from 'react-native';

export enum CameraFacing {
  FRONT = 'front',
  BACK = 'back',
}

export enum TextureSourceTypes {
  BASE64 = 'BASE64',
  URL = 'URL',
  PATH = 'PATH',
}

export interface IDeepAREvent {
  type: String;
  value: String;
  value2?: String;
}

export interface IRNTDeepARView {
  apiKey: String;
  onEventSent: ({nativeEvent}: {nativeEvent: IDeepAREvent}) => void;
}

export interface IDeepARProps extends ViewProps {
  apiKey: String;
  onEventSent?: (event: IDeepAREvent) => void;
  onInitialized?: () => void;
  onEffectSwitched?: (slot: String) => void;
  onCameraSwitched?: (facing: CameraFacing) => void;
  onScreenshotTaken?: (imagePath: String) => void;
  onVideoRecordingPrepared?: () => void;
  onVideoRecordingStarted?: () => void;
  onVideoRecordingFinished?: (tempVideoPath: String) => void;
  onFaceVisibilityChanged?: (isVisible: Boolean) => void;
  onImageVisibilityChanged?: (isVisible: Boolean, gameObject?: String) => void;
  onFrameAvailable?: () => void;
  onShutdownFinished?: () => void;
  onError?: (errorText: String) => void;
}

interface ISwitchEffect {
  mask: String;
  slot?: String;
}

interface ISwitchEffectWithPath {
  path: String;
  slot?: String;
}

interface IChangeParamater {
  gameObject: String;
  component: String;
  parameter: String;
}

interface IChangeParamaterFloat extends IChangeParamater {
  value: Number;
}

interface IChangeParamaterVec3 extends IChangeParamater {
  x: Number;
  y: Number;
  z: Number;
}

interface IChangeParamaterVec4 extends IChangeParamaterVec3 {
  w: Number;
}

interface IChangeParamaterBool extends IChangeParamater {
  value: Boolean;
}

interface IChangeParamaterTexture extends IChangeParamater {
  type: TextureSourceTypes;
  value: String;
}

interface IChangeParamaterString extends IChangeParamater {
  value: String;
}

export interface IDeepARHandle {
  switchEffect: (params: ISwitchEffect) => void;
  switchEffectWithPath: (params: ISwitchEffectWithPath) => void;
  fireTrigger: (trigger: String) => void;
  switchCamera: () => void;
  setFlashOn: (enabled: Boolean) => void;
  startRecording: () => void;
  resumeRecording: () => void;
  pauseRecording: () => void;
  finishRecording: () => void;
  setAudioMute: (enabled: Boolean) => void;
  pause: () => void;
  resume: () => void;
  takeScreenshot: () => void;
  setLiveMode: (enabled: Boolean) => void;
  setFaceDetectionSensitivity: (sensitivity: Number) => void;
  showStats: (enabled: Boolean) => void;
  changeParameterFloat: (params: IChangeParamaterFloat) => void;
  changeParameterVec3: (params: IChangeParamaterVec3) => void;
  changeParameterVec4: (params: IChangeParamaterVec4) => void;
  changeParameterBool: (params: IChangeParamaterBool) => void;
  changeParameterTexture: (params: IChangeParamaterTexture) => void;
  changeParameterString: (params: IChangeParamaterString) => void;
}

export default DeepARView;
