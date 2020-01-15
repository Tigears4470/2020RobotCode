/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <math.h>
#include "subsystems/WheelSubsystem.h"
#include <stdint.h>
#include <frc/Spark.h>
#include <frc/DriverStation.h>

#include "Constants.h"

using std::sqrt;
using std::pow;
/**
 * An example command.
 *
 * <p>Note that this extends CommandHelper, rather extending CommandBase
 * directly; this is crucially important, or else the decorator functions in
 * Command will *not* work!
 */
class SetColorCommand
    : public frc2::CommandHelper<frc2::CommandBase, SetColorCommand> {
 public:
  explicit SetColorCommand(WheelSubsystem *subsystem);

  void Initialize() override;

  void Execute() override;

  void End(bool interrupted) override;

  bool IsFinished() override;

  private:
    WheelSubsystem* wheel_sub;
    frc::Spark* m_spinner;
    std::string current_color;
    std::string color_needed;
    int distance( const int* expected, int* measured ); 
    bool is_finished;

};
