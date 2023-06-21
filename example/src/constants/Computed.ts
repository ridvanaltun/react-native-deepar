import { Platform, Dimensions } from 'react-native';

const { width, height } = Dimensions.get('window');

export default {
  IS_ANDROID: Platform.OS === 'android',
  IS_IOS: Platform.OS === 'ios',
  SCREEN_HEIGHT: height,
  SCREEN_WIDTH: width,
};
