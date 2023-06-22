/**
 * @file CameraController.h
 * @brief Contains the @link CameraController @endlink helper class that controls the camera device.
 * @copyright Copyright (c) 2021 DeepAR.ai
 */

#import <UIKit/UIKit.h>
#import <AVFoundation/AVFoundation.h>
#import "DeepAR.h"

@class ARView;

/**
 * @brief Helper class that wraps <a href="https://developer.apple.com/documentation/avfoundation?language=objc">AVFoundation</a> to handle camera-related logic like starting camera preview, choosing resolution, front or back camera, and video orientation.
 * @details @link CameraController @endlink works with both @link DeepAR @endlink and @link ARView @endlink implementations, just make sure to set one or the other as a property on @link CameraController @endlink instance. Check Github <a href="https://github.com/DeepARSDK/quickstart-ios-objc">example</a> for detailed usage example.
 */
@interface CameraController : NSObject

/**
 * @brief The @link DeepAR @endlink instance.
 * @details Must be set manually if using @link DeepAR @endlink. See @link init @endlink for more details.
 */
@property (nonatomic, weak) DeepAR* deepAR;

/**
 * @brief The @link ARView @endlink instance.
 * @details Must be set manually if using @link ARView @endlink. See @link init @endlink for more details.
 * @deprecated This API is deprecated. Please assign the @link DeepAR @endlink instance on <i>deepAR</i> property instead.
 */
@property (nonatomic, weak) ARView* arview;

/**
 * @brief The currently selected camera.
 * @details Options:
 * - <i>AVCaptureDevicePositionBack</i>
 * - <i>AVCaptureDevicePositionFront</i>
 * @details Changing this parameter in real-time causes the preview to switch to the given camera device.
 */
@property (nonatomic, assign) AVCaptureDevicePosition position;

/**
 * @brief Represents camera resolution currently used. Can be changed in real-time.
 */
@property (nonatomic, strong) AVCaptureSessionPreset preset;

/**
 * @brief Represents currently used video orientation. Should be called with right orientation when the device rotates.
 */
@property (nonatomic, assign) AVCaptureVideoOrientation videoOrientation;

/**
 * @brief Initializes a new @link CameraController @endlink instance.
 * @details Initialization example:
 * @code
 * ...
 * self.cameraController = [[CameraController alloc] init];
 * self.cameraController.deepAR = self.deepAR;
 * // or if using ARView
 * // self.cameraController.arview = self.arview;
 * [self.cameraController startCamera]; 
 * ...
 * @endcode
 */
- (instancetype)init;

/**
 * @brief Checks camera permissions.
 */
- (void)checkCameraPermission;

/**
 * @brief Checks microphone permissions.
 */
- (void)checkMicrophonePermission;

/**
 * @brief Starts camera preview using <a href="https://developer.apple.com/documentation/avfoundation?language=objc">AVFoundation</a>.
 * @details Checks camera permissions and asks if none has been given. If DeepAR started in rendering mode will render camera frames to the @link ARView @endlink.
 */
- (void)startCamera;

/**
 * @brief Starts camera preview using <a href="https://developer.apple.com/documentation/avfoundation?language=objc">AVFoundation</a>. Allows to start microphone as well.
 * @details Checks camera permissions and asks if none has been given. Additionally, checks for microphone permissions if specified. If DeepAR started in rendering mode, it will render camera frames to the @link ARView @endlink.
 * @param BOOL audio If set to true, camera won't need to reinitialize when starting video recording.
 */
- (void)startCameraWithAudio:(BOOL)audio;

/**
 * @brief Stops camera preview.
 */
- (void)stopCamera;

/**
 * @brief Starts capturing audio samples using <a href="https://developer.apple.com/documentation/avfoundation?language=objc">AVFoundation</a>.
 * @details Checks permissions and asks if none has been given. Must be called if @link DeepAR::startVideoRecordingWithOutputWidth:outputHeight: startVideoRecordingWithOutputWidth @endlink has been called with <i>recordAudio</i> parameter set to true.
 */
- (void)startAudio;

/**
 * @brief Stops capturing audio samples.
 */
- (void)stopAudio;

@end
