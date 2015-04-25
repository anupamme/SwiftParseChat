//
//  MMTextEntryList.h
//  mindmeld-ios-sdk
//
//  Created by Juan Rodriguez on 11/20/13.
//  Copyright (c) 2013 Expect Labs. All rights reserved.
//

#import "MMCollection.h"
#import "MMTextEntry.h"

/**
 *  Represents the [TextEntries](/docs/endpointSession#getSessionSessionidTextentries) collection
 *  in the MindMeld API. The history of [TextEntry](/docs/endpointTextEntry) objects posted to the Session.
 *  For examples on how to update this object, look at the [Code Examples](/docs/sdks/ios/codeSnippets#iosCodeSnippet10).
 */
@interface MMTextEntryList : MMCollection

/**
 *  This method returns a text entry inside this list.
 *  This method is deprecated. Instead use [MMCollection objectForID:].
 *
 *  @param objectID The ID of the text entry to be fetched.
 *
 *  @see [MMCollection objectForID:]
 */
- (MMTextEntry *)objectForId:(NSString *)objectID DEPRECATED_ATTRIBUTE;
@end

