//
//  WeiMaTool.h
//  SuperTool
//
//  Created by JITPlatform001 on 2018/1/5.
//  Copyright © 2018年 JIT. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface WeiMaTool : NSObject

/**
 * 非对称密钥生成
 * @author  han harvey
 * @param   keyPairType     密钥类型
 * @param   keyPairLen      密钥长度
 * @param   keyPairData    【出参】公钥数据
 * @remarks 备注 产生密钥对
 * @return  0:成功 其他值:错误码
 */
- (int)generateKeyPair:(NSString *)keyPairType andKeyPairLength:(NSString *)keyPairLen andKeyPair:(NSData **)keyPairData;

/**
 * 生成证书主题
 * @author  han harvey
 * @param   userID          UserID
 * @param   deviceID        DeviceID
 * @param   devFingerprint  设备指纹
 * @param   subjectStr     【出参】证书主题
 * @remarks 备注 生成证书主题
 * @return  0:成功 其他值:错误码
 */
- (int)generateDN:(NSString *)userID andDevID:(NSString *)deviceID andDevFingerprint:(NSString *)devFingerprint andCertDN:(NSString **)subjectStr;

/**
 * 证书申请生成
 * @author  han harvey
 * @param   subject         主题
 * @param   keyPairData     公钥数据
 * @param   p10ValB64Str   【出参】P10证书申请
 * @remarks 备注 产生PKCS10证书申请
 * @return  0:成功 其他值:错误码
 */
- (int)genP10:(NSString *)subject andKeyPair:(NSString *)keyPairData andP10ValB64:(NSString **)p10ValB64Str;

/**
 * 导入证书
 * @author  han harvey
 * @param   keyPairType     密钥类型
 * @param   p7bStr          证书数据
 * @remarks 备注 根据P7B证书链导入证书
 * @return  0:成功 其他值:错误码
 */
- (int)importCertWithP7b:(NSString *)keyPairType andP7b:(NSString *)p7bStr;

/**
 * 制作P7签名
 * @author  han harvey
 * @param   certSN          证书序列号
 * @param   digestAlg       摘要算法
 * @param   certB64         公钥数据
 * @param   srcData         待签名数据
 * @param   p7SignValB64Str【出参】签名结果
 * @remarks 备注 根据手机私钥和RefreshToken随机数生成签名
 * @return  0:成功 其他值:错误码
 */
- (int)signP7:(NSString *)certSN andDigestAlg:(NSString *)digestAlg andCertB64:(NSString *)certB64 andSrc:(NSData *)srcData andP7SignValB64:(NSString **)p7SignValB64Str;

/**
 * 验证P7签名
 * @author  han harvey
 * @param   p7SignValB64Str         P7签名数据
 * @param   p7VerifySignValData    【出参】P7验签结果
 * @remarks 备注 根据TSP公钥验证签名
 * @return  0:成功 其他值:错误码
 */
- (int)verifySignP7:(NSString *)p7SignValB64Str andVerifySignVal:(NSData **)p7VerifySignValData;

/**
 * 制作P1签名
 * @author  han harvey
 * @param   srcData             待签名数据
 * @param   digestAlg           摘要算法
 * @param   keyPairIndex        密钥索引
 * @param   p1SignValB64Str    【出参】签名结果
 * @remarks 备注 使用App私钥对数据进行签名
 * @return  0:成功 其他值:错误码
 */
- (int)signP1:(NSData *)srcData andDigestAlg:(NSString *)digestAlg andKeyPairIndex:(int)keyPairIndex andP1SignValB64:(NSString **)p1SignValB64Str;

/**
 * P1验签名
 * @author  han harvey
 * @param   srcData             签名数据
 * @param   p1SignValB64Str     P1签名结果
 * @param   certB64             公钥数据
 * @remarks 备注 根据TSP公钥验证签名
 * @return  0:成功 其他值:错误码
 */
- (int)verifySignP1:(NSData *)srcData andP1SignValB64:(NSString *)p1SignValB64Str andCertB64:(NSString *)certB64;

/**
 * 制作加密信封
 * @author  han harvey
 * @param   certB64         公钥数据
 * @param   alg             加密算法
 * @param   srcData         待加密数据
 * @param   encValB64Str   【出参】数字信封
 * @remarks 备注 根据TSP公钥对数据进行加密生成加密信封
 * @return  0:成功 其他值:错误码
 */
- (int)encryptP7:(NSString *)certB64 andEncAlg:(NSString *)alg andSrc:(NSData *)srcData andEncValB64:(NSString **)encValB64Str;

/**
 * 解密数字信封
 * @author  han harvey
 * @param   encValB64Str    信封数据
 * @param   privKeyIndex    私钥索引
 * @param   srcData        【出参】签名数据
 * @remarks 备注 使用手机私钥进行数据解密
 * @return  0:成功 其他值:错误码
 */
- (int)decryptP7:(NSString *)encValB64Str andPrivKeyIndex:(int)privKeyIndex andEncSrc:(NSData **)srcData;

@end
