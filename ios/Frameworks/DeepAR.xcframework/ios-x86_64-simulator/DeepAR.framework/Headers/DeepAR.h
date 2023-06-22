/**
 * @file DeepAR.h
 * @brief Conatins the main DeepAR classes, structures and enumerations.
 * @copyright Copyright (c) 2021 DeepAR.ai
 */

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <AVFoundation/AVFoundation.h>

/**
 * @brief Represents data structure containing all the information available about the detected face.
 */
typedef struct {
    /**
     * @brief Determines whether the face is detected or not.
     */
    BOOL detected;
    /**
     * @brief The X, Y and Z translation values of the face in the scene.
     */
    float translation[3];
    /**
     * @brief The pitch, yaw and roll rotation values in euler angles (degrees) of the face in the scene.
     */
    float rotation[3];
    /**
     * @brief Translation and rotation in matrix form (D3D style, column-major order).
     */
    float poseMatrix[16];
    /**
     * @brief Detected face feature points in 3D space (X, Y, Z). Read more <a href="https://help.deepar.ai/en/articles/4351347-deepar-reference-tracking-models">here</a>.
     */
    float landmarks[68 * 3];
    /**
     * @brief Detected face feature points in 2D screen space coordinates (X, Y).
     * @details Usually more precise than 3D points but no estimation for Z translation. Read more here about feature points <a href="https://help.deepar.ai/en/articles/4351347-deepar-reference-tracking-models">here</a>.
     */
    float landmarks2d[68 * 3]; // TODO: *3 is definitely a typo; fix and test
    /**
     * @brief A rectangle containing the face in screen coordinates (X, Y, Width, Height).
     */
    float faceRect[4];
    /**
     * @brief Estimated emotions for the face.
     * @details Each emotion has a value in [0.0, 1.0] range. The 1.0 value means 100% detected emotion.
     * @details We differentiate 5 different emotions:
     * - Index 0 is neutral
     * - Index 1 is happiness
     * - Index 2 is surprise
     * - Index 3 is sadness
     * - Index 4 is anger
     */
    float emotions[5];
    /**
     * @brief The array of action units.
     */
    float actionUnits[63]; // TODO: discover more
    /**
     * @brief The number of action units.
     */
    int numberOfActionUnits; // TODO: discover more
} FaceData;

/**
 * @brief Structure containing face data for up to 4 detected faces.
 */
typedef struct {
    /**
     * @brief Array of face data for up to 4 detected faces.
     */
    FaceData faceData[4];
} MultiFaceData;

/**
 * @brief The video (and audio) recording configuration.
 */
typedef struct {
    /**
     * @brief The output video width.
     */
    NSInteger outputWidth;
    /**
     * @brief The output video height.
     */
    NSInteger outputHeight;
    /**
     * @brief The sub rectangle of the @link ARView @endlink that you want to record in normalized coordinates (0.0 - 1.0).
     */
    CGRect subframe;
    /**
     * @brief An <a href="https://developer.apple.com/documentation/foundation/nsdictionary?language=objc">NSDictionary</a> used as the value for the key <a href="https://developer.apple.com/documentation/avfoundation/avvideocompressionpropertieskey?language=objc">AVVideoCompressionPropertiesKey</a>. Read more about video compression options in the official docs <a href="https://developer.apple.com/documentation/avfoundation/avvideocompressionpropertieskey?language=objc">here</a>.
     */
    NSDictionary* videoCompressionProperties;
    /**
     * @brief Determine whether audio is recorded or not.
     */
    BOOL recordAudio;
} RecordingConfig;

/**
 * @brief A four-dimensional float vector.
 */
typedef struct {
    /**
     * @brief X value.
     */
    float x;
    /**
     * @brief Y value.
     */
    float y;
    /**
     * @brief Z value.
     */
    float z;
    /**
     * @brief W value.
     */
    float w;
} Vector4;

/**
 * @brief A three-dimensional float vector.
 */
typedef struct {    
    /**
     * @brief X value.
     */
    float x;
    /**
     * @brief Y value.
     */
    float y;
    /**
     * @brief Z value.
     */
    float z;
} Vector3;

/**
 * @brief Output color format.
 */
typedef enum
{
    /**
     * @brief Undefined format.
     */
    Undefined, // 0
    /**
     * @brief Red, green, blue and alpha format.
     */
    RGBA,      // 1
    /**
     * @brief Blue, green, red and alpha format.
     */
    BGRA,      // 2
    /**
     * @brief Alpha, red, green and blue format.
     */
    ARGB,      // 3
    /**
     * @brief Alpha, blue, green and red format.
     */
    ABGR,      // 4
    /**
     * @brief Number of formats.
     */
    COUNT
} OutputFormat;

/**
 * @brief DeepAR error types.
 */
typedef enum {
    /**
     * @brief DeepAR debug type.
     */
    DEEPAR_ERROR_TYPE_DEBUG,
    /**
     * @brief DeepAR info type.
     */
    DEEPAR_ERROR_TYPE_INFO,
    /**
     * @brief DeepAR warning type.
     */
    DEEPAR_ERROR_TYPE_WARNING,
    /**
     * @brief DeepAR error type.
     */
    DEEPAR_ERROR_TYPE_ERROR
} ARErrorType;

/**
 * @brief Possible types of an occurred touch.
 */
typedef enum {
    /**
     * @brief Touch type that implies that a touch was started.
     */
    START,
    /**
     * @brief Touch type that implies that a previously started touch changed.
     */
    MOVE,
    /**
     * @brief Touch type that implies that a previously started touch ended.
     */
    END
} TouchType;

/**
 * @brief Possible variable types.
 */
typedef enum {
    /**
     * @brief Bool variable type.
     */
    BOOLEAN = 0,
    /**
     * @brief Integer variable type.
     */
    INT = 1,
    /**
     * @brief Double variable type.
     */
    DOUBLE = 2,
    /**
     * @brief String variable type.
     */
    STRING = 3
} VarType;

/**
 * @brief Contains information about the current location and status of the started touch.
 */
typedef struct {
    /**
     * @brief Value of the x coordinate of the current touch location.
     */
    CGFloat x;
    /**
     * @brief Value of the y coordinate of the current touch location.
     */
    CGFloat y;
    /**
     * @brief The status, i.e., touch type, of the touch.
     */
    TouchType type;
} TouchInfo;

