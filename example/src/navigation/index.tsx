import * as React from 'react';
import { createNativeStackNavigator } from '@react-navigation/native-stack';

import Screens from '../screens';

const Stack = createNativeStackNavigator();

export default () => {
  return (
    <Stack.Navigator
      screenOptions={{
        headerShown: false,
      }}
    >
      <Stack.Screen name="Home" component={Screens.HomeScreen} />
      <Stack.Screen name="Camera" component={Screens.CameraScreen} />
      <Stack.Screen name="Preview" component={Screens.PreviewScreen} />
    </Stack.Navigator>
  );
};
