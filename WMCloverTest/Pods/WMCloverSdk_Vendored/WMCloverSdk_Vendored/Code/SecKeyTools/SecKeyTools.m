//
//  SecKeyTools.m
//  SecurityiOS
//
//  Created by cocoa on 16/12/16.
//  Copyright © 2016年 dev.keke@gmail.com. All rights reserved.
//

#import "SecKeyTools.h"

@implementation SecKeyTools

/**
 从x509 cer证书中读取公钥
 */
+ (SecKeyRef )publicKeyFromCer:(NSString *)cerFile
{
    OSStatus            err;
    NSData *            certData;
    SecCertificateRef   cert;
    SecPolicyRef        policy;
    SecTrustRef         trust;
    SecTrustResultType  trustResult;
    SecKeyRef           publicKeyRef;
    
    certData = [NSData dataWithContentsOfFile:cerFile];
    cert = SecCertificateCreateWithData(NULL, (__bridge CFDataRef) certData);
    policy = SecPolicyCreateBasicX509();
    err = SecTrustCreateWithCertificates(cert, policy, &trust);
    NSAssert(err==errSecSuccess,@"证书加载失败");
    err = SecTrustEvaluate(trust, &trustResult);
    NSAssert(err==errSecSuccess,@"公钥加载失败");
    publicKeyRef = SecTrustCopyPublicKey(trust);
    
    CFRelease(policy);
    CFRelease(cert);
    return publicKeyRef;
}



/**
 从 p12 文件中读取私钥，一般p12都有密码
 */
+ (SecKeyRef )privateKeyFromP12:(NSString *)p12File password:(NSString *)pwd
{
    NSData *pkcs12Data = [NSData dataWithContentsOfFile:p12File];
    return [self privateKeyFromP12Data:pkcs12Data password:pwd];
}

+ (SecKeyRef)privateKeyFromP12Data:(NSData *)p12Data password:(NSString *)pwd
{
    CFArrayRef          imported;
    NSDictionary *      importedItem;
    SecIdentityRef      identity;
    OSStatus            err;
    SecKeyRef           privateKeyRef;
    
    const void *keys[] =   { kSecImportExportPassphrase };
    const void *values[] = { (__bridge CFStringRef)pwd };
    CFDictionaryRef optionsDictionary = CFDictionaryCreate(
                                                           NULL, keys,
                                                           values, (pwd ? 1 : 0),
                                                           NULL, NULL);
    err = SecPKCS12Import((__bridge_retained CFDataRef)p12Data,optionsDictionary, &imported);
    NSAssert(err==errSecSuccess,@"p12加载失败");
    importedItem = (__bridge NSDictionary *) CFArrayGetValueAtIndex(imported, 0);
    identity = (__bridge SecIdentityRef) importedItem[(__bridge NSString *) kSecImportItemIdentity];
    
    err = SecIdentityCopyPrivateKey(identity, &privateKeyRef);
    NSAssert(err==errSecSuccess,@"私钥加载失败");
    CFRelease(imported);
    
    return privateKeyRef;
}

// 将p12证书导入到keychain
+(int)importP12DataToKeyChainWithData:(NSData *)p12Data andPassword:(NSString *)password andErrorMessage:(NSString **)errorMessage
{
    
    OSStatus status = errSecSuccess;
    SecIdentityRef outIdentity;
    SecTrustRef outTrust;
    
    CFDataRef inPKCS12Data = (__bridge_retained CFDataRef)p12Data;
    
    //    Byte *byte = (Byte *)[p12Data bytes];
    //    for (int i = 0; i < p12Data.length; i++) {
    //        printf("%d ", byte[i]);
    //    }
    //    printf("\n\n");
    if (p12Data == nil) {
        *errorMessage = @"取p12Data失败，请检查路径";
        return -1;
    }
    
    // 1
    /* Create a dictionary containing the passphrase if one
     was specified.  Otherwise, create an empty dictionary. */
    const void *keys[] =   { kSecImportExportPassphrase };
    const void *values[] = { (__bridge CFStringRef)password };
    CFDictionaryRef optionsDictionary = CFDictionaryCreate(
                                                           NULL, keys,
                                                           values, (password ? 1 : 0),
                                                           NULL, NULL);
    
    // 2 导入p12
    CFArrayRef items = NULL;
    status = SecPKCS12Import(inPKCS12Data,
                             optionsDictionary,
                             &items);
    
    
    // 3
    if (status == 0) {
        CFDictionaryRef myIdentityAndTrust = (CFDictionaryRef)CFArrayGetValueAtIndex (items, 0);
        const void *tempIdentity = NULL;
        tempIdentity = CFDictionaryGetValue (myIdentityAndTrust,
                                             kSecImportItemIdentity);
        CFRetain(tempIdentity);
        outIdentity = (SecIdentityRef)tempIdentity;
        const void *tempTrust = NULL;
        tempTrust = CFDictionaryGetValue (myIdentityAndTrust, kSecImportItemTrust);
        
        CFRetain(tempTrust);
        outTrust = (SecTrustRef)tempTrust;
    } else {
        switch (status) {
            case errSecSuccess:
                *errorMessage = @"success";
                break;
                
            case errSecDuplicateItem:
                *errorMessage = @"The specified item already exists in the keychain.";
                break;
                
            case errSecAuthFailed:
                *errorMessage = @"The user name or passphrase you entered is not correct.";
                break;
                
            default:
                *errorMessage = [NSString stringWithFormat:@"errorCode=%d", (int)status];
                break;
        }
        return -2;
    }
    
    // 将SecIdentityRef导入到KeyChain
    status = errSecSuccess;
    CFTypeRef  persistent_ref = NULL;
    const void *keys1[] =   { kSecReturnPersistentRef, kSecValueRef };
    const void *values1[] = { kCFBooleanTrue,          outIdentity };
    CFDictionaryRef dict = CFDictionaryCreate(NULL, keys1, values1,
                                              2, NULL, NULL);
    status = SecItemAdd(dict, &persistent_ref);
    switch (status) {
        case errSecSuccess:
            *errorMessage = @"success";
            break;
            
        case errSecDuplicateItem:
            *errorMessage = @"The specified item already exists in the keychain.";
            break;
            
        case errSecAuthFailed:
            *errorMessage = @"The user name or passphrase you entered is not correct.";
            break;
            
        default:
            break;
    }
    
    // 释放缓存
    if (optionsDictionary)
        CFRelease(optionsDictionary);
    if (items)
        CFRelease(items);
    if (dict)
        CFRelease(dict);
    
    return status;
}