typedef struct {
    /**
     * Engine will initialize face tracking as soon as possible if true.
     * Else it will initialize when face tracking when it is needed. Eg. when loading effect that uses face tracking.
     */
    bool initializeEngineWithFaceTracking;

    /**
     * If true, face tracking will be initialized synchronously and will be blocking DeepAR rendering.
     * Else it will initialize in background thread and not block rendering.
     */
    bool initializeFaceTrackingSynchronously;
} FaceTrackingInitParameters;

/**
 * @brief A delegate that is used to notify events from DeepAR to the consumer of the DeepAR SDK.
 * @details It is set on @link DeepAR @endlink or @link ARView @endlink.
 */
@protocol DeepARDelegate <NSObject>

@optional

/**
 * @brief Called when DeepAR has finished taking a screenshot.
 * @details The result is given as an <a href="https://developer.apple.com/documentation/uikit/uiimage">UIImage</a> object in the <i>screenshot</i> parameter.
 * @param UIImage* screenshot The taken screenshot.
 */
- (void)didTakeScreenshot:(UIImage*)screenshot;

/**
 * @brief Called when the DeepAR engine initialization is complete.
 */
- (void)didInitialize;

/**
 * @brief Called when DeepAR detects a new face or loses a face that has been tracked.
 * @param BOOL faceVisible Any face visibility.
 */
- (void)faceVisiblityDidChange:(BOOL)faceVisible;

/**
 * @brief Called when a new processed frame is available.
 * @details Make sure to call @link DeepAR::startCaptureWithOutputWidth:outputHeight:subframe: startCaptureWithOutputWidth @endlink on @link DeepAR @endlink (or @link ARView::startFrameOutputWithOutputWidth:outputHeight:subframe: startFrameOutputWithOutputWidth @endlink if you use @link ARView @endlink) if you want this method to be called whenever a new frame is ready.
 * @param CMSampleBufferRef sampleBuffer New frame.
 */
- (void)frameAvailable:(CMSampleBufferRef)sampleBuffer;

/**
 * @brief Called on each frame where at least one face data is detected.
 * @param MultiFaceData faceData The face data.
 */
- (void)faceTracked:(MultiFaceData)faceData;

/**
 * @brief Whenever a face is detected or lost from the scene this method is called.
 * @param NSInteger facesVisible The number of currently detected faces in the frame.
 */
- (void)numberOfFacesVisibleChanged:(NSInteger)facesVisible;

/**
 * @brief DeepAR has successfully shut down after the method shutdown call.
 */
- (void)didFinishShutdown;

/**
 * @brief DeepAR has the ability to track arbitrary images in the scene.
 * @param NSString* gameObjectName The name of the node in the filter file to which the image is associated.
 * @param BOOL imageVisible New visibility.
 */
- (void)imageVisibilityChanged:(NSString*)gameObjectName imageVisible:(BOOL)imageVisible; // TODO: explore further

/**
 * @brief Called when the @link DeepAR::switchEffectWithSlot:path: switchEffect @endlink method has successfully switched given effect on a given slot.
 * @param NSString* slot The slot name.
 */
- (void)didSwitchEffect:(NSString*)slot;

/**
 * @brief Called when the conditions have been met for the animation to transition to the next state (e.g. mouth open, emotion detected etc.).
 * @param NSString* state The state name.
 */
- (void)animationTransitionedToState:(NSString*)state;

/**
 * @brief Called when DeepAR has started video recording (after calling @link DeepAR::startVideoRecordingWithOutputWidth:outputHeight: startVideoRecording @endlink method).
 */
- (void)didStartVideoRecording;

/**
 * @brief Called when the video recording preparation is finished.
 */
- (void)didFinishPreparingForVideoRecording;

/**
 * @brief Called when the video recording is finished.
 * @param NSString* videoFilePath The video file path.
 */
- (void)didFinishVideoRecording:(NSString*)videoFilePath;

/**
 * @brief Called when an error has occurred during video recording.
 * @param NSError* error The video recording error.
 */
- (void)recordingFailedWithError:(NSError*)error;

/**
 * @brief Called when an error has occurred.
 * @param ARErrorType code Error type.
 * @param NSString* error Error message.
 */
- (void)onErrorWithCode:(ARErrorType)code error:(NSString*)error;

@end

#define ARViewDelegate DeepARDelegate

/**
 * @brief Main class for interacting with DeepAR engine.
 * @details You need to create an instance of this class to interact with DeepAR. DeepAR can work in vision only or rendering mode. Vision only means only computer vision functionalities (like @link FaceData @endlink of detected faces etc.) are available and no rendering. Rendering mode means that result of DeepAR processing will be rendered live in the UI. Different initialization methods are used for each mode.
 */
@interface DeepAR : NSObject

/**
 * @brief The object which implements @link DeepARDelegate @endlink protocol to listen for async events coming from DeepAR.
 */
@property (nonatomic, weak) id<DeepARDelegate> delegate;

/**
 * @brief Indicates if computer vision components have been initialized during the initialization process.
 */
@property (nonatomic, readonly) BOOL visionInitialized;

/**
 * @brief Indicates if DeepAR rendering components have been initialized during the initialization process.
 */
@property (nonatomic, readonly) BOOL renderingInitialized;

/**
 * @brief Indicates if at least one face is detected in the current frame.
 */
@property (nonatomic, readonly) BOOL faceVisible;

/**
 * @brief Rendering resolution with which the DeepAR has been initialized.
 */
@property (nonatomic, readonly) CGSize renderingResolution;

