package frc.robot.jni;

import java.util.Arrays;
import java.util.List;
import java.util.stream.Collectors;

import frc.robot.Robot;

public class RoborioI2CJNI implements Runnable {
    static {
       System.loadLibrary("i2c_jni");
    }

    private native boolean I2CInit();

    private native boolean I2CVerifySensor(byte[] verifyBytes);

    @Override
    public void run() {
        byte[] verifyBytes = {(byte) 0XEA, (byte) 0XCC, (byte) 0X10};

        boolean verified = Robot.roborioI2CJNI.I2CVerifySensor(verifyBytes);
        if (verified) {
            System.out.println("INFO: Java Sensor verified");
        } else {
            System.out.println("INFO: Java Sensor NOT verified");
        }
    }
}
