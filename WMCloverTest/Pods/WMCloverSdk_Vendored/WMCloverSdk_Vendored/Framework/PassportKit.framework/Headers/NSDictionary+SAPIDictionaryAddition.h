//
//  NSDictionary+SAPIDictionaryAddition.h
//  SAPILib
//
//  Created by jinsong on 2/3/15.
//  Copyright (c) 2015 baidu. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface NSDictionary (SAPIDictionaryAddition)

- (NSString *)sapi_stringForKey:(NSString *)key;

- (NSString *)sapi_stringForKey:(NSString *)key fallback:(NSString *)value;

- (NSInteger)sapi_integerForKey:(NSString *)key;

- (NSInteger)sapi_integerForKey:(NSString *)key fallback:(NSInteger)value;

- (NSArray *)sapi_arrayForKey:(NSString *)key;

- (NSArray *)sapi_arrayForKey:(NSString *)key fallback:(NSArray *)value;

- (NSDictionary *)sapi_dictionaryForKey:(NSString *)key;

- (NSDictionary *)sapi_dictionaryForKey:(NSString *)key fallback:(NSDictionary *)value;

- (BOOL)sapi_boolForKey:(NSString *)key;

- (BOOL)sapi_boolForKey:(NSString *)key fallback:(BOOL)value;

- (double)sapi_doubleForKey:(NSString *)key;

- (double)sapi_doubleForKey:(NSString *)key fallback:(double)value;

// equals [self sapi_query:YES];
- (NSString *)sapi_query;

- (NSString *)sapi_query:(BOOL)needURLEncode;

@end
