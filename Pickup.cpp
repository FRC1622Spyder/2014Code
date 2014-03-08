#include "Subsystem.h"
#include "WPIObjMgr.h"
#include "Config.h"
#include <iostream>
#include <math.h>


class Pickup : public Spyder::Subsystem
{
		Spyder::ConfigVar<UINT32> extendSol; 
		Spyder::ConfigVar<UINT32> releaseSol;
		Spyder::TwoIntConfig eSol;
		Spyder::TwoIntConfig rSol;

		Spyder::ConfigVar<UINT32> arm;
		Spyder::TwoIntConfig pickButton_in;
		Spyder::TwoIntConfig pickButton_out;
		Spyder::ConfigVar<double> autoIntakeTime;
		unsigned char autoPickPhase;
		float autoPickStart;
public:
		Pickup() : Spyder::Subsystem("Pickup"), extendSol("pickup_open_sol", 5), releaseSol("pickup_close_sol", 6),
		eSol("bind_pickup_close", 3, 5), rSol("bind_pickup_open", 3, 6), 
		arm("pickup_arm_mot", 6), pickButton_in("bind_intake_button", 3, 8), pickButton_out("bind_outake_button",3,7),
		autoIntakeTime("pickup_autoIntake_time", 1), autoPickPhase(0)
		{	
		}	 
		virtual ~Pickup() 
		{
		}	
	
		virtual void Init(Spyder::RunModes runmode)
		{
			Spyder::GetSolenoid(extendSol.GetVal())->Set(false);
			Spyder::GetSolenoid(releaseSol.GetVal())->Set(true);
			Spyder::GetVictor(arm.GetVal())->Set(0.0f);
			struct timespec tp;
			switch(runmode)
			{
			case Spyder::M_AUTO:
				autoPickPhase = 0;
				clock_gettime(CLOCK_REALTIME, &tp);
				autoPickStart = (double)tp.tv_sec + double(double(tp.tv_nsec)*1e-9);
			break;
			default:
				break;
			}
		}

		virtual void Periodic(Spyder::RunModes runmode)
		{	
			switch(runmode)
				{
				case Spyder::M_DISABLED:
					/*Spyder::GetSolenoid(extendSol.GetVal())->Set(true);
					Spyder::GetSolenoid(releaseSol.GetVal())->Set(false);
					Spyder::GetVictor(arm.GetVal())->Set(0);	
					break;*/
					
					timespec theTimespec;
					clock_gettime(CLOCK_REALTIME, &theTimespec);
					double curTime = theTimespec.tv_sec;
					curTime+=theTimespec.tv_nsec*1e-9;
					double autoPickTime = curTime - autoPickStart;
					
				case Spyder::M_AUTO:
					switch(autoPickPhase)
					{
					case 0:
						Spyder::GetVictor(arm.GetVal())->Set(1);
						if(autoPickTime >= autoIntakeTime.GetVal())
						{
							autoPickPhase++;
						}
						break;
					case 1:
						Spyder::GetSolenoid(releaseSol.GetVal())->Set(false);
						Spyder::GetSolenoid(extendSol.GetVal())->Set(true);
						break;
					}
					break;
				case Spyder::M_TELEOP:
					int pickSwitch;
					if(Spyder::GetJoystick(pickButton_in.GetVar(1))->GetRawButton(pickButton_in.GetVar(2)))
					{
						pickSwitch = 1;
					}
					if(Spyder::GetJoystick(pickButton_out.GetVar(1))->GetRawButton(pickButton_out.GetVar(2)))
					{
						pickSwitch = 2;
					}
					
					switch(pickSwitch)
					{
					case 1:
						Spyder::GetVictor(arm.GetVal())->Set(1);
						break;
					case 2:
						Spyder::GetVictor(arm.GetVal())->Set(-1);
						break;
					default:
						Spyder::GetVictor(arm.GetVal())->Set(0);
						break;
					}
					
					if(Spyder::GetJoystick(eSol.GetVar(1))->GetRawButton(eSol.GetVar(2))==true) {
						Spyder::GetSolenoid(extendSol.GetVal())->Set(true);
						Spyder::GetSolenoid(releaseSol.GetVal())->Set(false);
					}
					else if(Spyder::GetJoystick(rSol.GetVar(1))->GetRawButton(rSol.GetVar(2))==true) {
						Spyder::GetSolenoid(extendSol.GetVal())->Set(false);
						Spyder::GetSolenoid(releaseSol.GetVal())->Set(true);
					}
					break;
					
				default:
					Spyder::GetSolenoid(extendSol.GetVal())->Set(false);
					Spyder::GetSolenoid(releaseSol.GetVal())->Set(true);
					Spyder::GetVictor(arm.GetVal())->Set(0.0f);
					break;
				}
		}
		virtual void RobotInit()
		{
		}
};
Pickup pickup;
