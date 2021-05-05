/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/DriveSubsystem.h"

DriveSubsystem::DriveSubsystem()
{
    //Initialize m_drive to be a new RobotDrive object passing in the LEFT_MOTOR and RIGHT_MOTOR variables to represent ports on the Roborio
    m_drive = new frc::RobotDrive(LEFT_MOTOR, RIGHT_MOTOR);
}


// This method will be called once per scheduler run
void DriveSubsystem::Periodic() {}

//Takes in 2 doubles (forward and reverse) and then passes those values in to the ArcadeDrive method in the RobotDrive class to move the Robot forward and determine rotation
void DriveSubsystem::ArcadeDrive(double fwd, double rot)
{
    m_drive -> ArcadeDrive(fwd, rot);
}

