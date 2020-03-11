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
    m_joystick = new frc::Joystick(0);
}


// This method will be called once per scheduler run
void DriveSubsystem::Periodic() {}


void DriveSubsystem::ArcadeDrive(double fwd, double rot)
{
    if(m_joystick -> GetRawButton(REVERSE_DRIVE_TRAIN_BUTTON))
    {
    m_drive -> ArcadeDrive(-fwd, -rot);
    frc::SmartDashboard::PutString("DB/String 5", "Reverse Drive Train");
    }
    else
    {
    m_drive -> ArcadeDrive(fwd, rot);
    frc::SmartDashboard::PutString("DB/String 5", "Normal Drive Train");
    }
    
}

