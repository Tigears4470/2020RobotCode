/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc2/command/Command.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <frc/Joystick.h>
#include <frc2/command/button/JoystickButton.h>

#include "commands/ArcadeDriveCommand.h"
#include "commands/GetColorCommand.h"
#include "commands/VisionCommand.h"
#include "commands/SetColorCommand.h"
#include "commands/RotateWheelCommand.h"
#include "commands/ShootCommand.h"
#include "commands/SuckCommand.h"
#include "commands/StopCommand.h"
#include "commands/AutonomousCommand.h"

#include "subsystems/WheelSubsystem.h"
#include "subsystems/DriveSubsystem.h"
#include "subsystems/CameraSubsystem.h"
#include "subsystems/BallShooterSubsystem.h"


#include "Constants.h"

/**
 * This class is where the bulk of the robot should be declared.  Since
 * Command-based is a "declarative" paradigm, very little robot logic should
 * actually be handled in the {@link Robot} periodic methods (other than the
 * scheduler calls).  Instead, the structure of the robot (including subsystems,
 * commands, and button mappings) should be declared here.
 */
class RobotContainer {
 public:
  RobotContainer();

  frc2::Command* GetAutonomousCommand();

 private:
  // The robot's subsystems and commands are defined here...
  frc::Joystick* m_joystick;
  DriveSubsystem m_drivetrain;  
  WheelSubsystem m_wheel;
  CameraSubsystem m_camera;
  BallShooterSubsystem m_shooter;
  frc2::Button* rotate_wheel;
  frc2::Button* set_color;
  frc2::Button* shoot;
  frc2::Button* suck;
  frc2::Button* stop;

  void ConfigureButtonBindings();
};
