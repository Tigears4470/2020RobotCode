/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/RotateWheelCommand.h"

RotateWheelCommand::RotateWheelCommand(WheelSubsystem* subsystem) {
  wheel_sub = subsystem;
  m_spinner = new frc::Spark(SPINNER_PORT);
  current_color = "Nothing";
  previous_color = "Nothing";
  is_finished = false;
  AddRequirements({subsystem});
  // Use addRequirements() here to declare subsystem dependencies.
}

// Called when the command is initially scheduled.
void RotateWheelCommand::Initialize() {
  frc::SmartDashboard::PutString("DB/String 6", "Rotate Wheel Command Initialized");
  frc::SmartDashboard::PutString("DB/String 6", "Still Spinning");
  int* read_clr_values = wheel_sub -> Read();
  int red_distance = distance(c_RED, read_clr_values);
  int green_distance = distance(c_GREEN, read_clr_values);
  int blue_distance = distance(c_BLUE, read_clr_values);
  int yellow_distance = distance(c_YELLOW, read_clr_values);

  int smallest_distance = std::min({red_distance, green_distance, blue_distance, yellow_distance }, [](int a, int b) {return a < b;});
  if(smallest_distance == red_distance)
  {
    starting_color = "RED";
    current_color = "RED";
    previous_color = "RED";
  }
  else if(smallest_distance == green_distance)
  {
    starting_color = "GREEN";
    current_color = "GREEN";
    previous_color = "GREEN";
  }
  else if(smallest_distance == blue_distance)
  {
    starting_color = "BLUE";
    current_color = "BLUE";
    previous_color = "BLUE";
  }
  else
  {
    starting_color = "YELLOW";
    current_color = "YELLOW";
    previous_color = "YELLOW";
  }

  m_spinner ->SetSpeed(SPINNER_SPEED);

}

// Called repeatedly when this Command is scheduled to run
void RotateWheelCommand::Execute() {
  int* read_clr_values = wheel_sub -> Read();
  int red_distance = distance(c_RED, read_clr_values);
  int green_distance = distance(c_GREEN, read_clr_values);
  int blue_distance = distance(c_BLUE, read_clr_values);
  int yellow_distance = distance(c_YELLOW, read_clr_values);
  previous_color = current_color;

  int smallest_distance = std::min({red_distance, green_distance, blue_distance, yellow_distance }, [](int a, int b) {return a < b;});
  if(smallest_distance == red_distance)
  {
    current_color = "RED";
  }
  else if(smallest_distance == green_distance)
  {
    current_color = "GREEN";
  }
  else if(smallest_distance == blue_distance)
  {
    current_color = "BLUE";
  }
  else
  {
    current_color = "YELLOW";
  }




  if(current_color == starting_color && current_color != previous_color)
  {
    revolutions++;
  }

  if(revolutions > REVOLUTIONS_NEEDED)
  {
    is_finished = true;
    m_spinner->SetSpeed(SPINNER_STOP_SPEED);
  }
}

// Called once the command ends or is interrupted.
void RotateWheelCommand::End(bool interrupted) {
   frc::SmartDashboard::PutString("DB/String 6", "Spinning End");
}

// Returns true when the command should end.
bool RotateWheelCommand::IsFinished() { return is_finished; }

int RotateWheelCommand::distance( const int* expected, int* measured) 
{
  int difference_one = expected[RED_SLOT]-measured[RED_SLOT];
  int difference_two = expected[GREEN_SLOT]-measured[GREEN_SLOT];
  int difference_three = expected[BLUE_SLOT]-measured[BLUE_SLOT]; 
  return static_cast<int>(sqrt(pow(difference_one,COLOR_SQUARED)+pow(difference_two,COLOR_SQUARED)+pow(difference_three,COLOR_SQUARED)));
}