/**
 * @brief If set to true, changes how @link DeepAR::startVideoRecordingWithOutputWidth:outputHeight: startVideoRecording @endlink and @link resumeVideoRecording @endlink methods work to allow the video recording to be started immediately during runtime
 * @details To use video recodring warmup follow these steps
 * - Set videoRecordingWarmupEnabled = true after calling deepar.initialize
 * @code
 * - (void)viewDidLoad {
 *  self.deepAR = [[DeepAR alloc] init];
 *  self.deepAR.videoRecordingWarmupEnabled = YES;
 * ...
 * }
 * @endcode
 * - After initialization is finished (@link DeepARDelegate::didInitialize didInitialize @endlink callback) call @link DeepAR::startVideoRecordingWithOutputWidth:outputHeight: startVideoRecording @endlink with desired parameters. Only needs to be called once.
 * @code
 * - (void)didInitialize {
 *     [self.deepAR startVideoRecordingWithOutputWidth:outputWidth outputHeight:outputHeight subframe:screenRect];
 *  }
 *  @endcode
 * - Wait for @link DeepARDelegate::didFinishPreparingForVideoRecording didFinishPreparingForVideoRecording @endlink callback (now working as expected) to enable recording
 * - Call @link resumeVideoRecording @endlink to start prepared recording
 * @code
 *  - (IBAction)startVideoRecordingPressed:(id)sender {
 *     // Start prepared recording
 *     [self.deepAR resumeVideoRecording];
 * }
 * @endcode
 *
 * - Call @link finishVideoRecording @endlink to finish recording. This will automatically start preparing for the next recording session with the parameters set in @link DeepAR::startVideoRecordingWithOutputWidth:outputHeight: startVideoRecording @endlink.
 * @code
 * - (IBAction)stopVideoRecordingPressed:(id)sender {
 *    //Finish recording. This will automatically start preparing for the next recording session with the same parameters
 *     [self.deepAR finishVideoRecording];
 * }
 * @endcode
 * - Wait for @link DeepARDelegate::didFinishPreparingForVideoRecording didFinishPreparingForVideoRecording @endlink callback and repeat the resumeVideoRecording step as needed
 */
@property (nonatomic, assign) BOOL videoRecordingWarmupEnabled;

/**
 * @brief The audio compression settings.
 */
@property (nonatomic, strong) NSDictionary* audioCompressionSettings;

/**
 * @brief The DeepAR SDK version number.
 * @return DeepAR SDK version number string.
 */
+ (NSString*) sdkVersion;

/**
 * @brief Set the license key for your app.
 * @details The license key is generated on the DeepAR Developer portal. Here are steps on how to generate a license key:
 * - Log in/Sign up to developer.deepar.ai
 * - Create a new project and in that project create an iOS app
 * - In the create app dialog enter your app name and bundle id that your app is using. Bundle id must match the one you are using in your app, otherwise, the license check will fail. Read more about iOS bundle id <a href="https://developer.apple.com/documentation/appstoreconnectapi/bundle_ids">here</a>.
 * - Copy the newly generated license key as a parameter in this method
 * @details You must call this method before you call the @link initialize @endlink.
 * @param NSString* key The license key.
 */
- (void)setLicenseKey:(NSString*)key;

/**
 * @brief Starts the engine initialization where the DeepAR will initialize in rendering mode.
 * @details This means users can use the rendering functionality of DeepAR, in addition to computer vision features, to load effects in the scene, render the frames in the UI, etc.
 * @param NSInteger width The rendering width.
 * @param NSInteger height The rendering height.
 * @param CAEAGLLayer* window Destination layer where the DeepAR engine will render the frames.
 */
- (void)initializeWithWidth:(NSInteger)width height:(NSInteger)height window:(CAEAGLLayer*)window;

/**
 * @brief Starts the engine initialization where the DeepAR will initialize in vision only mode.
 * @details Vision only means that it will process frames in terms of detecting faces and their properties that are available in @link FaceData @endlink object. No rendering will be available in this mode.
 */
- (void)initialize;

/**
 * @brief Starts the engine initialization for rendering in off-screen mode.
 * @param NSInteger width The rendering width.
 * @param NSInteger height The rendering height.
 */
- (void)initializeOffscreenWithWidth:(NSInteger)width height:(NSInteger)height;

/**
 * @brief Starts the engine initialization where the DeepAR will initialize in rendering mode.
 * @details This means users can use the rendering functionality of DeepAR, in addition to computer vision features, to load effects in the scene, render the frames in the UI, etc. This method returns an <a href="https://developer.apple.com/documentation/uikit/uiview">UIView</a> on which surface the frames will be rendered. Internally this method uses @link initializeWithWidth:height:window: initializeWithWidth @endlink, which means the rendering resolution and the size of the view will be the size of the provided frame.
 * @param CGRect frame The view dimensions.
 * @return UIView* The surface where the DeepAR frames will be rendered.
 */
- (UIView*)createARViewWithFrame:(CGRect)frame;

/**
 * @brief Indicates if DeepAR has been initialized in the vision-only mode or not.
 * @return BOOL Indication if the vision-only mode is active.
 */
- (BOOL)isVisionOnly;

/**
 * @brief Changes the output resolution of the processed frames.
 * @details Can be called any time.
 * @param NSInteger width The output resolution width.
 * @param NSInteger height The output resolution height.
 */
- (void)setRenderingResolutionWithWidth:(NSInteger)width height:(NSInteger)height;

/**
 * @brief Shuts down the DeepAR engine.
 * @details Reinitialization of a new DeepAR instance which has not been properly shut down can cause crashes and memory leaks. Usually, it is done in view controller <i>dealloc</i> method.
 */
- (void)shutdown;

/**
 * @brief Returns new <a href="https://developer.apple.com/documentation/uikit/uiview">UIView</a> in which DeepAR will render with a given frame size.
 * @details User can position the returned <a href="https://developer.apple.com/documentation/uikit/uiview">UIView</a> in the hierarchy to display the results in the app UI.
 * @param CGRect frame The frame size.
 * @return UIView* The new <a href="https://developer.apple.com/documentation/uikit/uiview">UIView</a> in which DeepAR will render with a given frame size.
 */
- (UIView*)switchToRenderingToViewWithFrame:(CGRect)frame;

/**
 * @brief Starts rendering in the off-screen buffer.
 * @details Does nothing if already rendering in off-screen mode. Internally calls @link startCaptureWithOutputWidth:outputHeight:subframe: startCaptureWithOutputWidth @endlink method meaning the frames will be available in the @link DeepARDelegate:frameAvailable: frameAvailable @endlink method as soon as they are ready.
 * @param NSInteger width The buffer width.
 * @param NSInteger height The buffer height.
 */
- (void)switchToRenderingOffscreenWithWidth:(NSInteger)width height:(NSInteger)height;

