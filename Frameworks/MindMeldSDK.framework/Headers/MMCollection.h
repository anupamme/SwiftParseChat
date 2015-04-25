//
//  MMCollection.h
//  mindmeld-ios-sdk
//
//  Created by J.J. Jackson on 30/09/14.
//  Copyright (c) 2014 Expect Labs. All rights reserved.
//

#import "MMObject.h"

@protocol MMCollectionOwner;

/**
 *  This is the base class for all the API collection objects. This is where functionality specific to getting
 *  data from and pushing data to the API collection endpoints is located.
 *  This class should never be used directly. Instead it's subclasses, such as MMDocumentList, MMSessionList,
 *  etc., are used.
 *  For examples on how to use this class to update the API objects, look at the
 *  [Code Examples](/docs/sdks/ios/codeSnippets#iosCodeSnippet10).
 */
@interface MMCollection : MMObject

@property (nonatomic, weak) id <MMCollectionOwner> owner;

/**
 * The count of objects in the collection.
 */
@property(readonly) NSUInteger count;

- (instancetype)initWithOwner:(id <MMCollectionOwner>)owner;

- (instancetype)initWithOwner:(id <MMCollectionOwner>)owner
                    onSuccess:(MMObjectUpdateSuccessHandler)successHandler
                    onFailure:(MMObjectUpdateFailureHandler)failureHandler;

/**
 * Returns the object at index `index`.  If `index` is beyond the end of the
 * list, an `NSRangeException` is raised. This is equivalent to `collection.json[i]`.
 *
 *  @param index     The index within the bounds of the array.
 *
 *  @return the object at index `index`
 */
- (id)objectAtIndex:(NSUInteger)index;

/**
 *  Identical to objectAtIndex:
 *
 *  @param index     The index within the bounds of the array.
 *
 *  @return the object at index `index`
 */
- (id)objectAtIndexedSubscript:(NSUInteger)index;


/**
 *  This method returns the an instance of the MMObject subclass appropriate for this collection, with the specified
 *  ID from this collection, or nil if no such object exists locally.
 *
 *  @param objectID The ID of the object to be returned.
 *
 *  @return The object that was found in this collection.
 */
- (id)objectForID:(NSString *)objectID;

/**
 *  Identical to objectForID:. If `key` is not a string, nil is returned.
 *
 *  @param key The ID of the object to be returned.
 *
 *  @return The object that was found in this collection.
 */
- (id)objectForKeyedSubscript:(id)key;


/**
 *  This method can only be called on a collection object, and deletes a particular item inside the collection.
 *
 *  @param objectID       The ID of the object that will be deleted.
 *  @param successHandler The block that will be called when the object is deleted.
 *  @param failureHandler The block that will be called when the object fails to be deleted.
 */
- (void)deleteWithID:(NSString *)objectID
           onSuccess:(MMSuccessHandler)successHandler
           onFailure:(MMFailureHandler)failureHandler;

/**
 *  This method is deprecated. Instead use [MMObject initWithAppID:userToken:userID:sessionID:onSuccess:onFailure:].
 *
 *  @see [MMObject initWithAppID:userToken:userID:sessionID:onSuccess:onFailure:]
 *
 *  @param appID     The app ID created via MindMeld Dev Center. This will be given to you
 *                   when you sign up for using the MindMeld API.
 *  @param userToken The API token that will be used to access the API.
 *  @param userID    The ID of the user that will be used to access the API.
 *  @param sessionID The session to which the collection belongs.
 *  @param delegate  the delegate
 *
 *  @return the collection
 */
- (instancetype)initWithAppID:(NSString *)appID
                    userToken:(NSString *)userToken
                       userID:(NSString *)userID
         andMindmeldSessionId:(NSString *)sessionID
                  andDelegate:(id)delegate DEPRECATED_ATTRIBUTE;

@end

@protocol MMCollectionOwner

// the api path of the collection owner
- (NSString *)apiPath;

- (NSString *)token;
- (NSString *)appID;
- (NSString *)userID;
- (NSString *)sessionID;

@end
