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
  frc::SmartDashboard::PutString("DB/String 6", "Set Color Command Initialized");
std::string gameData;
gameData = frc::DriverStation::GetInstance().GetGameSpecificMessage();
if(gameData.length() > 0)
{
  switch (gameData[0])
  {
    case 'B' :
      color_needed = "BLUE";
      //Blue case code
      break;
    case 'G' :
      //Green case code
      color_needed = "GREEN";
      break;
    case 'R' :
      //Red case code
      color_needed = "RED";
      break;
    case 'Y' :
      //Yellow case code
      color_needed = "YELLOW";
      break;
    default :
      //This is corrupt data
      color_needed = "Nothing";
      break;
  }
} else {
  color_needed = "Nothing";
  frc::SmartDashboard::PutString("DB/String 5", "No Data Read");
  //Code for no data received yet
} 
  if(color_needed == "Nothing") 
  {
    is_finished = true;
  }
  else
  {
    m_spinner ->SetSpeed(SPINNER_SPEED);
  }
   

}

// Called repeatedly when this Command is scheduled to run
void SetColorCommand::Execute() {
  //Read the pixels of the current color into the array read_clr_values
  int* read_clr_values = wheel_sub -> Read();
  //Calculate the distance between that color and a predetermined default for said color
  int red_distance = distance(c_RED, read_clr_values);
  int green_distance = distance(c_GREEN, read_clr_values);
  int blue_distance = distance(c_BLUE, read_clr_values);
  int yellow_distance = distance(c_YELLOW, read_clr_values);

  //Get smallest distance among the 4 colors (R, G, B, Y)
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


  //Rotates until predetermined color is read on the camera
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
  frc::SmartDashboard::PutString("DB/String 5", "");
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
