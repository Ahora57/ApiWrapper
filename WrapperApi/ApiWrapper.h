#pragma once
#include "NoCrt.h"

 



namespace ApiWrapper
{ 
    UNICODE_STRING InitUnicodeString(static const wchar_t* string_to_init)
	{

      UNICODE_STRING stringInit;
         
      stringInit.Length = sizeof(string_to_init) - sizeof(wchar_t);
      stringInit.MaximumLength = stringInit.Length + 2;
      stringInit.Buffer = (wchar_t*)string_to_init;
       return stringInit;

	}

    STRING InitSString(static const char* string_to_init)
    {
        // i don't shure ,what it's work  
         
        STRING stringInit{ 0 };
        stringInit.Length = sizeof(string_to_init) - sizeof(char);
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
        //just set buffer/Length

        /*
        in disassembly  RtlFreeUnicodeString use ExFreePoolWithTag
        */
        str.Buffer = 0;
        str.Length = 0;
        str.MaximumLength = 0;
    }
    
 
    void FreeString(STRING& str)
    {
        //just set buffer/Length

        /*
        */
        str.Buffer = 0;
        str.Length = 0;
        str.MaximumLength = 0;
    }

    BYTE GetWindowsNumber()
    { 
       auto NtMajorVersion = *(BYTE*)0x7FFE026C;
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
           switch (*(BYTE*)0x7FFE0270)
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
            return *(int*)0x7FFE0260;
        }
        return 0; //we can't get without winapi and it's work on 10/ 11 Windows or leater 
    }
    EXTERN_C DWORD GetKernelBase();//ntoskrnl
 

 
 



}
