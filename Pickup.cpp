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
		Spyder::TwoIntConfig stick;
		Spyder::ConfigVar<float> curvature;
public:
		Pickup() : Spyder::Subsystem("Pickup"), extendSol("pickup_open_sol", 5), releaseSol("pickup_close_sol", 6),
		eSol("bind_pickup_close", 3, 6), rSol("bind_pickup_open", 3, 7), 
		arm("pickup_arm_mot", 12), stick("bind_pickup_arm_axis", 3, 2), curvature("drive_curvature",0.3f)
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
		}

		virtual void Periodic(Spyder::RunModes runmode)
		{
			float motor = 0.0f;
			float curve = curvature.GetVal();
			Joystick *pickJoy  = Spyder::GetJoystick(stick.GetVar(1));
			
			switch(runmode)
				{
				case Spyder::M_DISABLED:
					Spyder::GetSolenoid(extendSol.GetVal())->Set(false);
					Spyder::GetSolenoid(releaseSol.GetVal())->Set(true);
					Spyder::GetVictor(arm.GetVal())->Set(0);	
					break;
				case Spyder::M_TELEOP:
					motor = pickJoy->GetRawAxis(stick.GetVar(2));
					motor = fabs(motor)> Spyder::GetDeadzone() ? motor : 0;			
					motor = ((motor*motor*motor)*curve + (motor*(1.f-curve)));
					Spyder::GetVictor(arm.GetVal())->Set(motor);
					
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
