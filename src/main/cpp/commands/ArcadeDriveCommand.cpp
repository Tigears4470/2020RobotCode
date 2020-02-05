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
  speed = 0;
  acceleration = 0;
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements({subsystem});
}

// Called when the command is initially scheduled.
void ArcadeDriveCommand::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void ArcadeDriveCommand::Execute() {
  drive_train->ArcadeDrive(speed, m_rotation());
  double cur = m_forward();
  double midpoint = cur / 2;
  if(cur > speed)
  {
    speed += acceleration;
    if(speed > midpoint)
    {
      acceleration -= ACCELERATION_CONSTANT;
    }
    else
    {
      acceleration += ACCELERATION_CONSTANT;
    }
  }
  else if(speed > cur)
  {
    speed -= acceleration;
    if(speed > midpoint)
    {
      acceleration += ACCELERATION_CONSTANT;
    }
    else
    {
      acceleration -= ACCELERATION_CONSTANT;
    }

  }

  
  if(speed > 1.0)
  {
    speed = 1.0;
  }
  else if(speed < -1.0)
  {
    speed = -1.0;
  }

  if(speed > -0.02 && speed < 0.02)
  {
    speed = 0;
  }


}

// Called once the command ends or is interrupted.
void ArcadeDriveCommand::End(bool interrupted) {}

// Returns true when the command should end.
bool ArcadeDriveCommand::IsFinished() { return false; }
