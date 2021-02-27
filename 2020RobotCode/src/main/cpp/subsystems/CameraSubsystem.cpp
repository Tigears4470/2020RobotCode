/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/CameraSubsystem.h"

CameraSubsystem::CameraSubsystem() {
    usb_camera = new cs::UsbCamera("USB Camera 0", 0);
}

cs::UsbCamera* CameraSubsystem::GetCamera()
{
    return usb_camera;
}

// This method will be called once per scheduler run
void CameraSubsystem::Periodic() {}
