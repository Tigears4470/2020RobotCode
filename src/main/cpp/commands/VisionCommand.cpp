/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/VisionCommand.h"

VisionCommand::VisionCommand(CameraSubsystem *subsystem)
{
  camera_sub = subsystem;
  AddRequirements({subsystem});
  // Use addRequirements() here to declare subsystem dependencies.
}

// Called when the command is initially scheduled.
void VisionCommand::Initialize()
{
  ConnectCamera();
}

void VisionCommand::ConnectCamera()
{
  cs::UsbCamera camera = frc::CameraServer::GetInstance()->StartAutomaticCapture();
  camera.SetResolution(640, 480);
  camera.SetFPS(30);
  cs::CvSink cvSink = frc::CameraServer::GetInstance()->GetVideo();
  cs::CvSource outputStreamStd = frc::CameraServer::GetInstance()->PutVideo("Processed", 640, 480);
  cv::Mat source;
  cv::Mat output;
  if (cvSink.GrabFrame(source) == 0)
  {
    cv::threshold(source, output, 127, 255, cv::THRESH_BINARY);
    outputStreamStd.PutFrame(output);
  }
  // for (int i = 0; i < source.rows; i++)
  // {
  //   for (int j = 0; j < source.cols; j++)
  //   {
  //     int blue_pixel_value = source.at<cv::Vec3b>(i, j)[0];
  //     int green_pixel_value = source.at<cv::Vec3b>(i, j)[1];
  //     int red_pixel_value = source.at<cv::Vec3b>(i, j)[2];
  //     if ((!(green_pixel_value >= 245) && blue_pixel_value <= 10 && red_pixel_value <= 10))
  //     {
  //       source.at<cv::Vec3b>(i, j)[0] = 255;
  //       source.at<cv::Vec3b>(i, j)[1] = 255;
  //       source.at<cv::Vec3b>(i, j)[2] = 255;
  //     }
  //   }
  // }
}

// Called repeatedly when this Command is scheduled to run
void VisionCommand::Execute() {}

// Called once the command ends or is interrupted.
void VisionCommand::End(bool interrupted) {}

// Returns true when the command should end.
bool VisionCommand::IsFinished() { return false; }
