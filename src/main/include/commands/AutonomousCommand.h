/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>
#include <frc/Timer.h>
#include <subsystems/DriveSubsystem.h>
#include <subsystems/BallShooterSubsystem.h>
#include <frc/Encoder.h>
#include <wpi/math>

/**
 * An example command.
 *
 * <p>Note that this extends CommandHelper, rather extending CommandBase
 * directly; this is crucially important, or else the decorator functions in
 * Command will *not* work!
 */
class AutonomousCommand
    : public frc2::CommandHelper<frc2::CommandBase, AutonomousCommand> {
 public:
  explicit AutonomousCommand(DriveSubsystem *subsystem, BallShooterSubsystem *subsystem2, int pos);

  void Initialize() override;

  void Execute() override;

  void End(bool interrupted) override;

  bool IsFinished() override;

  private:

  void RightStart();

  void LeftStart();

  void MiddleStart();

  DriveSubsystem* drive_train;
  BallShooterSubsystem* shooter;
  frc::Timer* timer;
  frc::Encoder* left_encoder;
  frc::Encoder* right_encoder;
  bool is_finished;
  int position;
};
