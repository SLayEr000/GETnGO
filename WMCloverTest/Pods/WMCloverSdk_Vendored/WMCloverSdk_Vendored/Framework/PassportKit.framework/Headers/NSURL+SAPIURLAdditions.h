//
//  NSURL+SAPIURLAdditions.h
//  SAPILib
//
//  Created by jinsong on 1/13/16.
//  Copyright © 2016 baidu. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface NSURL (SAPIURLAdditions)

// 如果 keyInQuery 不在查询字符串里面，则返回 nil；如果存在但没有值，则返回空字符
- (NSString *)sapi_valueInQueryForKey:(NSString *)keyInQuery;

- (NSDictionary *)sapi_allParametersInQuery;

// 键值为中文或特殊字符时需要URL Encode后传入
- (NSURL *)sapi_URLByAddingExtraParams:(NSDictionary *)extraParams;

// 键值为中文或特殊字符时需要URL Encode后传入
- (NSURL *)sapi_URLByAddingExtraParams:(NSDictionary *)extraParams priorityExtraParams:(BOOL)priorityExtraParams;

@end
