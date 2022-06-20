/**
 * @file ARView.h
 * @brief Conatins the @link ARView @endlink DeepAR view class which extends <a href="https://developer.apple.com/documentation/uikit/uiview">UIView</a>.
 * @copyright Copyright (c) 2021 DeepAR.ai
 */

#import <UIKit/UIKit.h>
#import <AVFoundation/AVFoundation.h>
#import "DeepAR.h"

/**
 * @brief @link ARView @endlink is a class that extends <a href="https://developer.apple.com/documentation/uikit/uiview">UIView</a> with all DeepAR features which can be positioned in the UI hierarchy.
 * @details DeepAR will render the result of the processed camera (or static image) frames within this view. @link ARView @endlink will be deprecated in the future releases because DeepAR has API to create custom view where the results are rendered. We keep it for backward compatibility.
 */
@interface ARView : UIView

/**
 * @brief Instance of the @link DeepAR @endlink object.
 */
@property (nonatomic, strong) DeepAR* deepAR;

/**
 * @brief Indicates if @link ARView @endlink and the underlying @link DeepAR @endlink engine are successfully initialized.
 * @details No method should be called on @link ARView @endlink until the initialization is fully finished.
 */
@property (nonatomic, readonly) BOOL initialized;

/**
 * @brief Indicates if at least one face is detected in the current frame.
 */
@property (nonatomic, readonly) BOOL faceVisible;

/**
 * @brief Rendering resolution with which the DeepAR has been initialized.
 */
@property (nonatomic, readonly) CGSize renderingResolution;

/**
 * @brief Set to the object which implements @link DeepARDelegate @endlink protocol to listen for async events coming from DeepAR.
 */
@property (nonatomic, weak) id<DeepARDelegate> delegate;

/**
 * @brief Set the license key for your app.
 * @details The license key is generated on DeepAR Developer portal. Here are steps how to generate license key:
 * - Log in/Sign up to developer.deepar.ai
 * - Create a new project and in that project create an iOS app
 * - In the create app dialog enter your app name and bundle id that your app is using. Bundle id must match the one you are using in your app, otherwise, the license check will fail. Read more about iOS bundle id <a href="https://developer.apple.com/documentation/appstoreconnectapi/bundle_ids">here</a>.
 * - Copy the newly generated license key as a parameter in this method
 * @details You must call this method before you call the @link initialize @endlink.
 * @param NSString* key The license key.
 * @deprecated This API is deprecated. Please use @link DeepAR @endlink method @link DeepAR::setLicenseKey: setLicenseKey @endlink instead.
 */
- (void)setLicenseKey:(NSString*)key;

/**
 * @brief Starts the DeepAR engine initialization.
 * @details @link ARView @endlink is initialized as one would any other iOS view. After instantiating the view, a user needs to call @link initialize @endlink. Other DeepAR methods can be safely called <strong>only when the initialization has properly finished</strong>. Successful initialization is notified via @link DeepARDelegate @endlink @link DeepARDelegate::didInitialize didInitialize @endlink method. Example of a proper @link ARView @endlink initialization:
 * @code
 * - (void)viewDidLoad {
 *     [super viewDidLoad];
 *     // Instantiate ARView and add it to view hierarchy.
 *     self.arview = [[ARView alloc] initWithFrame:[UIScreen mainScreen].bounds];
 *     [self.view insertSubview:self.arview atIndex:0];
 *     // Set delegate handler
 *     self.arview.delegate = self;
 *     [self.arview initialize];
 * }
 * 
 * ...
 * 
 * - (void)didInitialize {
 *    // Other ARView methods are safe to be invoked after this method has been called
 * }
 * @endcode
 * @deprecated This API is deprecated. Please use @link DeepAR @endlink method @link DeepAR::initializeWithWidth:height:window: initializeWithWidth @endlink instead.
 */
- (void)initialize;

/**
 * @brief Resumes the rendering if it was previously paused, otherwise doesn't do anything.
 * @deprecated This API is deprecated. Please use @link DeepAR @endlink method @link DeepAR::resume resume @endlink instead.
 */
- (void)resume;

