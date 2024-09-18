#include <windows.h>
#include "CMD.h"

HANDLE CMD_hShm[1];  // handle for shared memory
CMD_STRUCT *CMD[1]; // structure to share

// function to open CMD shared memory
void CMD_open_SM(unsigned char CMDnum){
    
    char SharedMemName[16]; // name of shared memory
    sprintf(SharedMemName, "CMD%d", CMDnum);
    
    // open shared memory
    CMD_hShm[CMDnum] = CreateFileMappingA((HANDLE) -1, NULL, PAGE_READWRITE, 0, sizeof(CMD_STRUCT), SharedMemName);
    // share structure
    CMD[CMDnum] = (CMD_STRUCT *)MapViewOfFile(CMD_hShm[CMDnum], FILE_MAP_ALL_ACCESS, 0, 0, sizeof(CMD_STRUCT));

}

// function to close CMD shared memory
void CMD_close_SM(unsigned char CMDnum){
    
    // close shared memory
    UnmapViewOfFile(CMD[CMDnum]);
    CloseHandle(CMD_hShm[CMDnum]);
    
}

int main(){
    
    int s, c;
    
    CMD_open_SM(0);
    
    while(1){
        system("cls");
        printf("AOCS mode[%d], STT power state[%d], STT output mode[%d], STT start output[%d], unloading flag[%d]\n",
                CMD[0]->AOCS_mode, CMD[0]->STT_power_state, CMD[0]->STT_output_mode, CMD[0]->STT_start_output, CMD[0]->unloading_flag);
        printf("\n");
        
        printf("1: AOCS mode\n");
        printf("2: STT power state\n");
        printf("3: STT output mode\n");
        printf("4: STT start output\n");
        printf("5: unloading flag\n");
        printf("> ");
        scanf("%d", &s);
        
        switch (s){
            case 1:
                printf("Input AOCS mode\n");
                printf("> ");
                scanf("%d", &c);
                CMD[0]->AOCS_mode = c;
                break;
            case 2:
                printf("Input STT power state (0: idel, 1: capture)\n");
                printf("> ");
                scanf("%d", &c);
                if(c == 0 || c == 1){
                    CMD[0]->STT_power_state = c;
                }
                break;
            case 3:
                printf("Input STT output mode (0: manual, 1: auto)\n");
                printf("> ");
                scanf("%d", &c);
                if(c == 0 || c == 1){
                    CMD[0]->STT_output_mode = c;
                }
                break;
            case 4:
                printf("Input STT start output (0: stop, 1: start)\n");
                printf("> ");
                scanf("%d", &c);
                if(c == 0 || c == 1){
                    CMD[0]->STT_start_output = c;
                }
                break;
            case 5:
                printf("Input unloading flag (0: no unloading, 1: unloading)\n");
                printf("> ");
                scanf("%d", &c);
                if(c == 0 || c == 1){
                    CMD[0]->unloading_flag = c;
                }
                break;
            default:
                break;
        }
    }
    
    CMD_close_SM(0);
    
    return 0;
}