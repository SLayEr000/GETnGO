//
//  NSString+SAPIStringAdditions.h
//  SAPILib
//
//  Created by jinsong on 5/12/15.
//  Copyright (c) 2015 baidu. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface NSString (SAPIStringAdditions)

- (NSString *)sapi_md5Encrypt;

- (NSString *)sapi_reverse;

- (NSString *)sapi_urlEncode;

+ (NSString *)sapi_uuid;

- (NSString *)sapi_stringByDecodingURLFormat;

- (BOOL)sapi_containtsString:(NSString *)aString;

- (BOOL)sapi_hasValue;

- (NSString *)sapi_trimString;

+ (NSString *)sapi_letterAndNumberRandomStringWithLength:(NSUInteger)length;

+ (NSString *)sapi_convertDataToHexStr:(NSData *)data;

@end
