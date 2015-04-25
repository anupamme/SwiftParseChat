//
//  MMDomain.h
//  mindmeld-ios-sdk
//
//  Created by J.J. Jackson on 12/15/14.
//  Copyright (c) 2014 Expect Labs. All rights reserved.
//

#import "MMObject.h"
#import "MMDocumentList.h"

/**
 *  Represents the object [Domain](/docs/endpointDomain) in the MindMeld API. TODO: add full description
 */
@interface MMDomain : MMObject <MMCollectionOwner>

/**
 *  The document list associated with this session object.
 */
@property (nonatomic, strong, readwrite) MMDocumentList *documents;

/**
 *  Creates an object with the provided API credentials and update handlers
 *
 *  @param appID          The app ID created via MindMeld Dev Center. This will be given to you
 *                        when you sign up for using the MindMeld API.
 *  @param userToken      The API token that will be used to access the API.
 *  @param userID         The ID of the user that will be used to access the API.
 *  @param domainID       The ID of the domain.
 *
 *  @return the domain object
 */
- (instancetype)initWithAppID:(NSString *)appID
                    userToken:(NSString *)userToken
                       userID:(NSString *)userID
                     domainID:(NSString *)domainID;

@end
