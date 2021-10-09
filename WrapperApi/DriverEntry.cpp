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
	Log("buffer no wrapper ->\t 0x%p", dayGood.Buffer);
	Log("buffer wrapper ->\t 0x%p", dayWrapper.Buffer);

	Log("lenght no wrapper ->\t 0x%p", dayGood.Length);
	Log("lenght wrapper ->\t 0x%p", dayWrapper.Length);
 
	Log("Max lenght no wrapper ->\t 0x%p", dayGood.MaximumLength);
	Log("Max lenght wrapper ->\t 0x%p", dayWrapper.MaximumLength);
	
	Log("Windows number ->\t %u", ApiWrapper::GetWindowsNumber());

	Log("Windows build number ->\t %u", ApiWrapper::GetNumberBuild());

	Log("Random number ->\t %u", ApiWrapper::RandomNumber()); 

	Log("Random number ->\t %u", ApiWrapper::RandomNumber()); 

	Log("Random number ->\t %u", ApiWrapper::RandomNumber());


	ApiWrapper::KeMessageBox(L"Test", L"Good day", MB_OK);
   
	return STATUS_SUCCESS;

    
}
