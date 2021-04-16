//
//  JITSafeModelTool.h
//  JITSafeModelTool
//
//  Created by han harvey on 2017/10/12.
//  Copyright © 2017年 JIT. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "JITSafeModel_Protocol.h"

#ifdef DEBUG
#define JITAPPLog(format, ...) printf("\n%s %s JIT-SafeModelLog %s(line%d) %s\n%s\n\n", __DATE__, __TIME__, [[[NSString stringWithUTF8String:__FILE__] lastPathComponent] UTF8String], __LINE__, __PRETTY_FUNCTION__, [[NSString stringWithFormat:(format), ##__VA_ARGS__] UTF8String])
#else
#define JITAPPLog(format, ...)
#endif



// 初始化成功还是失败
typedef void(^InitSuccessOrFailure)(BOOL *initState);

@interface JITSafeModelTool_Bluetooth : NSObject<SafeModel_Protocol>

@property (assign, nonatomic) SafeModel safeModel;
@property (assign, nonatomic) BOOL initOK;

@property (strong, nonatomic) NSString      *devName;           // 设备名称
@property (strong, nonatomic) NSString      *appName;           // 应用名称
@property (strong, nonatomic) NSString      *containerName;     // 容器名称
@property (assign, nonatomic) RSADigestAlg  rsaDigestAlg;       // rsa摘要算法

- (instancetype)initWithSafeType:(SafeModel)safeModel
                     andSavePath:(NSString *)savePath
               andDeviceIdentify:(NSString *)devIdentify;
//                      andSuccess:(void (^)(BOOL successOK))success;

/**
 * 设置做业务的证书
 * @author  han harvey
 * @param   containerName   容器名称
 * @param   password        证书密码
 * @remarks 备注 无
 * @return  0:成功 其他:错误码
 */
- (int)SetCertWithContainerName:(NSString *)containerName andDevName:(NSString *)strDevName andPassword:(NSString *)password;

/**
 * 获取密码模块的版本号
 * @author  han harvey
 * @remarks 备注 静态方法
 * @return  密码模块的当前版本号
 */
+ (NSString *)GetSafeModelVersion;

/**
 * 产生证书密钥对
 * @author  han harvey
 * @param   keyPairLen 证书密钥长度
 * @remarks 备注 国密证书、RSA 证书均支持
 * @return  0:成功 其他:错误码
 */
- (int)GenerateKeyPair:(KeyPairLength)keyPairLen andKeyPairData:(NSData **)keyPairData;

// 产生P10数据
- (int)CreatePKCS10:(NSString *)strCertCN andKeyPair:(NSData *)keyPairData andPass:(NSString *)passStr pkcs10Base64:(NSString **)ppRequestP10B64;

// 对P10申请数据做签名
- (int)CreatePKCS10Sign:(NSData *)srcData
                andPass:(NSString *)passStr
            andSignData:(NSData **)signData;

/**
 * 获取当前容器类型
 * @author  han harvey
 * @param   containerName   容器名称
 * @param   containerType   容器类型
 * @remarks 备注 containerType == 1 RSA
 * @return  0:成功 其他:错误码
 */
- (int)GetContainerType:(NSString *)containerName andType:(ContainerType *)containerType;

/**
 * 导入证书(更新证书)
 * @author  han harvey
 * @param   certData 公钥证书
 * @param   certFlag 证书标记（CertFlag_SignCert:签名证书，CertFlag_EncrCert:加密证书）
 * @remarks 备注 无
 * @return  0:成功 其他:错误码
 */
- (int)ImportCertWithCertData:(NSData *)certData andCertFlag:(CertFlag)certFlag;

/**
 * 导入证书(延期)
 * @author  han harvey
 * @param   certData 公钥证书
 * @param   certFlag 证书标记（CertFlag_SignCert:签名证书，CertFlag_EncrCert:加密证书）
 * @remarks 备注 无
 * @return  0:成功 其他:错误码
 */
- (int)ImportCertWithCertData2:(NSData *)certData andCertFlag:(CertFlag)certFlag;

/**
 * 导入SM2双证书
 * @author  han harvey
 * @param   certData        签名证书的公钥证书
 * @param   doubleCertData  加密证书的公钥证书
 * @param   keyType         对称加密的加密类型
 * @param   doubleEncryptedSessionKeyStr    对称加密的对称密钥
 * @param   doubleCertPubKey                加密证书的公钥
 * @param   doubleEncryptedPrivateKeyStr    被加密的加密证书的私钥结构
 * @param   certFlag 证书标记（CertFlag_SignCert:签名证书，CertFlag_EncrCert:加密证书）
 * @remarks 备注 无
 * @return  0:成功 其他:错误码
 */