/**
 * @brief An optimization method and it allows the user to indicate the DeepAR in which mode it should operate.
 * @details If called with true value, DeepAR will expect a continuous flow of new frames and it will optimize its inner processes for such workload. An example of this is the typical use case of processing the frames from the camera stream.
 * @details If called with false it will optimize for preserving resources and memory by pausing the rendering after each processed frame. A typical use case for this is when the user needs to process just one image. In that case, the user will feed the image to DeepAR by calling @link processFrame:mirror: processFrame @endlink or similar method, and DeepAR would process it and stop rendering until a new frame is received. If we did so when the DeepAR is in live mode, it would process the same frame over and over again without ever stopping the rendering process, thus wasting processing time.
 * @param BOOL liveMode Enable or disable live mode.
 */
- (void)changeLiveMode:(BOOL)liveMode;

/**
 * @brief Resumes the rendering if it was previously paused, otherwise doesn't do anything.
 */
- (void)resume;

/**
 * @brief Pauses the rendering.
 * @details This method will not release any resources and should be used only for temporary pause (e.g. user goes to the next screen). Use the @link shutdown @endlink method to stop the engine and to release the resources. 
 */
- (void)pause;

/**
 * @brief Feed frame to DeepAR for processing.
 * @details The result can be received in the @link DeepARDelegate::frameAvailable: frameAvailable @endlink delegate method.
 * @param CVPixelBufferRef imageBuffer The input image data that needs processing.
 * @param BOOL mirror Indicates whether the image should be flipped vertically before processing (front/back camera).
 */
- (void)processFrame:(CVPixelBufferRef)imageBuffer mirror:(BOOL)mirror;

/**
 * @brief Feed frame to DeepAR for processing.
 * @details The result can be received in the @link DeepARDelegate::frameAvailable: frameAvailable @endlink delegate method.
 * @param CVPixelBufferRef imageBuffer The input image data that needs processing.
 * @param BOOL mirror Indicates whether the image should be flipped vertically before processing (front/back camera).
 * @param CMTimeValue timestamp The frame timestamp.
 */
- (void)processFrame:(CVPixelBufferRef)imageBuffer mirror:(BOOL)mirror timestamp:(CMTimeValue)timestamp;

/**
 * @brief Feed frame to DeepAR for processing.
 * @details Outputs the result in the <i>outputBuffer</i> parameter. Requires frame capturing to be started (user must call @link startCaptureWithOutputWidth:outputHeight:subframe: startCaptureWithOutputWidth @endlink or @link startCaptureWithOutputWidthAndFormat:outputHeight:subframe:outputImageFormat: startCaptureWithOutputWidthAndFormat @endlink beforehand).
 * @param CVPixelBufferRef imageBuffer The input image data that needs processing.
 * @param CVPixelBufferRef outputBuffer The output image buffer.
 * @param BOOL mirror Indicates whether the image should be flipped vertically before processing (front/back camera).
 */
- (void)processFrameAndReturn:(CVPixelBufferRef)imageBuffer outputBuffer:(CVPixelBufferRef)outputBuffer mirror:(BOOL)mirror;

/**
 * @brief Same functionality as @link processFrame:mirror: processFrame @endlink with <a href="https://developer.apple.com/documentation/coremedia/cmsamplebufferref">CMSampleBufferRef</a> as an input type for frame data which is more suitable if using camera frames via <a href="https://developer.apple.com/documentation/avfoundation?language=objc">AVFoundation</a>.
 * @details It is advised to use this method instead of @link processFrame:mirror: processFrame @endlink when using camera frames as input because it will use native textures to fetch frames from the iPhone camera more efficiently.
 * @param CMSampleBufferRef sampleBuffer The sample buffer.
 * @param BOOL mirror Indicates whether the image should be flipped vertically before processing (front/back camera).
 */
- (void)enqueueCameraFrame:(CMSampleBufferRef)sampleBuffer mirror:(BOOL)mirror;

/**
 * @brief Passes an audio sample to the DeepAR engine.
 * @details Used in video recording when user wants to record audio too. Audio samples will be processed only if the @link startCaptureWithOutputWidth:outputHeight:subframe: startVideoRecordingWithOutputWidth @endlink method has been called with <i>recordAudio</i> parameter set to true.
 * @param CMSampleBufferRef sampleBuffer The sample buffer.
 */
- (void)enqueueAudioSample:(CMSampleBufferRef)sampleBuffer;

/**
 * @brief Sets the video recording file output name.
 * @details The argument is file name only, no extension. The file extension <i>.mov</i> will be appended automatically. Defalut value is <i>"export"</i>.
 * @param NSString* outputName Output file name without the extension.
 */
- (void)setVideoRecordingOutputName:(NSString*)outputName;

/**
 * @brief Changes the output path for all video recordings during runtime after it is called.
 * @details The argument is path only, no name. The defalut value is the AppData Documents folder. Example:
 * @code
 * [self.deepAR setVideoRecordingOutputPath:[NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES) firstObject]];
 * @endcode
 * @param NSString* outputPath Output video file path.
 */
- (void)setVideoRecordingOutputPath:(NSString*)outputPath;

/**
 * @brief Starts video recording of the @link ARView @endlink with given resolution.
 * @param int outputWidth The output width.
 * @param int outputHeight The output height.
 */
- (void)startVideoRecordingWithOutputWidth:(int)outputWidth outputHeight:(int)outputHeight;

/**
 * @brief Starts video recording of the @link ARView @endlink with given resolution.
 * @param int outputWidth The output width.
 * @param int outputHeight The output height.
 * @param CGRect subframe The <i>subframe</i> parameter defines the sub rectangle of the @link ARView @endlink that you want to record in normalized coordinates (0.0 - 1.0).
 */
- (void)startVideoRecordingWithOutputWidth:(int)outputWidth outputHeight:(int)outputHeight subframe:(CGRect)subframe;

