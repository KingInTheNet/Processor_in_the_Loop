/*
 * File: Subsystem_ca.c
 *
 * Abstract: Tests assumptions in the generated code.
 */

#include "Subsystem_ca.h"

CA_HWImpl_TestResults CA_Subsystem_HWRes;
CA_PWS_TestResults CA_Subsystem_PWSRes;
const CA_HWImpl CA_Subsystem_ExpHW = {
  8,                                   /* BitPerChar */
  16,                                  /* BitPerShort */
  32,                                  /* BitPerInt */
  32,                                  /* BitPerLong */
  64,                                  /* BitPerLongLong */
  32,                                  /* BitPerFloat */
  64,                                  /* BitPerDouble */
  64,                                  /* BitPerPointer */
  64,                                  /* BitPerSizeT */
  64,                                  /* BitPerPtrDiffT */
  CA_LITTLE_ENDIAN,                    /* Endianess */
  CA_ZERO,                             /* IntDivRoundTo */
  1,                                   /* ShiftRightIntArith */
  1,                                   /* LongLongMode */
  0,                                   /* PortableWordSizes */
  "MATLAB Host",                       /* HWDeviceType */
  0,                                   /* MemoryAtStartup */
  0,                                   /* DynamicMemoryAtStartup */
  0,                                   /* DenormalFlushToZero */
  0                                    /* DenormalAsZero */
};

CA_HWImpl CA_Subsystem_ActHW;
void Subsystem_caRunTests(void)
{
  /* verify hardware implementation */
  caVerifyPortableWordSizes(&CA_Subsystem_ActHW, &CA_Subsystem_ExpHW,
    &CA_Subsystem_PWSRes);
  caVerifyHWImpl(&CA_Subsystem_ActHW, &CA_Subsystem_ExpHW, &CA_Subsystem_HWRes);
}
