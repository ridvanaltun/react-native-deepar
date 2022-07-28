#import "RNTDeepAR.h"
#import "RNTDeepARViewManager.h"
#import "React/RCTBridge.h"
#import "React/RCTUIManager.h"
#import <Foundation/Foundation.h>

@implementation RNTDeepARViewManager

RCT_EXPORT_MODULE(RNTDeepARViewManager)
RCT_EXPORT_VIEW_PROPERTY(apiKey, NSString)
RCT_EXPORT_VIEW_PROPERTY(cameraPosition, NSString)
RCT_EXPORT_VIEW_PROPERTY(videoWarmup, NSString)
RCT_EXPORT_VIEW_PROPERTY(onEventSent, RCTBubblingEventBlock)

+ (BOOL)requiresMainQueueSetup {
  return YES;
}

- (dispatch_queue_t)methodQueue {
  return dispatch_get_main_queue();
}

- (UIView *)view {
  return [RNTDeepAR new];
}

RCT_EXPORT_METHOD(switchEffect
                  : (nonnull NSNumber *)reactTag andMaskPath
                  : (NSString *)effect andSlot
                  : (NSString *)slot) {
  [self.bridge.uiManager addUIBlock:^(__unused RCTUIManager *uiManager,
                                      NSDictionary<NSNumber *, RNTDeepAR *>
                                          *viewRegistry) {
    RNTDeepAR *view = viewRegistry[reactTag];
    if (![view isKindOfClass:[RNTDeepAR class]]) {
      RCTLogError(
          @"Invalid view returned from registry, expecting RNTDeepAR, got: %@",
          view);
    } else {
      [view switchEffect:effect andSlot:slot];
    }
  }];
}

RCT_EXPORT_METHOD(switchEffectWithPath
                  : (nonnull NSNumber *)reactTag andMaskPath
                  : (NSString *)path andSlot
                  : (NSString *)slot) {
  [self.bridge.uiManager addUIBlock:^(__unused RCTUIManager *uiManager,
                                      NSDictionary<NSNumber *, RNTDeepAR *>
                                          *viewRegistry) {
    RNTDeepAR *view = viewRegistry[reactTag];
    if (![view isKindOfClass:[RNTDeepAR class]]) {
      RCTLogError(
          @"Invalid view returned from registry, expecting RNTDeepAR, got: %@",
          view);
    } else {
      [view switchEffectWithPath:path andSlot:slot];
    }
  }];
}

RCT_EXPORT_METHOD(fireTrigger
                  : (nonnull NSNumber *)reactTag andTrigger
                  : (NSString *)trigger) {
  [self.bridge.uiManager addUIBlock:^(__unused RCTUIManager *uiManager,
                                      NSDictionary<NSNumber *, RNTDeepAR *>
                                          *viewRegistry) {
    RNTDeepAR *view = viewRegistry[reactTag];
    if (![view isKindOfClass:[RNTDeepAR class]]) {
      RCTLogError(
          @"Invalid view returned from registry, expecting RNTDeepAR, got: %@",
          view);
    } else {
      [view fireTrigger:trigger];
    }
  }];
}

RCT_EXPORT_METHOD(setFlashOn
                  : (nonnull NSNumber *)reactTag andIsFlashOn
                  : (BOOL)flashOn) {
  [self.bridge.uiManager addUIBlock:^(__unused RCTUIManager *uiManager,
                                      NSDictionary<NSNumber *, RNTDeepAR *>
                                          *viewRegistry) {
    RNTDeepAR *view = viewRegistry[reactTag];
    if (![view isKindOfClass:[RNTDeepAR class]]) {
      RCTLogError(
          @"Invalid view returned from registry, expecting RNTDeepAR, got: %@",
          view);
    } else {
      [view setFlashOn:flashOn];
    }
  }];
}

RCT_EXPORT_METHOD(pause : (nonnull NSNumber *)reactTag) {
  [self.bridge.uiManager addUIBlock:^(__unused RCTUIManager *uiManager,
                                      NSDictionary<NSNumber *, RNTDeepAR *>
                                          *viewRegistry) {
    RNTDeepAR *view = viewRegistry[reactTag];
    if (![view isKindOfClass:[RNTDeepAR class]]) {
      RCTLogError(
          @"Invalid view returned from registry, expecting RNTDeepAR, got: %@",
          view);
    } else {
      [view pause];
    }
  }];
}

