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

#include "Constants.h"

using std::sqrt;
using std::pow;
//using std::get;

/**
 * An example command.
 *
 * <p>Note that this extends CommandHelper, rather extending CommandBase
 * directly; this is crucially important, or else the decorator functions in
 * Command will *not* work!
 */
class GetColorCommand
    : public frc2::CommandHelper<frc2::CommandBase, GetColorCommand> {
 public:
  explicit GetColorCommand(WheelSubsystem *subsystem);

  void Initialize() override;

  void Execute() override;

  void End(bool interrupted) override;

  bool IsFinished() override;

  private:
    WheelSubsystem* wheel_sub;
    frc::Spark* m_spinner;
    std::string current_color;
    int distance( const int* expected, int* measured ); 
    //int distance[3] = {0 , 0, 0};
};
