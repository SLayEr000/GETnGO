//
//  WMFramework.h
//  WMCloverSDK
//
//  Created by apple on 2021/4/14.
//

#import <Foundation/Foundation.h>



@interface WMFramework : NSObject

+ (WMFramework*)defaultManager;

///注册
+ (void)registerWith:(UIApplication*)application launchOptions:(NSDictionary*)LaunchOptions;


@end


