//
//  MMDocument.h
//  mindmeld-ios-sdk
//
//  Created by Juan on 2/4/14.
//  Copyright (c) 2014 Expect Labs. All rights reserved.
//

#import "MMObject.h"

/**
 *  Represents the object [Document](/docs/endpointDocument) in the MindMeld API. This object
 *  refers to a single web page or document that has been indexed and
 *  made searchable within your App. You can specify the Document objects
 *  you would like the MindMeld Platform to index when you configure your
 *  App in the Developer Console. For example, the MindMeld API can create
 *  your index of Documents by automatically crawling a specified website;
 *  you can also post individual Document objects directly to your index using the MindMeld API.
 */
@interface MMDocument : MMObject

@property (nonatomic, copy, readonly) NSString *domainID;

- (instancetype)initWithAppID:(NSString *)appID
                    userToken:(NSString *)userToken
                       userID:(NSString *)userID
                     domainID:(NSString *)domainID
                   documentID:(NSString *)documentID;

/**
 *  This method is deprecated. Instead use [MMObject initWithAppID:userToken:userID:sessionID:objectID:].
 *
 *  @see [MMObject initWithAppID:userToken:userID:sessionID:objectID:]
 *
 *  @param appID       The app ID created via MindMeld Dev Center. This will be given to you
 *                     when you sign up for using the MindMeld API.
 *  @param userToken   The API token that will be used to access the API.
 *  @param userID      The ID of the user that will be used to access the API.
 *  @param sessionID   The session to which the object belongs.
 *  @param documentID  The ID of the document.
 *
 *  @return the corresponding document
 */
- (instancetype)initWithAppID:(NSString *)appID
                    userToken:(NSString *)userToken
                       userID:(NSString *)userID
            mindmeldSessionId:(NSString *)sessionID
                andDocumentId:(NSString *)documentID DEPRECATED_ATTRIBUTE;

@end
