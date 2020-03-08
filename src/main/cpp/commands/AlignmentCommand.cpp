/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/AlignmentCommand.h"

AlignmentCommand::AlignmentCommand() {
  // Use addRequirements() here to declare subsystem dependencies.
}

// Called when the command is initially scheduled.
void AlignmentCommand::Initialize() 
{
  auto inst = nt::NetworkTableInstance::GetDefault();
  auto table = inst.GetTable("database");
  reader = table->GetEntry("alignment");
}

// Called repeatedly when this Command is scheduled to run
void AlignmentCommand::Execute() 
{
  dir = reader.GetString("alignment");
  if(dir.compare("move left") == 0)
    m_yaw.Set(.1);
  else if(dir.compare("move right") == 0)
    m_yaw.Set(-.1);
  else if(dir.compare("center") == 0)
    m_yaw.Set(0);
}

// Called once the command ends or is interrupted.
void AlignmentCommand::End(bool interrupted) {}

// Returns true when the command should end.
bool AlignmentCommand::IsFinished() { return true; }
