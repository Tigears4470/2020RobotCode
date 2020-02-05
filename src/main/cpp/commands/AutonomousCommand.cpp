/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/AutonomousCommand.h"

AutonomousCommand::AutonomousCommand(DriveSubsystem *subsystem, BallShooterSubsystem *subsystem2) {
  drive_train = subsystem;
  is_finished = false;
  shooter = subsystem2;
  timer = new frc::Timer();
  AddRequirements({subsystem});
  AddRequirements({subsystem2});
  // Use addRequirements() here to declare subsystem dependencies.
}

// Called when the command is initially scheduled.
void AutonomousCommand::Initialize() {
  timer -> Reset();
  timer -> Start();
}

// Called repeatedly when this Command is scheduled to run
void AutonomousCommand::Execute() {
  if(timer -> Get() <= 5.0)
  {
    drive_train -> ArcadeDrive(0.5, 0);
  }
  else if(timer -> Get() > 5.0 && timer -> Get() <= 10.0)
  {
    drive_train -> ArcadeDrive(0.0, 0.0);
    shooter -> SetSpeed(0.5);
  }
  else
  {
    drive_train -> ArcadeDrive(0.0, 0.0);
    shooter -> SetSpeed(0.0);
    is_finished = true;
  }
  
}

// Called once the command ends or is interrupted.
void AutonomousCommand::End(bool interrupted) {
  drive_train -> ArcadeDrive(0.0, 0.0);
    shooter -> SetSpeed(0.0);
}

// Returns true when the command should end.
bool AutonomousCommand::IsFinished() { return is_finished; }
