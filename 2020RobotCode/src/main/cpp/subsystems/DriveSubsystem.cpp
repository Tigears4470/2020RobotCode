/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/DriveSubsystem.h"

DriveSubsystem::DriveSubsystem()
{
    m_drive = new frc::RobotDrive(LEFT_MOTOR, RIGHT_MOTOR);
}


// This method will be called once per scheduler run
void DriveSubsystem::Periodic() {}


void DriveSubsystem::ArcadeDrive(double fwd, double rot)
{
    m_drive -> ArcadeDrive(fwd, rot);
}

