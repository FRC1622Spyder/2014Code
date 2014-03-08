#include "Subsystem.h"
#include "WPIObjMgr.h"
#include "Config.h"
#include "Console.h"
#include "MyEncoder.h"
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
		
		Spyder::ConfigVar<float> autotime;
		Spyder::TwoIntConfig leftDrive_encoder;
		Spyder::ConfigVar<bool> leftDrive_encoder_inverse;
		Spyder::ConfigVar<double> auto_runDistance;
		double driveStart;
		unsigned char autoPhase;
	public:
		
		Drive() : Spyder::Subsystem("Drive"), leftJoystick("bind_leftDrive", 1, 2),
				rightJoystick("bind_rightDrive", 2, 1), leftMotor("leftDriveMotor", 2),
				rightMotor("rightDriveMotor", 1), leftMotorInv("leftDriveInverted", true),
				rightMotorInv("rightDriveInverted", false), halfSpeed("bind_halfSpeedDrive", 1, 1),
				ramp("drive_ramp", 0.666), reversed(false), lastRevBtnVal(false), 
				reverseBtn("bind_driveReverse", 2, 3),autotime("autonomous_run_time",10000.0f), 
				leftDrive_encoder("drive_leftEncoder_vals", 4 ,5), 
				leftDrive_encoder_inverse("drive_leftEncoder_inverse", 0),
				auto_runDistance("drive_autoDistance", 10), driveStart(0), autoPhase(0)
		{
		}
		
		virtual ~Drive()
		{
		}
		
		virtual void Init(Spyder::RunModes runmode)
		{
			switch(runmode)
			{
				case Spyder::M_AUTO:
					autoPhase = 0;
					break;
				default:
					;
			}
		}
		
		virtual void Periodic(Spyder::RunModes runmode)
		{
			float right = 0.0f;
			float left = 0.0f;
			Joystick *leftJoy = Spyder::GetJoystick(leftJoystick.GetVar(1));
			Joystick *rightJoy = Spyder::GetJoystick(rightJoystick.GetVar(1));
			Encoder *leftDriveEncoder = Spyder::GetEncoder(leftDrive_encoder.GetVar(1),leftDrive_encoder.GetVar(2), leftDrive_encoder_inverse.GetVal());
			leftDriveEncoder->SetDistancePerPulse(12.56);
			switch(runmode){
				case Spyder::M_AUTO:
					switch(autoPhase)
					{
					case 0:
						leftDriveEncoder->Start();
						autoPhase++;
						//break;
					case 1:
						Spyder::GetVictor(leftMotor.GetVal())->Set(-1);
						Spyder::GetVictor(rightMotor.GetVal())->Set(1);
						std::cout<<leftDriveEncoder->GetDistance()<<std::endl;
						if(leftDriveEncoder->GetDistance()>=auto_runDistance.GetVal())
						{
							leftDriveEncoder->Stop();
							leftDriveEncoder->Reset();
							Spyder::GetVictor(leftMotor.GetVal())->Set(0);
							Spyder::GetVictor(rightMotor.GetVal())->Set(0);
							autoPhase++;
						}
						break;
					case 2:
						break;
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
