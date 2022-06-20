//
//  RNTDeepAR.m
//  RNTDeepAR
//
//  Created by Work on 11.06.2022.
//  Copyright © 2022 Facebook. All rights reserved.
//

#import "JSONModelLib.h"
#import "RNTDeepAR.h"
#import "React/UIView+React.h"
#import <DeepAR/CameraController.h>
#import <Foundation/Foundation.h>

@implementation RNTDeepAR {
CGRect _frame;
ARView *_arview;
UIImageView *_backgroundView;
}

- (void)dealloc {
[self.deepar shutdown];
}

- (void)setApiKey:(NSString *)apiKey {
// Instantiate ARView and add it to view hierarchy.
self.deepar = [[DeepAR alloc] init];

[self.deepar setLicenseKey:apiKey];
[self.deepar initialize];
self.deepar.delegate = self;

_arview = (ARView *)[self.deepar
    createARViewWithFrame:[UIScreen mainScreen].bounds];
[self insertSubview:_arview atIndex:0];
self.cameraController = [[CameraController alloc] init];
self.cameraController.deepAR = self.deepar;

[self.cameraController startCamera];

AVAudioSession *session = [AVAudioSession sharedInstance];
[session setCategory:AVAudioSessionCategoryPlayAndRecord
         withOptions:AVAudioSessionCategoryOptionMixWithOthers
               error:nil];

[[NSNotificationCenter defaultCenter]
    addObserver:self
       selector:@selector(orientationChanged:)
           name:UIDeviceOrientationDidChangeNotification
         object:nil];
}

- (void)reactSetFrame:(CGRect)frame {
[super reactSetFrame:frame];
_frame = frame;
[self setupDeepARViewFrame];
}

- (void)switchCamera {
if (_arview) {
  self.cameraController.position =
      self.cameraController.position == AVCaptureDevicePositionBack
          ? AVCaptureDevicePositionFront
          : AVCaptureDevicePositionBack;

  NSString *message;
  if (self.cameraController.position == AVCaptureDevicePositionBack) {
    message = @"back";
  } else {
    message = @"front";
  }
  self.onEventSent(@{@"type" : @"cameraSwitched", @"value" : message});
}
}

- (void)switchEffect:(NSString *)effect andSlot:(NSString *)slot {
NSString *path = [[NSBundle mainBundle] pathForResource:effect ofType:@""];
[_arview switchEffectWithSlot:slot path:path];
}

- (void)switchEffectWithPath:(NSString *)path andSlot:(NSString *)slot {
[_arview switchEffectWithSlot:slot path:path];
}

- (void)fireTrigger:(NSString *)trigger {
[_arview fireTrigger:trigger];
}

- (void)setFlashOn:(bool)flashOn {
// check if flashlight available
Class captureDeviceClass = NSClassFromString(@"AVCaptureDevice");
if (captureDeviceClass != nil) {
  AVCaptureDevice *device =
      [AVCaptureDevice defaultDeviceWithMediaType:AVMediaTypeVideo];
  if ([device hasTorch] && [device hasFlash]) {

    [device lockForConfiguration:nil];
    if (flashOn) {
      [device setTorchMode:AVCaptureTorchModeOn];
      [device setFlashMode:AVCaptureFlashModeOn];
    } else {
      [device setTorchMode:AVCaptureTorchModeOff];
      [device setFlashMode:AVCaptureFlashModeOff];
    }
    [device unlockForConfiguration];
  }
}
}

- (void)pause {
if (_arview) {
  [_arview pause];
}
}

- (void)resume {
if (_arview) {
  [_arview resume];
}
}

- (void)takeScreenshot {
[_arview takeScreenshot];
}

- (void)startRecording {
if (self.flashOn &&
    self.cameraController.position == AVCaptureDevicePositionBack) {
  Class captureDeviceClass = NSClassFromString(@"AVCaptureDevice");
  if (captureDeviceClass != nil) {
    AVCaptureDevice *device =
        [AVCaptureDevice defaultDeviceWithMediaType:AVMediaTypeVideo];
    if ([device hasTorch] && [device hasFlash]) {

      [device lockForConfiguration:nil];
      [device setTorchMode:AVCaptureTorchModeOn];
      [device setFlashMode:AVCaptureFlashModeOn];
      [device unlockForConfiguration];

      dispatch_after(
          dispatch_time(DISPATCH_TIME_NOW, 0.25 * NSEC_PER_SEC),
          dispatch_get_main_queue(), ^{
            if (self->_arview) {
              [self->_arview
                  startVideoRecordingWithOutputWidth:self.frame.size.width *
                                                     0.75
                                        outputHeight:self.frame.size.height *
                                                     0.75];
            }
          });
    }
  }
} else {
  if (_arview) {
    [self->_arview
        startVideoRecordingWithOutputWidth:self.frame.size.width * 0.75
                              outputHeight:self.frame.size.height * 0.75];
    //[_arview startRecordingWithScale:0.5];
  }
}
}

