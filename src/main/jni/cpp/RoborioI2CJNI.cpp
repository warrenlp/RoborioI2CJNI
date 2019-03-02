

#include <jni.h>
#include <iostream>
#include <cstdio>

#include <frc/I2C.h>

#include "frc_robot_jni_RoborioI2CJNI.h"

frc::I2C *i2c = new frc::I2C(frc::I2C::Port::kOnboard, 0x0029);

JNIEXPORT jboolean JNICALL Java_frc_robot_jni_RoborioI2CJNI_I2CInit(JNIEnv *env, jobject thisObj)
{
    bool aborted = i2c->AddressOnly();
    if (aborted) {
        std::cout << "INFO: aborted on C++ side" << std::endl;
    } else {
        std::cout << "INFO: NOT aborted on C++ side" << std::endl;
    }
    return aborted;
}

JNIEXPORT jboolean JNICALL Java_frc_robot_jni_RoborioI2CJNI_I2CVerifySensor(JNIEnv *env, jobject thisObj, jbyteArray byteArr)
{   
    bool verified = true;
    uint8_t verifyIndex[] = {0x01, 0x0F};
    
    // uint8_t verifyBuffer[3];
    // uint8_t verifyVL53L0XBuffer[] = {0xEA, 0xCC, 0x10};

    jsize length = env->GetArrayLength(byteArr);
    jbyte *cbyteArr = env->GetByteArrayElements(byteArr, NULL);

    uint8_t *verifyBuffer = new uint8_t[length];

    bool aborted = i2c->Transaction(verifyIndex, 2, verifyBuffer, length);

    if (aborted) {
        std::cout << "INFO: VerifySensor aborted Transaction on C++ side" << std::endl;
        verified = false;
    } else {
        std::cout << "INFO: VerifySensor NOT aborted Transaction on C++ side" << std::endl;
    }

    if (!aborted) {
        for (int i=0; i<length; ++i) {
            if (verifyBuffer[i] == (uint8_t) cbyteArr[i]) {
                printf("INFO: C++ verified: %d %#X %#X\n", i, verifyBuffer[i], (uint8_t) cbyteArr[i]);
            } else {
                verified = false;
                printf("INFO: C++ NOT verified: %d %#X %#X\n", i, verifyBuffer[i], (uint8_t) cbyteArr[i]);
                break;
            } 
        }
    }

    delete verifyBuffer;
    env->ReleaseByteArrayElements(byteArr, cbyteArr, 0);

    return verified;
}
