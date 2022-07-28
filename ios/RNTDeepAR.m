//
//  RNTDeepAR.m
//  RNTDeepAR
//
//  Created by Work on 11.06.2022.
//  Copyright © 2022 Facebook. All rights reserved.
//

#import "RNTDeepAR.h"
#import "React/UIView+React.h"
#import <CameraController.h>
#import <Foundation/Foundation.h>

@implementation RNTDeepAR {
CGRect _frame;
}

BOOL touchMode = false;
AVCaptureDevicePosition _cameraPosition;

- (void)dealloc {
  [self.deepar shutdown];
}

- (void)setApiKey:(NSString *)apiKey {
  // Instantiate ARView and add it to view hierarchy.
  self.deepar = [[DeepAR alloc] init];

  [self.deepar setLicenseKey:apiKey];
  [self.deepar initialize];
  self.deepar.delegate = self;

  self.arview = (ARView *)[self.deepar
      createARViewWithFrame:[UIScreen mainScreen].bounds];
  [self insertSubview:self.arview atIndex:0];
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

- (void)setVideoWarmup:(NSString *)enabled {
    Boolean _enabled = [enabled isEqual:@"true"]
                          ? YES
                          : NO;
    self.deepar.videoRecordingWarmupEnabled = _enabled;
}

- (void)setCameraPosition:(NSString *)cameraPosition {

  _cameraPosition = [cameraPosition isEqual:@"back"]
                        ? AVCaptureDevicePositionBack
                        : AVCaptureDevicePositionFront;

  if (self.arview) {
    self.cameraController.position = _cameraPosition;

    NSString *const AVCaptureDevicePosition_toString[] = {
        [AVCaptureDevicePositionUnspecified] = @"unspecified",
        [AVCaptureDevicePositionBack] = @"back",
        [AVCaptureDevicePositionFront] = @"front",
    };

    self.onEventSent(@{
      @"type" : @"cameraSwitched",
      @"value" : AVCaptureDevicePosition_toString[_cameraPosition]
    });
  }
}

- (void)reactSetFrame:(CGRect)frame {
[super reactSetFrame:frame];
_frame = frame;
[self setupDeepARViewFrame];
}

- (void)switchEffect:(NSString *)effect andSlot:(NSString *)slot {
NSString *path = [[NSBundle mainBundle] pathForResource:effect ofType:@""];
if (self.deepar)
  [self.deepar switchEffectWithSlot:slot path:path];
}

- (void)switchEffectWithPath:(NSString *)path andSlot:(NSString *)slot {
if (self.deepar)
  [self.deepar switchEffectWithSlot:slot path:path];
}

- (void)fireTrigger:(NSString *)trigger {
if (self.deepar)
  [self.deepar fireTrigger:trigger];
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
  if (self.deepar)
    [self.deepar pause];
}

- (void)resume {
  if (self.deepar)
    [self.deepar resume];
}

- (void)takeScreenshot {
  if (self.deepar)
    [self.deepar takeScreenshot];
}

- (void)startRecording:(NSDictionary *)options {
    CGFloat _width = self.frame.size.width;
    CGFloat _height = self.frame.size.height;

    BOOL recordAudio = true;
    NSMutableDictionary *videoCompressionProperties =  [[NSMutableDictionary alloc] init];
    CGRect subframe = CGRectMake(0, 0, 1, 1); // select all view

//    if (![options[@"resolution"] isEqual:[NSNull null]] && [options[@"resolution"] isEqual: @"custom"]) {
//        if (![options[@"width"] isEqual:[NSNull null]]) {
//            _width = [options[@"width"] floatValue];
//        }
//
//        if (![options[@"height"] isEqual:[NSNull null]]) {
//            _height = [options[@"height"] floatValue];
//        }
//    }
    
    if (![options[@"width"] isEqual:[NSNull null]]) {
        _width = [options[@"width"] floatValue];
    }

    if (![options[@"height"] isEqual:[NSNull null]]) {
        _height = [options[@"height"] floatValue];
    }

    if (![options[@"recordAudio"] isEqual:[NSNull null]]) {
        recordAudio = [options[@"recordAudio"] boolValue];
    }

    if (![options[@"quality"] isEqual:[NSNull null]]) {
        [videoCompressionProperties setObject:[NSNumber numberWithFloat:[options[@"quality"] floatValue]] forKey:AVVideoQualityKey];
    }

    if (![options[@"bitrate"] isEqual:[NSNull null]]) {
        [videoCompressionProperties setObject:[NSNumber numberWithInt:[options[@"bitrate"] intValue]] forKey:AVVideoAverageBitRateKey];
    }

    if (![options[@"maxKeyFrameInterval"] isEqual:[NSNull null]]) {
        [videoCompressionProperties setObject:[NSNumber numberWithInt:[options[@"maxKeyFrameInterval"] intValue]] forKey:AVVideoMaxKeyFrameIntervalKey];
    }
    
    if (![options[@"maxKeyFrameIntervalDuration"] isEqual:[NSNull null]]) {
        [videoCompressionProperties setObject:[NSNumber numberWithInt:[options[@"maxKeyFrameIntervalDuration"] intValue]] forKey:AVVideoMaxKeyFrameIntervalDurationKey];
    }

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

        if (self->_deepar) {
dispatch_after(
   dispatch_time(DISPATCH_TIME_NOW, 0.25 * NSEC_PER_SEC),
   dispatch_get_main_queue(), ^{
     [self->_deepar
         startVideoRecordingWithOutputWidth:_width
                               outputHeight:_height
                                   subframe:subframe
                 videoCompressionProperties:videoCompressionProperties
                                recordAudio:recordAudio];
   });
}
    }
  }
} else {
    if (self.deepar) {
//        AVCaptureDevice *device =
//            [AVCaptureDevice defaultDeviceWithMediaType:AVMediaTypeVideo];
//
//        if ([device lockForConfiguration:nil]) {
//            int32_t desiredFPS = 30;
//            device.activeVideoMinFrameDuration = CMTimeMake(1, (int32_t)desiredFPS);
//            device.activeVideoMaxFrameDuration = CMTimeMake(1, (int32_t)desiredFPS);
//            [device unlockForConfiguration];
//        }
       
        dispatch_async(dispatch_get_main_queue(), ^{
            [self->_deepar startVideoRecordingWithOutputWidth:_width outputHeight:_height subframe:subframe videoCompressionProperties:videoCompressionProperties recordAudio:recordAudio];
        });
    }
}
}