- (void)resumeRecording {
[_arview resumeVideoRecording];
}

- (void)pauseRecording {
[_arview pauseVideoRecording];
}

- (void)finishRecording {
[_arview finishVideoRecording];
}

- (void)setAudioMute:(BOOL)enabled {
[_arview enableAudioProcessing:enabled];
}

- (void)setLiveMode:(BOOL)liveMode {
[self.deepar changeLiveMode:liveMode];
}

- (void)setFaceDetectionSensitivity:(int)sensitivity {
[self.deepar setFaceDetectionSensitivity:sensitivity];
}

- (void)showStats:(BOOL)enabled {
[_arview showStats:enabled];
}

- (void)changeParameterFloat:(NSString *)gameObject
                 component:(NSString *)component
                 parameter:(NSString *)parameter
                floatValue:(float)value {
[self.deepar changeParameter:gameObject
                   component:component
                   parameter:parameter
                  floatValue:value];
}

- (void)changeParameterVec4:(NSString *)gameObject
                component:(NSString *)component
                parameter:(NSString *)parameter
              vectorValue:(Vector4)value {
[self.deepar changeParameter:gameObject
                   component:component
                   parameter:parameter
                 vectorValue:value];
}

- (void)changeParameterVec3:(NSString *)gameObject
                component:(NSString *)component
                parameter:(NSString *)parameter
             vector3Value:(Vector3)value {
[self.deepar changeParameter:gameObject
                   component:component
                   parameter:parameter
                vector3Value:value];
}

- (void)changeParameterBool:(NSString *)gameObject
                component:(NSString *)component
                parameter:(NSString *)parameter
                boolValue:(bool)value {
[self.deepar changeParameter:gameObject
                   component:component
                   parameter:parameter
                   boolValue:value];
}

- (void)changeParameterTexture:(NSString *)gameObject
                   component:(NSString *)component
                   parameter:(NSString *)parameter
                       image:(UIImage *)image {
[self.deepar changeParameter:gameObject
                   component:component
                   parameter:parameter
                       image:image];
}

- (void)changeParameterString:(NSString *)gameObject
                  component:(NSString *)component
                  parameter:(NSString *)parameter
                stringValue:(NSString *)value {
[self.deepar changeParameter:gameObject
                   component:component
                   parameter:parameter
                 stringValue:value];
}

//
// DeepARDelegate
//

#pragma mark - ARViewDelegate methods

/**
* Called when the DeepAR engine initialization is complete
*/
- (void)didInitialize {
[self setupDeepARViewFrame];
}

- (void)setupDeepARViewFrame {
if (_arview.initialized && !CGRectIsEmpty(_frame) &&
    (_arview.frame.size.height != _frame.size.height ||
     _arview.frame.size.width != _frame.size.width ||
     _arview.frame.origin.x != _frame.origin.x ||
     _arview.frame.origin.y != _frame.origin.y)) {
  [_arview setFrame:_frame];

  //[_arview switchEffectWithSlot:@"watermark" path:[[NSBundle mainBundle]
  // pathForResource:@"watermark" ofType:@""]];
  self.onEventSent(@{@"type" : @"initialized", @"value" : @""});
}
}

// Called when the finished the preparing for video recording.
- (void)didFinishPreparingForVideoRecording {
self.onEventSent(@{@"type" : @"videoRecordingPrepared", @"value" : @""});
}

/**
* Called when DeepAR has started video recording (after calling
* startVideoRecording method).
*/
- (void)didStartVideoRecording {
self.onEventSent(@{@"type" : @"videoRecordingStarted", @"value" : @""});
}

/**
* Called when the video recording is finished and the video file is saved at
* videoFilePath path.
*/
- (void)didFinishVideoRecording:(NSString *)videoFilePath {
self.onEventSent(
    @{@"type" : @"videoRecordingFinished", @"value" : videoFilePath});
}

/**
* Called if there is error encountered while recording video
*/
- (void)recordingFailedWithError:(NSError *)error {
self.onEventSent(@{@"type" : @"error", @"value" : [error description]});
}

