//
//  NoticeCallback.h
//  hmisdk
//
//  Created by v_xiaowenzhang on 2020/2/11.
//  Copyright © 2020 baidu. All rights reserved.
//

#ifndef NoticeCallback_h
#define NoticeCallback_h

@protocol NoticeCallback<NSObject>

-(void)onNotice:(int)code msg:(NSString*)msg;

@end

#endif /* NoticeCallback_h */