- (void)resumeRecording {
  if (self.deepar)
    [self.deepar resumeVideoRecording];
}

- (void)pauseRecording {
  if (self.deepar)
    [self.deepar pauseVideoRecording];
}

- (void)finishRecording {
  if (self.deepar)
    [self.deepar finishVideoRecording];
}

- (void)setAudioMute:(BOOL)enabled {
  if (self.deepar)
    [self.deepar enableAudioProcessing:enabled];
}

- (void)setLiveMode:(BOOL)liveMode {
  if (self.deepar)
    [self.deepar changeLiveMode:liveMode];
}

- (void)setFaceDetectionSensitivity:(int)sensitivity {
  if (self.deepar)
    [self.deepar setFaceDetectionSensitivity:sensitivity];
}

- (void)showStats:(BOOL)enabled {
  if (self.deepar)
    [self.deepar showStats:enabled];
}

- (void)setTouchMode:(BOOL)enabled {
    touchMode = enabled;
}

// Retrieves and normalizes the location point of the given touch within the view
- (CGPoint)getPoint:(UITouch *)touch {
  CGPoint point = [touch locationInView:self.arview];
  CGRect frame = self.bounds;
  return CGPointMake(point.x / frame.size.width, point.y / frame.size.height);
}

// Called every time a new touch is detected
- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event {
if (touchMode == false) {
  return;
}

if (event.type == UIEventTypeTouches) {
  UITouch *touch = [touches allObjects][0];
  CGPoint point = [self getPoint:touch];
  TouchInfo info = {point.x, point.y, START};
  [self.deepar touchOccurred:info];
} else {
  [super touchesBegan:touches withEvent:event];
}
}

// Called every time a change in the previously started touch is detected
- (void)touchesMoved:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event {
if (touchMode == false) {
  return;
}

if (event.type == UIEventTypeTouches) {
  UITouch *touch = [touches allObjects][0];
  CGPoint point = [self getPoint:touch];
  TouchInfo info = {point.x, point.y, MOVE};
  [self.deepar touchOccurred:info];
} else {
  [super touchesMoved:touches withEvent:event];
}
}

