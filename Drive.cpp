#include "Subsystem.h"
#include "WPIObjMgr.h"
#include "Config.h"
#include <math.h>
#include <iostream>
#include <cmath>

class Drive : public Spyder::Subsystem
{
	
	private:
		Spyder::TwoIntConfig leftJoystick;
		Spyder::TwoIntConfig rightJoystick;
		
		Spyder::ConfigVar<UINT32> leftMotor;
		Spyder::ConfigVar<UINT32> rightMotor;
		
		Spyder::ConfigVar<bool> leftMotorInv;
		Spyder::ConfigVar<bool> rightMotorInv;
		
		Spyder::TwoIntConfig halfSpeed;
		Spyder::ConfigVar<double> ramp;
		
		bool reversed;
		bool lastRevBtnVal;
		Spyder::TwoIntConfig reverseBtn;
		
		float autospeed;
		float invautospeed;
		float autotime;
		double driveStart;
	
	public:
		
		Drive() : Spyder::Subsystem("Drive"), leftJoystick("bind_leftDrive", 1, 2),
				rightJoystick("bind_rightDrive", 2, 2), leftMotor("leftDriveMotor", 2),
				rightMotor("rightDriveMotor", 1), leftMotorInv("leftDriveInverted", true),
				rightMotorInv("rightDriveInverted", false), reversed(false),
				lastRevBtnVal(false), reverseBtn("bind_driveReverse", 2, 3),
				halfSpeed("bind_halfSpeedDrive", 1, 1), ramp("drive_ramp", 0.666), autospeed(127.f),
				invautospeed(-127.f), driveStart(0), autotime(10000.f)
		{
		}
		
		virtual ~Drive()
		{
		}
		
		virtual void Init(Spyder::RunModes runmode)
		{
		}
		
		virtual void Periodic(Spyder::RunModes runmode)
		{
			float right = 0.0f;
			float left = 0.0f;
			Joystick *leftJoy = Spyder::GetJoystick(leftJoystick.GetVar(1));
			Joystick *rightJoy = Spyder::GetJoystick(rightJoystick.GetVar(1));
			
			switch(runmode){
				case Spyder::M_AUTO:
					struct timespec tp;
					timespec theTimespec;
					clock_gettime(CLOCK_REALTIME, &theTimespec);
					double theTime = theTimespec.tv_sec;
					theTime+=theTimespec.tv_nsec*1e-9;
					double curTime = (double)tp.tv_sec + double(double(tp.tv_nsec)*1e-9);
					double teleopRunTime = curTime - driveStart;
					
					if(teleopRunTime < autotime)
					{
						Spyder::GetVictor(leftMotor.GetVal())->Set(invautospeed);
						Spyder::GetVictor(rightMotor.GetVal())->Set(autospeed);
					}
					else
					{
						Spyder::GetVictor(leftMotor.GetVal())->Set(0);
						Spyder::GetVictor(rightMotor.GetVal())->Set(0);
					}
					
					break;
				
				case Spyder::M_DISABLED:
					Spyder::GetVictor(leftMotor.GetVal())->Set(0);
					Spyder::GetVictor(leftMotor.GetVal())->Set(0);
					break;
					
				case Spyder::M_TELEOP:
					left = leftJoy->GetRawAxis(leftJoystick.GetVar(2));
					right = rightJoy->GetRawAxis(rightJoystick.GetVar(2));
					left = fabs(left) > Spyder::GetDeadzone() ? left : 0;
					right = fabs(right) > Spyder::GetDeadzone() ? right : 0;
					
					if(leftMotorInv.GetVal())
					{
						left *= -1;
					}
					
					if(rightMotorInv.GetVal())
					{
						right *= -1;
					}
					
					if(Spyder::GetJoystick(halfSpeed.GetVar(1))->GetRawButton(halfSpeed.GetVar(2)))
					{
						left /= 2.f;
						right /= 2.f;
					}
					
					if(Spyder::GetJoystick(reverseBtn.GetVar(1))->GetRawButton(reverseBtn.GetVar(2)) && !lastRevBtnVal)
					{
						lastRevBtnVal = true;
						reversed = !reversed;
					}
					lastRevBtnVal = Spyder::GetJoystick(reverseBtn.GetVar(1))->GetRawButton(reverseBtn.GetVar(2));
					
					if(reversed)
					{
						float temp = left;
						left = right;
						right = temp;
					}
					
					Spyder::GetVictor(leftMotor.GetVal())->Set(left);
					Spyder::GetVictor(rightMotor.GetVal())->Set(right);
					break;
					
				default:
					Spyder::GetVictor(leftMotor.GetVal())->Set(0);
					Spyder::GetVictor(rightMotor.GetVal())->Set(0);
					break;
			}
			
		}
		
		virtual void RobotInit()
		{
		}
};

Drive drive;
