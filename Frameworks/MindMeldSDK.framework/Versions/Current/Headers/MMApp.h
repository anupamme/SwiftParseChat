//
//  MMApp.h
//  mindmeld-ios-sdk
//
//  Created by Juan Rodriguez on 11/18/13.
//  Copyright (c) 2013 Expect Labs. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "MMAPICall.h"
#import "MMUser.h"
#import "MMLiveUserList.h"
#import "MMInvitedUserList.h"
#import "MMSession.h"
#import "MMSessionList.h"
#import "MMDomain.h"
#import "MMDomainList.h"
#import "MMTextEntryList.h"
#import "MMDocumentList.h"

/**
 *  Represents the [App](/docs/endpointApp) object in the MindMeld API.
 *  This object refers to an individual application created
 *  by a developer using the MindMeld Developer Console. An App
 *  is owned by a single developer account, and it is typically
 *  associated with a searchable corpus of documents specified by the developer.
 *
 *  Here is a simple example of getting started with an `MMApp`:
 *
 *      MMApp *mindMeldApp = [[MMApp alloc] initWithAppID:@"YOUR_MINDMELD_APP_ID_HERE"];
 *      [mindMeldApp start:nil onSuccess:^(id ignored){ mindMeldAppID.delegate = self; } onFailure:nil];
 *
 */
@interface MMApp : NSObject

/**
 *  The version of the iOS SDK.
 */
@property (nonatomic, copy, readonly) NSString *version;

/**
 *  The App id that will be used in all subsequent calls made to the MindMeld API.
 */
@property (nonatomic, copy, readonly) NSString *appID;

/**
 *  The Token that will be used in all subsequent calls made to the MindMeld API.
 */
@property (nonatomic, copy, readwrite) NSString *token;

/**
 *  The delegate that will implement the methods in the MMAppDelegate protocol
 */
@property (nonatomic, weak, readwrite) id delegate;

/**
 *  The active user for this App. The active user ID is used in all api calls that contain the field "user", such as user/:userid, user/:userid/sessions, etc.
 */
@property (nonatomic, strong, readonly) MMUser *activeUser;

/**
 * The user id of the active user. Modify this property to specify the activeUser. This specified user's token and user
 * id will be used in subsequent API calls.
 */
@property (nonatomic, copy, readwrite) NSString *activeUserID;

/**
 *  The active session for this App. The active session ID is used in all api calls that contain the field session, such
 *  as session/:sessionid, session/:sessionid/entities, etc. Use activeSessionID to specify the active session.
 */
@property (nonatomic, strong, readonly) MMSession *activeSession;

/**
 *  The session id of the active session. Modify this property to specify the activeSession. After setting this session
 *  object, calls for entities, textentries, etc, will all be done for this particular session.
 */
@property (nonatomic, copy, readwrite) NSString *activeSessionID;

// Handler for the push events in the App channel
@property (nonatomic, copy, readwrite) MMPushEventHandler customEventHandler;

/**
 *  The collection of domains for this App.
 */
@property (nonatomic, strong, readonly) MMDomainList *domains;

/**
 *  Init method that starts the MindMeld App object
 *
 *  @param appID The app ID created via MindMeld Dev Center. This will be given to you
 *               when you sign up for using the MindMeld API.
 *
 *  @return returns the MMApp object
 */
- (instancetype)initWithAppID:(NSString *)appID;


/**
 *  This is the simplest way to authenticate and start using the MindMeld API. This method will initialize the MindMeld
 *  SDK, get a token, set the user, and start a session. It is called instead of the `getToken:onSuccess:onFailure:`,
 *  `setActiveUserID:`, `setActiveSessionID:` sequence. By default it uses anonymous authentication and creates a new
 *  `inviteonly` session.
 *
 *  @param config                Configuration parameters containing information to be used with the start process.
 *  @param config["credentials"] A NSDictionary containing credentials for getting a token using `getToken:onSuccess:onFailure:`. 
 *                               Refer to the MindMeld API documentation for authentication 
 *                               [here](/docs/authentication) for more information.
 *  @param config["token"]       A valid token to use for `setToken:`. This requires userid to be supplied as well.
 *  @param config["userid"]      A valid user id to use for `setActiveUserID:`. This requires token to be supplied as well.
 *  @param config["sessionid"]   The sessionid of an existing session you wish to join with `setActiveSessionID:`.
 *  @param config["session"]     A NSDictionary containing new session data. Refer to the MindMeld API documentation for
 *                               creating sessions [here](/docs/endpointUser#postUserUseridSessions)
 *                               for more information.
 *  @param successHandler        The success block that gets called when the app has been initialized.
 *  @param failureHandler        The fail block that gets called if an API call fails.
 */
- (void)start:(NSDictionary *)config
    onSuccess:(MMSuccessHandler)successHandler
    onFailure:(MMFailureHandler)failureHandler;