/**
 * @brief Pauses the rendering.
 * @details This method will not release any resources and should be used only for temporary pause (e.g. user goes to the next screen). Use the @link shutdown @endlink method to stop the engine and to release the resources.
 * @deprecated This API is deprecated. Please use @link DeepAR @endlink method @link DeepAR::pause pause @endlink instead.
 */
- (void)pause;

/**
 * @brief Load a DeepAR Studio file as an effect/filter in the scene.
 * @param NSString* slot The <i>slot</i> specifies a namespace for the effect in the scene. In each slot, there can be only one effect. If you load another effect in the same slot the previous one will be removed and replaced with a new effect. Example of loading 2 effects in the same scene:
 * @code
 * [self.arview switchEffectWithSlot:@"mask" path:"flowers"];
 * [self.arview switchEffectWithSlot:@"filter" path:"tv80"];
 * @endcode
 * @param NSString* path The <i>path</i> is a string path to a file located in the app bundle or anywhere in the filesystem where the app has access to. For example, one can download the filters from online locations and save them in the Documents directory. Value <i>nil</i> for the <i>path</i> param will remove the effect from the scene.
 * @deprecated This API is deprecated. Please use @link DeepAR @endlink method @link DeepAR::switchEffectWithSlot:path: switchEffectWithSlot @endlink instead.
 */
- (void)switchEffectWithSlot:(NSString*)slot path:(NSString*)path;

/**
 * @brief Load a DeepAR Studio file as an effect/filter in the scene.
 * @param NSString* slot The <i>slot</i> specifies a namespace for the effect in the scene. In each slot, there can be only one effect. If you load another effect in the same slot the previous one will be removed and replaced with a new effect.
 * @param NSString* path The <i>path</i> is a string path to a file located in the app bundle or anywhere in the filesystem where the app has access to. For example, one can download the filters from online locations and save them in the Documents directory. Value <i>nil</i> for the <i>path</i> param will remove the effect from the scene.
 * @param uint32_t face The <i>face</i> parameter indicates on which face to apply the effect. DeepAR offers tracking up to 4 faces, so valid values for this parameter are 0, 1, 2, and 3. For example, if you call this method with face value 2, the effect will be only applied to the third detected face in the scene. If you want to set an effect on a different face make sure to also use a different value for the slot parameter to avoid removing the previously added effect. Example: 
 * @code
 * // apply flowers effect to the first face
 * [self.arview switchEffectWithSlot:@"mask_f0" path:"flowers" face:0];
 * // apply beard effect to the second face
 * [self.arview switchEffectWithSlot:@"mask_f1" path:"beard" face:1];
 * // replace the effect on the first face with the lion
 * [self.arview switchEffectWithSlot:@"mask_f0" path:"lion" face:0];
 * // remove the beard effect from the second face
 * [self.arview switchEffectWithSlot:@"mask_f1" path:nil face:1];
 * @endcode
 * @deprecated This API is deprecated. Please use @link DeepAR @endlink method @link DeepAR::switchEffectWithSlot:path:face: switchEffectWithSlot @endlink instead.
 */
- (void)switchEffectWithSlot:(NSString*)slot path:(NSString*)path face:(uint32_t)face;

/**
 * @brief Load a DeepAR Studio file as an effect/filter in the scene.
 * @param NSString* slot The <i>slot</i> specifies a namespace for the effect in the scene. In each slot, there can be only one effect. If you load another effect in the same slot the previous one will be removed and replaced with a new effect.
 * @param NSString* path The <i>path</i> is a string path to a file located in the app bundle or anywhere in the filesystem where the app has access to. For example, one can download the filters from online locations and save them in the Documents directory. Value <i>nil</i> for the <i>path</i> param will remove the effect from the scene.
 * @param uint32_t face The <i>face</i> parameter indicates on which face to apply the effect. DeepAR offers tracking up to 4 faces, so valid values for this parameter are 0, 1, 2, and 3. For example, if you call this method with face value 2, the effect will be only applied to the third detected face in the scene. If you want to set an effect on a different face make sure to also use a different value for the slot parameter to avoid removing the previously added effect.
 * @param NSString* targetGameObject The <i>targetGameObject</i> parameter indicates a node in the currently loaded scene/effect into which the new effect will be loaded. By default, effects are loaded in the root node object.
 * @deprecated This API is deprecated. Please use @link DeepAR @endlink method @link DeepAR::switchEffectWithSlot:path:face:targetGameObject: switchEffectWithSlot @endlink instead.
 */
