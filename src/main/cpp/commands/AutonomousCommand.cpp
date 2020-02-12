/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/AutonomousCommand.h"

AutonomousCommand::AutonomousCommand(DriveSubsystem *subsystem, BallShooterSubsystem *subsystem2, int pos) {
  drive_train = subsystem;
  shooter = subsystem2;
  is_finished = false;
  timer = new frc::Timer();
  left_encoder = new frc::Encoder(1, 2, false, frc::Encoder::k4X);
  right_encoder = new frc::Encoder(3, 4, false, frc::Encoder::k4X);
  AddRequirements({subsystem});
  AddRequirements({subsystem2});
  position = pos;
  left_encoder -> SetSamplesToAverage(5);
  left_encoder -> SetDistancePerPulse(1.0 / 360.0 * 2.0 * wpi::math::pi * 1.5);
  left_encoder -> SetMinRate(1.0);
  right_encoder -> SetSamplesToAverage(5);
  right_encoder -> SetDistancePerPulse(1.0 / 360.0 * 2.0 * wpi::math::pi * 1.5);
  right_encoder -> SetMinRate(1.0);
  // Use addRequirements() here to declare subsystem dependencies.
}

// Called when the command is initially scheduled.
void AutonomousCommand::Initialize() {
  timer -> Reset();
  timer -> Start();
}

// Called repeatedly when this Command is scheduled to run
void AutonomousCommand::Execute() {
  
  if(position == 0)
  {
    RightStart();
  }
  else if(position == 1)
  {
    MiddleStart();
  }
  else
  {
    LeftStart();
  }
  
  
}

// Called once the command ends or is interrupted.
void AutonomousCommand::End(bool interrupted) {
  drive_train -> ArcadeDrive(0.0, 0.0);
  shooter -> SetSpeed(0.0);
}

// Returns true when the command should end.
bool AutonomousCommand::IsFinished() { return is_finished; }

void AutonomousCommand::LeftStart()
{

}

void AutonomousCommand::MiddleStart()
{
  
}

void AutonomousCommand::RightStart()
{
  
}
