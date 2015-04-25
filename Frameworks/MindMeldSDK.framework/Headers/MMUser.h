//
//  MMUser.h
//  mindmeld-ios-sdk
//
//  Created by Juan Rodriguez on 11/18/13.
//  Copyright (c) 2013 Expect Labs. All rights reserved.
//

#import "MMObject.h"
#import "MMSessionList.h"

/**
 *  Represents the [User](/docs/endpointUser) object in the MindMeld API.
 *  This object represents any user of your application.
 *  User objects are uniquely identified by authentication credentials
 *  you provide to the API when you request Tokens for accessing the API endpoints.
 *  For examples on how to update this object, look at the [Code Examples](/docs/sdks/ios/codeSnippets#iosCodeSnippet10).
 */
@interface MMUser : MMObject

/**
 *  The session list associated to this user object.
 */
@property (nonatomic, strong, readwrite) MMSessionList *sessions;

@property (nonatomic, copy, readwrite) MMPushEventHandler customEventHandler;

/**
 *  Creates a new user object
 *
 *  @param appID          The app ID created via MindMeld Dev Center. This will be given to you
 *                        when you sign up for using the MindMeld API.
 *  @param userToken      The API token that will be used to access the API.
 *  @param userID         The ID of the user.
 *  @param successHandler The handler which will be called when updates to this object are successful
 *  @param failureHandler The handler which will be called when updates to this object are not successful
 *
 *  @return the user object
 */
- (instancetype)initWithAppID:(NSString *)appID
                    userToken:(NSString *)userToken
                       userID:(NSString *)userID
                    onSuccess:(MMObjectUpdateSuccessHandler)successHandler
                    onFailure:(MMObjectUpdateFailureHandler)failureHandler;

/**
 *  This method makes the subscription to a custom event in the User channel.
 *
 *  @param eventName   The name of the custom event to which the session channel is subscribing.
 *  @param eventHandler The block that will handle the messages received in this event.
 */
- (void)subscribeToEvent:(NSString *)eventName onEvent:(MMPushEventHandler)eventHandler;

/**
 *  This method removes the subscription to a custom event in the User channel.
 *
 *  @param eventName The name of the custom event from which the user channel will unsubscribe.
 */
- (void)unsubscribeFromEvent:(NSString *)eventName;

/**
 *  This method publishes an event on the User channel.
 *
 *  @param eventName The name of the event that will be created.
 *  @param payload   A NSDictionary that contains payload information about the event.
 */
- (void)publishEvent:(NSString *)eventName
             payload:(NSDictionary *)payload;


#pragma mark - Deprecated


/**
 *  This method is deprecated. Instead use initWithAppID:userToken:userID:onSuccess:onFailure:.
 *
 *  @see initWithAppID:userToken:userID:onSuccess:onFailure:
 *
 *  @param appID      The app ID created via MindMeld Dev Center. This will be given to you
 *                    when you sign up for using the MindMeld API.
 *  @param userToken  The API token that will be used to access the API.
 *  @param userID     The ID of the user.
 *  @param delegate   The update delegate.
 *
 *  @return the corresponding user
 */
- (instancetype)initWithAppID:(NSString *)appID
                    userToken:(NSString *)userToken
                       userID:(NSString *)userID
                  andDelegate:(id)delegate DEPRECATED_ATTRIBUTE;

@end
