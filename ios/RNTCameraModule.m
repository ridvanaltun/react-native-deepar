//
//  RNTCameraModule.m
//  RNTCameraModule
//
//  Created by Work on 5.07.2022.
//

#import "RNTCameraModule.h"
#import "AVFoundation/AVFoundation.h"

@implementation RNTCameraModule

// To export a module named RNTCameraModule
RCT_EXPORT_MODULE();

RCT_REMAP_METHOD(requestCameraPermission,
                 withResolverForCamera:(RCTPromiseResolveBlock)resolve
                 withRejecterForCamera:(RCTPromiseRejectBlock)reject)
{
    [AVCaptureDevice requestAccessForMediaType:AVMediaTypeVideo completionHandler:^(BOOL granted) {
        if (granted) {
            resolve(@"authorized");
        } else {
            resolve(@"denied");
        }
    }];
}

RCT_REMAP_METHOD(requestMicrophonePermission,
                 withResolverForMic:(RCTPromiseResolveBlock)resolve
                 withRejecterForMic:(RCTPromiseRejectBlock)reject)
{
    [AVCaptureDevice requestAccessForMediaType:AVMediaTypeAudio completionHandler:^(BOOL granted) {
        if (granted) {
            resolve(@"authorized");
        } else {
            resolve(@"denied");
        }
    }];
}

RCT_REMAP_METHOD(getCameraPermissionStatus,
                 withResolverForCameraStatus:(RCTPromiseResolveBlock)resolve
                 withRejecterForCameraStatus:(RCTPromiseRejectBlock)reject)
{
    AVAuthorizationStatus status = [AVCaptureDevice authorizationStatusForMediaType:AVMediaTypeVideo];
    
    NSString * const AVAuthorizationStatus_toString[] = {
        [AVAuthorizationStatusNotDetermined] = @"not-determined",
        [AVAuthorizationStatusRestricted] = @"restricted",
        [AVAuthorizationStatusDenied] = @"denied",
        [AVAuthorizationStatusAuthorized] = @"authorized"
    };
    
    resolve(AVAuthorizationStatus_toString[status]);
}

RCT_REMAP_METHOD(getMicrophonePermissionStatus,
                 withResolverForMicStatus:(RCTPromiseResolveBlock)resolve
                 withRejecterForMicStatus:(RCTPromiseRejectBlock)reject)
{
    AVAuthorizationStatus status = [AVCaptureDevice authorizationStatusForMediaType:AVMediaTypeAudio];
    
    NSString * const AVAuthorizationStatus_toString[] = {
        [AVAuthorizationStatusNotDetermined] = @"not-determined",
        [AVAuthorizationStatusRestricted] = @"restricted",
        [AVAuthorizationStatusDenied] = @"denied",
        [AVAuthorizationStatusAuthorized] = @"authorized"
    };
    
    resolve(AVAuthorizationStatus_toString[status]);
}

@end