- (int)ImportDoubleCertWithCertData:(NSData *)certData andDoubleCertData:(NSData *)doubleCertData andKeyType:(NSString *)keyType andDoubleEncryptedSessionKey:(NSString *)doubleEncryptedSessionKeyStr andDoubleCertPubKey:(NSData *)doubleCertPubKey andDoubleEncryptedPrivateKey:(NSString *)doubleEncryptedPrivateKeyStr andCertFlag:(CertFlag)certFlag;

/**
 * 导入RSA双证书
 * @author  han harvey
 * @param   certData        签名证书的公钥证书
 * @param   doubleCertData  加密证书的公钥证书
 * @param   keyType         对称加密的加密类型
 * @param   doubleEncryptedSessionKeyStr    对称加密的对称密钥
 * @param   doubleCertPubKey                加密证书的公钥
 * @param   doubleEncryptedPrivateKeyStr    被加密的加密证书的私钥结构
 * @param   certFlag 证书标记（CertFlag_SignCert:签名证书，CertFlag_EncrCert:加密证书）
 * @remarks 备注 无
 * @return  0:成功 其他:错误码
 */
- (int)ImportRSADoubleCertWithCertData:(NSData *)certData andDoubleCertData:(NSData *)doubleCertData andKeyType:(NSString *)keyType andDoubleEncryptedSessionKey:(NSString *)doubleEncryptedSessionKeyStr andDoubleCertPubKey:(NSData *)doubleCertPubKey andDoubleEncryptedPrivateKey:(NSString *)doubleEncryptedPrivateKeyStr andCertFlag:(CertFlag)certFlag;

/**
 * 获取证书列表
 * @author  han harvey
 * @param   certList 证书列表
 * @remarks 备注 无
 * @return  0:成功 其他:错误码
 */
- (int)GetCertList:(NSArray **)certList;

/**
 * 登录应用
 * @author  han harvey
 * @param   strPassword 应用密码LoginApplicationPassword
 * @remarks 备注 用户与应用一一对应且一个用户只有一个应用
 * @return  0:成功 其他:错误码
 */
- (int)LoginApplicationWithPassword:(NSString *)strPassword;

/**
 * P1签名
 * @author  han harvey
 * @param   srcData 签名原数据
 * @remarks 备注 无
 * @return  签名原数据的签名结果的Base64
 */
- (NSString *)P1Sign:(NSData *)srcData andDigestAlg:(SafeModelDigestAlg )digestAlg;

- (NSString *)P1Sign:(NSData *)srcData;

/**
 * 修改用户PIN码
 * @author  han harvey
 * @param   oldPass 旧密码
 * @param   newPass 新密码
 * @remarks 备注 无
 * @return  0:成功 其他:错误码
 */
- (int)ModifyPINWithOldPIN:(NSString *)oldPass andNewPIN:(NSString *)newPass;

/**
 * 删除容器（证书）
 * @author  han harvey
 * @param   containerName 容器名称
 * @param   passStr       用户PIN码
 * @remarks 备注 无
 * @return  0:成功 其他:错误码
 */
- (int)DeleteCertWithContainerName:(NSString *)containerName andPassword:(NSString *)passStr;

/**
 * 删除所有证书
 * @author  han harvey
 * @param   passStr 用户PIN码
 * @remarks 备注 无
 * @return  0:成功 其他:错误码
 */
- (int)DeleteAllCertWithPassword:(NSString *)passStr;

/**
 * 根据容器名称获取证书对应的X509证书数据
 * @author  han harvey
 * @param   containerName 容器名称
 * @remarks 备注 无
 * @return  X509数据
 */
- (NSData*)FindX509DataWithContainerName:(NSString *)containerName andCertFlag:(CertFlag)certFlag;

/**
 * 获取公钥
 * @author  han harvey
 * @param   containerName 容器名称
 * @remarks 备注 无
 * @return  公钥数据
 */
- (NSData *)GetPubKeyPairWithContainerName:(NSString *)containerName;

- (int)ChangeUserPIN:(NSString *)newPass;

// RSA对摘要做签名
- (NSData *)Jit_Req_SKF_RSASign:(NSData *)srcData;

// 解信封(非对称解密)
- (NSData *)DecryptP7Envelope:(const unsigned char *)asymmEncData andLen:(int)asymmEncDataLen andSymmEncData:(const unsigned char *)symmEncData andSymmLen:(int)symmEncDataLen andSymmAlg:(NSString *)symmAlg andIVData:(NSData *)ivData;

// 将从信封里取出来的加密数据封装成密码模块需要的密文结构
- (NSData *)GetInfoWithData1:(NSData *)data1
                    andData2:(NSData *)data2
                    andData3:(NSData *)data3
                    andData4:(NSData *)data4;

// 非对称解密
- (NSData *)asymmDecWithEncData:(NSData *)encData
                     andSymmAlg:(NSString *)symmAlg;


@end