- (void)switchEffectWithSlot:(NSString*)slot path:(NSString*)path face:(uint32_t)face targetGameObject:(NSString*)targetGameObject;

/**
 * @brief Produces a snapshot of the current screen preview.
 * @details Resolution is equal to the dimension with which the @link ARView @endlink has been initialized. The @link DeepARDelegate @endlink method @link DeepARDelegate::didTakeScreenshot: didTakeScreenshot @endlink will be called upon successful screenshot capture is finished with a path where the image has been temporarily stored.
 * @deprecated This API is deprecated. Please use @link DeepAR @endlink method @link DeepAR::takeScreenshot takeScreenshot @endlink instead.
 */
- (void)takeScreenshot;

/**
 * @brief Starts video recording of the @link ARView @endlink with given <i>outputWidth</i> and <i>outputHeight</i> resolution.
 * @param int outputWidth Output video width.
 * @param int outputHeight Output video height.
 * @deprecated This API is deprecated. Please use @link DeepAR @endlink method @link DeepAR::startVideoRecordingWithOutputWidth:outputHeight: startVideoRecordingWithOutputWidth @endlink instead.
 */
- (void)startVideoRecordingWithOutputWidth:(int)outputWidth outputHeight:(int)outputHeight;

/**
 * @brief Starts video recording of the @link ARView @endlink with given <i>outputWidth</i> and <i>outputHeight</i> resolution.
 * @param int outputWidth Output video width.
 * @param int outputHeight Output video height.
 * @param CGRect subframe The <i>subframe</i> parameter defines the sub rectangle of the @link ARView @endlink that you want to record in normalized coordinates (0.0 - 1.0).
 * @deprecated This API is deprecated. Please use @link DeepAR @endlink method @link DeepAR::startVideoRecordingWithOutputWidth:outputHeight:subframe: startVideoRecordingWithOutputWidth @endlink instead.
 */
- (void)startVideoRecordingWithOutputWidth:(int)outputWidth outputHeight:(int)outputHeight subframe:(CGRect)subframe;

/**
 * @brief Starts video recording of the @link ARView @endlink with given <i>outputWidth</i> and <i>outputHeight</i> resolution.
 * @param int outputWidth Output video width.
 * @param int outputHeight Output video height.
 * @param CGRect subframe The <i>subframe</i> parameter defines the sub rectangle of the @link ARView @endlink that you want to record in normalized coordinates (0.0 - 1.0).
 * @param NSDictionary* videoCompressionProperties The <i>videoCompressionProperties</i> is an <a href="https://developer.apple.com/documentation/foundation/nsdictionary">NSDictionary</a> used as the value for the key <a href="https://developer.apple.com/documentation/avfoundation/avvideocompressionpropertieskey?language=objc">AVVideoCompressionPropertiesKey</a>. Read more about video compression options in the official docs <a href="https://developer.apple.com/documentation/avfoundation/avvideocompressionpropertieskey?language=objc">here</a>.
 * @deprecated This API is deprecated. Please use @link DeepAR @endlink method @link DeepAR::startVideoRecordingWithOutputWidth:outputHeight:subframe:videoCompressionProperties: startVideoRecordingWithOutputWidth @endlink instead.
 */
- (void)startVideoRecordingWithOutputWidth:(int)outputWidth outputHeight:(int)outputHeight subframe:(CGRect)subframe videoCompressionProperties:(NSDictionary*)videoCompressionProperties;

