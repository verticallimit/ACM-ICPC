#include <stdio.h>  
#include <iostream.h>  
#include <windows.h>  

typedef void(*pHookStart)();
typedef void(*pHookStop)();

pHookStart HookStart;
pHookStop HookStop;
  
int main(void)  
{  
    HINSTANCE hdll;
	pHookStart hookstart;
	pHookStop hookstop;
    //pMax mm ; 
  
    hdll = LoadLibraryA("KeyBoardDll.dll") ;  
	//hdll = LoadLibraryA("keyboard.dll") ;  
    if (hdll == NULL){  
        printf("can not find dll file.") ;  
        return 1 ;  
    }
	else printf("kankan\n");
  
    hookstart =(pHookStart)GetProcAddress(hdll, "HookStart") ;  
    if (hookstart == NULL)  
    {  
        printf("can not find the Max function.");  
        return 1 ;  
    }  

	hookstart();

	MessageBox(NULL, "Hook", "Information", MB_OK);


	hookstop =(pHookStop)GetProcAddress(hdll, "HookStop") ;  

	hookstop();
	
    FreeLibrary(hdll) ;  
	
	system("pause");
    return 0 ;  
}  