RCT_EXPORT_METHOD(resume : (nonnull NSNumber *)reactTag) {
  [self.bridge.uiManager addUIBlock:^(__unused RCTUIManager *uiManager,
                                      NSDictionary<NSNumber *, RNTDeepAR *>
                                          *viewRegistry) {
    RNTDeepAR *view = viewRegistry[reactTag];
    if (![view isKindOfClass:[RNTDeepAR class]]) {
      RCTLogError(
          @"Invalid view returned from registry, expecting RNTDeepAR, got: %@",
          view);
    } else {
      [view resume];
    }
  }];
}

RCT_EXPORT_METHOD(takeScreenshot : (nonnull NSNumber *)reactTag) {
  [self.bridge.uiManager addUIBlock:^(__unused RCTUIManager *uiManager,
                                      NSDictionary<NSNumber *, RNTDeepAR *>
                                          *viewRegistry) {
    RNTDeepAR *view = viewRegistry[reactTag];
    if (![view isKindOfClass:[RNTDeepAR class]]) {
      RCTLogError(
          @"Invalid view returned from registry, expecting RNTDeepAR, got: %@",
          view);
    } else {
      [view takeScreenshot];
    }
  }];
}

RCT_EXPORT_METHOD(startRecording
                  : (nonnull NSNumber *)reactTag withOptions
                  : (NSDictionary *)options) {
  [self.bridge.uiManager addUIBlock:^(__unused RCTUIManager *uiManager,
                                      NSDictionary<NSNumber *, RNTDeepAR *>
                                          *viewRegistry) {
    RNTDeepAR *view = viewRegistry[reactTag];
    if (![view isKindOfClass:[RNTDeepAR class]]) {
      RCTLogError(
          @"Invalid view returned from registry, expecting RNTDeepAR, got: %@",
          view);
    } else {
        [view startRecording:options];
    }
  }];
}

RCT_EXPORT_METHOD(resumeRecording : (nonnull NSNumber *)reactTag) {
  [self.bridge.uiManager addUIBlock:^(__unused RCTUIManager *uiManager,
                                      NSDictionary<NSNumber *, RNTDeepAR *>
                                          *viewRegistry) {
    RNTDeepAR *view = viewRegistry[reactTag];
    if (![view isKindOfClass:[RNTDeepAR class]]) {
      RCTLogError(
          @"Invalid view returned from registry, expecting RNTDeepAR, got: %@",
          view);
    } else {
      [view resumeRecording];
    }
  }];
}

RCT_EXPORT_METHOD(pauseRecording : (nonnull NSNumber *)reactTag) {
  [self.bridge.uiManager addUIBlock:^(__unused RCTUIManager *uiManager,
                                      NSDictionary<NSNumber *, RNTDeepAR *>
                                          *viewRegistry) {
    RNTDeepAR *view = viewRegistry[reactTag];
    if (![view isKindOfClass:[RNTDeepAR class]]) {
      RCTLogError(
          @"Invalid view returned from registry, expecting RNTDeepAR, got: %@",
          view);
    } else {
      [view pauseRecording];
    }
  }];
}

RCT_EXPORT_METHOD(finishRecording : (nonnull NSNumber *)reactTag) {
  [self.bridge.uiManager addUIBlock:^(__unused RCTUIManager *uiManager,
                                      NSDictionary<NSNumber *, RNTDeepAR *>
                                          *viewRegistry) {
    RNTDeepAR *view = viewRegistry[reactTag];
    if (![view isKindOfClass:[RNTDeepAR class]]) {
      RCTLogError(
          @"Invalid view returned from registry, expecting RNTDeepAR, got: %@",
          view);
    } else {
      [view finishRecording];
    }
  }];
}

RCT_EXPORT_METHOD(setAudioMute
                  : (nonnull NSNumber *)reactTag andEnabled
                  : (BOOL)enabled) {
  [self.bridge.uiManager addUIBlock:^(__unused RCTUIManager *uiManager,
                                      NSDictionary<NSNumber *, RNTDeepAR *>
                                          *viewRegistry) {
    RNTDeepAR *view = viewRegistry[reactTag];
    if (![view isKindOfClass:[RNTDeepAR class]]) {
      RCTLogError(
          @"Invalid view returned from registry, expecting RNTDeepAR, got: %@",
          view);
    } else {
      [view setAudioMute:enabled];
    }
  }];
}

