#include "Subsystem.h"
#include "WPIObjMgr.h"
#include "Config.h"
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
		Spyder::TwoIntConfig altPickButton_in;
		Spyder::TwoIntConfig altPickButton_out;
		Spyder::TwoIntConfig altESol;
		Spyder::TwoIntConfig altRSol;
		
public:
		Pickup() : Spyder::Subsystem("Pickup"), extendSol("pickup_open_sol", 5), 
		releaseSol("pickup_close_sol", 6),
		eSol("bind_pickup_close", 3, 5), rSol("bind_pickup_open", 3, 6), 
		arm("pickup_arm_mot", 6), pickButton_in("bind_intake_button", 3, 8), 
		pickButton_out("bind_outake_button",3,7),
		altPickButton_in("altPickButton_in", 2,4),
		altPickButton_out("altPickButton_out",2,5),
		altESol("altESol", 2, 2),
		altRSol("altRSol", 2, 1)
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
					Spyder::GetVictor(arm.GetVal())->Set(0);	
					break;
				case Spyder::M_AUTO:
					Spyder::GetSolenoid(extendSol.GetVal())->Set(true);
					Spyder::GetSolenoid(releaseSol.GetVal())->Set(false);
					break;
				case Spyder::M_TELEOP:
					int pickSwitch;
					if(Spyder::GetJoystick(pickButton_in.GetVar(1))->GetRawButton(pickButton_in.GetVar(2))
							|| Spyder::GetJoystick(altPickButton_in.GetVar(1))->GetRawButton(altPickButton_in.GetVar(2)))
					{
						pickSwitch = 1;
					}
					if(Spyder::GetJoystick(pickButton_out.GetVar(1))->GetRawButton(pickButton_out.GetVar(2))
							|| Spyder::GetJoystick(altPickButton_out.GetVar(1))->GetRawButton(altPickButton_out.GetVar(2)))
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
					
					if((Spyder::GetJoystick(eSol.GetVar(1))->GetRawButton(eSol.GetVar(2))||
							Spyder::GetJoystick(altESol.GetVar(1))->GetRawButton(altESol.GetVar(2)))==true) {
						Spyder::GetSolenoid(extendSol.GetVal())->Set(true);
						Spyder::GetSolenoid(releaseSol.GetVal())->Set(false);
					}
					else if((Spyder::GetJoystick(rSol.GetVar(1))->GetRawButton(rSol.GetVar(2))||
							Spyder::GetJoystick(altRSol.GetVar(1))->GetRawButton(altRSol.GetVar(2)))==true) {
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
