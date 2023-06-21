import 'react-native-config';

declare module 'react-native-config' {
  interface NativeConfig {
    DEEPAR_ANDROID_API_KEY: string;
    DEEPAR_IOS_API_KEY: string;
  }
}