// Called every time a previously started touch is ended
- (void)touchesEnded:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event {
if (touchMode == false) {
  return;
}

if (event.type == UIEventTypeTouches) {
  UITouch *touch = [touches allObjects][0];
  CGPoint point = [self getPoint:touch];
  TouchInfo info = {point.x, point.y, END};
  [self.deepar touchOccurred:info];
} else {
  [super touchesEnded:touches withEvent:event];
}
}

// Called every time a previously started touch is cancelled (interrupted)
- (void)touchesCancelled:(NSSet<UITouch *> *)touches
             withEvent:(UIEvent *)event {
if (touchMode == false) {
  return;
}

if (event.type == UIEventTypeTouches) {
  UITouch *touch = [touches allObjects][0];
  CGPoint point = [self getPoint:touch];
  TouchInfo info = {point.x, point.y, END};
  [self.deepar touchOccurred:info];
} else {
  [super touchesCancelled:touches withEvent:event];
}
}

- (void)changeParameterFloat:(NSString *)gameObject
                   component:(NSString *)component
                   parameter:(NSString *)parameter
                  floatValue:(float)value {
  if (self.deepar)
    [self.deepar changeParameter:gameObject
                       component:component
                       parameter:parameter
                      floatValue:value];
}

- (void)changeParameterVec4:(NSString *)gameObject
                  component:(NSString *)component
                  parameter:(NSString *)parameter
                vectorValue:(Vector4)value {
  if (self.deepar)
    [self.deepar changeParameter:gameObject
                       component:component
                       parameter:parameter
                     vectorValue:value];
}

- (void)changeParameterVec3:(NSString *)gameObject
                  component:(NSString *)component
                  parameter:(NSString *)parameter
               vector3Value:(Vector3)value {
  if (self.deepar)
    [self.deepar changeParameter:gameObject
                       component:component
                       parameter:parameter
                    vector3Value:value];
}

- (void)changeParameterBool:(NSString *)gameObject
                  component:(NSString *)component
                  parameter:(NSString *)parameter
                  boolValue:(bool)value {
  if (self.deepar)
    [self.deepar changeParameter:gameObject
                       component:component
                       parameter:parameter
                       boolValue:value];
}

- (void)changeParameterTexture:(NSString *)gameObject
                     component:(NSString *)component
                     parameter:(NSString *)parameter
                         image:(UIImage *)image {
  if (self.deepar)
    [self.deepar changeParameter:gameObject
                       component:component
                       parameter:parameter
                           image:image];
}

- (void)changeParameterString:(NSString *)gameObject
                    component:(NSString *)component
                    parameter:(NSString *)parameter
                  stringValue:(NSString *)value {
  if (self.deepar)
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
  self.cameraController.position = _cameraPosition;

  [self setupDeepARViewFrame];
}

- (void)setupDeepARViewFrame {
    dispatch_async(dispatch_get_main_queue(), ^{
        if (self.deepar.renderingInitialized && !CGRectIsEmpty(self->_frame) &&
            (self.arview.frame.size.height != self->_frame.size.height ||
             self.arview.frame.size.width != self->_frame.size.width ||
             self.arview.frame.origin.x != self->_frame.origin.x ||
             self.arview.frame.origin.y != self->_frame.origin.y)) {
            [self.arview setFrame:self->_frame];

          self.onEventSent(@{@"type" : @"initialized", @"value" : @""});
        }
    });
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
  NSString * const DEEPAR_ERROR_TYPE_VIDEO = @"VIDEO";
  self.onEventSent(@{@"type" : @"error", @"value" : [error description], @"value2" : DEEPAR_ERROR_TYPE_VIDEO});
}

/**
 * Called when an error has occurred.
 */
- (void)onErrorWithCode:(ARErrorType)code error:(NSString *)error {
    NSString * const ARErrorType_toString[] = {
        [DEEPAR_ERROR_TYPE_DEBUG] = @"DEBUG",
        [DEEPAR_ERROR_TYPE_INFO] = @"INFO",
        [DEEPAR_ERROR_TYPE_WARNING] = @"WARNING",
        [DEEPAR_ERROR_TYPE_ERROR] = @"ERROR"
    };

    self.onEventSent(@{@"type" : @"error", @"value" : [error description], @"value2" : ARErrorType_toString[code]});
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
