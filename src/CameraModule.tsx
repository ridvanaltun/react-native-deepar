import { NativeModules } from 'react-native';

import type {
  CameraPermissionRequestResult,
  CameraPermissionStatus,
} from './index';

const { RNTCameraModule } = NativeModules;

type CameraPermission =
  | CameraPermissionStatus
  | CameraPermissionStatus.AUTHORIZED
  | CameraPermissionStatus.DENIED
  | CameraPermissionStatus.NOT_DETERMINED
  | CameraPermissionStatus.RESTRICTED;

type CameraPermissionRequest =
  | CameraPermissionRequestResult
  | CameraPermissionRequestResult.AUTHORIZED
  | CameraPermissionRequestResult.DENIED;

export default {
  requestCameraPermission: (): Promise<CameraPermissionRequest> => {
    return RNTCameraModule.requestCameraPermission();
  },
  requestMicrophonePermission: (): Promise<CameraPermissionRequest> => {
    return RNTCameraModule.requestMicrophonePermission();
  },
  getCameraPermissionStatus: (): Promise<CameraPermission> => {
    return RNTCameraModule.getCameraPermissionStatus();
  },
  getMicrophonePermissionStatus: (): Promise<CameraPermission> => {
    return RNTCameraModule.getMicrophonePermissionStatus();
  },
};
