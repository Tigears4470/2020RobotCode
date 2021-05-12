/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/GetColorCommand.h"


GetColorCommand::GetColorCommand(WheelSubsystem *subsystem) {
  // Use addRequirements() here to declare subsystem dependencies.
  wheel_sub = subsystem;
  m_spinner = new frc::Spark(SPINNER_PORT);
  current_color = "Nothing";
  AddRequirements({subsystem});
}

// Called when the command is initially scheduled.
void GetColorCommand::Initialize() {
  
  
}

// Called repeatedly when this Command is scheduled to run
void GetColorCommand::Execute() {
  //Get the current color read by the wheel stored in an array of size 3 (RGB Values)
  int* read_clr_values = wheel_sub -> Read();
  //Get the difference in color values between the color just read and the ideal color values
  int red_distance = distance(c_RED, read_clr_values);
  int green_distance = distance(c_GREEN, read_clr_values);
  int blue_distance = distance(c_BLUE, read_clr_values);
  int yellow_distance = distance(c_YELLOW, read_clr_values);

  //Find the smallest value among the 4 color_distance varaiables and set smallest_distance equal to that
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
}

// Called once the command ends or is interrupted.
void GetColorCommand::End(bool interrupted) {}

// Returns true when the command should end.
bool GetColorCommand::IsFinished() { return false; }

// Finds the distance between a three dimensional ordered pair
int GetColorCommand::distance( const int* expected, int* measured) 
{
  int difference_one = expected[RED_SLOT]-measured[RED_SLOT];
  int difference_two = expected[GREEN_SLOT]-measured[GREEN_SLOT];
  int difference_three = expected[BLUE_SLOT]-measured[BLUE_SLOT]; 
  return static_cast<int>(sqrt(pow(difference_one,COLOR_SQUARED)+pow(difference_two,COLOR_SQUARED)+pow(difference_three,COLOR_SQUARED)));
}
