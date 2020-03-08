/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/ShootAndSuckCommand.h"

ShootAndSuckCommand::ShootAndSuckCommand(BallShooterSubsystem* subsystem) {
  shooter = subsystem;
  m_stick = new frc::Joystick(0);
  AddRequirements({subsystem});
  // Use addRequirements() here to declare subsystem dependencies.
}

// Called when the command is initially scheduled.
void ShootAndSuckCommand::Initialize() {
  if(m_stick -> GetRawButton(SHOOTER_SHOOT_BUTTON))
  {
    shooter -> SetSpeed(SHOOTER_SHOOT_SPEED);
  }
  else if(m_stick -> GetRawButton(SHOOTER_STOP_SPEED))
  {
    shooter -> SetSpeed(SHOOTER_SUCK_BUTTON);
  }
  else
  {
    shooter ->SetSpeed(0);
  }
}

// Called repeatedly when this Command is scheduled to run
void ShootAndSuckCommand::Execute() {}

// Called once the command ends or is interrupted.
void ShootAndSuckCommand::End(bool interrupted) {}

// Returns true when the command should end.
bool ShootAndSuckCommand::IsFinished() { return false; }
