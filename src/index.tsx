import { requireNativeComponent, ViewStyle } from 'react-native';

type DeeparProps = {
  color: string;
  style: ViewStyle;
};

export const DeeparViewManager = requireNativeComponent<DeeparProps>(
'DeeparView'
);

export default DeeparViewManager;