RCT_EXPORT_METHOD(setLiveMode
                  : (nonnull NSNumber *)reactTag andLiveMode
                  : (BOOL)liveMode) {
  [self.bridge.uiManager addUIBlock:^(__unused RCTUIManager *uiManager,
                                      NSDictionary<NSNumber *, RNTDeepAR *>
                                          *viewRegistry) {
    RNTDeepAR *view = viewRegistry[reactTag];
    if (![view isKindOfClass:[RNTDeepAR class]]) {
      RCTLogError(
          @"Invalid view returned from registry, expecting RNTDeepAR, got: %@",
          view);
    } else {
      [view setLiveMode:liveMode];
    }
  }];
}

RCT_EXPORT_METHOD(setFaceDetectionSensitivity
                  : (nonnull NSNumber *)reactTag andLiveMode
                  : (int)sensitivity) {
  [self.bridge.uiManager addUIBlock:^(__unused RCTUIManager *uiManager,
                                      NSDictionary<NSNumber *, RNTDeepAR *>
                                          *viewRegistry) {
    RNTDeepAR *view = viewRegistry[reactTag];
    if (![view isKindOfClass:[RNTDeepAR class]]) {
      RCTLogError(
          @"Invalid view returned from registry, expecting RNTDeepAR, got: %@",
          view);
    } else {
      [view setFaceDetectionSensitivity:sensitivity];
    }
  }];
}

RCT_EXPORT_METHOD(showStats
                  : (nonnull NSNumber *)reactTag andEnabled
                  : (BOOL)enabled) {
  [self.bridge.uiManager addUIBlock:^(__unused RCTUIManager *uiManager,
                                      NSDictionary<NSNumber *, RNTDeepAR *>
                                          *viewRegistry) {
    RNTDeepAR *view = viewRegistry[reactTag];
    if (![view isKindOfClass:[RNTDeepAR class]]) {
      RCTLogError(
          @"Invalid view returned from registry, expecting RNTDeepAR, got: %@",
          view);
    } else {
        [view showStats:enabled];
    }
  }];
}

RCT_EXPORT_METHOD(setTouchMode
                  : (nonnull NSNumber *)reactTag andEnabled
                  : (BOOL)enabled) {
  [self.bridge.uiManager addUIBlock:^(__unused RCTUIManager *uiManager,
                                      NSDictionary<NSNumber *, RNTDeepAR *>
                                          *viewRegistry) {
    RNTDeepAR *view = viewRegistry[reactTag];
    if (![view isKindOfClass:[RNTDeepAR class]]) {
      RCTLogError(
          @"Invalid view returned from registry, expecting RNTDeepAR, got: %@",
          view);
    } else {
        [view setTouchMode:enabled];
    }
  }];
}

RCT_EXPORT_METHOD(changeParameterFloat
                  : (nonnull NSNumber *)reactTag andMaskPath
                  : (NSString *)gameObject andComponent
                  : (NSString *)component andParameter
                  : (NSString *)parameter andFloatValue
                  : (float)floatValue) {
  [self.bridge.uiManager addUIBlock:^(__unused RCTUIManager *uiManager,
                                      NSDictionary<NSNumber *, RNTDeepAR *>
                                          *viewRegistry) {
    RNTDeepAR *view = viewRegistry[reactTag];
    if (![view isKindOfClass:[RNTDeepAR class]]) {
      RCTLogError(
          @"Invalid view returned from registry, expecting RNTDeepAR, got: %@",
          view);
    } else {
        [view changeParameterFloat:gameObject component:component parameter:parameter floatValue:floatValue];
    }
  }];
}

RCT_EXPORT_METHOD(changeParameterVec4
                  : (nonnull NSNumber *)reactTag andMaskPath
                  : (NSString *)gameObject andComponent
                  : (NSString *)component andParameter
                  : (NSString *)parameter andValX
                  : (float)valX andValY
                  : (float)valY andValZ
                  : (float)valZ andValW
                  : (float)valW) {
  [self.bridge.uiManager addUIBlock:^(__unused RCTUIManager *uiManager,
                                      NSDictionary<NSNumber *, RNTDeepAR *>
                                          *viewRegistry) {
    RNTDeepAR *view = viewRegistry[reactTag];
    if (![view isKindOfClass:[RNTDeepAR class]]) {
      RCTLogError(
          @"Invalid view returned from registry, expecting RNTDeepAR, got: %@",
          view);
    } else {
        Vector4 value = {.x = valX, .y = valY, .z = valZ, .w = valW};
        [view changeParameterVec4:gameObject component:component parameter:parameter vectorValue:value];
    }
  }];
}

