#ifndef __US_HW_POWER_CONTROL_H__
#define __US_HW_POWER_CONTROL_H__
          
#define CTRL_SUSPEND		1
#define CTRL_REBOOT			2
#define CTRL_SHUTDOWN		3

bool EnableShutdownPrivilege();
bool ShutDownOS(bool bForce);
bool RebootOS(bool bForce);
void SuspendOS();

void CtrlOS(int ctrl);



#endif
