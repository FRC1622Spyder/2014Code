#include "Subsystem.h"
#include "WPIObjMgr.h"
#include "Config.h"



class Pickup : public Spyder::Subsystem
{
		Spyder::ConfigVar<UINT32> extendSol; 
		Spyder::ConfigVar<UINT32> releaseSol;
		Spyder::TwoIntConfig eSol;
		Spyder::TwoIntConfig rSol;

		Spyder::ConfigVar<UINT32> arm;
		Spyder::TwoIntConfig stick;
		Spyder::ConfigVar<double> rampPickup;
		double counter;
		int init;
public:
		Pickup() : Spyder::Subsystem("Pickup"), extendSol("pickup_open_sol", 5), releaseSol("pickup_close_sol", 6),
		eSol("bind_pickup_close", 3, 6), rSol("bind_pickup_open", 3, 7), 
		arm("pickup_arm_mot", 12), stick("bind_pickup_arm_axis", 3, 2), 
		rampPickup("pickup_ramp", 0.666), counter(0.), init(0)
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
				switch(runmode)
				{
				case Spyder::M_DISABLED:
					Spyder::GetSolenoid(extendSol.GetVal())->Set(false);
					Spyder::GetSolenoid(releaseSol.GetVal())->Set(true);
					Spyder::GetVictor(arm.GetVal())->Set(0.0f);	
						break;
				case Spyder::M_TELEOP:
					Spyder::GetVictor(arm.GetVal())->Set(Spyder::GetJoystick(stick.GetVar(1))->GetRawAxis(stick.GetVar(2)));
					if(init < 10);
					{
						 counter = rampPickup.GetVal() * Spyder::GetJoystick(stick.GetVar(1))->GetRawAxis(stick.GetVar(1));
						 Spyder::GetVictor(arm.GetVal())->Set(counter);
						 init++;
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