RCT_EXPORT_METHOD(changeParameterVec3
                  : (nonnull NSNumber *)reactTag andMaskPath
                  : (NSString *)gameObject andComponent
                  : (NSString *)component andParameter
                  : (NSString *)parameter andValX
                  : (float)valX andValY
                  : (float)valY andValZ
                  : (float)valZ) {
  [self.bridge.uiManager addUIBlock:^(__unused RCTUIManager *uiManager,
                                      NSDictionary<NSNumber *, RNTDeepAR *>
                                          *viewRegistry) {
    RNTDeepAR *view = viewRegistry[reactTag];
    if (![view isKindOfClass:[RNTDeepAR class]]) {
      RCTLogError(
          @"Invalid view returned from registry, expecting RNTDeepAR, got: %@",
          view);
    } else {
        Vector3 value = {.x = valX, .y = valY, .z = valZ};
        [view changeParameterVec3:gameObject component:component parameter:parameter vector3Value:value];
    }
  }];
}

RCT_EXPORT_METHOD(changeParameterBool
                  : (nonnull NSNumber *)reactTag andMaskPath
                  : (NSString *)gameObject andComponent
                  : (NSString *)component andParameter
                  : (NSString *)parameter andValue
                  : (bool)value) {
  [self.bridge.uiManager addUIBlock:^(__unused RCTUIManager *uiManager,
                                      NSDictionary<NSNumber *, RNTDeepAR *>
                                          *viewRegistry) {
    RNTDeepAR *view = viewRegistry[reactTag];
    if (![view isKindOfClass:[RNTDeepAR class]]) {
      RCTLogError(
          @"Invalid view returned from registry, expecting RNTDeepAR, got: %@",
          view);
    } else {
        [view changeParameterBool:gameObject component:component parameter:parameter boolValue:value];
    }
  }];
}

RCT_EXPORT_METHOD(changeParameterTexture
                  : (nonnull NSNumber *)reactTag andMaskPath
                  : (NSString *)gameObject andComponent
                  : (NSString *)component andParameter
                  : (NSString *)parameter andValue
                  : (NSString *)value andType
                  : (NSString *)type) {
  [self.bridge.uiManager addUIBlock:^(__unused RCTUIManager *uiManager,
                                      NSDictionary<NSNumber *, RNTDeepAR *>
                                          *viewRegistry) {
    RNTDeepAR *view = viewRegistry[reactTag];
    if (![view isKindOfClass:[RNTDeepAR class]]) {
      RCTLogError(
          @"Invalid view returned from registry, expecting RNTDeepAR, got: %@",
          view);
    } else {
        if([type isEqual: @"URL"]) {
            NSURL * url = [NSURL URLWithString:value];
            NSData * data = [NSData dataWithContentsOfURL:url];
            UIImage * image = [UIImage imageWithData:data];

            [view changeParameterTexture:gameObject component:component parameter:parameter image:image];
        }

        if([type isEqual: @"BASE64"]) {
            NSData *data = [[NSData alloc]initWithBase64EncodedString:value options:NSDataBase64DecodingIgnoreUnknownCharacters];
            UIImage *image = [UIImage imageWithData:data];

            [view changeParameterTexture:gameObject component:component parameter:parameter image:image];
        }

        if([type isEqual: @"PATH"]) {
            UIImage *image = [UIImage imageWithContentsOfFile:value];

            [view changeParameterTexture:gameObject component:component parameter:parameter image:image];
        }
    }
  }];
}

RCT_EXPORT_METHOD(changeParameterString
                  : (nonnull NSNumber *)reactTag andMaskPath
                  : (NSString *)gameObject andComponent
                  : (NSString *)component andParameter
                  : (NSString *)parameter andValue
                  : (NSString *)value) {
  [self.bridge.uiManager addUIBlock:^(__unused RCTUIManager *uiManager,
                                      NSDictionary<NSNumber *, RNTDeepAR *>
                                          *viewRegistry) {
    RNTDeepAR *view = viewRegistry[reactTag];
    if (![view isKindOfClass:[RNTDeepAR class]]) {
      RCTLogError(
          @"Invalid view returned from registry, expecting RNTDeepAR, got: %@",
          view);
    } else {
        [view changeParameterString:gameObject component:component parameter:parameter stringValue:value];
    }
  }];
}

@end
