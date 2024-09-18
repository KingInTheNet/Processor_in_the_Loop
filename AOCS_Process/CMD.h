typedef struct{
    unsigned char AOCS_mode;
    unsigned char STT_power_state; // 0: idel, 1: capture
    unsigned char STT_output_mode; // 0: manual, 1: auto
    unsigned char STT_start_output; // 0: stop, 1: start
    unsigned char unloading_flag; // 0: no unloading, 1: unloading
} CMD_STRUCT;