#include "ApiWrapper.h"




VOID OnDriverUnload(IN PDRIVER_OBJECT pDriverObject)
{
	UNREFERENCED_PARAMETER(pDriverObject);
	Log("Driver unload!\n");
}

NTSTATUS DriverEntry(IN PDRIVER_OBJECT pDriverObject, IN PUNICODE_STRING pRegistryPath)
{
	UNREFERENCED_PARAMETER(pRegistryPath);
 
	auto dayWrapper = ApiWrapper::InitUnicodeString(L"Test day");
	UNICODE_STRING dayGood;
	RtlInitUnicodeString(&dayGood, L"Test day");
	Log("buffer no wrapper ->\t 0x%p\n", dayGood.Buffer);
	Log("buffer wrapper ->\t 0x%p\n", dayWrapper.Buffer);

	Log("lenght no wrapper ->\t 0x%p\n", dayGood.Length);
	Log("lenght wrapper ->\t 0x%p\n", dayWrapper.Length);
 
	Log("Max lenght no wrapper ->\t 0x%p\n", dayGood.MaximumLength);
	Log("Max lenght wrapper ->\t 0x%p\n", dayWrapper.MaximumLength);
	
	Log("Windows number ->\t 0x%u", ApiWrapper::GetWindowsNumber());

	Log("Windows build number ->\t 0x%u", ApiWrapper::GetNumberBuild());

	ApiWrapper::KeMessageBox(L"Test", L"Good day", MB_OK);

   
	return STATUS_SUCCESS;
}
