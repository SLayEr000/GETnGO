//
//  PASSShareAuthorizeViewController.h
//  PassportKit
//
//  Created by jiangzhenjie on 2018/7/9.
//  Copyright © 2018年 Baidu Passport. All rights reserved.
//

#import "PASSBaseViewController.h"

@interface PASSShareAuthorizeViewModel: NSObject

@property (nonatomic, strong) UIImage *targetAppIcon;
@property (nonatomic, copy) NSString *targetAppName;
@property (nonatomic, copy) NSString *callbackScheme;

- (instancetype)initFromPasteboard;

@end

@interface PASSShareAuthorizeViewController : PASSBaseViewController

@property (nonatomic, copy) void(^submitAuthorizationHandler)(BOOL approval);

- (instancetype)initWithViewModel:(PASSShareAuthorizeViewModel *)viewModel;

@end