/**
 * @brief Starts video recording of the @link ARView @endlink with given <i>outputWidth</i> and <i>outputHeight</i> resolution.
 * @param int outputWidth Output video width.
 * @param int outputHeight Output video height.
 * @param CGRect subframe The <i>subframe</i> parameter defines the sub rectangle of the @link ARView @endlink that you want to record in normalized coordinates (0.0 - 1.0).
 * @param NSDictionary* videoCompressionProperties The <i>videoCompressionProperties</i> is an <a href="https://developer.apple.com/documentation/foundation/nsdictionary">NSDictionary</a> used as the value for the key <a href="https://developer.apple.com/documentation/avfoundation/avvideocompressionpropertieskey?language=objc">AVVideoCompressionPropertiesKey</a>. Read more about video compression options in the official docs <a href="https://developer.apple.com/documentation/avfoundation/avvideocompressionpropertieskey?language=objc">here</a>.
 * @param BOOL recordAudio If <i>recordAudio</i> parameter is set to true the recording will wait until you call @link enqueueAudioSample @endlink on @link ARView @endlink. When DeepAR is ready to receive audio samples it will publish <a href="https://developer.apple.com/documentation/foundation/nsnotification?language=objc">NSNotification</a> with key <i>deepar_start_audio</i>. You can subscribe to this notification and start feeding audio samples once you receive it. If you use provided @link CameraController @endlink this is handled for you by default.
 * @deprecated This API is deprecated. Please use @link DeepAR @endlink method @link DeepAR::startVideoRecordingWithOutputWidth:outputHeight:subframe:videoCompressionProperties:recordAudio: startVideoRecordingWithOutputWidth @endlink instead.
 */
- (void)startVideoRecordingWithOutputWidth:(int)outputWidth outputHeight:(int)outputHeight subframe:(CGRect)subframe videoCompressionProperties:(NSDictionary*)videoCompressionProperties recordAudio:(BOOL)recordAudio;

/**
 * @brief Finishes the video recording.
 * @details Delegate method @link DeepARDelegate::didFinishVideoRecording: didFinishVideoRecording @endlink will be called when the recording is done with the temporary path of the recorded video.
 * @deprecated This API is deprecated. Please use @link DeepAR @endlink method @link DeepAR::finishVideoRecording finishVideoRecording @endlink instead.
 */
- (void)finishVideoRecording;

/**
 * @brief Pauses video recording.
 * @deprecated This API is deprecated. Please use @link DeepAR @endlink method @link DeepAR::pauseVideoRecording pauseVideoRecording @endlink instead.
 */
- (void)pauseVideoRecording;

/**
 * @brief Resumes video recording after it has been paused with @link pauseVideoRecording @endlink.
 * @deprecated This API is deprecated. Please use @link DeepAR @endlink method @link DeepAR::resumeVideoRecording resumeVideoRecording @endlink instead.
 */
- (void)resumeVideoRecording;

/**
 * @brief Enables or disables audio pitch processing for video recording.
 * @param BOOL enabled Enable audio processing.
 * @deprecated This API is deprecated. Please use @link DeepAR @endlink method @link DeepAR::enableAudioProcessing: enableAudioProcessing @endlink instead.
 */
- (void)enableAudioProcessing:(BOOL)enabled;

/**
 * @brief Sets the pitch change amount.
 * @details Negative values will make the recorded audio lower in pitch and positive values will make it higher in pitch. Must call @link enableAudioProcessing @endlink to enable the pitch processing beforehand.
 * @param float sts The pitch change amount.
 * @deprecated This API is deprecated. Please use @link DeepAR @endlink method @link DeepAR::setAudioProcessingSemitone: setAudioProcessingSemitone @endlink instead.
 */
- (void)setAudioProcessingSemitone:(float)sts;

/**
 * @brief Shuts down the DeepAR engine.
 * @details This method should be called when the @link ARView @endlink parent view controller has been disposed of. Reinitialization of a new DeepAR instance which has not been properly shut down can cause crashes and memory leaks. Usually, it is done in view controllers <i>dealloc</i> method, example:
 * @code
 * -(void)dealloc {
 *     [self.deepAR shutdown];
 *     [self.arview removeFromSuperview];
 * }
 * @endcode
 * @deprecated This API is deprecated. Please use @link DeepAR @endlink method @link DeepAR::shutdown shutdown @endlink instead.
 */
- (void)shutdown;

