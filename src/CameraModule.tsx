import {NativeModules} from 'react-native';

import type {
  CameraPermissionRequestResult,
  CameraPermissionStatus,
} from './index';

const {RNTCameraModule} = NativeModules;

export default {
  requestCameraPermission: (): Promise<CameraPermissionRequestResult> => {
    return RNTCameraModule.requestCameraPermission();
  },
  requestMicrophonePermission: (): Promise<CameraPermissionRequestResult> => {
    return RNTCameraModule.requestMicrophonePermission();
  },
  getCameraPermissionStatus: (): Promise<CameraPermissionStatus> => {
    return RNTCameraModule.getCameraPermissionStatus();
  },
  getMicrophonePermissionStatus: (): Promise<CameraPermissionStatus> => {
    return RNTCameraModule.getMicrophonePermissionStatus();
  },
};
