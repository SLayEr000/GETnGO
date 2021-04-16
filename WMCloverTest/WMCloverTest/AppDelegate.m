//
//  AppDelegate.m
//  WMCloverTest
//
//  Created by apple on 2021/4/15.
//

#import "AppDelegate.h"
#import <WMCloverSDK/WMFramework.h>
@interface AppDelegate ()

@end

@implementation AppDelegate


- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
    // Override point for customization after application launch.
    [WMFramework defaultManager] ;
    return YES;
}




@end