/**
 * @brief Enables @link DeepARDelegate::frameAvailable: frameAvailable @endlink method callback.
 * @details By default @link DeepARDelegate @endlink will not call @link DeepARDelegate::frameAvailable: frameAvailable @endlink method on each new processed frame to save on processing time and resources. If we want the processed frames to be available in @link DeepARDelegate::frameAvailable: frameAvailable @endlink method of @link DeepARDelegate @endlink we need to call this method first on @link ARView @endlink.
 * @param int outputWidth The width of the processed frames.
 * @param int outputHeight The height of the processed frames.
 * @param CGRect subframe The subrectangle of @link ARView @endlink which will be outputted. This means that the output frame in @link DeepARDelegate::frameAvailable: frameAvailable @endlink does not need to be the same size and/or position as the one rendered to the @link ARView ARView @endlink.
 * @deprecated This API is deprecated. Please use @link DeepAR @endlink method @link DeepAR::startCaptureWithOutputWidth:outputHeight:subframe: startCaptureWithOutputWidth @endlink instead.
 */
- (void)startFrameOutputWithOutputWidth:(int)outputWidth outputHeight:(int)outputHeight subframe:(CGRect)subframe;

/**
 * @brief Stops outputting frames to @link DeepARDelegate::frameAvailable: frameAvailable @endlink.
 * @deprecated This API is deprecated. Please use @link DeepAR @endlink method @link DeepAR::stopCapture stopCapture @endlink instead.
 */
- (void)stopFrameOutput;

/**
 * @brief Enqueues an image frame for processing to DeepAR.
 * @details The processed frame will be rendered in @link ARView @endlink. Additionally if @link DeepARDelegate @endlink is set the same frame will be available in @link DeepARDelegate::frameAvailable: frameAvailable @endlink delegate method when ready (and @link startFrameOutputWithOutputWidth @endlink is called).
 * @param CMSampleBufferRef sampleBuffer The camera frame.
 * @param BOOL mirror If <i>mirror</i> is set to true the image frame will be flipped vertically before processing (e.g. depending if you use back or front camera).
 * @deprecated This API is deprecated. Please use @link DeepAR @endlink method @link DeepAR::enqueueCameraFrame:mirror: enqueueCameraFrame @endlink instead.
 */
- (void)enqueueCameraFrame:(CMSampleBufferRef)sampleBuffer mirror:(BOOL)mirror;

/**
 * @brief Passes an audio sample to the DeepAR engine.
 * @details Used in video recording when user wants to record audio too. Audio samples will be processed only if the @link startVideoRecording @endlink method has been called with <i>recordAudio</i> parameter set to true.
 * @param CMSampleBufferRef sampleBuffer The audio sample.
 * @deprecated This API is deprecated. Please use @link DeepAR @endlink method @link DeepAR::enqueueAudioSample: enqueueAudioSample @endlink instead.
 */
- (void)enqueueAudioSample:(CMSampleBufferRef)sampleBuffer;

/**
 * @brief Changes a node or component float parameter.
 * @details For more details about changeParameter API read our article <a href="https://help.deepar.ai/en/articles/3732006-changing-filter-parameters-from-code">here</a>.
 * @param NSString* gameObject The name of the node. If multiple nodes share the same name, only the first one will be affected.
 * @param NSString* component The name of the component. If the name of the component is null or an empty string, the node itself will be affected.
 * @param NSString* parameter The name of the parameter.
 * @param float value New parameter value.
 * @deprecated This API is deprecated. Please use @link DeepAR @endlink method @link DeepAR::changeParameter:component:parameter:floatValue: changeParameter @endlink instead.
 */
- (void)changeParameter:(NSString*)gameObject component:(NSString*)component parameter:(NSString*)parameter floatValue:(float)value;

/**
 * @brief Changes a node or component 4D vector parameter.
 * @details For more details about changeParameter API read our article <a href="https://help.deepar.ai/en/articles/3732006-changing-filter-parameters-from-code">here</a>.
 * @param NSString* gameObject The name of the node. If multiple nodes share the same name, only the first one will be affected.
 * @param NSString* component The name of the component. If the name of the component is null or an empty string, the node itself will be affected.
 * @param NSString* parameter The name of the parameter.
 * @param Vector4 value New parameter value.
 * @deprecated This API is deprecated. Please use @link DeepAR @endlink method @link DeepAR::changeParameter:component:parameter:vectorValue: changeParameter @endlink instead.
 */
- (void)changeParameter:(NSString*)gameObject component:(NSString*)component parameter:(NSString*)parameter vectorValue:(Vector4)value;

