/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/
//inherits include/subsystem/WheelSubsystem.h
#include "subsystems/WheelSubsystem.h"

//constructor for WheelSystem object
WheelSubsystem::WheelSubsystem()
{
    //gets color_sensor object that was created in include and initializes it taking in port on the color sensor as the parameter
    color_sensor = new rev::ColorSensorV3(frc::I2C::Port::kOnboard);
}

//creates the periodic method made in include, does nothing
// This method will be called once per scheduler run
void WheelSubsystem::Periodic()
{
}

//creates read function from include
int* WheelSubsystem::Read()
{
    //make array of values read
    int* int_read_val = new int[3];
    //Color object created
    frc::Color color_read = color_sensor->GetColor();
    //array filled with values from color reader
    int_read_val[0] = static_cast<int>(color_read.red*MAX_COLOR_RANGE);
    int_read_val[1] = static_cast<int>(color_read.green*MAX_COLOR_RANGE);
    int_read_val[2] = static_cast<int>(color_read.blue*MAX_COLOR_RANGE);

    //statements displayed on dashboard about what is happening with colors
    frc::SmartDashboard::PutString("DB/String 2", std::to_string(int_read_val[RED_SLOT]));
    frc::SmartDashboard::PutString("DB/String 3", std::to_string(int_read_val[GREEN_SLOT]));
    frc::SmartDashboard::PutString("DB/String 4", std::to_string(int_read_val[BLUE_SLOT]));

    return int_read_val;
    //return int_read_val;
}

//creates turn function which does nothing
void WheelSubsystem::Turn() {}
