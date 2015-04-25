//
//  MMTextEntry.h
//  mindmeld-ios-sdk
//
//  Created by Juan Rodriguez on 11/28/13.
//  Copyright (c) 2013 Expect Labs. All rights reserved.
//

#import "MMObject.h"

/**
 *  Represents the object [TextEntry](/docs/endpointTextEntry) in the MindMeld API. This object
 *  represents each individual text-based contextual signal sent to the
 *  MindMeld Platform. Each TextEntry captures a segment of human-language
 *  text that will be lexically and semantically analyzed by the MindMeld Platform.
 *  For examples on how to update this object, look at the [Code Examples](/docs/sdks/ios/codeSnippets#iosCodeSnippet10).
 */
@interface MMTextEntry : MMObject

/**
 *  Creates a text entry object
 *
 *  @param appID       The app ID created via MindMeld Dev Center. This will be given to you
 *                     when you sign up for using the MindMeld API.
 *  @param userToken   The API token that will be used to access the API.
 *  @param userID      The ID of the user that will be used to access the API.
 *  @param sessionID   The session to which the object belongs.
 *  @param objectID The ID of the text entry.
 *  @param json        The json containing the text entry's data.
 *
 *  @return the corresponding text entry
 */
- (instancetype)initWithAppID:(NSString *)appID
                    userToken:(NSString *)userToken
                       userID:(NSString *)userID
                    sessionID:(NSString *)sessionID
                     objectID:(NSString *)objectID
                         json:(NSDictionary *)json;

/**
 *  This method is deprecated. Instead use initWithAppID:userToken:userID:sessionID:objectID:json.
 *
 *  @see initWithAppID:userToken:userID:sessionID:objectID:json:
 *
 *  @param appID       The app ID created via MindMeld Dev Center. This will be given to you
 *                     when you sign up for using the MindMeld API.
 *  @param userToken   The API token that will be used to access the API.
 *  @param userID      The ID of the user that will be used to access the API.
 *  @param sessionID   The session to which the object belongs.
 *  @param textEntryID The ID of the text entry.
 *  @param json        The json containing the text entry's data.
 *
 *  @return the corresponding text entry
 */
- (instancetype)initWithAppID:(NSString *)appID
                    userToken:(NSString *)userToken
                       userID:(NSString *)userID
            mindmeldSessionId:(NSString *)sessionID
               andTextEntryId:(NSString *)textEntryID
                      andJson:(NSDictionary *)json DEPRECATED_ATTRIBUTE;

@end
