//
//  SAPIURLFactory.h
//  SAPILib
//
//  Created by Vinson.D.Warm on 2/14/14.
//  Copyright (c) 2014 baidu. All rights reserved.
//

#import <Foundation/Foundation.h>

#define ABSURL(X) [[SAPIURLFactory factory] getUrlStringByPath:X]

DEPRECATED_MSG_ATTRIBUTE("This class is deprecated and will be removed in a future release, you should avoid using this class anymore")
@interface SAPIURLFactory : NSObject

- (NSString *)getUrlStringByPath:(NSString *)path;

- (NSString *)getCurrentDomainName;

+ (SAPIURLFactory *)factory;

+ (NSString *)passportDomain;

+ (NSString *)wappassDomain;

@end
