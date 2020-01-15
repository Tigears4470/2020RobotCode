/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/ArcadeDriveCommand.h"

ArcadeDriveCommand::ArcadeDriveCommand(DriveSubsystem *subsystem, std::function<double()> forward, std::function<double()> rotation) {
  drive_train = subsystem;
  m_forward = forward;
  m_rotation = rotation;
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements({subsystem});
}

// Called when the command is initially scheduled.
void ArcadeDriveCommand::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void ArcadeDriveCommand::Execute() {
  drive_train->ArcadeDrive(m_forward(), m_rotation());
}

// Called once the command ends or is interrupted.
void ArcadeDriveCommand::End(bool interrupted) {}

// Returns true when the command should end.
bool ArcadeDriveCommand::IsFinished() { return false; }
