/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include "rev/CANSparkMax.h"
#include <Constants.h>
#include <frc/Victor.h>

#include <frc2/command/SubsystemBase.h>

class BallShooterSubsystem : public frc2::SubsystemBase {
 public:
  BallShooterSubsystem();

  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */
  void Periodic();

  void Shoot(double speed);

  void Suck(double speed);

 private:
  rev::CANSparkMax* shooter;
  frc::Victor* sucker;
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.
};
