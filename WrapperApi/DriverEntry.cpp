#include "ApiWrapper.h"




VOID OnDriverUnload(IN PDRIVER_OBJECT pDriverObject)
{
	UNREFERENCED_PARAMETER(pDriverObject);
	Log("Driver unload!\n");
}

NTSTATUS DriverEntry(IN PDRIVER_OBJECT pDriverObject, IN PUNICODE_STRING pRegistryPath)
{
	UNREFERENCED_PARAMETER(pRegistryPath);
 
	Log("Windows number ->\t %u\n", ApiWrapper::GetWindowsNumber());

	Log("Windows NtOskrlnBase ->\t 0x%p\n", GetKernelBase());

   
	return STATUS_SUCCESS;
}