//
//  MMEntity.h
//  mindmeld-ios-sdk
//
//  Created by Juan Rodriguez on 11/28/13.
//  Copyright (c) 2013 Expect Labs. All rights reserved.
//

#import "MMObject.h"

/**
 *  Represents the object [Entity](/docs/endpointEntity) in the MindMeld API. This object identifies
 *  an individual logical concept associated with a Session. For example,
 *  an Entity could be a proper noun, such as the name of a person or company,
 *  or it could also be any noun phrase describing a single concept indicative
 *  of the context of a Session. Entities can be either posted directly to a
 *  Session or derived automatically from submitted TextEntry objects.
 *  For examples on how to update this object, look at the [Code Examples](/docs/sdks/ios/codeSnippets#iosCodeSnippet10).
 */
@interface MMEntity : MMObject

/**
 *  This method is deprecated. Instead use [MMObject initWithAppID:userToken:userID:sessionID:objectID:].
 *
 *  @see [MMObject initWithAppID:userToken:userID:sessionID:objectID:]
 *
 *  @param appID     The app ID created via MindMeld Dev Center. This will be given to you
 *                   when you sign up for using the MindMeld API.
 *  @param userToken The API token that will be used to access the API.
 *  @param userID    The ID of the user that will be used to access the API.
 *  @param sessionID The session to which the object belongs.
 *  @param entityID  The ID of the entity.
 *
 *  @return the corresponding entity
 */
- (instancetype)initWithAppID:(NSString *)appID
                    userToken:(NSString *)userToken
                       userID:(NSString *)userID
            mindmeldSessionId:(NSString *)sessionID
                  andEntityId:(NSString *)entityID DEPRECATED_ATTRIBUTE;

@end