/**
 *  This method assigns a token to a given user. When calling this method, the
 *  token property of this MMApp object will be set to the requested token, as
 *  well as setting `activeUserID`.  This means that all consequent API calls
 *  will be made on behalf of the credentials used in this getToken call.
 *
 *  @param userCredentials This is an NSDictionary that should contain the [credentials](/docs/authentication)
 *  of a given user.
 *  @param successHandler  The success block that gets called when the token has been obtained from the API.
 *  @param failureHandler  The fail block that gets called if the API call fails.
 */
- (void)getToken:(NSDictionary *)userCredentials
       onSuccess:(MMSuccessHandler)successHandler
       onFailure:(MMFailureHandler)failureHandler;

/**
 *  Updates the activeUser to the that specified by activeSessionID. After the user
 *  object is updated, the specified user's token and id will be used in subsequent API calls.
 *
 *  @param activeUserID   The ID of the desired user.
 *  @param successHandler The success block that gets called when the user has been updated.
 *  @param failureHandler The fail block that gets called if the API call fails.
 */
- (void)setActiveUserID:(NSString *)activeUserID
              onSuccess:(MMSuccessHandler)successHandler
              onFailure:(MMFailureHandler)failureHandler;

/**
 *  Updates the activeSession to the that specified by activeSessionID. After the session
 *  object is updated, calls for entities, textentries, etc, will all be done for this particular session.
 *
 *  @param activeSessionID The ID of the desired session.
 *  @param successHandler  The success block that gets called when the user has been updated.
 *  @param failureHandler  The fail block that gets called if the API call fails.
 */
- (void)setActiveSessionID:(NSString *)activeSessionID
                 onSuccess:(MMSuccessHandler)successHandler
                 onFailure:(MMFailureHandler)failureHandler;


/**
 *  This method makes custom calls to the MindMeld API.
 *
 *  @param method         NSString that is the method, which can be "get", "delete" or "post".
 *  @param path           NSString that is the path to be accessed, for example "/session/:sessionid/entities".
 *  @param params         NSDictionary containing the optional parameters for this method.
 *  @param body           NSDictionary containing the body of the call, if the body is required.
 *  @param successHandler The block that will be called when the API call completes successfully.
 *  @param failureHandler The block that will be called when the API call fails.
 */
- (void)callAPIWithMethod:(NSString *)method
                     path:(NSString *)path
                   params:(NSDictionary *)params
                     body:(NSDictionary *)body
                onSuccess:(MMSuccessHandler)successHandler
                onFailure:(MMFailureHandler)failureHandler;

/**
 *  This method revokes the token in the active user object.
 */
- (void)revokeToken;

/**
 *  This method subscribes to a custom event in the App channel.
 *
 *  @param eventName    The name of the custom event to which the session channel is subscribing.
 *  @param eventHandler The block that handles the messages received in this event.
 */
- (void)subscribeToEvent:(NSString *)eventName onEvent:(MMPushEventHandler)eventHandler;

/**
 *  This method unsubscribes from a custom event in the App channel.
 *
 *  @param eventName The name of the custom event from which the app channel will unsubscribe.
 */
- (void)unsubscribeFromEvent:(NSString *)eventName;

/**
 *  This method publishes an event on the App channel.
 *
 *  @param eventName The name of the event that will be created.
 *  @param payload   An NSDictionary that contains payload information about the event.
 */
- (void)publishEvent:(NSString *)eventName payload:(NSDictionary *)payload;


#pragma mark - deprecated

@property (nonatomic, copy, readonly) NSString *userid DEPRECATED_ATTRIBUTE;
@property (nonatomic, copy, readonly) NSString *sessionid DEPRECATED_ATTRIBUTE;

- (instancetype)initWithAppid:(NSString *)appID DEPRECATED_ATTRIBUTE;

- (void)callApiWithMethod:(NSString *)method path:(NSString *)path
                   params:(NSDictionary *)params
                     body:(NSDictionary *)body
                onSuccess:(MMSuccessHandler)successHandler
                   onFail:(MMFailureHandler)failureHandler DEPRECATED_ATTRIBUTE;

- (void)getToken:(NSDictionary *)userCredentials
       onSuccess:(MMSuccessHandler)successHandler
       failBlock:(MMFailureHandler)failureHandler DEPRECATED_ATTRIBUTE;

@end

/**
 *  This protocol is used to respond to various MindMeld object updates.
 */
@protocol MMAppDelegate
@optional

/**
 *  This is called when the activeUser object in MMApp has received new data from the MindMeld API.
 *
 *  @param user The MMUser object that has just updated its data.
 */
- (void)activeUserDidUpdate:(MMUser *)user;

