/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/SetColorCommand.h"

SetColorCommand::SetColorCommand(WheelSubsystem* subsystem) {
  wheel_sub = subsystem;
  m_spinner = new frc::Spark(SPINNER_PORT);
  current_color = "Nothing";
  is_finished = false;
  AddRequirements({subsystem});
  // Use addRequirements() here to declare subsystem dependencies.
}

// Called when the command is initially scheduled.
void SetColorCommand::Initialize() {
  color_needed = "BLUE";
  is_finished = false;
// std::string gameData;
// gameData = frc::DriverStation::GetInstance().GetGameSpecificMessage();
// if(gameData.length() > 0)
// {
//   switch (gameData[0])
//   {
//     case 'B' :
//       color_needed = "BLUE";
//       //Blue case code
//       break;
//     case 'G' :
//       //Green case code
//       color_needed = "GREEN";
//       break;
//     case 'R' :
//       //Red case code
//       color_needed = "RED";
//       break;
//     case 'Y' :
//       //Yellow case code
//       color_needed = "YELLOW";
//       break;
//     default :
//       //This is corrupt data
//       color_needed = "Nothing";
//       break;
//   }
// } else {
//   color_needed = "Nothing";
//   frc::SmartDashboard::PutString("DB/String 5", "No Data Read");
//   //Code for no data received yet
// } 
//   if(color_needed == "Nothing") 
//   {
//     is_finished = true;
//   }
//   else
//   {
     m_spinner ->SetSpeed(SPINNER_SPEED);
//   }
   

}

// Called repeatedly when this Command is scheduled to run
void SetColorCommand::Execute() {
  int* read_clr_values = wheel_sub -> Read();
  int red_distance = distance(c_RED, read_clr_values);
  int green_distance = distance(c_GREEN, read_clr_values);
  int blue_distance = distance(c_BLUE, read_clr_values);
  int yellow_distance = distance(c_YELLOW, read_clr_values);

  int smallest_distance = std::min({red_distance, green_distance, blue_distance, yellow_distance }, [](int a, int b) {return a < b;});
  if(smallest_distance == red_distance)
  {
    frc::SmartDashboard::PutString("DB/String 1", "Color: Red");
    current_color = "RED";
  }
  else if(smallest_distance == green_distance)
  {
    frc::SmartDashboard::PutString("DB/String 1", "Color: Green");
    current_color = "GREEN";
  }
  else if(smallest_distance == blue_distance)
  {
    frc::SmartDashboard::PutString("DB/String 1", "Color: Blue");
    current_color = "BLUE";
  }
  else
  {
    frc::SmartDashboard::PutString("DB/String 1", "Color: Yellow");
    current_color = "YELLOW";
  }


  frc::SmartDashboard::PutString("DB/String 5", "Set Color Running");
  if(color_needed == "RED" && current_color == "BLUE")
  {
    is_finished = true;
    m_spinner->SetSpeed(SPINNER_STOP_SPEED);
  }
  else if(color_needed == "BLUE" && current_color == "RED")
  {
    is_finished = true;
    m_spinner->SetSpeed(SPINNER_STOP_SPEED);
  }
  else if(color_needed == "GREEN" && current_color == "YELLOW")
  {
    is_finished = true;
    m_spinner->SetSpeed(SPINNER_STOP_SPEED);
  }
  else if(color_needed == "YELLOW" && current_color == "GREEN")
  {
    is_finished = true;
    m_spinner->SetSpeed(SPINNER_STOP_SPEED);
  }



  
}

// Called once the command ends or is interrupted.
void SetColorCommand::End(bool interrupted) {
  frc::SmartDashboard::PutString("DB/String 5", "Set Color Finished");
}

// Returns true when the command should end.
bool SetColorCommand::IsFinished() { return is_finished; }

int SetColorCommand::distance( const int* expected, int* measured) 
{
  int difference_one = expected[RED_SLOT]-measured[RED_SLOT];
  int difference_two = expected[GREEN_SLOT]-measured[GREEN_SLOT];
  int difference_three = expected[BLUE_SLOT]-measured[BLUE_SLOT]; 
  return static_cast<int>(sqrt(pow(difference_one,COLOR_SQUARED)+pow(difference_two,COLOR_SQUARED)+pow(difference_three,COLOR_SQUARED)));
}
