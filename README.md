# react-native-deepar <!-- omit in toc -->

[![npm version](https://img.shields.io/npm/v/react-native-deepar.svg)](https://npmjs.com/package/react-native-deepar)
[![CircleCI](https://circleci.com/gh/ridvanaltun/react-native-deepar/tree/master.svg?style=shield)](https://circleci.com/gh/ridvanaltun/react-native-deepar/tree/master)
[![Commitizen friendly](https://img.shields.io/badge/commitizen-friendly-brightgreen.svg)](http://commitizen.github.io/cz-cli/)
[![license](https://img.shields.io/npm/l/react-native-deepar.svg)](https://github.com/ridvanaltun/react-native-deepar/blob/master/LICENSE)

> [DeepAR](https://www.deepar.ai/) wrapper for React-Native

# Table of Contents <!-- omit in toc -->

- [Getting started](#getting-started)
- [Installing AR Models](#installing-ar-models)
- [Using AR Models over Internet](#using-ar-models-over-internet)
- [Usage](#usage)
  - [General](#general)
  - [Camera Control](#camera-control)
  - [Video Recording](#video-recording)
  - [Change Parameters](#change-parameters)
  - [Core](#core)
- [Example App](#example-app)
- [Contributing](#contributing)
- [License](#license)

## Getting started

```sh
npm install react-native-deepar
```

**Note:** Don't forget install Pods for iOS and rebuild your app.
**Note:** Only works on physical devices, not will work with simulator.

## Installing AR Models

1. Put your AR models into a desired destination
2. Create `react-native.config.js` like below:

```js
module.exports = {
  assets: ['./assets/effects'], // <-- example destination
};
```

3. Add a NPM script like below:

```diff
{
  "scripts": {
+   "asset": "./node_modules/.bin/react-native-deepar-link"
  }
}
```

4. Run the script to link your AR models

```sh
npm run asset
```

**Note:** If you remove an AR model, you can run the same command for unlinking removed asset.

## Using AR Models over Internet

1. Install [rn-fetch-blob](https://github.com/joltup/rn-fetch-blob) to your project
2. You can use AR models over internet like below:

```tsx
import RNFetchBlob from 'rn-fetch-blob';

RNFetchBlob.config({
  fileCache: true,
})
  .fetch('GET', 'http://betacoins.magix.net/public/deepar-filters/8bitHearts')
  .then((res) => {
    deepARRef?.current?.switchEffectWithPath({
      path: res.path(),
      slot: 'effect',
    });
  });
```

## Usage

[Make registration to DeepAR](https://developer.deepar.ai/) and get an API key from developer panel.

```tsx
import React, { useRef } from 'react';
import DeepAR, { CameraFacing, IDeepARHandle } from 'react-native-deepar';

const App = () => {
  const deepARRef = useRef<IDeepARHandle>(null);

  return (
    <DeepAR
      ref={deepARRef}
      apiKey="your-api-key"
      style={{ flex: 1 }}
      onInitialized={() => {
        // Called when the DeepAR is initialized.
        // DeepAR methods should not be called before the initialization is completed.
      }}
      onEffectSwitched={(slot: String) => {
        // Called when an effect has been switched.
      }}
      onScreenshotTaken={(path: String) => {
        // Called when the screen capture is finished.
      }}
      onVideoRecordingPrepared={() => {
        // Called when the video recording is prepared.
      }}
      onVideoRecordingStarted={() => {
        // The start of the video recording process is not synchronous,
        // so this method will be called when the video recording is started.
      }}
      onVideoRecordingFinished={(path: String) => {
        // Called when the video recording is finished.
      }}
      onCameraSwitched={(status: CameraFacing) => {
        // Todo camera switched.
      }}
      onFaceVisibilityChanged={(isVisible: Boolean) => {
        // Called when the user's face becomes visible or invisible.
      }}
      onImageVisibilityChanged={(isVisible: Boolean, gameObject?: String) => {
        // Called when a natural image is being tracked and the visibility has changed.
      }}
      onError={(errorText: String) => {
        // Called when an error occur
        // like the model path not found or the effect file failed to load.
      }}
    />
  );
};
```

### General

**Switch Effect:**

The method used to switch any effect in the scene. Effects are places in slots. Every slot is identified by its unique name and can hold one effect at any given moment. Every subsequent call to this method removes the effect that was previously displayed in this slot.

```tsx
import type {ISwitchEffect} from 'react-native-deepar';

deepARRef?.current?.switchEffect(params: ISwitchEffect) => void;
```

**Switch Effect with Path:**

```tsx
import type {ISwitchEffectWithPath} from 'react-native-deepar';

deepARRef?.current?.switchEffectWithPath(params: ISwitchEffectWithPath) => void;
```

**Fire Trigger:**

This method allows the user to fire a custom animation trigger for model animations from code. To fire a custom trigger, the trigger string must match the custom trigger set in the Studio when creating the effect.

```tsx
deepARRef?.current?.fireTrigger(trigger: String) => void;
```

**Take Screenshot:**

Captures a screenshot of the current screen. When a screenshot is done `onScreenshotTaken` will be called with a resulting screenshot.

```tsx
deepARRef?.current?.takeScreenshot() => void;
```

### Camera Control

**Switch Camera:**

```tsx
deepARRef?.current?.switchCamera() => void;
```

**Toggle Flash:**

```tsx
deepARRef?.current?.setFlashOn(enabled: Boolean) => void;
```

### Video Recording

**Start Recording:**

Starts video recording of the camera preview.

```tsx
deepARRef?.current?.startRecording() => void;
```

**Pause Recording:**

Pauses video recording.

```tsx
deepARRef?.current?.pauseRecording() => void;
```

**Resume Recording:**

Resumes video recording after it has been paused with `pauseRecording`.

```tsx
deepARRef?.current?.resumeRecording() => void;
```

**Finish Recording:**

Stops video recording and starts the process of saving the recorded video to the file system. When the file is saved, the method `onVideoRecordingFinished` will be called.

```tsx
deepARRef?.current?.finishRecording() => void;
```

**Mute:**

Mutes/unmutes the audio while video recording.

```tsx
deepARRef?.current?.setAudioMute(enabled: Boolean) => void;
```

### Change Parameters

For more details about changeParameter API read our article [here](https://help.deepar.ai/en/articles/3732006-changing-filter-parameters-from-code).

**Change Float:**

This method allows the user to change float parameters during runtime. The method requires a Game Object name, Component name, Parameter name, and a float value.

- `gameObject` is the name of the Game Object in the hierarchy as visible in the Studio. The name should be unique for the method to work properly.
- `component` is the internal component type.
- `parameter` is the name or the parameter to be changed, for example, the name of the blendshape on a mesh. The parameter must exist for the component.
- `value` is the new value to be applied to the parameter.

```tsx
import type {IChangeParamaterFloat} from 'react-native-deepar';

deepARRef?.current?.changeParameterFloat(params: IChangeParamaterFloat) => void;
```

**Change Vector4:**

Same as above except the method takes four float values which represent one Vector4. Can be used to change material color. If multiple Game Objects share the same material, changing the parameter once for any Game Object using the material will change it for all Game Objects. To change a uniform on a material, such as color, the parameter must use the internal uniform name. These names can be found in the shader files.

```tsx
import type {IChangeParamaterVec4} from 'react-native-deepar';

deepARRef?.current?.changeParameterVec4(params: IChangeParamaterVec4) => void;
```

**Change Vector3:**

Same as above except the method takes three float values which represent one Vector3. Can be used to change the transform of a Game Object at runtime. Rotations should be written as Euler angles in degrees. To set a parameter on GameObject, the component parameter should be an empty string.

```tsx
import type {IChangeParamaterVec3} from 'react-native-deepar';

deepARRef?.current?.changeParameterVec3(params: IChangeParamaterVec3) => void;
```

**Change Boolean:**

Same as above except val takes a bool value. Can be used to disable or enable GameObjects at runtime. To set a parameter on GameObject, the component parameter should be an empty string.

```tsx
import type {IChangeParamaterBool} from 'react-native-deepar';

deepARRef?.current?.changeParameterBool(params: IChangeParamaterBool) => void;
```

**Change String:**

**Note:** Only available in iOS

Change a string parameter on a game object. The parameter is the name of the parameter you want to change. The most common use for this override is to change blend mode and culling mode properties of a game object.

```tsx
import type {IChangeParamaterString} from 'react-native-deepar';

deepARRef?.current?.changeParameterString(params: IChangeParamaterString) => void;
```

**Change Texture:**

This method allows the user to change the texture at runtime. The component should be "MeshRenderer". The parameter is the name of the texture that should be changed, this name can be found in the shader that is applied to the material/GameObject.

```tsx
import type {IChangeParamaterTexture} from 'react-native-deepar';

deepARRef?.current?.changeParameterTexture(params: IChangeParamaterTexture) => void;
```

### Core

**Pause:**

Pauses the rendering. This method will not release any resources and should be used only for temporary pause (e.g. user goes to the next screen).

```tsx
deepARRef?.current?.pause() => void;
```

**Resume:**

Resumes the rendering if it was previously paused, otherwise doesn't do anything.

```tsx
deepARRef?.current?.resume() => void;
```

**Change Live Mode:**

This is an optimization method and it allows the user to indicate the DeepAR in which mode it should operate. If called with true value, DeepAR will expect a continuous flow of new frames and it will optimize its inner processes for such workload. An example of this is the typical use case of processing the frames from the camera stream.

If called with false it will optimize for preserving resources and memory by pausing the rendering after each processed frame. A typical use case for this is when the user needs to process just one image.

```tsx
deepARRef?.current?.setLiveMode(enabled: Boolean) => void;
```

**Set Face Detection Sensitivity:**

This method allows the user to change face detection sensitivity. The sensitivity parameter can range from 0 to 3, where 0 is the fastest but might not recognize smaller (further away) faces, and 3 is the slowest but will find smaller faces. By default, this parameter is set to 1.

```tsx
deepARRef?.current?.setFaceDetectionSensitivity(sensitivity: Number) => void;
```

**Show Stats:**

Display debugging stats on screen.

```tsx
deepARRef?.current?.showStats(enabled: Boolean) => void;
```

## Example App

```sh
# clone the project
git clone https://github.com/ridvanaltun/react-native-deepar.git

# go into the project
cd react-native-deepar

# make project ready
npm run bootstrap

# go into the example
cd example

# copy environment file and set your api keys (bundle id is com.example.reactnativedeepar)
cp .env.example .env

# run for android
npm run android

# or

# run for ios
npm run ios
```

## Contributing

See the [contributing guide](CONTRIBUTING.md) to learn how to contribute to the repository and the development workflow.

## License

MIT