/**
 * @brief Starts video recording of the @link ARView @endlink with given resolution.
 * @param int outputWidth The output width.
 * @param int outputHeight The output height.
 * @param CGRect subframe The <i>subframe</i> parameter defines the sub rectangle of the @link ARView @endlink that you want to record in normalized coordinates (0.0 - 1.0).
 * @param NSDictionary* videoCompressionProperties The <i>videoCompressionProperties</i> is an <a href="https://developer.apple.com/documentation/foundation/nsdictionary?language=objc">NSDictionary</a> used as the value for the key <a href="https://developer.apple.com/documentation/avfoundation/avvideocompressionpropertieskey?language=objc">AVVideoCompressionPropertiesKey</a>. Read more about video compression options in the official docs <a href="https://developer.apple.com/documentation/avfoundation/avvideocompressionpropertieskey?language=objc">here</a>.
 */
- (void)startVideoRecordingWithOutputWidth:(int)outputWidth outputHeight:(int)outputHeight subframe:(CGRect)subframe videoCompressionProperties:(NSDictionary*)videoCompressionProperties;

/**
 * @brief Starts video recording of the @link ARView @endlink with given resolution.
 * @param int outputWidth The output width.
 * @param int outputHeight The output height.
 * @param CGRect subframe The <i>subframe</i> parameter defines the sub rectangle of the @link ARView @endlink that you want to record in normalized coordinates (0.0 - 1.0).
 * @param NSDictionary* videoCompressionProperties The <i>videoCompressionProperties</i> is an <a href="https://developer.apple.com/documentation/foundation/nsdictionary?language=objc">NSDictionary</a> used as the value for the key <a href="https://developer.apple.com/documentation/avfoundation/avvideocompressionpropertieskey?language=objc">AVVideoCompressionPropertiesKey</a>. Read more about video compression options in the official docs <a href="https://developer.apple.com/documentation/avfoundation/avvideocompressionpropertieskey?language=objc">here</a>.
 * @param BOOL recordAudio If <i>recordAudio</i> parameter is set to true the recording will wait until you call @link enqueueAudioSample: enqueueAudioSample @endlink. When DeepAR is ready to receive audio samples it will publish <a href="https://developer.apple.com/documentation/foundation/nsnotification">NSNotification</a> with key <i>deepar_start_audio</i>. You can subscribe to this notification and start feeding audio samples once you receive it. If you use provided @link CameraController @endlink this is handled for you by default.
 */
- (void)startVideoRecordingWithOutputWidth:(int)outputWidth outputHeight:(int)outputHeight subframe:(CGRect)subframe videoCompressionProperties:(NSDictionary*)videoCompressionProperties recordAudio:(BOOL)recordAudio;

/**
 * @brief Load a DeepAR Studio file as an effect/filter in the scene.
 * @param NSString* slot The <i>slot</i> specifies a namespace for the effect in the scene. In each slot, there can be only one effect. If you load another effect in the same slot the previous one will be removed and replaced with a new effect. Example of loading 2 effects in the same scene:
 * @code
 * [self.deepAR switchEffectWithSlot:@"mask" path:"flowers"];
 * [self.deepAR switchEffectWithSlot:@"filter" path:"tv80"];
 * @endcode
 * @param NSString* path The <i>path</i> is a string path to a file located in the app bundle or anywhere in the filesystem where the app has access to. For example, one can download the filters from online locations and save them in the Documents directory. Value <i>nil</i> for the <i>path</i> param will remove the effect from the scene.
 */
- (void)switchEffectWithSlot:(NSString*)slot path:(NSString*)path;

/**
 * @brief Load a DeepAR Studio file as an effect/filter in the scene.
 * @param NSString* slot The <i>slot</i> specifies a namespace for the effect in the scene. In each slot, there can be only one effect. If you load another effect in the same slot the previous one will be removed and replaced with a new effect.
 * @param NSString* path The <i>path</i> is a string path to a file located in the app bundle or anywhere in the filesystem where the app has access to. For example, one can download the filters from online locations and save them in the Documents directory. Value <i>nil</i> for the <i>path</i> param will remove the effect from the scene.
 * @param NSInteger face The <i>face</i> parameter indicates on which face to apply the effect. DeepAR offers tracking up to 4 faces, so valid values for this parameter are 0, 1, 2, and 3. For example, if you call this method with face value 2, the effect will be only applied to the third detected face in the scene. If you want to set an effect on a different face make sure to also use a different value for the slot parameter to avoid removing the previously added effect. Example: 
 * @code
 * // apply flowers effect to the first face
 * [self.deepAR switchEffectWithSlot:@"mask_f0" path:"flowers" face:0];
 * // apply beard effect to the second face
 * [self.deepAR switchEffectWithSlot:@"mask_f1" path:"beard" face:1];
 * // replace the effect on the first face with the lion
 * [self.deepAR switchEffectWithSlot:@"mask_f0" path:"lion" face:0];
 * // remove the beard effect from the second face
 * [self.deepAR switchEffectWithSlot:@"mask_f1" path:nil face:1];
 * @endcode
 */
- (void)switchEffectWithSlot:(NSString*)slot path:(NSString*)path face:(NSInteger)face;

/**
 * @brief Load a DeepAR Studio file as an effect/filter in the scene.
 * @param NSString* slot The <i>slot</i> specifies a namespace for the effect in the scene. In each slot, there can be only one effect. If you load another effect in the same slot the previous one will be removed and replaced with a new effect.
 * @param NSString* path The <i>path</i> is a string path to a file located in the app bundle or anywhere in the filesystem where the app has access to. For example, one can download the filters from online locations and save them in the Documents directory. Value <i>nil</i> for the <i>path</i> param will remove the effect from the scene.
 * @param NSInteger face The <i>face</i> parameter indicates on which face to apply the effect. DeepAR offers tracking up to 4 faces, so valid values for this parameter are 0, 1, 2, and 3. For example, if you call this method with face value 2, the effect will be only applied to the third detected face in the scene. If you want to set an effect on a different face make sure to also use a different value for the slot parameter to avoid removing the previously added effect.
 * @param NSString* targetGameObject The <i>targetGameObject</i> parameter indicates a node in the currently loaded scene/effect into which the new effect will be loaded. By default, effects are loaded in the root node object.
 */
- (void)switchEffectWithSlot:(NSString*)slot path:(NSString*)path face:(NSInteger)face targetGameObject:(NSString*)targetGameObject;

/**
 * @brief Load contents of a DeepAR Studio file as an effect/filter in the scene.
 * @param NSString* slot The <i>slot</i> specifies a namespace for the effect in the scene. In each slot, there can be only one effect. If you load another effect in the same slot the previous one will be removed and replaced with a new effect.
 * @param NSData* data The contents of the file.
 */
