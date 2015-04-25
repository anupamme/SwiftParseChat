//
//  MMEnvironment.h
//  mindmeld-ios-sdk
//
//  Created by J.J. Jackson on 8/27/14.
//  Copyright (c) 2014 Expect Labs. All rights reserved.
//

#import <Foundation/Foundation.h>


NS_ENUM(NSInteger, MMEnvironmentTier) {
    MMEnvironmentTierProduction = 0,
    MMEnvironmentTierStaging = 1,
    MMEnvironmentTierDevelopment = 2
};

@interface MMEnvironment : NSObject

@property (atomic, assign) enum MMEnvironmentTier tier;

@property (atomic, copy, readonly) NSString *apiServerURLString;
@property (atomic, copy, readonly) NSString *pushServerURLString;

/**
 *  If set, apiServerURLString will always return this value, regardless of tier.
 */
@property (nonatomic, copy) NSString *customAPIServerURLString;


/**
 *  If set pushServerURLString will always return this value, regardless of tier.
 */
@property (nonatomic, copy) NSString *customPushServerURLString;

+ (instancetype)sharedEnvironment;

@end
