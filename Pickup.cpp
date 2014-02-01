#include "Subsystem.h"
#include "WPIObjMgr.h"
#include "Config.h"

class Pickup : public Spyder::Subsystem
{
		/*Spyder::ConfigVar<UINT32> extendSol; 
		Spyder::ConfigVar<UINT32> releaseSol;
		Spyder::TwoIntConfig eSol;
		Spyder::TwoIntConfig rSol;
		
		Spyder::ConfigVar<UINT32> arm;
		Spyder::TwoIntConfig stick;*/
public:
		Pickup()
		{
			
		}	 
		virtual ~Pickup() 
		{
		
		}	
	
		virtual void Init(Spyder::RunModes runmode)
		{
				
		}

		virtual void Periodic(Spyder::RunModes runmode)
		{
				switch(runmode)
				{
				case Spyder::M_DISABLED:
					break;
				case Spyder::M_TELEOP:
					break;
				default:
					break;
				}
		}	
};

Pickup pickup;
