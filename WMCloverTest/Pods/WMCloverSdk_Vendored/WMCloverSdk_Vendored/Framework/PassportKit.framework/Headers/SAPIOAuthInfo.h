//
//  SAPIOAuthInfo.h
//  SAPILib
//
//  Created by jinsong on 1/12/16.
//  Copyright © 2016 baidu. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface SAPIOAuthInfo : NSObject

/**
 *  百度开放平台accesstoken
 */
@property (nonatomic, copy) NSString *accessToken;

/**
 *  百度开放平台refreshToken
 */
@property (nonatomic, copy) NSString *refreshToken;

/**
 *  百度开放平台scope
 */
@property (nonatomic, copy) NSString *scope;

/**
 *  百度开放平台sessionKey
 */
@property (nonatomic, copy) NSString *sessionKey;

/**
 *  百度开放平台sessionSecret
 */
@property (nonatomic, copy) NSString *sessionSecret;

/**
 *  百度开放平台expiresIn
 */
@property (nonatomic, assign) NSUInteger expiresIn;

/**
 *  根据传入参数初始化SAPIOAuthInfo实例
 *
 *  @param info 传入键值对
 *
 *  @return SAPIOAuthInfo实例
 */
- (instancetype)initWithDictionary:(NSDictionary *)info;

/**
 *  将SAPIOAuthInfo实例转换为键值对
 *
 *  @return 转换后的键值对
 */
- (NSDictionary *)toDictionary;

@end