- (void)switchEffectWithSlot:(NSString*)slot data:(NSData*)data;

/**
 * @brief Load contents of a DeepAR Studio file as an effect/filter in the scene.
 * @param NSString* slot The <i>slot</i> specifies a namespace for the effect in the scene. In each slot, there can be only one effect. If you load another effect in the same slot the previous one will be removed and replaced with a new effect.
 * @param NSData* data The contents of the file.
 * @param NSInteger face The <i>face</i> parameter indicates on which face to apply the effect. DeepAR offers tracking up to 4 faces, so valid values for this parameter are 0, 1, 2, and 3. For example, if you call this method with face value 2, the effect will be only applied to the third detected face in the scene. If you want to set an effect on a different face make sure to also use a different value for the slot parameter to avoid removing the previously added effect.
 */
- (void)switchEffectWithSlot:(NSString*)slot data:(NSData*)data face:(NSInteger)face;

/**
 * @brief Produces a snapshot of the current screen preview.
 * @details Resolution is equal to the dimension with which the @link DeepAR @endlink has been initialized. The @link DeepARDelegate @endlink method @link DeepARDelegate::didTakeScreenshot: didTakeScreenshot @endlink will be called upon successful screenshot capture is finished with a path where the image has been temporarily stored. 
 */
- (void)takeScreenshot;

/**
 * @brief Finishes the video recording.
 * @details Delegate method @link DeepARDelegate::didFinishVideoRecording: didFinishVideoRecording @endlink will be called when the recording is done with the temporary path of the recorded video.
 */
- (void)finishVideoRecording;

/**
 * @brief Pauses video recording if it has been started beforehand.
 */
- (void)pauseVideoRecording;

/**
 * @brief Resumes video recording after it has been paused with @link pauseVideoRecording @endlink.
 */
- (void)resumeVideoRecording;

/**
 * @brief Enables or disables audio pitch processing for video recording.
 * @param BOOL enabled Enable or disable audio processing.
 */
- (void)enableAudioProcessing:(BOOL)enabled;

/**
 * @brief Sets the pitch change amount.
 * @details Negative values will make the recorded audio lower in pitch and positive values will make it higher in pitch. Must call @link enableAudioProcessing: enableAudioProcessing @endlink to enable the pitch processing beforehand.
 * @param float sts The pitch change amount.
 */
- (void)setAudioProcessingSemitone:(float)sts;

/**
 * @brief Enables @link DeepARDelegate::frameAvailable: frameAvailable @endlink method callback.
 * @details By default @link DeepARDelegate @endlink will not call @link DeepARDelegate::frameAvailable: frameAvailable @endlink method on each new processed frame to save on processing time and resources. If we want the processed frames to be available in @link DeepARDelegate::frameAvailable: frameAvailable @endlink method of @link DeepARDelegate @endlink we need to call this method first on @link DeepAR @endlink.
 * @param NSInteger outputWidth The width of the processed frames.
 * @param NSInteger outputHeight The height of the processed frames.
 * @param CGRect subframe The subrectangle of @link ARView @endlink which will be outputted. This means that the output frame in @link DeepARDelegate::frameAvailable: frameAvailable @endlink does not need to be the same size and/or position as the one rendered to the @link ARView @endlink.
 */
- (void)startCaptureWithOutputWidth:(NSInteger)outputWidth outputHeight:(NSInteger)outputHeight subframe:(CGRect)subframe;

/**
 * @brief Enables @link DeepARDelegate::frameAvailable: frameAvailable @endlink method callback.
 * @details By default @link DeepARDelegate @endlink will not call @link DeepARDelegate::frameAvailable: frameAvailable @endlink method on each new processed frame to save on processing time and resources. If we want the processed frames to be available in @link DeepARDelegate::frameAvailable: frameAvailable @endlink method of @link DeepARDelegate @endlink we need to call this method first on @link DeepAR @endlink.
 * @param NSInteger outputWidth The width of the processed frames.
 * @param NSInteger outputHeight The height of the processed frames.
 * @param CGRect subframe The subrectangle of @link ARView @endlink which will be outputted. This means that the output frame in @link DeepARDelegate::frameAvailable: frameAvailable @endlink does not need to be the same size and/or position as the one rendered to the @link ARView @endlink.
 * @param OutputFormat outputFormat Parameter for user to control the pixel output format of @link DeepARDelegate::frameAvailable: frameAvailable @endlink method
 */
- (void)startCaptureWithOutputWidthAndFormat:(NSInteger)outputWidth outputHeight:(NSInteger)outputHeight subframe:(CGRect)subframe outputImageFormat:(OutputFormat)outputFormat;

/**
 * @brief Stops outputting frames to @link DeepARDelegate::frameAvailable: frameAvailable @endlink.
 */
- (void)stopCapture;

/**
 * @brief Fire named trigger of an fbx animation set on the currently loaded effect.
 * @details To learn more about fbx and image sequence animations on DeepAR please read our article <a href="https://help.deepar.ai/en/articles/4354740-animations-tutorial-fbx-model-animations">here</a>.
 * @param NSString* trigger The trigger name.
 */
- (void)fireTrigger:(NSString*)trigger;

/**
 * @brief Informs DeepAR that a touch with was detected.
 */
- (void)touchOccurred:(TouchInfo)touchInfo;

/**
 * @brief Display debugging stats on screen.
 * @param BOOL enabled Enable debugging stats.
 */
- (void)showStats:(BOOL) enabled;

/**
 * @brief Enable or disable global physics simulation.
 * @param BOOL enabled Enable global physics simulation.
 */
- (void)simulatePhysics:(BOOL) enabled;

/**
 * @brief Display physics colliders preview on screen.
 * @param BOOL enabled Enable physics colliders preview.
 */
- (void)showColliders:(BOOL) enabled;

/**
 * @brief This method allows the user to change face detection sensitivity.
 * @param NSInteger sensitivity The <i>sensitivity</i> parameter can range from 0 to 3, where 0 is the fastest but might not recognize smaller (further away) faces, and 3 is the slowest but will find smaller faces. By default, this parameter is set to 1.
 */
