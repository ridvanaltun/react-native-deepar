import React from 'react';
import { View, Image, Alert, StyleSheet } from 'react-native';
import { CameraRoll } from '@react-native-camera-roll/camera-roll';
import Video from 'react-native-video';

import { Button } from '../components';
import { Enums, Computed } from '../constants';
import Utils from '../utils';

const PreviewScreen = ({ navigation, route }: any) => {
  const { path, type } = route.params;

  const renderContent = () => {
    if (type === Enums.PREVIEW_TYPES.PHOTO) {
      return <Image style={styles.image} source={{ uri: path }} />;
    }

    return (
      <Video
        resizeMode="contain"
        source={{ uri: path }}
        style={styles.video}
        controls
      />
    );
  };

  const renderButtons = () => {
    return (
      <View style={styles.buttons}>
        <Button text="Back" onPress={() => navigation.goBack()} />
        <Button
          text="Save to Gallery"
          onPress={() => {
            CameraRoll.save(path, { type })
              .then(() => {
                Alert.alert(
                  `${Utils.capitalize(type)} Saved`,
                  `${Utils.capitalize(type)} saved to Gallery!`
                );
              })
              .catch((err) => {
                Alert.alert('Something Goes Wrong', err.message);
              });
          }}
        />
      </View>
    );
  };

  return (
    <View style={styles.container}>
      {renderContent()}
      {renderButtons()}
    </View>
  );
};

const styles = StyleSheet.create({
  container: {
    flex: 1,
    alignItems: 'center',
    justifyContent: 'center',
  },
  image: {
    position: 'absolute',
    flex: 1,
    width: '100%',
    height: '100%',
  },
  buttons: {
    position: 'absolute',
    bottom: 20,
    height: 150,
  },
  video: {
    height: Computed.SCREEN_HEIGHT,
    width: Computed.SCREEN_WIDTH,
  },
});

export default PreviewScreen;
