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
	Spyder::ConfigVar<UINT32> pistonSolenoidExt;
	Spyder::ConfigVar<UINT32> pistonSolenoidRet;
	Spyder::ConfigVar<double> firePhase1Time;
	Spyder::ConfigVar<double> firePhase2Time;
	Spyder::ConfigVar<float> firePreset1;
	Spyder::ConfigVar<float> firePreset2;
	Spyder::ConfigVar<float> firePreset3;

	Spyder::TwoIntConfig fireButton;
	Spyder::TwoIntConfig fireWinch1;//winch preset location1
	Spyder::TwoIntConfig fireWinch2;
	Spyder::TwoIntConfig fireWinch3;
	
	unsigned char firePhase;
	double fireStart;
	float autofireStart;
	unsigned char autofirePhase;
	double winchTime;
	
public:
	Shooter() : Spyder::Subsystem("Shooter"), motorShoot1("firstShooterMotor",4), //Get correct numbers
			motorShoot2("secondShooterMotor", 3), pistonSolenoidExt("shooter_pistonSolenoidExt", 1), 
			pistonSolenoidRet("shooter_pistonSolenoidRet", 2), firePhase1Time ("shooter_firetime1", 1),
			firePhase2Time("shooter_firetime2", 1), firePreset1("winch_time_preset1", 1),
			firePreset2("winch_time_preset2", 0.75),firePreset3("winch_time_preset3", 0.5),
			fireButton("bind_shooterFire1", 3, 2), fireWinch1("winch_pos1", 3, 1), 
			fireWinch2("winch_pos2", 3, 3), fireWinch3("winch_pos3", 3, 4),
			firePhase(0), fireStart(0), winchTime(0)
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
		case Spyder::M_AUTO:
			firePhase = 0;
			clock_gettime(CLOCK_REALTIME, &tp);
			autofireStart = (double)tp.tv_sec + double(double(tp.tv_nsec)*1e-9);
			break;
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
				winchTime = firePreset3.GetVal();
				struct timespec tp;
				timespec theTimespec;
				clock_gettime(CLOCK_REALTIME, &theTimespec);
				double theTime = theTimespec.tv_sec;
				theTime+=theTimespec.tv_nsec*1e-9;
				double curTime = (double)tp.tv_sec + double(double(tp.tv_nsec)*1e-9);
				double autoRunTime = curTime - autofireStart;
				switch(autofirePhase)
				{
				case 1:
					Spyder::GetSolenoid(pistonSolenoidRet.GetVal())->Set(false);
					Spyder::GetSolenoid(pistonSolenoidExt.GetVal())->Set(true);
					if(autoRunTime > firePhase1Time.GetVal())
					{
						autofireStart = curTime;
						autofirePhase++;
					}
					break;
				case 2:
					Spyder::GetSolenoid(pistonSolenoidExt.GetVal())->Set(false);
					Spyder::GetSolenoid(pistonSolenoidRet.GetVal())->Set(true);
					break;
				case 0:
					Spyder::GetVictor(motorShoot1.GetVal())->Set(1);
					Spyder::GetVictor(motorShoot2.GetVal())->Set(1);
					if(autoRunTime > winchTime)
					{
						Spyder::GetVictor(motorShoot1.GetVal())->Set(0);
						Spyder::GetVictor(motorShoot2.GetVal())->Set(0);
						autofireStart = curTime;
						autofirePhase++;
					}
					break;
				}
			}
				break;
			case Spyder::M_TEST:
			case Spyder::M_TELEOP://Tele-operation code here
			{	
				if(Spyder::GetJoystick(fireWinch1.GetVar(1))->GetRawButton(fireWinch1.GetVar(2)))
					winchTime = firePreset1.GetVal();//Trial + Error the shit out of this
				
				if(Spyder::GetJoystick(fireWinch1.GetVar(1))->GetRawButton(fireWinch1.GetVar(2)))
					winchTime = firePreset2.GetVal();//Ditto
				
				if(Spyder::GetJoystick(fireWinch1.GetVar(1))->GetRawButton(fireWinch1.GetVar(2)))
					winchTime = firePreset3.GetVal();//Ditto
				
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
							firePhase = 0;
						}
						break;
					case 3://Winch it back down !
						Spyder::GetVictor(motorShoot1.GetVal())->Set(1);
						Spyder::GetVictor(motorShoot2.GetVal())->Set(1);
						if(teleopRunTime >winchTime)//Get actual time
						{
							firePhase = 0;
						}
						break;
					case 0://Stop motors after winching
						Spyder::GetVictor(motorShoot1.GetVal())->Set(0);
						Spyder::GetVictor(motorShoot2.GetVal())->Set(0);
						break;
				}
			}
				break;
		};
	}
	
	virtual void RobotInit()
	{
	}
};

Shooter shooter;
