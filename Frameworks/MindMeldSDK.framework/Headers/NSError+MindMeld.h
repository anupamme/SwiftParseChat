//
//  NSError+MindMeld.h
//  mindmeld-ios-sdk
//
//  Created by J.J. Jackson on 19/09/14.
//  Copyright (c) 2014 Expect Labs. All rights reserved.
//

#import <Foundation/Foundation.h>

FOUNDATION_EXPORT NSString *const MMMindMeldSDKErrorDomain;
FOUNDATION_EXPORT NSString *const MMMindMeldSDKListenerErrorDomain;

/**
 *  Access to the microphone was denied.
 */
FOUNDATION_EXPORT const NSUInteger MMMindMeldSDKListenerMicrophoneAccessError;

/**
 *  An error was encountered with the network while making the request.
 */
FOUNDATION_EXPORT const NSUInteger MMMindMeldSDKListenerNetworkError;

@interface NSError (MindMeld)

+ (NSError *)errorWithDomain:(NSString *)domain
                        code:(NSInteger)code
                 description:(NSString *)description;

@end
