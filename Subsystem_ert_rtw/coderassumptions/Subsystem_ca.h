/*
 * File: Subsystem_ca.h
 *
 * Abstract: Tests assumptions in the generated code.
 */

#ifndef SUBSYSTEM_CA_H
#define SUBSYSTEM_CA_H

/* preprocessor validation checks */
#include "Subsystem_ca_preproc.h"
#include "coder_assumptions_hwimpl.h"

/* variables holding test results */
extern CA_HWImpl_TestResults CA_Subsystem_HWRes;
extern CA_PWS_TestResults CA_Subsystem_PWSRes;

/* variables holding "expected" and "actual" hardware implementation */
extern const CA_HWImpl CA_Subsystem_ExpHW;
extern CA_HWImpl CA_Subsystem_ActHW;

/* entry point function to run tests */
void Subsystem_caRunTests(void);

#endif                                 /* SUBSYSTEM_CA_H */
