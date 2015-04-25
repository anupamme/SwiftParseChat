//
//  MMListenerResult.h
//  mindmeld-ios-sdk
//
//  Created by J.J. Jackson on 8/26/14.
//  Copyright (c) 2014 Expect Labs. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 *  A value object encapsulating speech recognition results from an MMListener
 */
@interface MMListenerResult : NSObject <NSCopying, NSCoding>

/**
 *  The transcript of the speech.
 */
@property (nonatomic, copy, readonly) NSString *transcript;

/**
 *  Indicates whether a result is final or interim. When a result is final, the listener will not make corrections to
 *  this portion of the transcript.
 */
@property (nonatomic, readonly) BOOL final;

/**
 *  Creates a listener result.
 *
 *  @param transcript the result's transcript
 *  @param final      whether the result is final.
 *
 *  @return the result
 */
+ (instancetype)resultWithTranscript:(NSString *)transcript
                               final:(BOOL)final;
/**
 *  Initializes a listener result
 *
 *  @param transcript the result's transcript
 *  @param final      whether the result is final.
 *
 *  @return the result
 */
- (instancetype)initWithTranscript:(NSString *)transcript
                             final:(BOOL)final;

@end
