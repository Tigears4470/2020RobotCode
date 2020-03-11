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
  speed = 0.0;
  turn = 0.0;
}

// Called repeatedly when this Command is scheduled to run
void AutonomousCommand::Execute() {
  
  if(position == 0)
  {
    AutonomousRun(200,400,800,1000,1200);
  }
  else if(position == 1)
  {
    AutonomousRun(200,400,600,800,100);
  }
  else
  {
    AutonomousRun(200,400,400,600,800);
  }
  
  
}

// Called once the command ends or is interrupted.
void AutonomousCommand::End(bool interrupted) {
  drive_train -> ArcadeDrive(0.0, 0.0);
  shooter -> Shoot(0.0);
  shooter -> Suck(0.0);
}

// Returns true when the command should end.
bool AutonomousCommand::IsFinished() { return is_finished; }

void AutonomousCommand::AutonomousRun(int firstDistance, int firstTurn, int secondDistance, int secondTurn, int lastDistance)
{
  if (right_encoder -> Get() <= firstDistance) 
  {
     drive_train -> ArcadeDrive(speed, turn);
     if (speed <= 0.5)
     {
     speed += .05;
     }
     shooter->Suck(-0.5);
  }
  else if(right_encoder -> Get() <= firstTurn-100)
  {
    drive_train -> ArcadeDrive(speed, turn);
     if (turn <= 0.5)
     {
     turn += .05;
     }
  }
  else if(right_encoder -> Get() <= firstTurn)
  {
    drive_train -> ArcadeDrive(speed, turn);
     if (turn >= 0.5)
     {
     turn -= .05;
     }
  }
  else if(right_encoder -> Get() <= secondDistance)
{
  turn = 0;
  drive_train -> ArcadeDrive(speed, turn);
}
 else if(right_encoder -> Get() <= secondTurn-100)
  {
    drive_train -> ArcadeDrive(speed, turn);
     if (turn <= 0.5)
     {
     turn += .05;
     }
  }
   else if(right_encoder -> Get() <= secondTurn)
  {
    drive_train -> ArcadeDrive(speed, turn);
     if (turn >= 0.5)
     {
     turn -= .05;
     }
  }
   else if(right_encoder -> Get() <= lastDistance)
  {
    drive_train -> ArcadeDrive(speed, turn);
    turn = 0;
     if (speed >= 0)
     {
     speed -= .05;
     }
     
  }
  else
  {
  speed, turn = 0;
  drive_train -> ArcadeDrive(speed, turn);
  shooter-> Shoot(1.0);
  }
}

// void AutonomousCommand::LeftStart()
// {
// if(right_encoder->Get() <= 200)
// {
//   drive_train->ArcadeDrive(speed,turn);
//   if(speed <= 0.5)
//   {
//     speed += 0.05;
//   }
//   shooter -> SetSpeed(-0.5);
// }
// else if(right_encoder -> Get() <= 600)
// {
//   drive_train -> ArcadeDrive(speed, turn);
//   if(turn <= 0.5)
//   {
//   turn += 0.05;
//   }
// }
// else if(right_encoder -> Get() <= 800)
// {
//   turn = 0;
//   drive_train -> ArcadeDrive(speed, turn);
//   if(speed >= 0)
//   {
//     speed -= 0.05;
//   }
// }
// else
// {
//   speed = 0;
//   turn = 0;
//   drive_train -> ArcadeDrive(speed, turn);
//   shooter -> SetSpeed(1.0);
// }
// }

// void AutonomousCommand::MiddleStart()
// {
//     if(right_encoder -> Get() <= 200)
//     {
//       drive_train -> ArcadeDrive(speed, turn);
//       if(speed <= 0.5)
//       {
//         speed += 0.05;
//       }
//       shooter -> SetSpeed(-0.5);
//     }
//     else if(right_encoder -> Get() <= 400)
//     {
//       drive_train -> ArcadeDrive(speed, turn);
//       if(turn <= 0.5)
//       {
//         turn += 0.05;
//       }
//     }
//     else if(right_encoder -> Get() <= 600)
//     {
//       turn = 0;
//       drive_train -> ArcadeDrive(speed, turn);
//     }
//     else if(right_encoder -> Get() <= 800)
//     {
//       drive_train -> ArcadeDrive(speed, turn);
//       if(turn <= 0.5)
//       {
//         turn += 0.05;
//       }
//     }
//     else if(right_encoder -> Get() <= 1000)
//     {
//       drive_train -> ArcadeDrive(speed, turn);
//       if(speed >= 0)
//       {
//         speed -= 0.02;
//       }
//     }
//     else
//     {
//       speed = 0;
//       drive_train -> ArcadeDrive(speed, turn);
//       shooter -> SetSpeed(1.0);
//     }
    
// }

// void AutonomousCommand::RightStart()
// {
//   if (right_encoder -> Get() <= 200) 
//   {
//      drive_train -> ArcadeDrive(speed, turn);
//      if (speed <= 0.5)
//      {
//      speed += .05;
//      }
//      shooter->SetSpeed(-0.5);
//   }
//   else if(right_encoder -> Get() <= 400)
//   {
//     drive_train -> ArcadeDrive(speed, turn);
//      if (turn <= 0.5)
//      {
//      turn += .05;
//      }
//   }
//   else if(right_encoder -> Get() <= 800)
// {
//   turn = 0;
//   drive_train -> ArcadeDrive(speed, turn);
// }
//  else if(right_encoder -> Get() <= 1000)
//   {
//     drive_train -> ArcadeDrive(speed, turn);
//      if (turn <= 0.5)
//      {
//      turn += .05;
//      }
//   }
//    else if(right_encoder -> Get() <= 1200)
//   {
//     drive_train -> ArcadeDrive(speed, turn);
//     turn = 0;
//      if (speed >= 0)
//      {
//      speed -= .05;
//      }
     
//   }
//   else
//   {
//   speed, turn = 0;
//   drive_train -> ArcadeDrive(speed, turn);
//   shooter-> SetSpeed(1.0);
//   }
//}