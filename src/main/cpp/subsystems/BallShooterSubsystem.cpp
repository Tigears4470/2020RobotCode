/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/BallShooterSubsystem.h"

BallShooterSubsystem::BallShooterSubsystem() {
    shooter = new frc::Spark(SHOOTER_PORT);
}

// This method will be called once per scheduler run
void BallShooterSubsystem::Periodic() {}

void BallShooterSubsystem::SetSpeed(double speed)
{
    shooter -> Set(speed);
}
