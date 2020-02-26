/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include <frc/Joystick.h>
#include <frc/PWMVictorSPX.h>
#include <frc/TimedRobot.h>
#include <frc/drive/DifferentialDrive.h>
#include <networktables/NetworkTable.h>
#include <networktables/NetworkTableEntry.h>
#include <networktables/NetworkTableInstance.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <mutex>

#include "GripPipeline.h"
#include "cameraserver/CameraServer.h"
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/features2d.hpp>

/**
 * This sample program shows how to control a motor using a joystick. In the
 * operator control part of the program, the joystick is read and the value is
 * written to the motor.
 *
 * Joystick analog values range from -1 to 1 and speed controller inputs as
 * range from -1 to 1 making it easy to work together.
 */
class Robot : public frc::TimedRobot {
 public:
  void RobotInit() override {
    cs::UsbCamera usb_camera = frc::CameraServer::GetInstance()->StartAutomaticCapture();
  }

  void TeleopInit() override {
    auto inst = nt::NetworkTableInstance::GetDefault();
    auto table = inst.GetTable("database");
    testEntry = table->GetEntry("test");
    std::thread visionThread(VisionThread);
    visionThread.detach();
  }
  void TeleopPeriodic() override {
    mtx.lock();
    frc::SmartDashboard::PutString("DB/String 0", testEntry.SetString("THE NETWORK TABLES ARE WORKING")?"true":"false");
    mtx.unlock();
  }

 private:
  static void VisionThread()
  {
    cs::CvSink cvSink = frc::CameraServer::GetInstance()->GetVideo();
    cv::Mat source;
    grip::GripPipeline* grip = new grip::GripPipeline();
   cs::CvSource outputStreamStd = frc::CameraServer::GetInstance()->PutVideo("Gray", 640, 480);
    nt::NetworkTableEntry leftXEntry;
    nt::NetworkTableEntry rightXEntry;
    auto inst = nt::NetworkTableInstance::GetDefault();
    auto table = inst.GetTable("database");
    leftXEntry = table->GetEntry("leftmost x value");
    rightXEntry = table->GetEntry("rightmost x value");
    int r,g,b,i,j;
    i = 0;
    j = 0;
    //std::vector<std::vector<cv::Point>> output;
    cv::Mat output2;
    while(true)
    {
      if(cvSink.GrabFrame(source))
      {
        grip -> Process(source);
        output2 = *grip->GetCvErodeOutput();
        //cameraEntry.SetDouble(output.size());
        /*i = 0;
        j = 0;
        while(j < output2.rows && (output2.at<cv::Vec3b>(i,j)[0] < 230 && output2.at<cv::Vec3b>(i,j)[1] < 230 && output2.at<cv::Vec3b>(i,j)[2] < 200))
        {
          if(i < output2.cols)
            i++;
          else
          {
            i = 0;
            j++;
          }
        }
        if(j < output2.rows)
        {
            output2.at<cv::Vec3b>(i,j) = 125;
        } */
        bool pixelFound = false;
        int firstX = 0;
        for(i = 0; i < output2.cols; i++)
        {
          for(j = 0; j < output2.rows; j++)
          {
            r = output2.at<cv::Vec3b>(j,i)[0];
            g = output2.at<cv::Vec3b>(j,i)[1];
            b = output2.at<cv::Vec3b>(j,i)[2];
            if(!pixelFound)
            {
              if(r >= 230 && g >= 230 && b >= 230)
              {
                firstX = i; 
                pixelFound = true;
              }
            }
          }
        }

        pixelFound = false;
        int secondX = 0;
        for(i = output2.cols - 1; i >= 0; i--)
        {
          for(j = output2.rows - 1; j >= 0; j--)
          {
            r = output2.at<cv::Vec3b>(j,i)[0];
            g = output2.at<cv::Vec3b>(j,i)[1];
            b = output2.at<cv::Vec3b>(j,i)[2];
            if(!pixelFound)
            {
              if(r >= 230 && g >= 230 && b >= 230)
              {
                secondX = i; 
                pixelFound = true;
              }
            }
          }
        }
        //output2.at<cv::Vec3b>(i,j)[1] = 0;
        //output2.at<cv::Vec3b>(i,j)[0] = 0;
        outputStreamStd.PutFrame(output2);
        leftXEntry.SetDouble(firstX);
        rightXEntry.SetDouble(secondX);
        /*int b = source.at<cv::Vec3b>(i,j)[0];
        int g = source.at<cv::Vec3b>(i,j)[1];
        int r = source.at<cv::Vec3b>(i,j)[2];*/
        //rightXEntry.SetDoubleArray({output[0][output.size()-1].x, output[0][output.size()-1].x});

    }
  }
  }

  nt::NetworkTableEntry testEntry;
  std::mutex mtx;
};

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
