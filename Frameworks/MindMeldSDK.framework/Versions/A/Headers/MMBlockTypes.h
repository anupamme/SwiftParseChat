//
//  MMBlockTypes.h
//  mindmeld-ios-sdk
//
//  Created by J.J. Jackson on 9/5/14.
//  Copyright (c) 2014 Expect Labs. All rights reserved.
//

#import <Foundation/Foundation.h>

@class MMAPICall;

typedef void (^MMAPICallResponseHandler)(MMAPICall *call);

/**
 *  This is the success block definition used in many of the methods in this object.
 *
 *  @param response The dictionary containing the response from the call.
 */
typedef void (^MMSuccessHandler)(id response);

/**
 *  This is the fail block definition used in many of the methods in this object.
 *
 *  @param error The error that happened when trying to make the call.
 */
typedef void (^MMFailureHandler)(NSError *error);


typedef void (^MMPushEventHandler)(id payload);

typedef void (^MMObjectUpdateSuccessHandler)(id json);
typedef void (^MMObjectUpdateFailureHandler)(id object, NSError *error);



typedef MMSuccessHandler successblock DEPRECATED_ATTRIBUTE;
typedef MMFailureHandler failblock DEPRECATED_ATTRIBUTE;
typedef MMPushEventHandler handleEvent DEPRECATED_ATTRIBUTE;

typedef MMAPICallResponseHandler MMApiCallSuccessBlock DEPRECATED_ATTRIBUTE;
typedef MMAPICallResponseHandler MMApiCallFailBlock DEPRECATED_ATTRIBUTE;