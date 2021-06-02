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
    //Connect our Camera and set Specifications
    cs::UsbCamera camera = frc::CameraServer::GetInstance()->StartAutomaticCapture();
    camera.SetResolution(640, 480);
    camera.SetFPS(30);
    //Create Sink and output to connect to DriverStation and camera
    cs::CvSink cvSink = frc::CameraServer::GetInstance()->GetVideo();
    cs::CvSource outputStreamStd = frc::CameraServer::GetInstance()->PutVideo("Processed", 640, 480);
    cv::Mat source;
    while(true)
     {
       //Get the current frame and put it into source
      if (cvSink.GrabFrame(source) == 0)
       {
        continue;
      }
      //Look through the source (picture that is a matrix which contains arrays that store rgb values)
      for(int i = 0; i < source.rows; i++)
      {
        for(int j = 0; j < source.cols; j++)
        {
          //Get the rbg value of that specific pixel
          int b = source.at<cv::Vec3b>(i,j)[0];
          int g = source.at<cv::Vec3b>(i,j)[1];
          int r = source.at<cv::Vec3b>(i,j)[2];
          //If that pixel is not within threshold (not yellow/greenish)
          if(     (!g >= 245 && b <= 10 && r <= 10)   )
          {
            //Set that array to black so that pixel shows up as black on the picture
            source.at<cv::Vec3b>(i,j)[0] = 255;
            source.at<cv::Vec3b>(i,j)[1] = 255;
            source.at<cv::Vec3b>(i,j)[2] = 255;
          }
        }
      }
      //Put that image onto the driver station
      outputStreamStd.PutFrame(source);

      //Filters out anything that isnt green (color of our LED light reflecting off of the reflective tape on the arena)
    }
  
}

// Called repeatedly when this Command is scheduled to run
void VisionCommand::Execute() {}

// Called once the command ends or is interrupted.
void VisionCommand::End(bool interrupted) {}

// Returns true when the command should end.
bool VisionCommand::IsFinished() { return false; }
