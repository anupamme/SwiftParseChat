//
//  EntityList.h
//  MindMeld
//
//  Created by Timothy Tuttle on 10/20/11.
//  Copyright 2011 Expect Labs, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "MMCollection.h"
#import "MMEntity.h"

/**
 *  Represents the [Entities](/docs/endpointSession#getSessionSessionidEntities) collection
 *  in the MindMeld API. The history of [Entity](/docs/endpointEntity) objects,
 *  which are derived from TextEntries or directly posted to the Session.
 *  For examples on how to update this object, look at the [Code Examples](/docs/sdks/ios/codeSnippets#iosCodeSnippet10).
 */
@interface MMEntityList : MMCollection

/**
 *  This method returns an entity inside this list.
 *  This method is deprecated. Instead use [MMCollection objectForID:].
 *
 *  @param objectID The ID of the entity to be fetched.
 *
 *  @return The MMEntity that was found in this list.
 *  @see [MMCollection objectForID:]
 */
- (MMEntity *)objectForId:(NSString *)objectID DEPRECATED_ATTRIBUTE;

@end
