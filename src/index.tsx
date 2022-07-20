import DeepARView from './DeepARView';
import CameraModule from './CameraModule';

import type {ViewProps} from 'react-native';

export enum CameraPosition {
  FRONT = 'front',
  BACK = 'back',
  UNSPECIFIED = 'unspecified',
}

export enum TextureSourceTypes {
  BASE64 = 'BASE64',
  URL = 'URL',
  PATH = 'PATH',
}

export enum CameraPermissionStatus {
  AUTHORIZED = 'authorized',
  NOT_DETERMINED = 'not-determined',
  DENIED = 'denied',
  RESTRICTED = 'restricted',
}

export enum CameraPermissionRequestResult {
  AUTHORIZED = 'authorized',
  DENIED = 'denied',
}

export interface IDeepAREvent {
  type: String;
  value: String;
  value2?: String;
}

export interface IRNTDeepARView {
  apiKey: String;
  cameraPosition?: CameraPosition;
  videoWarmupEnabled?: string;
  onEventSent: ({nativeEvent}: {nativeEvent: IDeepAREvent}) => void;
}

export enum ErrorTypes {
  DEBUG = 0,
  INFO = 1,
  WARNING = 2,
  ERROR = 3,
  VIDEO = 4,
  UNKNOWN = 5,
}

export interface IDeepARProps extends ViewProps {
  apiKey: String;
  position?: CameraPosition;
  videoWarmupEnabled?: boolean;
  onEventSent?: (event: IDeepAREvent) => void;
  onInitialized?: () => void;
  onEffectSwitched?: (slot: String) => void;
  onCameraSwitched?: (position: CameraPosition) => void;
  onScreenshotTaken?: (imagePath: String) => void;
  onVideoRecordingPrepared?: () => void;
  onVideoRecordingStarted?: () => void;
  onVideoRecordingFinished?: (tempVideoPath: String) => void;
  onFaceVisibilityChanged?: (isVisible: Boolean) => void;
  onImageVisibilityChanged?: (isVisible: Boolean, gameObject?: String) => void;
  onFrameAvailable?: () => void;
  onShutdownFinished?: () => void;
  onError?: (text: String, type: ErrorTypes) => void;
}

export interface ISwitchEffect {
  mask: String;
  slot?: String;
}

export interface ISwitchEffectWithPath {
  path: String;
  slot?: String;
}

export interface IChangeParamater {
  gameObject: String;
  component: String;
  parameter: String;
}

export interface IChangeParamaterFloat extends IChangeParamater {
  value: Number;
}

export interface IChangeParamaterVec3 extends IChangeParamater {
  x: Number;
  y: Number;
  z: Number;
}

export interface IChangeParamaterVec4 extends IChangeParamaterVec3 {
  w: Number;
}

export interface IChangeParamaterBool extends IChangeParamater {
  value: Boolean;
}

export interface IChangeParamaterTexture extends IChangeParamater {
  type: TextureSourceTypes;
  value: String;
}

export interface IChangeParamaterString extends IChangeParamater {
  value: String;
}

export interface IDeepARHandle {
  switchEffect: (params: ISwitchEffect) => void;
  switchEffectWithPath: (params: ISwitchEffectWithPath) => void;
  fireTrigger: (trigger: String) => void;
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
  setTouchMode: (enabled: Boolean) => void;
  changeParameterFloat: (params: IChangeParamaterFloat) => void;
  changeParameterVec3: (params: IChangeParamaterVec3) => void;
  changeParameterVec4: (params: IChangeParamaterVec4) => void;
  changeParameterBool: (params: IChangeParamaterBool) => void;
  changeParameterTexture: (params: IChangeParamaterTexture) => void;
  changeParameterString: (params: IChangeParamaterString) => void;
}

export const Camera = CameraModule;

export default DeepARView;
