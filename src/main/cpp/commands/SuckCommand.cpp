/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/SuckCommand.h"

SuckCommand::SuckCommand(BallShooterSubsystem* subsystem) {
  shooter = subsystem;
  AddRequirements({subsystem});
  // Use addRequirements() here to declare subsystem dependencies.
}

// Called when the command is initially scheduled.
void SuckCommand::Initialize() {
    shooter -> SetSpeed(SHOOTER_SUCK_SPEED);
}

// Called repeatedly when this Command is scheduled to run
void SuckCommand::Execute() {
}

// Called once the command ends or is interrupted.
void SuckCommand::End(bool interrupted) {}

// Returns true when the command should end.
bool SuckCommand::IsFinished() { return true; }