/**
 * @brief Changes a node or component 3D vector parameter.
 * @details For more details about changeParameter API read our article <a href="https://help.deepar.ai/en/articles/3732006-changing-filter-parameters-from-code">here</a>.
 * @param NSString* gameObject The name of the node. If multiple nodes share the same name, only the first one will be affected.
 * @param NSString* component The name of the component. If the name of the component is null or an empty string, the node itself will be affected.
 * @param NSString* parameter The name of the parameter.
 * @param Vector3 value New parameter value.
 * @deprecated This API is deprecated. Please use @link DeepAR @endlink method @link DeepAR::changeParameter:component:parameter:vector3Value: changeParameter @endlink instead.
 */
- (void)changeParameter:(NSString*)gameObject component:(NSString*)component parameter:(NSString*)parameter vector3Value:(Vector3)value;

/**
 * @brief Changes a node or component boolean parameter.
 * @details For more details about changeParameter API read our article <a href="https://help.deepar.ai/en/articles/3732006-changing-filter-parameters-from-code">here</a>.
 * @param NSString* gameObject The name of the node. If multiple nodes share the same name, only the first one will be affected.
 * @param NSString* component The name of the component. If the name of the component is null or an empty string, the node itself will be affected.
 * @param NSString* parameter The name of the parameter.
 * @param bool value New parameter value.
 * @deprecated This API is deprecated. Please use @link DeepAR @endlink method @link DeepAR::changeParameter:component:parameter:boolValue: changeParameter @endlink instead.
 */
- (void)changeParameter:(NSString*)gameObject component:(NSString*)component parameter:(NSString*)parameter boolValue:(bool)value;

/**
 * @brief Changes a node or component image parameter.
 * @details For more details about changeParameter API read our article <a href="https://help.deepar.ai/en/articles/3732006-changing-filter-parameters-from-code">here</a>.
 * @param NSString* gameObject The name of the node. If multiple nodes share the same name, only the first one will be affected.
 * @param NSString* component The name of the component. If the name of the component is null or an empty string, the node itself will be affected.
 * @param NSString* parameter The name of the parameter.
 * @param UIImage* image New image parameter.
 * @deprecated This API is deprecated. Please use @link DeepAR @endlink method @link DeepAR::changeParameter:component:parameter:image: changeParameter @endlink instead.
 */
- (void)changeParameter:(NSString*)gameObject component:(NSString*)component parameter:(NSString*)parameter image:(UIImage*)image;

/**
 * @brief Fire named trigger of an fbx animation set on the currently loaded effect.
 * @details To learn more about fbx and image sequence animations on DeepAR please read our article <a href="https://help.deepar.ai/en/articles/4354740-animations-tutorial-fbx-model-animations">here</a>.
 * @param NSString* trigger The trigger name.
 * @deprecated This API is deprecated. Please use @link DeepAR @endlink method @link DeepAR::fireTrigger: fireTrigger @endlink instead.
 */
- (void)fireTrigger:(NSString*)trigger;

/**
 * @brief This method allows the user to change face detection sensitivity.
 * @param int sensitivity The <i>sensitivity</i> parameter can range from 0 to 3, where 0 is the fastest but might not recognize smaller (further away) faces, and 3 is the slowest but will find smaller faces. By default, this parameter is set to 1.
 * @deprecated This API is deprecated. Please use @link DeepAR @endlink method @link DeepAR::setFaceDetectionSensitivity: setFaceDetectionSensitivity @endlink instead.
 */
- (void)setFaceDetectionSensitivity:(int)sensitivity;

/**
 * @brief Display debugging stats on screen.
 * @param bool enabled Enable debugging stats.
 * @deprecated This API is deprecated. Please use @link DeepAR @endlink method @link DeepAR::showStats: showStats @endlink instead.
 */
- (void)showStats:(bool)enabled;

/**
 * @brief Sets the internal SDK parameter.
 * @param NSString* key The parameter key.
 * @param NSString* value The parameter value.
 * @deprecated This API is deprecated. Please use @link DeepAR @endlink method @link DeepAR::setParameterWithKey:value: setParameterWithKey @endlink instead.
 */
- (void)setParameterWithKey:(NSString*)key value:(NSString*)value;
@end

#import "ARView.h"
#import "CameraController.h"
