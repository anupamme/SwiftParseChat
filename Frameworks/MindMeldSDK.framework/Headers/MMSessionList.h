//
//  MindMeldSessionList.h
//  MindMeld
//
//  Created by Timothy Tuttle on 10/14/11.
//  Copyright 2011 Expect Labs, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "MMCollection.h"

#import "MMSession.h"

/**
 *  Represents the [Sessions](/docs/endpointUser#getUserUseridSessions) collection
 *  in the MindMeld API. The collection of [Session](/docs/endpointSession) objects that can be accessed by the User.
 *  For examples on how to update this object, look at the [Code Examples](/docs/sdks/ios/codeSnippets#iosCodeSnippet10).
 */
@interface MMSessionList : MMCollection

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

/**
 *  This method returns a session inside this list.
 *  This method is deprecated. Instead use [MMCollection objectForID:].
 *
 *  @param objectID The ID of the session to be fetched.
 *
 *  @return The MMSession that was found in this list.
 *  @see [MMCollection objectForID:]
 */
- (MMSession *)objectForId:(NSString *)objectID DEPRECATED_ATTRIBUTE;

@end
