//
//  CatchCrash.h
//  JITMiddleWareSDK
//
//  Created by JITPlatform001 on 2018/1/17.
//  Copyright © 2018年 jit. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface CatchCrash : NSObject

void uncaughtExceptionHandler(NSException *exception);

@end
