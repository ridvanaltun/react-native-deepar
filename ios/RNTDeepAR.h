//
//  RNTDeepAR.h
//  RNTDeepAR
//
//  Created by Work on 11.06.2022.
//  Copyright © 2022 Facebook. All rights reserved.
//

#ifndef RNTDeepAR_h
#define RNTDeepAR_h

#import <AVKit/AVKit.h>
#import <ARView.h>
#import <React/RCTComponent.h>
#import <React/RCTView.h>

@interface RNTDeepAR
    : RCTView <ARViewDelegate, AVCaptureVideoDataOutputSampleBufferDelegate>

@property(nonatomic, assign) BOOL flashOn;
@property(nonatomic, strong) CameraController *cameraController;
@property(nonatomic, strong) DeepAR *deepar;
@property(nonatomic, strong) ARView *arview;
@property(nonatomic, copy) RCTBubblingEventBlock onEventSent;
@property(nonatomic, copy) NSString *apiKey;

- (void)pause;
- (void)resume;
- (void)startRecording:(NSDictionary *)options;
- (void)resumeRecording;
- (void)pauseRecording;
- (void)finishRecording;
- (void)setAudioMute:(BOOL)enabled;
- (void)takeScreenshot;
- (void)switchEffect:(NSString *)effect andSlot:(NSString *)slot;
- (void)switchEffectWithPath:(NSString *)path andSlot:(NSString *)slot;
- (void)fireTrigger:(NSString *)trigger;
- (void)setFlashOn:(BOOL)flashOn;
- (void)setLiveMode:(BOOL)liveMode;
- (void)setFaceDetectionSensitivity:(int)sensitivity;
- (void)showStats:(BOOL)enabled;
- (void)setTouchMode:(BOOL)enabled;
- (void)changeParameterFloat:(NSString*)gameObject component:(NSString*)component parameter:(NSString*)parameter floatValue:(float)value;
- (void)changeParameterVec4:(NSString*)gameObject component:(NSString*)component parameter:(NSString*)parameter vectorValue:(Vector4)value;
- (void)changeParameterVec3:(NSString*)gameObject component:(NSString*)component parameter:(NSString*)parameter vector3Value:(Vector3)value;
- (void)changeParameterBool:(NSString*)gameObject component:(NSString*)component parameter:(NSString*)parameter boolValue:(bool)value;
- (void)changeParameterTexture:(NSString*)gameObject component:(NSString*)component parameter:(NSString*)parameter image:(UIImage*)image;
- (void)changeParameterString:(NSString*)gameObject component:(NSString*)component parameter:(NSString*)parameter stringValue:(NSString *)value;

@end

#endif /* RNTDeepAR_h */
