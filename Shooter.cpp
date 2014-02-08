#include "Subsystem.h"
#include "WPIObjMgr.h"
#include "Config.h"
#include "Console.h"
#include <cmath>
#include <iostream>

class Shooter : public Spyder::Subsystem
{
private:
	Spyder::ConfigVar<UINT32> motorShoot1;
	Spyder::ConfigVar<UINT32> motorShoot2;
	Spyder::ConfigVar<UINT32> shooterRamp;
	Spyder::ConfigVar<UINT32> pistonSolenoidExt;
	Spyder::ConfigVar<UINT32> pistonSolenoidRet;
	Spyder::ConfigVar<double> firePhase1Time;
	Spyder::ConfigVar<double> firePhase2Time;
	Spyder::ConfigVar<double> firePhase3Time;
	
	Spyder::TwoIntConfig fireButton;
	Spyder::TwoIntConfig shooterJoystick;
	
	bool isPistonOut;
	float speed;
	double lastShooterChange;
	unsigned char firePhase;
	double fireStart;
	
public:
	Shooter() : Spyder::Subsystem("Shooter"), motorShoot1("firstShooterMotor",4), //Get correct numbers
			motorShoot2("secondShooterMotor", 3), shooterJoystick("adjustShooterHeight", 3, 1),
			pistonSolenoidExt("shooter_pistonSolenoidExt", 1), pistonSolenoidRet("shooter_pistonSolenoidRet", 2),
			fireButton("bind_shooterFire", 3, 2), isPistonOut(false), speed(0.f), lastShooterChange(0.0), 
			shooterRamp("Motor ramp is set", 0.66)
	{
	}
	virtual ~Shooter()
	{
	}
	
	virtual void Init(Spyder::RunModes runmode)
	{
		Spyder::GetVictor(motorShoot1.GetVal())->Set(0);
		Spyder::GetVictor(motorShoot2.GetVal())->Set(0);
		struct timespec tp;
		switch(runmode)
		{
		case Spyder::M_TELEOP:
			firePhase = 0;
			clock_gettime(CLOCK_REALTIME, &tp);
			fireStart = (double)tp.tv_sec + double(double(tp.tv_nsec)*1e-9);
			break;
		default:
			break; 
		}
	}
	
	virtual void Periodic(Spyder::RunModes runmode)//CHECK IF JOYSTICK IS POS/NEG
	{
		
		switch(runmode)//Winch motor can only drive forwards
		{
			case Spyder::M_DISABLED://disabled code here
			{	Spyder::GetVictor(motorShoot1.GetVal())->Set(0);
				Spyder::GetVictor(motorShoot2.GetVal())->Set(0);
				Spyder::GetSolenoid(pistonSolenoidExt.GetVal())->Set(false);
				Spyder::GetSolenoid(pistonSolenoidRet.GetVal())->Set(true);
			}
				break;
			case Spyder::M_AUTO://autonomous code here
			{
				Spyder::GetVictor(motorShoot1.GetVal())->Set(0);
				Spyder::GetVictor(motorShoot2.GetVal())->Set(0);
			}
				break;
				
			case Spyder::M_TELEOP://Tele-operation code here
			{
				Joystick *joystick = Spyder::GetJoystick(shooterJoystick.GetVar(1));//get correct joystick number from mechanical
				float val = joystick->GetRawAxis(shooterJoystick.GetVar(2));
				val = std::fabs(val) > Spyder::GetDeadzone() ? val : 0;
				if(val < 0)
					val=0;
				
				struct timespec tp;
				timespec theTimespec;
				clock_gettime(CLOCK_REALTIME, &theTimespec);
				double theTime = theTimespec.tv_sec;
				theTime+=theTimespec.tv_nsec*1e-9;
				double curTime = (double)tp.tv_sec + double(double(tp.tv_nsec)*1e-9);
				double teleopRunTime = curTime - fireStart;
				
				//when Kyle presses button, firephase = 0
				if(Spyder::GetJoystick(fireButton.GetVar(1))->GetRawButton(fireButton.GetVar(2))
						&& !firePhase)
				{
					
					firePhase = 1;
				}
					
				switch(firePhase)//meant to fire then reset
				{
					case 1://initialize
						Spyder::GetSolenoid(pistonSolenoidRet.GetVal())->Set(false);
						Spyder::GetSolenoid(pistonSolenoidExt.GetVal())->Set(true);
						if (teleopRunTime >= firePhase1Time.GetVal())
						{
							fireStart = curTime;
							++firePhase;
						}
						break;
					case 2://Re-engage the arm!
						Spyder::GetSolenoid(pistonSolenoidExt.GetVal())->Set(false);
						Spyder::GetSolenoid(pistonSolenoidRet.GetVal())->Set(true);
						if(teleopRunTime >=firePhase2Time.GetVal())
						{
							++firePhase;
						}
						break;
					case 3://Winch it back down !
						Spyder::GetVictor(motorShoot1.GetVal())->Set(1);
						Spyder::GetVictor(motorShoot2.GetVal())->Set(1);
						if(teleopRunTime >firePhase3Time.GetVal())//Get actual time
						{
							firePhase = 0;
						}
						break;
					case 0://Stop motors after winching
						Spyder::GetVictor(motorShoot1.GetVal())->Set(0);
						Spyder::GetVictor(motorShoot2.GetVal())->Set(0);
						break;
				}
					
					/*Spyder::GetVictor(motorShoot1.GetVal())->Set(speed);//find what speed it needs to be
					Spyder::GetVictor(motorShoot2.GetVal())->Set(speed);*/
				
			}
				break;
		};
	}
	
	virtual void RobotInit()
	{
	}
};

Shooter shooter;
