//
//  SAPIRegisterService.h
//  SAPILib
//
//  Created by Vinson.D.Warm on 13-9-26.
//  Copyright (c) 2013年 baidu. All rights reserved.
//

@interface SAPIRegisterService : NSObject

/**
 *  上行短信注册
 *
 *  @param smsContent      短信内容
 *  @param completionBlock 完成时回调
 *  @param errorBlock      失败时回调
 */
- (void)registerAtOnceWithSMSContent:(NSString *)smsContent
                        onCompletion:(SAPIRequestCompletionBlock)completionBlock
                             onError:(SAPIRequestErrorBlock)errorBlock DEPRECATED_MSG_ATTRIBUTE("Use -[SAPILoginService registerBySendSMS:timeout:success:failure:] instead");

- (void)cancelRequest;

@end
