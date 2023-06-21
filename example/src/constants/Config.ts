import { Platform } from 'react-native';
import Config from 'react-native-config';

export default {
  DEEPAR: {
    API_KEY: Platform.select({
      android: Config.DEEPAR_ANDROID_API_KEY,
      ios: Config.DEEPAR_IOS_API_KEY,
    }) as string,
  },
  TEST: {
    REMOTE_EFFECT_URL: 'http://betacoins.magix.net/public/deepar-filters/',
    EFFECTS: ['8bitHearts'],
  },
};
