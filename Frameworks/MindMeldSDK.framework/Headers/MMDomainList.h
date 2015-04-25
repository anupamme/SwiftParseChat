//
//  MMDomainList.h
//  mindmeld-ios-sdk
//
//  Created by J.J. Jackson on 12/15/14.
//  Copyright (c) 2014 Expect Labs. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "MMCollection.h"

#import "MMDomain.h"

/**
 *  Represents the [Domains](/docs/endpointApp#getDomains) collection in the 
 *  MindMeld API. The collection of [Domain](/docs/endpointDomain) objects that
 *  can be accessed in an App. 
 */
@interface MMDomainList : MMCollection

/**
 *  Creates an object with the provided API credentials and update handlers
 *
 *  @param appID          The app ID created via MindMeld Dev Center. This will be given to you
 *                        when you sign up for using the MindMeld API.
 *  @param userToken      The API token that will be used to access the API.
 *  @param userID         The ID of the user that will be used to access the API.
 *  @param successHandler The handler which will be called when updates to this object are successful
 *  @param failureHandler The handler which will be called when updates to this object are not successful
 *
 *  @return the collection
 */
- (instancetype)initWithAppID:(NSString *)appID
                    userToken:(NSString *)userToken
                       userID:(NSString *)userID
                    onSuccess:(MMObjectUpdateSuccessHandler)successHandler
                    onFailure:(MMObjectUpdateFailureHandler)failureHandler;

@end
