#pragma once
#pragma once
#include <ntdef.h>
#include <ntifs.h>
#include <ntddk.h>
#include <minwindef.h>
#include <intrin.h>



#define Log(x,...)  DbgPrintEx(0, 0, "[ApiWrapper] " x, __VA_ARGS__)
 
 
 