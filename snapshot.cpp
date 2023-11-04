#include <iostream>  
#include <windows.h>  
#include <tlhelp32.h>  

int main(int argc, char* argv[])
{
    BOOL bGet = FALSE;
    char buf[260] = "";
    HANDLE hSnapshot;
    PROCESSENTRY32 ppe;     //구성된 자료구조를 저장하기 위한 엔트리.  

    hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);//system 프로세서(pid=0)의 상태를 읽어 온다   
    ppe.dwSize = sizeof(PROCESSENTRY32);                        //엔트리 구조체 사이즈를 정해준다.  
    bGet = Process32First(hSnapshot, &ppe);                     //엔트리 중 자료를 가져온다.  

    while (bGet)
    {
        WideCharToMultiByte(CP_ACP, 0, ppe.szExeFile, 260, buf, 260, NULL, NULL);
        fprintf(stdout, "processName:%-15s\t", buf);          //프로세스 이름을 출력  
        fprintf(stdout, "processID:%5d\n", ppe.th32ProcessID);//프로세스 아이디를 출력  
        bGet = Process32Next(hSnapshot, &ppe);
    }

    CloseHandle(hSnapshot);

    return 0;
}
