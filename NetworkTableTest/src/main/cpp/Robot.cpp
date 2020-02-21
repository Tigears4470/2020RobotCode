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

/**
 * This is a demo program showing the use of the DifferentialDrive class.
 * Runs the motors with arcade steering.
 */
class Robot : public frc::TimedRobot {
  frc::PWMVictorSPX m_leftMotor{0};
  frc::PWMVictorSPX m_rightMotor{1};
  frc::DifferentialDrive m_robotDrive{m_leftMotor, m_rightMotor};
  frc::Joystick m_stick{0};
  nt::NetworkTableEntry testEntry;
  std::shared_ptr<NetworkTable> table2;
  std::mutex mtx;

 public:
  void RobotInit()
  {
    frc::SmartDashboard::PutString("DB/String 5", "working");
  }

  void TeleopInit() 
  {
    auto inst = nt::NetworkTableInstance::GetDefault();
    auto table = inst.GetTable("database");
    testEntry = table->GetEntry("test");
    table2 = nt::NetworkTable::GetTable("database");
    std::thread visionThread(VisionThread);
    visionThread.detach();
    /*table.SetClientMode();
    table.SetServerTeam("4470");
    table.SetServer("roborio-4470-frc.local"); // ip of roborio
    table.StartServer();
    testEntry = table->GetEntry("test"); // what table data is put in*/
  }

  void TeleopPeriodic() 
  {
    // Drive with arcade style
    mtx.lock();
    frc::SmartDashboard::PutString("DB/String 0", testEntry.SetString("THE NETWORK TABLES ARE WORKING")?"true":"false");
    frc::SmartDashboard::PutString("DB/String 1", table2->GetEntry("test").GetString("test"));
    m_robotDrive.ArcadeDrive(m_stick.GetY(), m_stick.GetX());
    mtx.unlock();

  }

  private:
   static void VisionThread()
  {
    cs::UsbCamera usb_camera = frc::CameraServer::GetInstance()->StartAutomaticCapture();
    cs::CvSink cvSink = frc::CameraServer::GetInstance()->GetVideo();
    cv::Mat source;
    grip::GripPipeline* grip = new grip::GripPipeline();
    cs::CvSource outputStreamStd = frc::CameraServer::GetInstance()->PutVideo("Gray", 640, 480);
    nt::NetworkTableEntry cameraEntry;
    auto inst = nt::NetworkTableInstance::GetDefault();
    auto table = inst.GetTable("database");
    cameraEntry = table->GetEntry("camera");
    while(true)
    {
      if(cvSink.GrabFrame(source))
      {    
        grip -> Process(source);
        cv::Mat* output = grip->GetHsvThresholdOutput();
        //shared_ptr<Mat> processed(output);
        cameraEntry.Set(output.size());
    }
  }

  }
};

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
