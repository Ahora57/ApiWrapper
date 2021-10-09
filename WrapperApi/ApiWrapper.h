#pragma once
#include "NoCrt.h"

 



namespace ApiWrapper
{ 
    UNICODE_STRING InitUnicodeString(static const wchar_t* string_to_init)
	{

      UNICODE_STRING stringInit;
         
       stringInit.Length = NoCRT::string::wstrlen(string_to_init) *2;
      stringInit.MaximumLength = stringInit.Length + 2;
      stringInit.Buffer = (wchar_t*)string_to_init;
       return stringInit;

	}

    STRING InitSString(static const char* string_to_init)
    {
        // i don't shure ,what it's work  
         
        STRING stringInit{ 0 };
        stringInit.Length = NoCRT::string::strlen(string_to_init);
        stringInit.MaximumLength = stringInit.Length + 2;
        stringInit.Buffer = (char*)string_to_init;
        return stringInit;
    }





    int CompareUnicodeString(UNICODE_STRING str_1, UNICODE_STRING str_2,bool case_int_sensitive = false)
    {
        //return 0 if equal
        if (case_int_sensitive)
        { 
            return NoCRT::string::wstrcmp(str_1.Buffer,str_2.Buffer);
        }
        else 
        {
            return NoCRT::string::wstricmp(str_1.Buffer, str_2.Buffer);
        }
        
    }
     

    bool  EqualUnicodeString(UNICODE_STRING str_1, UNICODE_STRING str_2, bool case_in_sensitive = false)
    {
        //return 1 if equal
        if (case_in_sensitive)
        {
            return !NoCRT::string::wstrcmp(str_1.Buffer, str_2.Buffer);
        }
        else
        {
            return !NoCRT::string::wstricmp(str_1.Buffer, str_2.Buffer);
        }
    }




    int CompareString(STRING str_1, STRING str_2)
    {
        //return 0 if equal

        return NoCRT::string::stricmp(str_1.Buffer, str_2.Buffer);


    }

    
    void FreeUnicodeString(UNICODE_STRING& str)
    {
        //just set 0  buffer/Length

        /*
        in disassembly  RtlFreeUnicodeString use ExFreePoolWithTag wtf?
        */
        str.Buffer = 0;
        str.Length = 0;
        str.MaximumLength = 0;
    }
    
 
    void FreeString(STRING& str)
    {
        //just set 0  buffer/Length

       
        str.Buffer = 0;
        str.Length = 0;
        str.MaximumLength = 0;
    }

    BYTE GetWindowsNumber()
    { 
       auto NtMajorVersion = *(BYTE*)0xFFFFF7800000026C;   //  0x7FFE026C
       if (NtMajorVersion == 10)
       {
           return 10;
       }
       else if (NtMajorVersion == 5)
       {
           return 6;//Windows XP
       }
       else if (NtMajorVersion == 6)
       {
           /*
           https://www.godeye.club/2021/06/03/002-mhyprot-insider-callbacks.html
           */
            switch (*(BYTE*)0xFFFFF78000000270)  //0x7FFE0270 NtMinorVersion
           {
           case 1:
               return 7;//windows 7
           case 2:
               return 8; //window 8
           case 3:
               return 9; //windows 8.1
           default:
               return 11;
           }

       }
       else
           return 11;
    }
    int GetNumberBuild()
    {
        if (GetWindowsNumber() >= 10)
        {
            return *(int*)0xFFFFF78000000260; //NtBuildNumber
           // return *(int*)0x7FFE0260;
        }
        return 0; //we can't get without winapi and it's work on 10/ 11 Windows or leater 
    }
    EXTERN_C DWORD GetKernelBase();//ntoskrnl
 
	/*
	https://github.com/VollRagm/NoEQU8/blob/059e38040fa501cdad55160ef501fc1fd9608f77/src/EQU8_Hook/util.cpp#L3
	*/
 
   ULONG KeMessageBox(PCWSTR title, PCWSTR text, ULONG_PTR type)
    {
        UNICODE_STRING u_title = InitUnicodeString(title);
        UNICODE_STRING u_text = InitUnicodeString(text);
         
        ULONG_PTR args[] = { (ULONG_PTR)&u_text, (ULONG_PTR)&u_title, type };
        ULONG response = 0;

        ExRaiseHardError(STATUS_SERVICE_NOTIFICATION, 3, 3, args, 1, &response);
        return response;
    }

  DWORD64 RandomNumber(int max_number = 1337)
    {

         /*
         use 2 tick from timer APERF and  timer  rdtsc +  SystemTime(KUSER_SHARED_DATA) 
         */


        int cpuid[4]{ 0 };
        DWORD64 SystemTime = *(DWORD*)0xFFFFF78000000014;
        __cpuid(cpuid, 0);//vm-exit for update tick
        auto  tick_aperf= __readmsr(0x000000E8);
        auto tick_rdtsc = __readmsr(0x000010);
        return  (SystemTime + tick_aperf + tick_rdtsc)% max_number;
    }

}