/**
* DeepAR has finished taking a screenshot. The result is given as an UIImage
* object in the screenshot parameter.
*/
- (void)didTakeScreenshot:(UIImage *)screenshot {

// Turn of torch
if (self.flashOn) {
  // check if flashlight available
  Class captureDeviceClass = NSClassFromString(@"AVCaptureDevice");
  if (captureDeviceClass != nil) {
    AVCaptureDevice *device =
        [AVCaptureDevice defaultDeviceWithMediaType:AVMediaTypeVideo];
    if ([device hasTorch] && [device hasFlash]) {
      [device lockForConfiguration:nil];
      [device setTorchMode:AVCaptureTorchModeOff];
      [device setFlashMode:AVCaptureFlashModeOff];
      [device unlockForConfiguration];
    }

    // @todo
    // self.onEventSent(@{ @"type": @"effectSwitched", @"value": slot});
  }
}

NSData *data = UIImageJPEGRepresentation(screenshot, 1.0);
NSFileManager *fileManager = [NSFileManager defaultManager];
NSString *cachesDir = [NSSearchPathForDirectoriesInDomains(
    NSCachesDirectory, NSUserDomainMask, YES) lastObject];
NSString *fullPath =
    [cachesDir stringByAppendingPathComponent:@"temp_screenshot.jpg"];
[fileManager createFileAtPath:fullPath contents:data attributes:nil];

self.onEventSent(@{@"type" : @"screenshotTaken", @"value" : fullPath});
}

/**
* Called when an effect has been switched on a slot given by the slot
* parameter.
*/
- (void)effectSwitched:(NSString *)slot {
self.onEventSent(@{@"type" : @"effectSwitched", @"value" : slot});
}

/**
* Called when DeepAR detects a new face or loses a face that has been tracked.
*/
- (void)faceVisiblityDidChange:(BOOL)faceVisible {
self.onEventSent(@{
  @"type" : @"faceVisibilityChanged",
  @"value" : faceVisible ? @"true" : @"false"
});
}

/**
* This method notifies when tracked image visibility changes.
* gameObjectName is the name of the game object/node in the filter file to
* which the image is associated.
*/
- (void)imageVisibilityChanged:(NSString *)gameObjectName
                imageVisible:(BOOL)imageVisible {
self.onEventSent(@{
  @"type" : @"imageVisibilityChanged",
  @"value" : gameObjectName,
  @"value2" : imageVisible ? @"true" : @"false",
});
}

- (void)orientationChanged:(NSNotification *)notification {
UIInterfaceOrientation orientation =
    [[UIApplication sharedApplication] statusBarOrientation];
if (orientation == UIInterfaceOrientationLandscapeLeft) {
  self.cameraController.videoOrientation =
      AVCaptureVideoOrientationLandscapeLeft;
} else if (orientation == UIInterfaceOrientationLandscapeRight) {
  self.cameraController.videoOrientation =
      AVCaptureVideoOrientationLandscapeRight;
} else if (orientation == UIInterfaceOrientationPortrait) {
  self.cameraController.videoOrientation = AVCaptureVideoOrientationPortrait;
} else if (orientation == UIInterfaceOrientationPortraitUpsideDown) {
  self.cameraController.videoOrientation =
      AVCaptureVideoOrientationPortraitUpsideDown;
}
}

/**
* A new processed frame is available.
* Make sure to call startCaptureWithOutputWidth on DeepAR (or
* startFrameOutputWithOutputWidth if you use ARView) if you want this method to
* be called whenever a new frame is ready.
*/
- (void)frameAvailable:(CMSampleBufferRef)sampleBuffer {
self.onEventSent(@{@"type" : @"frameAvailable", @"value" : @""});
}

/**
* DeepAR has successfully shut down after the method shutdown call.
*/
- (void)didFinishShutdown {
self.onEventSent(@{@"type" : @"shutdownFinished", @"value" : @""});
}

//
// Not included on Android
//

/**
* Called on each frame where at least one face data is detected.
*/
- (void)faceTracked:(MultiFaceData)faceData {
//  NSString *faceDataStr = [faceData.faceData toJSONString];
//  self.onEventSent(@{@"type" : @"faceTracked", @"value":
//  faceData.faceData[0].});
}

/**
* Whenever a face is detected or lost from the scene this method is called.
* facesVisible represents the number of currently detected faces in the frame.
*/
- (void)numberOfFacesVisibleChanged:(NSInteger)facesVisible {
NSString *inStr = [NSString stringWithFormat:@"%ld", (long)facesVisible];
self.onEventSent(
    @{@"type" : @"numberOfFacesVisibleChanged", @"value" : inStr});
}

/**
* Called when the conditions have been met for the animation to transition to
* the next state (e.g. mouth open, emotion detected etc.)
*/
- (void)animationTransitionedToState:(NSString *)state {
self.onEventSent(
    @{@"type" : @"animationTransitionedToState", @"value" : state});
}

@end
