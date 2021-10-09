#pragma once
#pragma once
#include <ntdef.h>
#include <ntifs.h>
#include <ntddk.h>
#include <minwindef.h>
#include <intrin.h>

typedef enum _uTypeBoxReason 
{
	 MB_OK,
	 MB_OKCANCEL,
	 MB_ABORTRETRYIGNORE,
	 MB_YESNOCANCEL,
	 MB_YESNO,
	 MB_RETRYCANCEL,
	 MB_HELP = 0x00004000L
}uTypeBoxReason;


#define Log(x,...)  DbgPrintEx(0, 0, "[ApiWrapper] " x, __VA_ARGS__)
 
 
 EXTERN_C NTSTATUS NTAPI ExRaiseHardError
(	NTSTATUS ErrorStatus,
	ULONG NumberOfParameters,
	ULONG UnicodeStringParameterMask, 
	PULONG_PTR Parameters,
	ULONG ValidResponseOptions,
	PULONG Response
);
