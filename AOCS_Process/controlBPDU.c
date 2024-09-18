#include <windows.h>
#include "BPDU.h"

HANDLE BPDU_hShm[1];  // handle for shared memory
BPDU_STRUCT *BPDU[1]; // structure to share

// function to open BPDU shared memory
void BPDU_open_SM(unsigned char BPDUnum){
    
    char SharedMemName[16]; // name of shared memory
    sprintf(SharedMemName, "BPDU%d", BPDUnum);
    
    // open shared memory
    BPDU_hShm[BPDUnum] = CreateFileMappingA((HANDLE) -1, NULL, PAGE_READWRITE, 0, sizeof(BPDU_STRUCT), SharedMemName);
    // share structure
    BPDU[BPDUnum] = (BPDU_STRUCT *)MapViewOfFile(BPDU_hShm[BPDUnum], FILE_MAP_ALL_ACCESS, 0, 0, sizeof(BPDU_STRUCT));

}

// function to close BPDU shared memory
void BPDU_close_SM(unsigned char BPDUnum){
    
    // close shared memory
    UnmapViewOfFile(BPDU[BPDUnum]);
    CloseHandle(BPDU_hShm[BPDUnum]);
    
}

int main(){
    
    int s, c;
    
    BPDU_open_SM(0);
    
    while(1){
        printf("BPDU: DCDC_SNS[%d] DCDC_MTQ[%d] DCDC_RW[%d]\n",
                BPDU[0]->dcdc_sns, BPDU[0]->dcdc_mtq, BPDU[0]->dcdc_rw);
        printf("BPDU: FOG[%d] GAS[%d] NSAS1[%d] NSAS2[%d] NSAS3[%d] NSAS4[%d] NSAS5[%d] NSAS6[%d]\n",
                BPDU[0]->gyro, BPDU[0]->gas, BPDU[0]->nsas1, BPDU[0]->nsas2, BPDU[0]->nsas3, BPDU[0]->nsas4, BPDU[0]->nsas5, BPDU[0]->nsas6);
        printf("BPDU: GPS[%d] RW1[%d] RW2[%d] RW3[%d] RW4[%d] STT[%d]\n",
                BPDU[0]->gps, BPDU[0]->rw1, BPDU[0]->rw2, BPDU[0]->rw3, BPDU[0]->rw4, BPDU[0]->stt1);
        
        printf("0: OFF\n");
        printf("1: ON\n");
        printf("> ");
        scanf("%d", &s);
        
        if(s == 0 || s == 1){
            printf(" 1: DCDC_SNS\n");
            printf(" 2: DCDC_MTQ\n");
            printf(" 3: DCDC_RW\n");
            printf(" 4: FOG\n");
            printf(" 5: GAS\n");
            printf(" 6: NSAS1\n");
            printf(" 7: NSAS2\n");
            printf(" 8: NSAS3\n");
            printf(" 9: NSAS4\n");
            printf("10: NSAS5\n");
            printf("11: NSAS6\n");
            printf("12: GPS\n");
            printf("13: RW1\n");
            printf("14: RW2\n");
            printf("15: RW3\n");
            printf("16: RW4\n");
            printf("17: STT\n");
			printf("18: ALL\n");
            printf("> ");
            scanf("%d", &c);
            switch (c){
                case  1: BPDU[0]->dcdc_sns = s; break;
                case  2: BPDU[0]->dcdc_mtq = s; break;
                case  3: BPDU[0]->dcdc_rw  = s; break;
                case  4: BPDU[0]->gyro     = s; break;
                case  5: BPDU[0]->gas      = s; break;
                case  6: BPDU[0]->nsas1    = s; break;
                case  7: BPDU[0]->nsas2    = s; break;
                case  8: BPDU[0]->nsas3    = s; break;
                case  9: BPDU[0]->nsas4    = s; break;
                case 10: BPDU[0]->nsas5    = s; break;
                case 11: BPDU[0]->nsas6    = s; break;
                case 12: BPDU[0]->gps      = s; break;
                case 13: BPDU[0]->rw1      = s; break;
                case 14: BPDU[0]->rw2      = s; break;
                case 15: BPDU[0]->rw3      = s; break;
                case 16: BPDU[0]->rw4      = s; break;
                case 17: BPDU[0]->stt1     = s; break;
				case 18:
					BPDU[0]->dcdc_sns = s;
					BPDU[0]->dcdc_mtq = s;
					BPDU[0]->dcdc_rw  = s;
					BPDU[0]->gyro     = s;
					BPDU[0]->gas      = s;
					BPDU[0]->nsas1    = s;
					BPDU[0]->nsas2    = s;
					BPDU[0]->nsas3    = s;
                    BPDU[0]->nsas4    = s;
					BPDU[0]->nsas5    = s;
					BPDU[0]->nsas6    = s;
					BPDU[0]->gps      = s;
					BPDU[0]->rw1      = s;
					BPDU[0]->rw2      = s;
					BPDU[0]->rw3      = s;
					BPDU[0]->rw4      = s;
					BPDU[0]->stt1     = s;
					break;
                default: break;
            }
        }
        
    }
    
    BPDU_close_SM(0);
    
    return 0;
}