+ (SecKeyRef )publicKeyFromPem:(NSString *)pemFile keySize:(size_t )size
{
    SecKeyRef pubkeyref;
    NSError *readFErr = nil;
    CFErrorRef errref = noErr;
    NSString *pemStr = [NSString stringWithContentsOfFile:pemFile encoding:NSASCIIStringEncoding error:&readFErr];
    NSAssert(readFErr==nil, @"pem文件加载失败");
    pemStr = [pemStr stringByReplacingOccurrencesOfString:@"-----BEGIN PUBLIC KEY-----" withString:@""];
    pemStr = [pemStr stringByReplacingOccurrencesOfString:@"\r" withString:@""];
    pemStr = [pemStr stringByReplacingOccurrencesOfString:@"\n" withString:@""];
    pemStr = [pemStr stringByReplacingOccurrencesOfString:@"-----END PUBLIC KEY-----" withString:@""];
    NSData *dataPubKey = [[NSData alloc]initWithBase64EncodedString:pemStr options:0];

    NSMutableDictionary *dicPubkey = [[NSMutableDictionary alloc]initWithCapacity:1];
    [dicPubkey setObject:(__bridge id)kSecAttrKeyTypeRSA forKey:(__bridge id)kSecAttrKeyType];
    [dicPubkey setObject:(__bridge id) kSecAttrKeyClassPublic forKey:(__bridge id)kSecAttrKeyClass];
    [dicPubkey setObject:@(size) forKey:(__bridge id)kSecAttrKeySizeInBits];

    pubkeyref = SecKeyCreateWithData((__bridge CFDataRef)dataPubKey, (__bridge CFDictionaryRef)dicPubkey, &errref);

    NSAssert(errref==noErr, @"公钥加载错误");
    
    return pubkeyref;
}

+ (SecKeyRef )privaKeyFromPem:(NSString *)pemFile keySize:(size_t )size
{
    SecKeyRef prikeyRef;
    NSError *readFErr = nil;
    CFErrorRef err = noErr;
    
    NSString *pemStr = [NSString stringWithContentsOfFile:pemFile encoding:NSASCIIStringEncoding error:&readFErr];
    NSAssert(readFErr==nil, @"pem文件加载失败");
    pemStr = [pemStr stringByReplacingOccurrencesOfString:@"-----BEGIN RSA PRIVATE KEY-----" withString:@""];
    pemStr = [pemStr stringByReplacingOccurrencesOfString:@"\r" withString:@""];
    pemStr = [pemStr stringByReplacingOccurrencesOfString:@"\n" withString:@""];
    pemStr = [pemStr stringByReplacingOccurrencesOfString:@"-----END RSA PRIVATE KEY-----" withString:@""];
    NSData *pemData = [[NSData alloc]initWithBase64EncodedString:pemStr options:0];
    
    NSMutableDictionary *dicPrikey = [[NSMutableDictionary alloc]initWithCapacity:1];
    [dicPrikey setObject:(__bridge id)kSecAttrKeyTypeRSA forKey:(__bridge id)kSecAttrKeyType];
    [dicPrikey setObject:(__bridge id) kSecAttrKeyClassPrivate forKey:(__bridge id)kSecAttrKeyClass];
    [dicPrikey setObject:@(size) forKey:(__bridge id)kSecAttrKeySizeInBits];
    
    prikeyRef = SecKeyCreateWithData((__bridge CFDataRef)pemData, (__bridge CFDictionaryRef)dicPrikey, &err);
    NSAssert(err==noErr, @"私钥加载错误");
    
    
    return prikeyRef;
}

@end
