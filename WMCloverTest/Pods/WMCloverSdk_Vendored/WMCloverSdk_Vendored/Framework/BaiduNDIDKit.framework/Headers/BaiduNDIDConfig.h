//
//  BaiduNDIDConfig.h
//  BaiduNDIDKit
//
//  Created by jiangzhenjie on 2018/1/15.
//  Copyright © 2018年 Baidu Passport. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "BaiduPassEnum.h"

NS_ASSUME_NONNULL_BEGIN

/**
 NDID 配置项
 */
@interface BaiduNDIDConfig : NSObject

/**
 环境，默认是线上环境。可选
 */
@property (nonatomic, assign) BaiduPassEnv environment;

/**
 是否开启Debug模式
 */
@property (nonatomic, assign) BOOL debug;

/**
 配置项构造方法

 @return 配置项实例
 */
+ (instancetype)config;

@end

NS_ASSUME_NONNULL_END
