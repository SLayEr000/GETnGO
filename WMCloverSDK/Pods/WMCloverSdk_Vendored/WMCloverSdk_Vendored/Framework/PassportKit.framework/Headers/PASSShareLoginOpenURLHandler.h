//
//  PASSShareLoginOpenURLHandler.h
//  PassportKit
//
//  Created by jiangzhenjie on 2018/7/10.
//  Copyright © 2018年 Baidu Passport. All rights reserved.
//

#import "PASSOpenURLHandler.h"

@interface PASSShareLoginOpenURLHandler : PASSOpenURLHandler

+ (void)requestShareLoginWithTargetScheme:(NSString *)targetScheme;

@end