- (void)setFaceDetectionSensitivity:(NSInteger)sensitivity;

/**
 * @brief Changes a node or component float parameter.
 * @details For more details about changeParameter API read our article <a href="https://help.deepar.ai/en/articles/3732006-changing-filter-parameters-from-code">here</a>.
 * @param NSString* gameObject The name of the node. If multiple nodes share the same name, only the first one will be affected.
 * @param NSString* component The name of the component. If the name of the component is null or an empty string, the node itself will be affected.
 * @param NSString* parameter The name of the parameter.
 * @param float value New parameter value.
 */
- (void)changeParameter:(NSString*)gameObject component:(NSString*)component parameter:(NSString*)parameter floatValue:(float)value;

/**
 * @brief Changes a node or component 4D vector parameter.
 * @details For more details about changeParameter API read our article <a href="https://help.deepar.ai/en/articles/3732006-changing-filter-parameters-from-code">here</a>.
 * @param NSString* gameObject The name of the node. If multiple nodes share the same name, only the first one will be affected.
 * @param NSString* component The name of the component. If the name of the component is null or an empty string, the node itself will be affected.
 * @param NSString* parameter The name of the parameter.
 * @param Vector4 value New parameter value.
 */
- (void)changeParameter:(NSString*)gameObject component:(NSString*)component parameter:(NSString*)parameter vectorValue:(Vector4)value;

/**
 * @brief Changes a node or component 3D vector parameter.
 * @details For more details about changeParameter API read our article <a href="https://help.deepar.ai/en/articles/3732006-changing-filter-parameters-from-code">here</a>.
 * @param NSString* gameObject The name of the node. If multiple nodes share the same name, only the first one will be affected.
 * @param NSString* component The name of the component. If the name of the component is null or an empty string, the node itself will be affected.
 * @param NSString* parameter The name of the parameter.
 * @param Vector3 value New parameter value.
 */
- (void)changeParameter:(NSString*)gameObject component:(NSString*)component parameter:(NSString*)parameter vector3Value:(Vector3)value;

/**
 * @brief Changes a node or component boolean parameter.
 * @details For more details about changeParameter API read our article <a href="https://help.deepar.ai/en/articles/3732006-changing-filter-parameters-from-code">here</a>.
 * @param NSString* gameObject The name of the node. If multiple nodes share the same name, only the first one will be affected.
 * @param NSString* component The name of the component. If the name of the component is null or an empty string, the node itself will be affected.
 * @param NSString* parameter The name of the parameter.
 * @param BOOL value New parameter value.
 */
- (void)changeParameter:(NSString*)gameObject component:(NSString*)component parameter:(NSString*)parameter boolValue:(BOOL)value;

/**
 * @brief Changes a node or component image parameter.
 * @details For more details about changeParameter API read our article <a href="https://help.deepar.ai/en/articles/3732006-changing-filter-parameters-from-code">here</a>.
 * @param NSString* gameObject The name of the node. If multiple nodes share the same name, only the first one will be affected.
 * @param NSString* component The name of the component. If the name of the component is null or an empty string, the node itself will be affected.
 * @param NSString* parameter The name of the parameter.
 * @param UIImage* image New image parameter.
 */
- (void)changeParameter:(NSString*)gameObject component:(NSString*)component parameter:(NSString*)parameter image:(UIImage*)image;

/**
 * @brief Changes a node or component string parameter.
 * @details For more details about changeParameter API read our article <a href="https://help.deepar.ai/en/articles/3732006-changing-filter-parameters-from-code">here</a>.
 * @param NSString* gameObject The name of the node. If multiple nodes share the same name, only the first one will be affected.
 * @param NSString* component The name of the component. If the name of the component is null or an empty string, the node itself will be affected.
 * @param NSString* parameter The name of the parameter.
 * @param NSString* value New parameter value.
 */
- (void)changeParameter:(NSString*)gameObject component:(NSString*)component parameter:(NSString*)parameter stringValue:(NSString*)value;


/**
 * @brief Moves the selected game object from its current position in a tree and sets it as a direct child of a target game object.
 * @details This is equivalent to moving around a node in the node hierarchy in the DeepAR Studio.
 * @param NSString* selectedGameObjectName Node to move.
 * @param NSString* targetGameObjectName New node parent.
 */
- (void)moveGameObject:(NSString*)selectedGameObjectName targetGameObjectname:(NSString*)targetGameObjectName;

/**
 * @brief Starts recording profiling stats by writing them to a CSV-formatted stream.
 */
- (void)startProfiling;

/**
 * @brief Stops recording profiling stats and sends the recorded CSV to the stat export server.
 */
- (void)stopProfiling;

/**
 * @brief Set parameters that will determine how the face tracking is initialized.
 * @param params @link FaceTrackingInitParameters @endlink
 */
- (void)setFaceTrackingInitParameters:(FaceTrackingInitParameters)params;

/**
 * @brief Check if variable with the given name is already created in the specified effect.
 * @param NSString* name The variable name.
 * @param NSString* slot The slot of the effect in which to search the variable.
 * @return true The variable is already created.
 * @return false The variable is not created.
 */
- (bool)hasVar:(NSString*)name slot:(NSString*) slot;

/**
 * @brief Check if variable with the given name is already created in at least one effect.
 * @param NSString* name The variable name.
 * @return true The variable is already created.
 * @return false The variable is not created.
 */
- (bool)hasVar:(NSString*)name;

/**
 * @brief Get the type of the variable with the given name in the specified effect.
 * @param NSString* name The variable name.
 * @param NSString* slot The slot of the effect in which to search the variable.
 * @throw NSException Variable with the specified name does not exist.
 * @return The variable type. Supported types are: boolean, int, double and string.
 */
- (VarType)getVarType:(NSString*)name slot:(NSString*) slot;

/**
 * @brief Get the type of the variable with the given name.
 *      The variable is searched in all effects.
 * @param NSString* name The variable name.
 * @throw NSException Variable with the specified name does not exist.
 * @return The variable type. Supported types are: boolean, int, double and string.
 */
- (VarType)getVarType:(NSString*)name;

/**
 * @brief Get boolean variable with the given name.
 * @param NSString* name The variable name.
 * @param NSString* slot The slot of the effect in which to search the variable.
 * @throw NSException Variable with the specified name does not exist or is not a boolean.
 * @return Value of the variable with the specified name.
 */
