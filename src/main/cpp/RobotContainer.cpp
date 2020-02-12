/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "RobotContainer.h"

RobotContainer::RobotContainer() {
  // Initialize all of your commands and subsystems here
  m_joystick = new frc::Joystick(JOYSTICK_PORT);
  m_switchbox = new frc::Joystick(2);


  frc::SmartDashboard::PutData(&m_drivetrain);

  m_drivetrain.SetDefaultCommand(ArcadeDriveCommand(
      &m_drivetrain,
      [this] {return m_joystick->GetY(); },
      [this] {return m_joystick->GetX(); }));
  //frc::SmartDashboard::PutString("DB/String 1", "b4 read");
  m_wheel.SetDefaultCommand(GetColorCommand(&m_wheel));
  //m_camera.SetDefaultCommand(VisionCommand(&m_camera));

  // Configure the button bindings
  ConfigureButtonBindings();
}

void RobotContainer::ConfigureButtonBindings() {
  // Configure your button bindings here
  rotate_wheel = new frc2::Button([&] { return m_joystick -> GetRawButton(ROTATE_WHEEL_BUTTON); });
  rotate_wheel -> WhenPressed(RotateWheelCommand(&m_wheel));

  set_color = new frc2::Button([&] { return m_joystick -> GetRawButton(SET_COLOR_BUTTON); });
  set_color -> WhenReleased(SetColorCommand(&m_wheel));

  shoot = new frc2::Button([&] { return m_joystick -> GetRawButton(SHOOTER_SHOOT); });
  shoot -> WhenPressed(ShootCommand(&m_shooter));

  suck = new frc2::Button([&] { return m_joystick -> GetRawButton(SHOOTER_SUCK); });
  suck -> WhenPressed(SuckCommand(&m_shooter));

  stop = new frc2::Button([&] { return m_joystick -> GetRawButton(SHOOTER_SHOOT); });
  stop -> WhenReleased(StopCommand(&m_shooter));

  stop = new frc2::Button([&] { return m_joystick -> GetRawButton(SHOOTER_SUCK); });
  stop -> WhenReleased(StopCommand(&m_shooter));
  
}

frc2::Command* RobotContainer::GetAutonomousCommand() {
  if(m_switchbox -> GetRawButton(0))
  {
    AutonomousCommand(new DriveSubsystem(), new BallShooterSubsystem(), 0);
  }
  else if(m_switchbox -> GetRawButton(1))
  {
    AutonomousCommand(new DriveSubsystem(), new BallShooterSubsystem(), 1);
  }
  else
  {
    AutonomousCommand(new DriveSubsystem(), new BallShooterSubsystem(), 2);
  }
  // An example command will be run in autonomous
  return nullptr;
}
