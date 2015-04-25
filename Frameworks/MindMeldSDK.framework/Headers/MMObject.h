//
//  MMObject.h
//  MindMeld
//
//  Created by Timothy Tuttle on 10/19/11.
//  Copyright 2011 Expect Labs, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "MMBlockTypes.h"

@class MMAPICall;
@class PullManager;


/**
 *  This is the base class for all the API objects. This is where the functionality for getting
 *  data from and pushing data to the API is located.
 *  This class is never used directly, it's always one of the child classes that will be used: MMSession, etc..
 *  For examples on how to use this class to update the API objects, look at the
 *  [Code Examples](/docs/sdks/ios/codeSnippets#iosCodeSnippet10).
 */
@interface MMObject : NSObject

@property (atomic, strong, readwrite) NSMutableDictionary *result;
@property (atomic, strong, readwrite) NSDate *lastUpdateTime;

/**
 *  Used to decide whether the data for this object will be stored in disk when the data is updated.
 */
@property (nonatomic, assign, readwrite) BOOL shouldPersist;

// Properties used for API calls, they come from MMApp
@property (nonatomic,   copy, readwrite) NSString *appID;
@property (nonatomic,   copy, readwrite) NSString *token;
@property (nonatomic,   copy, readwrite) NSString *userID;
@property (nonatomic,   copy, readwrite) NSString *sessionID;
@property (nonatomic,   copy, readwrite) NSString *objectID;
@property (nonatomic,   copy, readwrite) NSString *objectName;
@property (nonatomic,   copy, readwrite) NSString *elementName;
@property (nonatomic,   copy, readwrite) MMObjectUpdateSuccessHandler onUpdateSuccess;
@property (nonatomic,   copy, readwrite) MMObjectUpdateFailureHandler onUpdateFailure;
@property (nonatomic,   copy, readwrite) NSString *apiMethod;
@property (nonatomic,   copy, readwrite) NSString *apiPath;
@property (nonatomic, strong, readwrite) NSDictionary *apiParams;
@property (nonatomic, strong, readwrite) NSDictionary *body;
@property (nonatomic, assign, readwrite) double refreshInterval;
@property (nonatomic,   copy, readwrite) NSString *eTag;
@property (nonatomic,   copy, readwrite) NSString *modSince;

/**
 *  Used to decide if automatic updates will be done via both push updates and polling, or only via push updates.
 */
@property (nonatomic, assign, readwrite) BOOL useBothPushAndPull;

@property (   atomic, strong, readwrite) MMAPICall *lastGetCall;
@property (nonatomic, strong, readwrite) PullManager *pullManager;

- (instancetype)initWithAppID:(NSString *)appID
                    userToken:(NSString *)userToken
                       userID:(NSString *)userID
                    sessionID:(NSString *)sessionID;

/**
 *  Creates an object with the provided API credentials and object ID.
 *
 *  @param appID     The app ID created via MindMeld Dev Center. This will be given to you
 *                   when you sign up for using the MindMeld API.
 *  @param userToken The API token that will be used to access the API.
 *  @param userID    The ID of the user that will be used to access the API.
 *  @param sessionID The session to which the object belongs.
 *  @param objectID  The ID of the object being modeled.
 *
 *  @return An object model for the specified object.
 */
- (instancetype)initWithAppID:(NSString *)appID
                    userToken:(NSString *)userToken
                       userID:(NSString *)userID
                    sessionID:(NSString *)sessionID
                     objectID:(NSString *)objectID;

/**
 *  Creates an object with the provided API credentials and update handlers
 *
 *  @param appID          The app ID created via MindMeld Dev Center. This will be given to you
 *                        when you sign up for using the MindMeld API.
 *  @param userToken      The API token that will be used to access the API.
 *  @param userID         The ID of the user that will be used to access the API.
 *  @param sessionID      The session to which the object belongs.
 *  @param successHandler The handler which will be called when updates to this object are successful
 *  @param failureHandler The handler which will be called when updates to this object are not successful
 *
 *  @return the object
 */
- (instancetype)initWithAppID:(NSString *)appID
                    userToken:(NSString *)userToken
                       userID:(NSString *)userID
                    sessionID:(NSString *)sessionID
                    onSuccess:(MMObjectUpdateSuccessHandler)successHandler
                    onFailure:(MMObjectUpdateFailureHandler)failureHandler;

/**
 *  This method saves the data in the object to disk. This is called automatically when the json dictionary is changed, either by the API or manually.
 */
- (void)backupData;

/**
 *  Restores the data of this object from disk.
 *
 *  @param successHandler The block that will be called when the data is restored.
 *  @param failureHandler   The block that will be called is the data failed to be restored.
 */
- (void)restoreOnSuccess:(MMSuccessHandler)successHandler
               onFailure:(MMFailureHandler)failureHandler;

- (void)clearCache;

/**
 *  This method posts to this object. If the object is a collection, a new item is added to the collection. If the object is a single item,
 *  then the data is updated.
 *
 *  @param body           The dictionary that contains the data to be posted.
 *  @param successHandler The handler that will be called when the post is complete.
 *  @param failureHandler The handler that will be called when the post fails.
 */
- (void)postWithBody:(NSDictionary *)body
           onSuccess:(MMSuccessHandler)successHandler
           onFailure:(MMFailureHandler)failureHandler;

/**
 *  This method completely reloads the data stored in this object by fetching a clean copy of the data from the MindMeld API.
 */
