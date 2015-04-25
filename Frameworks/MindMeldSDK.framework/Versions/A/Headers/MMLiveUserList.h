//
//  MMLiveUserList.h
//  mindmeld-ios-sdk
//
//  Created by Juan Rodriguez on 11/20/13.
//  Copyright (c) 2013 Expect Labs. All rights reserved.
//

#import "MMCollection.h"

@class MMUser;

/**
 *  Represents the [LiveUsers](/docs/endpointSession#getSessionSessionidLiveusers) collection
 *  in the MindMeld API. The list of [User](/docs/endpointUser) objects who are currently using the Session.
 *  For examples on how to update this object, look at the [Code Examples](/docs/sdks/ios/codeSnippets#iosCodeSnippet10).
 */
@interface MMLiveUserList : MMCollection

/*  This method returns a user inside this list.
 *  This method is deprecated. Instead use [MMCollection objectForID:].
 *
 *  @param objectID The ID of the user to be fetched.
 *
 *  @return The MMUser that was found in this list.
 *  @see [MMCollection objectForID:]
 */
- (MMUser *)objectForId:(NSString *)objectID DEPRECATED_ATTRIBUTE;

@end
