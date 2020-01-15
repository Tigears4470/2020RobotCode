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
void VisionCommand::Initialize() {
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
    while(true)
     {
      if (cvSink.GrabFrame(source) == 0)
       {
        continue;
      }
      for(int i = 0; i < source.rows; i++)
      {
        for(int j = 0; j < source.cols; j++)
        {
          int b = source.at<cv::Vec3b>(i,j)[0];
          int g = source.at<cv::Vec3b>(i,j)[1];
          int r = source.at<cv::Vec3b>(i,j)[2];
          if(     (!g >= 245 && b <= 10 && r <= 10)   )
          {
            source.at<cv::Vec3b>(i,j)[0] = 255;
            source.at<cv::Vec3b>(i,j)[1] = 255;
            source.at<cv::Vec3b>(i,j)[2] = 255;
          }
        }
      }
      outputStreamStd.PutFrame(source);
    }
  
}

// Called repeatedly when this Command is scheduled to run
void VisionCommand::Execute() {}

// Called once the command ends or is interrupted.
void VisionCommand::End(bool interrupted) {}

// Returns true when the command should end.
bool VisionCommand::IsFinished() { return false; }