- (bool)getBoolVar:(NSString*)name slot:(NSString*) slot;

/**
 * @brieg Get boolean variable with the given name. The variable is searched in all effects.
 * @param NSString* name The variable name.
 * @throw NSException Variable with the specified name does not exist or is not a boolean.
 * @return Value of the variable with the specified name.
 */
- (bool)getBoolVar:(NSString*)name;

/**
 * @brief Get integer variable with the given name.
 * @param NSString* name The variable name.
 * @param NSString* slot The slot of the effect in which to search the variable.
 * @throw NSException Variable with the specified name does not exist or is not an int.
 * @return Value of the variable with the specified name.
 */
- (int)getIntVar:(NSString*)name slot:(NSString*) slot;

/**
 * @brief Get integer variable with the given name. The variable is searched in all effects.
 * @param NSString* name The variable name.
 * @throw NSException Variable with the specified name does not exist or is not an int.
 * @return Value of the variable with the specified name.
 */
- (int)getIntVar:(NSString*)name;

/**
 * @brief Get double variable with the given name.
 * @param NSString* name The variable name.
 * @param NSString* slot The slot of the effect in which to search the variable.
 * @throw NSException Variable with the specified name does not exist or is not a double.
 * @return Value of the variable with the specified name.
 */
- (double)getDoubleVar:(NSString*)name slot:(NSString*) slot;

/**
 * @brief Get double variable with the given name. The variable is searched in all effects.
 * @param NSString* name The variable name.
 * @throw NSException Variable with the specified name does not exist or is not a double.
 * @return Value of the variable with the specified name.
 */
- (double)getDoubleVar:(NSString*)name;

/**
 * @brief Get string variable with the given name.
 * @param NSString* name The variable name.
 * @param NSString* slot The slot of the effect in which to search the variable.
 * @throw NSException Variable with the specified name does not exist or is not a string.
 * @return Value of the variable with the specified name.
 */
- (NSString*)getStringVar:(NSString*)name slot:(NSString*) slot;

/**
 * @brief Get string variable with the given name. The variable is searched in all effects.
 * @param NSString* name The variable name.
 * @throw NSException Variable with the specified name does not exist or is not a string.
 * @return Value of the variable with the specified name.
 */
- (NSString*)getStringVar:(NSString*)name;

/**
 * @brief Set the boolean variable wih the given name.
 * @param NSString* name The variable name.
 * @param NSString* slot The slot of the effect in which to search the variable.
 * @param bool value Value to be set.
 * @return YES The variable is created.
 * @return NO The variable with the given name already exists and the new value is set.
 */
- (bool)setBoolVar:(NSString*)name value:(bool)value slot:(NSString*) slot;

/**
 * @brief Set the boolean variable with the given name. The variable is set globally, for all effects.
 * @param NSString* name The variable name.
 * @param bool value Value to be set.
 * @return YES The variable is created.
 * @return NO The variable with the given name already exists and the new value is set.
 */
- (bool)setBoolVar:(NSString*)name value:(bool)value;

/**
 * @brief Set the int variable wih the given name.
 * @param NSString* name The variable name.
 * @param NSString* slot The slot of the effect in which to search the variable.
 * @param int value Value to be set.
 * @return YES The variable is created.
 * @return NO The variable with the given name already exists and the new value is set.
 */
- (bool)setIntVar:(NSString*)name value:(int)value slot:(NSString*) slot;

/**
 * @brief Set the int variable with the given name. The variable is set globally, for all effects.
 * @param NSString* name The variable name.
 * @param int value Value to be set.
 * @return YES The variable is created.
 * @return NO The variable with the given name already exists and the new value is set.
 */
- (bool)setIntVar:(NSString*)name value:(int)value;

/**
 * @brief Set the double variable wih the given name.
 * @param NSString* name The variable name.
 * @param NSString* slot The slot of the effect in which to search the variable.
 * @param double value Value to be set.
 * @return YES The variable is created.
 * @return NO The variable with the given name already exists and the new value is set.
 */
- (bool)setDoubleVar:(NSString*)name value:(double)value slot:(NSString*) slot;

/**
 * @brief Set the double variable with the given name. The variable is set globally, for all effects.
 * @param NSString* name The variable name.
 * @param double value Value to be set.
 * @return YES The variable is created.
 * @return NO The variable with the given name already exists and the new value is set.
 */
- (bool)setDoubleVar:(NSString*)name value:(double)value;

/**
 * @brief Set the string variable wih the given name.
 * @param NSString* name The variable name.
 * @param NSString* slot The slot of the effect in which to search the variable.
 * @param NSString* value Value to be set.
 * @return YES The variable is created.
 * @return NO The variable with the given name already exists and the new value is set.
 */
- (bool)setStringVar:(NSString*)name value:(NSString*)value slot:(NSString*) slot;

/**
 * @brief Set the string variable with the given name. The variable is set globally, for all effects.
 * @param NSString* name The variable name.
 * @param NSString* value Value to be set.
 * @return YES The variable is created.
 * @return NO The variable with the given name already exists and the new value is set.
 */
- (bool)setStringVar:(NSString*)name value:(NSString*)value;

/**
 * @brief Delete the variable with the given name.
 * @param NSString* name The variable name.
 * @param NSString* slot The slot of the effect in which to search the variable.
 * @return YES The variable is deleted.
 * @return NO The variable is not deleted.
 */
- (bool)deleteVar:(NSString*)name slot:(NSString*) slot;

/**
 * @brief Delete the variable with the given name. The variable is searched in all effects.
 * @param NSString* name The variable name.
 * @return YES The variable is deleted.
 * @return NO The variable is not deleted.
 */
- (bool)deleteVar:(NSString*)name;

/**
 * @brief Clear all variables or variables from the specified effect.
 * @param NSString* slot The ID of the effect in which to search the variable.
 * @return YES One of more variables are deleted.
 * @return NO No variables are deleted
 */
- (bool)clearVars:(NSString*)slot;

/**
 * @brief Clear all variables.
 * @return YES One of more variables are deleted.
 * @return NO No variables are deleted
 */
- (bool)clearVars;

@end

#import "ARView.h"
#import "CameraController.h"
