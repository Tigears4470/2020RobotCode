/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc2/command/SubsystemBase.h>
#include <frc/I2C.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include "rev/ColorSensorV3.h"

#include "Constants.h"

class WheelSubsystem : public frc2::SubsystemBase {
 public:
  WheelSubsystem();

  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */
  void Periodic();

  int* Read();

  void Turn();

 private:
  rev::ColorSensorV3 *color_sensor;
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.
};
