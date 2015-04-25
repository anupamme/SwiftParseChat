//
//  MindMeldSession.h
//  MindMeld
//
//  Created by Timothy Tuttle on 10/20/11.
//  Copyright 2011 Expect Labs, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "MMObject.h"
#import "MMTextEntryList.h"
#import "MMEntityList.h"
#import "MMDocumentList.h"
#import "MMLiveUserList.h"
#import "MMInvitedUserList.h"

#import "MMBlockTypes.h"

/**
 *  Represents the object [Session](/docs/endpointSession) in the MindMeld API. This object is a container
 *  for capturing a history of contextual information for one or more users interacting
 *  with your application. The Session contains several child object collections that
 *  can be used to upload contextual information and display relevant search results to your users.
 *  For examples on how to update this object, look at the [Code Examples](/docs/sdks/ios/codeSnippets#iosCodeSnippet10).
 */
@interface MMSession : MMObject <MMCollectionOwner>

/**
 *  The session id of this particlar session.
 */
@property (nonatomic, copy, readwrite) NSString *sessionID;

/**
 *  The text entry list associated with this session object.
 */
@property (nonatomic, strong, readwrite) MMTextEntryList *textEntries;

/**
 *  The entity list associated with this session object.
 */
@property (nonatomic, strong, readwrite) MMEntityList *entities;

/**
 *  The document list associated with this session object.
 */
@property (nonatomic, strong, readwrite) MMDocumentList *documents;

/**
 *  The liveuser list associated with this session object.
 */
@property (nonatomic, strong, readwrite) MMLiveUserList *liveUsers;

/**
 *  The inviteduser list associated with this session object.
 */
@property (nonatomic, strong, readwrite) MMInvitedUserList *invitedUsers;

@property (nonatomic, copy, readwrite) MMPushEventHandler customEventHandler;

/**
 *  This method makes the subscription to a custom event in the Session channel.
 *
 *  @param eventName   The name of the custom event to which the session channel is subscribing.
 *  @param handleEvent The block that will handle the messages received in this event.
 */
- (void)subscribeToEvent:(NSString *)eventName onEvent:(MMPushEventHandler)handleEvent;

/**
 *  This method removes the subscription to a custom event in the Session channel.
 *
 *  @param eventName The name of the custom event from which the session channel will unsubscribe.
 */
- (void)unsubscribeFromEvent:(NSString *)eventName;

/**
 *  This method publishes an event on the Session channel.
 *
 *  @param eventName The name of the event that will be created.
 *  @param payload   A NSDictionary that contains payload information about the event.
 */
- (void)publishEvent:(NSString *)eventName payload:(NSDictionary *)payload;


#pragma mark - deprecated

@property (nonatomic, strong, readwrite) MMTextEntryList *textentries DEPRECATED_ATTRIBUTE;
@property (nonatomic, strong, readwrite) MMLiveUserList *liveusers DEPRECATED_ATTRIBUTE;
@property (nonatomic, strong, readwrite) MMInvitedUserList *invitedusers DEPRECATED_ATTRIBUTE;

/**
 *  This method is deprecated. Instead use [MMObject initWithAppID:userToken:userID:sessionID:onSuccess:onFailure:].
 *
 *  @see [MMObject initWithAppID:userToken:userID:sessionID:onSuccess:onFailure:]
 *
 *  @param appID      The app ID created via MindMeld Dev Center. This will be given to you
 *                    when you sign up for using the MindMeld API.
 *  @param userToken  The API token that will be used to access the API.
 *  @param userID     The ID of the user that will be used to access the API.
 *  @param sessionID  The ID of the session.
 *  @param delegate   The update delegate.
 *
 *  @return the corresponding session
 */
- (instancetype)initWithAppID:(NSString *)appID
                    userToken:(NSString *)userToken
                       userID:(NSString *)userID
         andMindmeldSessionId:(NSString *)sessionID
                  andDelegate:(id)delegate DEPRECATED_ATTRIBUTE;

@end
