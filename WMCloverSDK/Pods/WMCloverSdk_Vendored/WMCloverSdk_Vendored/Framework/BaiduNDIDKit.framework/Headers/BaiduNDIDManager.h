//
//  BaiduNDIDManager.h
//  BaiduNDIDKit
//
//  Created by Song,Bin(FFTD) on 2017/11/13.
//  Copyright © 2017年 Baidu Passport. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

// NDID Cookie Name 字段默认值，默认为 "NDID"
FOUNDATION_EXPORT NSString * const BaiduNDIDCookieDefaultName;
// NDID Cookie Name 字段备选值，值为 "BDPP_NDID"
FOUNDATION_EXPORT NSString * const BaiduNDIDCookieNameBDPPNDID;
// NDID Cookie Domain 字段默认值，默认为 ".baidu.com"
FOUNDATION_EXPORT NSString * const BaiduNDIDCookieDefaultDomain;

@class BaiduNDIDConfig;

/**
 NDID 主类
 */
@interface BaiduNDIDManager : NSObject

/**
 百度设备标识 NDID (Native Device Identifier)
 */
@property (nonatomic, copy, readonly) NSString *ndid;

/**
 NDID 配置项，通过 +[BaiduNDIDManager setConfig:] 设置
 */
@property (nonatomic, strong, readonly) BaiduNDIDConfig *config;

/**
 设置配置项，SDK初始化入口
 
 @important 传入 config 为 nil 时，将抛 NSInvalidArgumentException 异常

 @param config 配置项
 */
+ (void)setConfig:(BaiduNDIDConfig *)config;

/**
 单例
 
 @important 未调用 setConfig: 方法初始化时，该方法将返回 nil

 @return 单例对象
 */
+ (nullable instancetype)sharedManager;

@end

/**
 NDID Manager Cookie 扩展
 */
@interface BaiduNDIDManager (BaiduNDIDCookie)

/**
 获取 NDID Cookie 实例

 @return NDID Cookie 实例
 */
- (NSHTTPCookie *)ndidCookie;

/**
 获取 NDID Cookie 实例。使用非默认 name 或 domain 时可使用该方法创建

 @param name NDID Cookie 的 name 字段值，比如 "BDPP_NDID"
 @param domain NDID Cookie 的 domain 字段值，比如 ".nuomi.com"
 @return NDID Cookie 实例，传入 name 和 domain 字段长度为0时，返回nil
 */
- (nullable NSHTTPCookie *)ndidCookieForName:(NSString *)name domain:(NSString *)domain;

@end

NS_ASSUME_NONNULL_END
