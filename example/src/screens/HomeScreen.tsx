import React from 'react';
import {View, Text, TouchableOpacity, StyleSheet} from 'react-native';

const HomeScreen = ({navigation}: {navigation: any}) => {
  return (
    <View style={styles.container}>
      <TouchableOpacity
        onPress={() => {
          navigation.navigate('Camera');
        }}>
        <Text>Go Camera Screen</Text>
      </TouchableOpacity>
    </View>
  );
};

const styles = StyleSheet.create({
  container: {
    flex: 1,
    justifyContent: 'center',
    alignItems: 'center',
  },
});

export default HomeScreen;
