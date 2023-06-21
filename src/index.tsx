import DeepARView from './DeepARView';
import CameraModule from './CameraModule';

import type { ViewProps } from 'react-native';

export enum CameraPositions {
  FRONT = 'front',
  BACK = 'back',
  UNSPECIFIED = 'unspecified',
}

type CameraPosition =
  | CameraPositions
  | CameraPositions.BACK
  | CameraPositions.FRONT;

export enum TextureSourceTypes {
  BASE64 = 'BASE64',
  URL = 'URL',
  PATH = 'PATH',
}

type TextureSourceType =
  | TextureSourceTypes
  | TextureSourceTypes.BASE64
  | TextureSourceTypes.PATH
  | TextureSourceTypes.URL;

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
  type: string;
  value: string;
  value2?: string;
}

export interface IRNTDeepARView {
  apiKey: string;
  cameraPosition?: CameraPosition;
  videoWarmup?: string;
  onEventSent: ({ nativeEvent }: { nativeEvent: IDeepAREvent }) => void;
}

export enum ErrorTypes {
  DEBUG = 0,
  INFO = 1,
  WARNING = 2,
  ERROR = 3,
  VIDEO = 4,
  UNKNOWN = 5,
}

type ErrorType =
  | ErrorTypes
  | ErrorTypes.DEBUG
  | ErrorTypes.ERROR
  | ErrorTypes.INFO
  | ErrorTypes.UNKNOWN
  | ErrorTypes.VIDEO
  | ErrorTypes.WARNING;

export interface IDeepARProps extends ViewProps {
  apiKey: string;
  position?: CameraPosition;
  videoWarmup?: boolean;
  onEventSent?: (event: IDeepAREvent) => void;
  onInitialized?: () => void;
  onEffectSwitched?: (slot: string) => void;
  onCameraSwitched?: (position: CameraPosition) => void;
  onScreenshotTaken?: (imagePath: string) => void;
  onVideoRecordingPrepared?: () => void;
  onVideoRecordingStarted?: () => void;
  onVideoRecordingFinished?: (tempVideoPath: string) => void;
  onFaceVisibilityChanged?: (isVisible: boolean) => void;
  onImageVisibilityChanged?: (isVisible: boolean, gameObject?: string) => void;
  onFrameAvailable?: () => void;
  onShutdownFinished?: () => void;
  onError?: (text: string, type: ErrorType) => void;
}

export interface ISwitchEffect {
  mask: string;
  slot?: string;
}

export interface ISwitchEffectWithPath {
  path: string;
  slot?: string;
}

export interface IChangeParamater {
  gameObject: string;
  component: string;
  parameter: string;
}

export interface IChangeParamaterFloat extends IChangeParamater {
  value: number;
}

export interface IChangeParamaterVec3 extends IChangeParamater {
  x: number;
  y: number;
  z: number;
}

export interface IChangeParamaterVec4 extends IChangeParamaterVec3 {
  w: number;
}

export interface IChangeParamaterBool extends IChangeParamater {
  value: boolean;
}

export interface IChangeParamaterTexture extends IChangeParamater {
  type: TextureSourceType;
  value: string;
}

export interface IChangeParamaterString extends IChangeParamater {
  value: string;
}

export interface IStartRecording {
  width?: number;
  height?: number;
  recordAudio?: boolean;
  quality?: number; // 0.0 -> 1.0
  bitrate?: number;
  maxKeyFrameInterval?: number;
  maxKeyFrameIntervalDuration?: number;
}

export interface IDeepARHandle {
  switchEffect: (params: ISwitchEffect) => void;
  switchEffectWithPath: (params: ISwitchEffectWithPath) => void;
  fireTrigger: (trigger: string) => void;
  setFlashOn: (enabled: boolean) => void;
  startRecording: (params?: IStartRecording) => void;
  resumeRecording: () => void;
  pauseRecording: () => void;
  finishRecording: () => void;
  setAudioMute: (enabled: boolean) => void;
  pause: () => void;
  resume: () => void;
  takeScreenshot: () => void;
  setLiveMode: (enabled: boolean) => void;
  setFaceDetectionSensitivity: (sensitivity: number) => void;
  showStats: (enabled: boolean) => void;
  setTouchMode: (enabled: boolean) => void;
  changeParameterFloat: (params: IChangeParamaterFloat) => void;
  changeParameterVec3: (params: IChangeParamaterVec3) => void;
  changeParameterVec4: (params: IChangeParamaterVec4) => void;
  changeParameterBool: (params: IChangeParamaterBool) => void;
  changeParameterTexture: (params: IChangeParamaterTexture) => void;
  changeParameterString: (params: IChangeParamaterString) => void;
}

export const Camera = CameraModule;

export default DeepARView;
