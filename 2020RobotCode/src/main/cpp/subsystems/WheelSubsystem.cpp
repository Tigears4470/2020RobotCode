/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/WheelSubsystem.h"

WheelSubsystem::WheelSubsystem()
{
    color_sensor = new rev::ColorSensorV3(frc::I2C::Port::kOnboard);
}

// This method will be called once per scheduler run
void WheelSubsystem::Periodic()
{
}

int* WheelSubsystem::Read()
{
    int* int_read_val = new int[3];
    frc::Color color_read = color_sensor->GetColor();
    int_read_val[0] = static_cast<int>(color_read.red*MAX_COLOR_RANGE);
    int_read_val[1] = static_cast<int>(color_read.green*MAX_COLOR_RANGE);
    int_read_val[2] = static_cast<int>(color_read.blue*MAX_COLOR_RANGE);

    frc::SmartDashboard::PutString("DB/String 2", std::to_string(int_read_val[RED_SLOT]));
    frc::SmartDashboard::PutString("DB/String 3", std::to_string(int_read_val[GREEN_SLOT]));
    frc::SmartDashboard::PutString("DB/String 4", std::to_string(int_read_val[BLUE_SLOT]));

    return int_read_val;
    //return int_read_val;
}

void WheelSubsystem::Turn() {}
