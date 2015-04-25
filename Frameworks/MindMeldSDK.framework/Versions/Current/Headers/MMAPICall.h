//
//  MMAPICall.h
//  MindMeld
//
//  Created by Timothy Tuttle on 10/14/11.
//  Copyright 2011 Expect Labs, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "MMBlockTypes.h"

@class MMAPICall;
@class WebConnection;

@interface MMAPICall : NSObject

@property (atomic, strong, readwrite) id result;
@property (atomic, strong, readwrite) NSError *error;

// Properties used for API calls, the come from MMApp
@property (atomic, copy, readwrite) NSString *appID;
@property (atomic, copy, readwrite) NSString *userToken;
@property (atomic, copy, readwrite) NSString *userID;

@property (nonatomic, copy, readwrite) MMAPICallResponseHandler onSuccess;
@property (nonatomic, copy, readwrite) MMAPICallResponseHandler onFailure;

@property (atomic, copy, readwrite) NSString *method;
@property (atomic, copy, readwrite) NSString *path;
@property (atomic, strong, readwrite) NSDictionary *params;
@property (atomic, strong, readwrite) NSDictionary *body;


@property (atomic, strong, readwrite) WebConnection *webConn;
@property (atomic, assign, readwrite) int cancelled;

+ (instancetype)callWithAppID:(NSString *)appID
                    userToken:(NSString *)userToken
                       method:(NSString *)method
                         path:(NSString *)path
                       params:(NSDictionary *)params
                         body:(NSDictionary*)body
                    onSuccess:(MMAPICallResponseHandler)successBlock
                    onFailure:(MMAPICallResponseHandler)failBlock;

- (instancetype)initWithAppID:(NSString *)appID
                    userToken:(NSString *)userToken;

- (instancetype)initWithAppID:(NSString *)appID
                    userToken:(NSString *)userToken
                       method:(NSString *)method
                         path:(NSString *)path
                       params:(NSDictionary *)params
                         body:(NSDictionary *)body
                    onSuccess:(MMAPICallResponseHandler)successBlock
                    onFailure:(MMAPICallResponseHandler)failBlock;

- (void)callWithMethod:(NSString *)method
                  path:(NSString *)path
                params:(NSDictionary *)params
             onSuccess:(MMAPICallResponseHandler)successBlock
             onFailure:(MMAPICallResponseHandler)failBlock;

- (void)call;

- (void)cancel;

- (void)setAllParams;

@property (atomic, copy, readonly) NSString *serializeURL;

- (id)parseJSONResponse:(NSData *)data
                  error:(NSError **)error;


- (id)formError:(NSInteger)code userInfo:(NSDictionary *)errorData;


@end

#pragma mark - Deprecated

DEPRECATED_ATTRIBUTE
@interface MMApiCall : MMAPICall

@property (nonatomic, copy, readwrite) MMApiCallSuccessBlock successBlock DEPRECATED_ATTRIBUTE;
@property (nonatomic, copy, readwrite) MMApiCallFailBlock failBlock DEPRECATED_ATTRIBUTE;


+ (instancetype)callWithAppID:(NSString *)appID
                    userToken:(NSString *)userToken
                       method:(NSString *)method
                         path:(NSString *)path
                       params:(NSDictionary *)params
                         body:(NSDictionary*)body
                    onSuccess:(MMApiCallSuccessBlock)successBlock
                       onFail:(MMApiCallFailBlock)failBlock DEPRECATED_ATTRIBUTE;

- (instancetype)initWithAppID:(NSString *)appID
                    userToken:(NSString *)userToken
                       method:(NSString *)method
                         path:(NSString *)path
                       params:(NSDictionary *)params
                         body:(NSDictionary *)body
                    onSuccess:(MMApiCallSuccessBlock)successBlock
                       onFail:(MMApiCallFailBlock)failBlock DEPRECATED_ATTRIBUTE;

- (void)callWithMethod:(NSString *)method
                  path:(NSString *)path
                params:(NSDictionary *)params
             onSuccess:(MMApiCallSuccessBlock)successBlock
                onFail:(MMApiCallFailBlock)failBlock DEPRECATED_ATTRIBUTE;

- (id)parseJsonResponse:(NSData *)data
                  error:(NSError **)error DEPRECATED_ATTRIBUTE;

@end