/**
 *  This is called when the activeUser object in MMApp has failed to receive new data from the MindMeld API.
 *
 *  @param user  The MMUser object that has failed to update its data.
 *  @param error The error containing the description of why this operation failed
 */
- (void)activeUser:(MMUser *)user didFailUpdateWithError:(NSError *)error;

/**
 *  This is called when the activeSession object in MMApp has received new data from the MindMeld API.
 *
 *  @param session The MMSession object that has just updated its data.
 */
- (void)activeSessionDidUpdate:(MMSession *)session;

/**
 *  This is called when the activeSession object in MMApp has failed to receive new data from the MindMeld API.
 *
 *  @param session  The MMSession object that has failed to update its data.
 *  @param error The error containing the description of why this operation failed.
 */
- (void)activeSession:(MMSession *)session didFailUpdateWithError:(NSError *)error;

/**
 *  This is called when the session list object in the active user has received new data from the MindMeld API.
 *
 *  @param sessions The MMSessionList object that has just updated its data.
 */
- (void)sessionListDidUpdate:(MMSessionList *)sessions;

/**
 *  This is called when the active user's session list object has failed to receive new data from the MindMeld API.
 *
 *  @param sessions  The MMSessionList object that has failed to update its data.
 *  @param error The error containing the description of why this operation failed.
 */
- (void)sessionList:(MMSessionList *)sessions didFailUpdateWithError:(NSError *)error;

/**
 *  This is called when the domain list object in the app has received new data from the MindMeld API.
 *
 *  @param domains The MMDomainList object that has just updated its data.
 */
- (void)domainListDidUpdate:(MMDomainList *)domains;

/**
 *  This is called when the domain list object in the app has failed to receive new data from the MindMeld API.
 *
 *  @param domains The MMDomainList object that has failed to update its data.
 *  @param error  The error containing the description of why this operation failed.
 */
- (void)domainList:(MMDomainList *)domains didFailUpdateWithError:(NSError *)error;


/**
 *  This is called when the textentries object in the active session has received new data from the MindMeld API.
 *
 *  @param textEntries The MMTextEntryList object that has just updated its data.
 */
- (void)textEntryListDidUpdate:(MMTextEntryList *)textEntries;

/**
 *  This is called when the textentries object in activeSession has failed to receive new data from the MindMeld API.
 *
 *  @param textentries  The MMTextEntryList object that has failed to update its data.
 *  @param error The error containing the description of why this operation failed.
 */
- (void)textEntryList:(MMTextEntryList *)textentries didFailUpdateWithError:(NSError *)error;

/**
 *  This is called when the entities object in the active session has received new data from the MindMeld API.
 *
 *  @param entities The MMEntityList object that has just updated its data.
 */
- (void)entityListDidUpdate:(MMEntityList *)entities;

/**
 *  This is called when the entities object in activeSession has failed to receive new data from the MindMeld API.
 *
 *  @param entities  The MMEntityList object that has failed to update its data.
 *  @param error The error containing the description of why this operation failed.
 */
- (void)entityList:(MMEntityList *)entities didFailUpdateWithError:(NSError *)error;

/**
 *  This is called when the documents object in the active session has received new data from the MindMeld API.
 *
 *  @param documents The MMDocumentList object that has just updated its data.
 */
- (void)documentListDidUpdate:(MMDocumentList *)documents;

/**
 *  This is called when the documents object in activeSession has failed to receive new data from the MindMeld API.
 *
 *  @param documents  The MMDocumentList object that has failed to update its data.
 *  @param error The error containing the description of why this operation failed.
 */
- (void)documentList:(MMDocumentList *)documents didFailUpdateWithError:(NSError *)error;

/**
 *  This is called when the liveusers object in the active session has received new data from the MindMeld API.
 *
 *  @param liveusers The MMLiveUserList object that has just updated its data.
 */
- (void)liveUserListDidUpdate:(MMLiveUserList *)liveusers;

/**
 *  This is called when the liveusers object in activeSession has failed to receive new data from the MindMeld API.
 *
 *  @param liveusers  The MMLiveUserList object that has failed to update its data.
 *  @param error The error containing the description of why this operation failed.
 */
- (void)liveUserList:(MMLiveUserList *)liveusers didFailUpdateWithError:(NSError *)error;

/**
 *  This is called when the invitedusers object in the active session has received new data from the MindMeld API.
 *
 *  @param invitedusers The MMInvitedUserList object that has just updated its data.
 */
- (void)invitedUserListDidUpdate:(MMInvitedUserList *)invitedusers;

/**
 *  This is called when the invitedusers object in activeSession has failed to receive new data from the MindMeld API.
 *
 *  @param invitedusers  The MMInvitedUserList object that has failed to update its data.
 *  @param error The error containing the description of why this operation failed.
 */
- (void)invitedUserList:(MMInvitedUserList *)invitedusers didFailUpdateWithError:(NSError *)error;

@end
