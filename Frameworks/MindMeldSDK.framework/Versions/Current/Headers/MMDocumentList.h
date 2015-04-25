//
//  MMDocumentList.h
//  mindmeld-ios-sdk
//
//  Created by Juan on 2/4/14.
//  Copyright (c) 2014 Expect Labs. All rights reserved.
//

#import "MMCollection.h"
#import "MMDocument.h"

/**
 *  Represents a documents collection a searchable corpus of [Document](/docs/endpointDocument) 
 *  objects. There are two document collections in the MindMeld API. The [Session Documents](/docs/endpointSession#getSessionSessionIDDocuments)
 *  collection includes documents that are contextually related to a session. The [Domain Documents](/docs/endpointDomain#getDomainDomainIDDocuments)
 *  collection includes documents that belong to a domain.
 *  For examples on how to update this object, look at the [Code Examples](/docs/sdks/ios/codeSnippets#iosCodeSnippet10).
 */
@interface MMDocumentList : MMCollection

/**
 *  This method returns a document inside this list.
 *  This method is deprecated. Instead use [MMCollection objectForID:].
 *
 *  @param objectID The ID of the document to be fetched.
 *
 *  @return The MMDocument that was found in this list.
 *  @see [MMCollection objectForID:]
 */
- (MMDocument *)objectForId:(NSString *)objectID DEPRECATED_ATTRIBUTE;

@end