- (void)reloadData;

/**
 *  This method queries a collection with parameters.
 *
 *  @param params         The parameters for the query. An example is quering the documents collection for
 *                        documents of type "video".
 *  @param successHandler The block that will be called when the call succedess.
 *  @param failureHandler The block that will be called when the call fails.
 */
- (void)getWithParams:(NSDictionary *)params
            onSuccess:(MMSuccessHandler)successHandler
            onFailure:(MMFailureHandler)failureHandler;

/**
 *  This method frees the memory of the object, by removing the data stored in the json dictionary.
 */
- (void)freeMemory;

/**
 *  Removes the "data" section of the json dictionary.
 */
- (void)clearData;

/**
 *  Sets the json dictionary stored in this object. This manually sets the data of this particular object.
 *
 *  @param object The JSON dictionary that is the data source for this object.
 */
- (void)setJSONWithObject:(id)object;

/**
 *  The JSON object that contains the data for this object.
 *
 *  @return The JSON object that contains the data for this object.
 */
@property (atomic, strong, readonly) id json;

- (void)callAPI;
- (void)callAPIWithPath:(NSString *)path;
- (void)callAPIWithPath:(NSString *)path
              onSuccess:(MMSuccessHandler)successHandler
              onFailure:(MMFailureHandler)failureHandler;

@property (atomic, copy, readonly, getter=getFileUrl) NSURL *fileUrl;

@property (nonatomic, readonly, copy, getter=getPushChannelName) NSString *pushChannelName;
@property (nonatomic, readonly, copy, getter=getPushEventName) NSString *pushEventName;

- (NSArray *)dictForField:(NSString *)name
                withValue:(NSString *)value;
- (NSDictionary *)dictForID:(NSString *)objectID;

/**
 *  Returns the value associated with a given key from within the object's underlying data. This is a shortcut for 
 *  `object.json[key]`.
 *
 *  @param key The key for which to return the corresponding value.
 *
 *  @return The value associated with key, or nil if no value is associated with key.
 */
- (id)objectForKeyedSubscript:(id)key;

/**
 *  Sets the interval between polling updates.
 *
 *  @param pollingInterval The interval between polling updates.
 */
- (void)setPollingInterval:(double)pollingInterval;

/**
 *  This method start push updates for this object. If the property "useBothPushAndPull" is set to YES, then polling on this object is also started, which will be done at the interval set by setPollingInterval:.
 */
- (void)startUpdates;

/**
 *  Stops both the push and polling updates for this object.
 */
- (void)stopUpdates;


#pragma mark - deprecated

@property (nonatomic, copy, readwrite) NSString *mmSessionId DEPRECATED_ATTRIBUTE;
@property (nonatomic, weak, readwrite) id delegate DEPRECATED_ATTRIBUTE;
@property (nonatomic, assign, readwrite) SEL onSuccess DEPRECATED_ATTRIBUTE;
@property (nonatomic, assign, readwrite) SEL onFail DEPRECATED_ATTRIBUTE;

- (instancetype)initWithAppId:(NSString *)appID
                    userToken:(NSString *)userToken
                       userID:(NSString *)userID
         andMindmeldSessionId:(NSString *)sessionID
                andObjectName:(NSString *)objectName
                  andDelegate:(id)delegate
                  andSelector:(SEL)onSuccess DEPRECATED_ATTRIBUTE;

-  (instancetype)initWithAppID:(NSString *)appID
                     userToken:(NSString *)userToken
                        userID:(NSString *)userID
          andMindmeldSessionId:(NSString *)sessionID
                 andObjectName:(NSString *)objectName
                   andDelegate:(id)delegate
                   andSelector:(SEL)onSuccess
            andFailureSelector:(SEL)onFail DEPRECATED_ATTRIBUTE;

- (void)invokeDelegate:(id)result DEPRECATED_ATTRIBUTE;
- (void)invokeFailureDelegate:(NSError *)error DEPRECATED_ATTRIBUTE;
- (NSDictionary *)dictForId:(NSString *)objectID DEPRECATED_ATTRIBUTE;

- (void)deleteWithId:(NSString *)objectID
           onSuccess:(MMSuccessHandler)successHandler
              onFail:(MMFailureHandler)failureHandler DEPRECATED_ATTRIBUTE;

- (void)setJsonWithObject:(id)object DEPRECATED_ATTRIBUTE;

- (void)callApi DEPRECATED_ATTRIBUTE;
- (void)callApiWithPath:(NSString *)path DEPRECATED_ATTRIBUTE;
- (void)callApiWithPath:(NSString *)path
           successBlock:(MMSuccessHandler)successHandler
           andFailBlock:(MMFailureHandler)failureHandler DEPRECATED_ATTRIBUTE;

- (void)restoreOnSuccess:(MMSuccessHandler)successHandler
                  onFail:(MMFailureHandler)failureHandler DEPRECATED_ATTRIBUTE;

- (void)getWithParams:(NSDictionary *)params
            onSuccess:(MMSuccessHandler)successHandler
               onFail:(MMFailureHandler)failureHandler DEPRECATED_ATTRIBUTE;
- (void)postWithBody:(NSDictionary *)body
           onSuccess:(MMSuccessHandler)successHandler
              onFail:(MMFailureHandler)failureHandler DEPRECATED_ATTRIBUTE;

@end


DEPRECATED_ATTRIBUTE
@interface ManagedDataObject : MMObject
@end

