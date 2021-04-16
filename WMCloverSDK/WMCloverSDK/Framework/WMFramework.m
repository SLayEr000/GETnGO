//
//  WMFramework.m
//  WMCloverSDK
//
//  Created by apple on 2021/4/14.
//

#import "WMFramework.h"

@implementation WMFramework

+ (WMFramework *)defaultManager{
    static WMFramework *WMFramework_default = nil;
    static dispatch_once_t predicate;
    dispatch_once(&predicate, ^{
        WMFramework_default = [[self alloc] init];
    });
    return WMFramework_default;
}

+ (void)registerWith:(UIApplication*)application launchOptions:(NSDictionary*)LaunchOptions{
    WMFramework *framework = [WMFramework defaultManager];
    [framework initWithApplication:application launchOptions:LaunchOptions environment:WMFEnvironment_JKX];
}

- (void)initWithApplication:(UIApplication*)application launchOptions:(NSDictionary*)aLaunchOptions  environment:(WMFEnvironment)EnvironmentType{

}
@end
