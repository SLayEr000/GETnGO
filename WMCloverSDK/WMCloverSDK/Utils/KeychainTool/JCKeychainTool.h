//
//  JCKeychainTool.h
//  Clover
//
//  Created by 🧍‍♀️ on 2020/12/29.
//  Copyright © 2020 guiming.zheng. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Security/Security.h>
@interface JCKeychainTool : NSObject

/**
 *  储存字符串到🔑钥匙串
 *
 *  @param sValue 对应的Value
 *  @param sKey   对应的Key
 */
+ (void)saveKeychainValue:(NSString *)sValue key:(NSString *)sKey;


/**
 *  从🔑钥匙串获取字符串
 *
 *  @param sKey 对应的Key
 *
 *  @return 返回储存的Value
 */
+ (NSString *)readKeychainValue:(NSString *)sKey;


/**
 *  从🔑钥匙串删除字符串
 *
 *  @param sKey 对应的Key
 */
+ (void)deleteKeychainValue:(NSString *)sKey;


@end
