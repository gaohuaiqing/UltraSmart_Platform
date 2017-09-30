#include <windows.h>
#include <powrprof.h>
#include "UsHwPowerControl.h"


bool EnableShutdownPrivilege()
{
	HANDLE hProcess = NULL;
	HANDLE hToken = NULL;
	LUID uID = {0};
	TOKEN_PRIVILEGES stToken_Privileges = {0};

	hProcess = ::GetCurrentProcess();

	if ( ! OpenProcessToken(hProcess, TOKEN_ADJUST_PRIVILEGES, &hToken ) )
	{
		return false;
	}

	if ( ! LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME, &uID)  )
	{
		return false;
	}

	stToken_Privileges.PrivilegeCount = 1;
	stToken_Privileges.Privileges[0].Luid = uID;
	stToken_Privileges.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

	if ( ! AdjustTokenPrivileges(hToken, FALSE, &stToken_Privileges, 
		sizeof(stToken_Privileges), NULL, NULL)  )
	{
		return false;
	}

	if ( GetLastError() != ERROR_SUCCESS )
	{
		return FALSE;
	}


	::CloseHandle(hToken);
	return TRUE;
}


bool ShutDownOS(bool bForce)
{
	EnableShutdownPrivilege();
	if (bForce)
	{
		return ::ExitWindowsEx(EWX_SHUTDOWN | EWX_FORCE, 0);
	} 
	else
	{
		return ::ExitWindowsEx(EWX_SHUTDOWN | EWX_FORCE, 0);
	}
}


bool RebootOS(bool bForce)
{
	EnableShutdownPrivilege();
	if (bForce)
	{
		return ::ExitWindowsEx(EWX_REBOOT | EWX_FORCE, 0);
	} 
	else
	{
		return ::ExitWindowsEx(EWX_REBOOT | EWX_FORCE, 0);
	}

}


void SuspendOS()
{
	//进入待机
    if(0 == SetSuspendState(false, false, false))
	{	
		//如果尝试进入待机失败，则强制进入待机
        if(0 == SetSuspendState(false, true, false))
		{

		}
	}
}


void CtrlOS(int ctrl)
{
	switch (ctrl)
	{
	case CTRL_SUSPEND:		
		SuspendOS();
		break;

	case CTRL_REBOOT:
		RebootOS(TRUE);
		break;

	case CTRL_SHUTDOWN:
		ShutDownOS(TRUE);
		break;

	default:
		break;
	}
}
