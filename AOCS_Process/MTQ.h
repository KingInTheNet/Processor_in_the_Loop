typedef union{
    unsigned char byte;
    struct{
        unsigned : 2;
        unsigned x : 2;
        unsigned y : 2;
        unsigned z : 2;
    } bit;
} MTQ_STRUCT;