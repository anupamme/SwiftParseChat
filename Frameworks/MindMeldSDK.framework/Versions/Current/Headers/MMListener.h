//
//  MMListener.h
//  mindmeld-ios-sdk
//
//  Created by J.J. Jackson on 8/26/14.
//  Copyright (c) 2014 Expect Labs. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "MMListenerResult.h"

@class MMListener;

/**
 *  A block for handling events from a listener instance.
 *
 *  @param listener the listener emitting the events
 */
typedef void (^MMListenerEventHandler)(MMListener *listener);

/**
 *  A block for handling listener errors.
 *
 *  @param listener the listener emitting the events
 *  @param error    the error that was encountered
 */
typedef void (^MMListenerErrorHandler)(MMListener *listener, NSError *error);

/**
 *  A block for handling listener results.
 *
 *  @param listener the listener emitting the events
 *  @param result   the speech result
 */
typedef void (^MMListenerResultHandler)(MMListener *listener, MMListenerResult *result);

/**
 *  A block for handling changes in volume level.
 *
 *  @param listener        the listener emitting the events
 *  @param avgVolumeLevel  a value between 0 and 1 representing the current average volume level
 *  @param peakVolumeLevel a value between 0 and 1 representing the current peak volume level
 */
typedef void (^MMListenerVolumeChangeHandler)(MMListener *listener, Float32 avgVolumeLevel, Float32 peakVolumeLevel);

/**
 *  MMListener is the class for the MindMeld speech recognition interface.
 */
@interface MMListener : NSObject

/**
 *  Indicates whether or not the listener is active.
 */
@property (nonatomic, assign, readonly) BOOL listening;

/**
 *  Indicates whether or not continuous recognition is enabled. When continuous recognition is enabled, the listener
 *  will keep listening until stopListening is called.
 *
 *  @default NO
 */
@property (nonatomic, assign) BOOL continuous;

/**
 *  Indicates whether or not interim results are enabled.
 *
 *  @default YES
 */
@property (nonatomic, assign) BOOL interimResults;

/**
 *  A language tag specifying the language the listener should recognize. For example, use 'ko' for Korean, 'en-US' for
 *  American English, and 'de-DE' for German. This tag is the simple language sub tag or language region tag of the
 *  [BCP47](http://tools.ietf.org/html/bcp47) code for languages.
 *
 * @default "en-US"
 */
@property (nonatomic, copy) NSString *language;

/**
 *  An array of MMListenerResult objects from the current or most recent speech recognition session.
 */
@property (nonatomic, readonly) NSArray *results;

/**
 *  This block is called when the listener begins recording. This occurs after the startListening method is called.
 */
@property (nonatomic, copy) MMListenerEventHandler onBeganRecording;

/**
 *  This block is called when the listener has finished recording. The listener may still be processing speech. This 
 *  will always be before onFinished.
 */
@property (nonatomic, copy) MMListenerEventHandler onFinishedRecording;

/**
 *  This method is called when the listener has finished a session.
 *
 */
@property (nonatomic, copy) MMListenerEventHandler onFinished;

/**
 *  This block is called when the listener encounters an error.
 */
@property (nonatomic, copy) MMListenerErrorHandler onError;

/**
 *  This block is called when a change in volume is detected
 */
@property (nonatomic, copy) MMListenerVolumeChangeHandler onVolumeChanged;

/**
 *  This block is called when the listener receives a result
 */
@property (nonatomic, copy) MMListenerResultHandler onResult;

/**
 *  This method configures the audio session for a listener by setting the AVAudioSessionCategory to 
 *  AVAudioSessionPlayAndRecord and activating the session. Applications which use a listener should invoke this from
 *  application:didFinishLaunchingWithOptions: and applicationDidBecomeActive: in the application delegate.
 *  See the AVAudioSession documentation if you would like to manage the audio session differently.
 */
+ (void)prepareAudioSession;

/**
 *  Creates a listener.
 *
 *  @return the listener
 */
+ (instancetype)listener;

/**
 *  Starts a speech recognition session.
 */
- (void)startListening;

/**
 *  Stops the active speech recognition session. The listener may still be processing and send more results.
 */
- (void)stopListening;


/**
 * Stops the active speech recognition session. The listener will not send any additional results.
 */
- (void)cancel;

@end
