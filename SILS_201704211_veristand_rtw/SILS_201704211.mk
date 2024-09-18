###########################################################################
## Makefile generated for component 'SILS_201704211'. 
## 
## Makefile     : SILS_201704211.mk
## Generated on : Sun Sep 15 17:16:09 2024
## Final product: $(RELATIVE_PATH_TO_ANCHOR)/SILS_201704211.dll
## Product type : executable
## 
###########################################################################

###########################################################################
## MACROS
###########################################################################

# Macro Descriptions:
# PRODUCT_NAME            Name of the system to build
# MAKEFILE                Name of this makefile
# COMPILER_COMMAND_FILE   Compiler command listing model reference header paths
# CMD_FILE                Command file

PRODUCT_NAME              = SILS_201704211
MAKEFILE                  = SILS_201704211.mk
MATLAB_ROOT               = C:/PROGRA~1/POLYSP~1/R2020b
MATLAB_BIN                = C:/PROGRA~1/POLYSP~1/R2020b/bin
MATLAB_ARCH_BIN           = $(MATLAB_BIN)/win64
START_DIR                 = C:/Users/hapham/Documents/SILS/SILS
SOLVER                    = 
SOLVER_OBJ                = 
CLASSIC_INTERFACE         = 0
TGT_FCN_LIB               = None
MODEL_HAS_DYNAMICALLY_LOADED_SFCNS = 0
RELATIVE_PATH_TO_ANCHOR   = ..
COMPILER_COMMAND_FILE     = SILS_201704211_comp.rsp
CMD_FILE                  = SILS_201704211.rsp
C_STANDARD_OPTS           = 
CPP_STANDARD_OPTS         = 

###########################################################################
## TOOLCHAIN SPECIFICATIONS
###########################################################################

# Toolchain Name:          GCC Compiler for VeriStand Windows targets | gmake makefile (64-bit Windows)
# Supported Version(s):    5.4
# ToolchainInfo Version:   2020b
# Specification Revision:  1.0
# 
#-------------------------------------------
# Macros assumed to be defined elsewhere
#-------------------------------------------

# MINGW_ROOT
# ldebug
# conflags
# cflags

#-----------
# MACROS
#-----------

MW_EXTERNLIB_DIR     = $(MATLAB_ROOT)/extern/lib/win64/mingw64
MW_LIB_DIR           = $(MATLAB_ROOT)/lib/win64
CFLAGS_ADDITIONAL    = -c -m64 -std=c99 -fwrapv -fPIC -fdollars-in-identifiers
CPPFLAGS_ADDITIONAL  = -c -m64 -fwrapv -fPIC -fdollars-in-identifiers
LIBS_TOOLCHAIN       = $(conlibs)
LINKFLAGS_ADDITIONAL = -m64 -shared -static-libgcc -static-libstdc++

TOOLCHAIN_SRCS = 
TOOLCHAIN_INCS = 
TOOLCHAIN_LIBS = 

#------------------------
# BUILD TOOL COMMANDS
#------------------------

# C Compiler: GNU C Compiler
CC_PATH = $(MINGW_ROOT)
CC = "$(CC_PATH)/gcc"

# Linker: GNU Linker
LD_PATH = $(MINGW_ROOT)
LD = "$(LD_PATH)/g++"

# C++ Compiler: GNU C++ Compiler
CPP_PATH = $(MINGW_ROOT)
CPP = "$(CPP_PATH)/g++"

# C++ Linker: GNU C++ Linker
CPP_LD_PATH = $(MINGW_ROOT)
CPP_LD = "$(CPP_LD_PATH)/g++"

# Archiver: GNU Archiver
AR_PATH = $(MINGW_ROOT)
AR = "$(AR_PATH)/ar"

# MEX Tool: MEX Tool
MEX_PATH = $(MATLAB_ARCH_BIN)
MEX = "$(MEX_PATH)/mex"

# Download: Download
DOWNLOAD =

# Execute: Execute
EXECUTE = $(PRODUCT)

# Builder: GMAKE Utility
MAKE_PATH = %MATLAB%\bin\win64
MAKE = "$(MAKE_PATH)/gmake"


#-------------------------
# Directives/Utilities
#-------------------------

CDEBUG              = -g
C_OUTPUT_FLAG       = -o
LDDEBUG             =
OUTPUT_FLAG         = -o
CPPDEBUG            = -g
CPP_OUTPUT_FLAG     = -o
CPPLDDEBUG          =
OUTPUT_FLAG         = -o
ARDEBUG             =
STATICLIB_OUTPUT_FLAG =
MEX_DEBUG           = -g
RM                  = @del /F
ECHO                = @echo
MV                  = @move
RUN                 =

#--------------------------------------
# "Faster Runs" Build Configuration
#--------------------------------------

ARFLAGS              = rcs
CFLAGS               = $(cflags) $(CVARSFLAG) $(CFLAGS_ADDITIONAL) \
                       -O2 \
                       -DNDEBUG
CPPFLAGS             = $(cflags) $(CVARSFLAG) $(CPPFLAGS_ADDITIONAL) \
                       -O2 \
                       -DNDEBUG
CPP_LDFLAGS          = $(ldebug) $(conflags) $(LINKFLAGS_ADDITIONAL) $(LIBS_TOOLCHAIN)
CPP_SHAREDLIB_LDFLAGS  =
DOWNLOAD_FLAGS       =
EXECUTE_FLAGS        =
LDFLAGS              = $(ldebug) $(conflags) $(LINKFLAGS_ADDITIONAL) $(LIBS_TOOLCHAIN)
MEX_CPPFLAGS         =
MEX_CPPLDFLAGS       =
MEX_CFLAGS           =
MEX_LDFLAGS          =
MAKE_FLAGS           = -f $(MAKEFILE)
SHAREDLIB_LDFLAGS    = $(ldebug) $(conflags) $(LINKFLAGS_ADDITIONAL) $(LIBS_TOOLCHAIN) \
                       -shared -def:$(DEF_FILE)



###########################################################################
## OUTPUT INFO
###########################################################################

PRODUCT = $(RELATIVE_PATH_TO_ANCHOR)/SILS_201704211.dll
PRODUCT_TYPE = "executable"
BUILD_TYPE = "Top-Level Standalone Executable"

###########################################################################
## INCLUDE PATHS
###########################################################################

INCLUDES_BUILDINFO = 

INCLUDES = $(INCLUDES_BUILDINFO)

###########################################################################
## DEFINES
###########################################################################

DEFINES_ = -DVSMODEL_STEP_SIZE0=0.010000 -DVSMODEL_MAJOR_VERSION=24u -DVSMODEL_MINOR_VERSION=3u
DEFINES_BUILD_ARGS = -DCLASSIC_INTERFACE=0 -DALLOCATIONFCN=0 -DMAT_FILE=0 -DONESTEPFCN=0 -DTERMFCN=1 -DMULTI_INSTANCE_CODE=0 -DINTEGER_CODE=0 -DMT=1
DEFINES_CUSTOM = 
DEFINES_OPTS = -DTID01EQ=1
DEFINES_STANDARD = -DMODEL=SILS_201704211 -DNUMST=3 -DNCSTATES=36 -DHAVESTDIO -DRT -DUSE_RTMODEL

DEFINES = $(DEFINES_) $(DEFINES_BUILD_ARGS) $(DEFINES_CUSTOM) $(DEFINES_OPTS) $(DEFINES_STANDARD)

###########################################################################
## SOURCE FILES
###########################################################################

SRCS = $(MATLAB_ROOT)/rtw/c/src/rt_matrx.c $(MATLAB_ROOT)/rtw/c/src/rt_printf.c $(START_DIR)/SILS_201704211_veristand_rtw/SILS_201704211.c $(START_DIR)/SILS_201704211_veristand_rtw/SILS_201704211_capi.c $(START_DIR)/SILS_201704211_veristand_rtw/SILS_201704211_data.c $(START_DIR)/SILS_201704211_veristand_rtw/rtGetInf.c $(START_DIR)/SILS_201704211_veristand_rtw/rtGetNaN.c $(START_DIR)/SILS_201704211_veristand_rtw/rt_nonfinite.c $(START_DIR)/library/sfunc_nrlmsise00/sfunc_nrlmsise00_wrapper.c $(START_DIR)/library/sfunc_nrlmsise00/nrlmsise-00.c $(START_DIR)/library/sfunc_nrlmsise00/nrlmsise-00_data.c $(START_DIR)/component_communication/createHandle.c $(START_DIR)/AOCS_Process/globals.c $(START_DIR)/AOCS_Process/AOCS_Process.c $(START_DIR)/AOCS_Process/sfunc_AOBC.c $(START_DIR)/component_communication/sfunc_FOG.c $(START_DIR)/component_communication/sfunc_GAS.c $(START_DIR)/component_communication/sfunc_GPS.c $(START_DIR)/component_communication/sfunc_MTQ.c $(START_DIR)/component_communication/sfunc_NSAS.c $(START_DIR)/component_communication/sfunc_RW_RX.c $(START_DIR)/component_communication/sfunc_RW_TX.c $(START_DIR)/component_communication/sfunc_STT.c $(START_DIR)/library/sfunc_nrlmsise00/sfunc_nrlmsise00.c C:/Users/hapham/AppData/Roaming/MATHWO~1/MATLAB~1/TOOLBO~1/VERIST~1/RUNTIM~1/VERIST~1.CPP

ALL_SRCS = $(SRCS)

###########################################################################
## OBJECTS
###########################################################################

OBJS = rt_matrx.obj rt_printf.obj SILS_201704211.obj SILS_201704211_capi.obj SILS_201704211_data.obj rtGetInf.obj rtGetNaN.obj rt_nonfinite.obj sfunc_nrlmsise00_wrapper.obj nrlmsise-00.obj nrlmsise-00_data.obj createHandle.obj globals.obj AOCS_Process.obj sfunc_AOBC.obj sfunc_FOG.obj sfunc_GAS.obj sfunc_GPS.obj sfunc_MTQ.obj sfunc_NSAS.obj sfunc_RW_RX.obj sfunc_RW_TX.obj sfunc_STT.obj sfunc_nrlmsise00.obj veristand_model_capi.obj

ALL_OBJS = $(OBJS)

###########################################################################
## PREBUILT OBJECT FILES
###########################################################################

PREBUILT_OBJS = 

###########################################################################
## LIBRARIES
###########################################################################

LIBS = 

###########################################################################
## SYSTEM LIBRARIES
###########################################################################

SYSTEM_LIBS = 

###########################################################################
## ADDITIONAL TOOLCHAIN FLAGS
###########################################################################

#---------------
# C Compiler
#---------------

CFLAGS_BASIC = $(DEFINES) $(INCLUDES) @$(COMPILER_COMMAND_FILE)

CFLAGS += $(CFLAGS_BASIC)

#-----------------
# C++ Compiler
#-----------------

CPPFLAGS_BASIC = $(DEFINES) $(INCLUDES) @$(COMPILER_COMMAND_FILE)

CPPFLAGS += $(CPPFLAGS_BASIC)

#---------------------
# MEX C++ Compiler
#---------------------

MEX_CPP_Compiler_BASIC =  @$(COMPILER_COMMAND_FILE)

MEX_CPPFLAGS += $(MEX_CPP_Compiler_BASIC)

#-----------------
# MEX Compiler
#-----------------

MEX_Compiler_BASIC =  @$(COMPILER_COMMAND_FILE)

MEX_CFLAGS += $(MEX_Compiler_BASIC)

###########################################################################
## INLINED COMMANDS
###########################################################################


TOOLCHAIN_LIBS += -lws2_32


###########################################################################
## PHONY TARGETS
###########################################################################

.PHONY : all build buildobj clean info prebuild download execute


all : build
	@echo "### Successfully generated all binary outputs."


build : prebuild $(PRODUCT)


buildobj : prebuild $(OBJS) $(PREBUILT_OBJS)
	@echo "### Successfully generated all binary outputs."


prebuild : 


download : $(PRODUCT)


execute : download
	@echo "### Invoking postbuild tool "Execute" ..."
	$(EXECUTE) $(EXECUTE_FLAGS)
	@echo "### Done invoking postbuild tool."


###########################################################################
## FINAL TARGET
###########################################################################

#-------------------------------------------
# Create a standalone executable            
#-------------------------------------------

$(PRODUCT) : $(OBJS) $(PREBUILT_OBJS)
	@echo "### Creating standalone executable "$(PRODUCT)" ..."
	$(CPP_LD) $(CPP_LDFLAGS) -o$(PRODUCT) @$(CMD_FILE) $(SYSTEM_LIBS) $(TOOLCHAIN_LIBS)
	@echo "### Created: $(PRODUCT)"


###########################################################################
## INTERMEDIATE TARGETS
###########################################################################

#---------------------
# SOURCE-TO-OBJECT
#---------------------

%.obj : %.c
	$(CC) $(CFLAGS) -o"$@" "$<"


%.obj : %.cpp
	$(CPP) $(CPPFLAGS) -o"$@" "$<"


%.obj : $(RELATIVE_PATH_TO_ANCHOR)/%.c
	$(CC) $(CFLAGS) -o"$@" "$<"


%.obj : $(RELATIVE_PATH_TO_ANCHOR)/%.cpp
	$(CPP) $(CPPFLAGS) -o"$@" "$<"


%.obj : $(START_DIR)/%.c
	$(CC) $(CFLAGS) -o"$@" "$<"


%.obj : $(START_DIR)/%.cpp
	$(CPP) $(CPPFLAGS) -o"$@" "$<"


%.obj : $(START_DIR)/SILS_201704211_veristand_rtw/%.c
	$(CC) $(CFLAGS) -o"$@" "$<"


%.obj : $(START_DIR)/SILS_201704211_veristand_rtw/%.cpp
	$(CPP) $(CPPFLAGS) -o"$@" "$<"


%.obj : $(START_DIR)/library/sfunc_nrlmsise00/%.c
	$(CC) $(CFLAGS) -o"$@" "$<"


%.obj : $(START_DIR)/library/sfunc_nrlmsise00/%.cpp
	$(CPP) $(CPPFLAGS) -o"$@" "$<"


%.obj : $(START_DIR)/component_communication/%.c
	$(CC) $(CFLAGS) -o"$@" "$<"


%.obj : $(START_DIR)/component_communication/%.cpp
	$(CPP) $(CPPFLAGS) -o"$@" "$<"


%.obj : $(START_DIR)/AOCS_Process/%.c
	$(CC) $(CFLAGS) -o"$@" "$<"


%.obj : $(START_DIR)/AOCS_Process/%.cpp
	$(CPP) $(CPPFLAGS) -o"$@" "$<"


%.obj : $(MATLAB_ROOT)/rtw/c/src/%.c
	$(CC) $(CFLAGS) -o"$@" "$<"


%.obj : $(MATLAB_ROOT)/rtw/c/src/%.cpp
	$(CPP) $(CPPFLAGS) -o"$@" "$<"


%.obj : $(MATLAB_ROOT)/simulink/src/%.c
	$(CC) $(CFLAGS) -o"$@" "$<"


%.obj : $(MATLAB_ROOT)/simulink/src/%.cpp
	$(CPP) $(CPPFLAGS) -o"$@" "$<"


rt_matrx.obj : $(MATLAB_ROOT)/rtw/c/src/rt_matrx.c
	$(CC) $(CFLAGS) -o"$@" "$<"


rt_printf.obj : $(MATLAB_ROOT)/rtw/c/src/rt_printf.c
	$(CC) $(CFLAGS) -o"$@" "$<"


SILS_201704211.obj : $(START_DIR)/SILS_201704211_veristand_rtw/SILS_201704211.c
	$(CC) $(CFLAGS) -o"$@" "$<"


SILS_201704211_capi.obj : $(START_DIR)/SILS_201704211_veristand_rtw/SILS_201704211_capi.c
	$(CC) $(CFLAGS) -o"$@" "$<"


SILS_201704211_data.obj : $(START_DIR)/SILS_201704211_veristand_rtw/SILS_201704211_data.c
	$(CC) $(CFLAGS) -o"$@" "$<"


rtGetInf.obj : $(START_DIR)/SILS_201704211_veristand_rtw/rtGetInf.c
	$(CC) $(CFLAGS) -o"$@" "$<"


rtGetNaN.obj : $(START_DIR)/SILS_201704211_veristand_rtw/rtGetNaN.c
	$(CC) $(CFLAGS) -o"$@" "$<"


rt_nonfinite.obj : $(START_DIR)/SILS_201704211_veristand_rtw/rt_nonfinite.c
	$(CC) $(CFLAGS) -o"$@" "$<"


sfunc_nrlmsise00_wrapper.obj : $(START_DIR)/library/sfunc_nrlmsise00/sfunc_nrlmsise00_wrapper.c
	$(CC) $(CFLAGS) -o"$@" "$<"


nrlmsise-00.obj : $(START_DIR)/library/sfunc_nrlmsise00/nrlmsise-00.c
	$(CC) $(CFLAGS) -o"$@" "$<"


nrlmsise-00_data.obj : $(START_DIR)/library/sfunc_nrlmsise00/nrlmsise-00_data.c
	$(CC) $(CFLAGS) -o"$@" "$<"


createHandle.obj : $(START_DIR)/component_communication/createHandle.c
	$(CC) $(CFLAGS) -o"$@" "$<"


globals.obj : $(START_DIR)/AOCS_Process/globals.c
	$(CC) $(CFLAGS) -o"$@" "$<"


AOCS_Process.obj : $(START_DIR)/AOCS_Process/AOCS_Process.c
	$(CC) $(CFLAGS) -o"$@" "$<"


sfunc_AOBC.obj : $(START_DIR)/AOCS_Process/sfunc_AOBC.c
	$(CC) $(CFLAGS) -o"$@" "$<"


sfunc_FOG.obj : $(START_DIR)/component_communication/sfunc_FOG.c
	$(CC) $(CFLAGS) -o"$@" "$<"


sfunc_GAS.obj : $(START_DIR)/component_communication/sfunc_GAS.c
	$(CC) $(CFLAGS) -o"$@" "$<"


sfunc_GPS.obj : $(START_DIR)/component_communication/sfunc_GPS.c
	$(CC) $(CFLAGS) -o"$@" "$<"


sfunc_MTQ.obj : $(START_DIR)/component_communication/sfunc_MTQ.c
	$(CC) $(CFLAGS) -o"$@" "$<"


sfunc_NSAS.obj : $(START_DIR)/component_communication/sfunc_NSAS.c
	$(CC) $(CFLAGS) -o"$@" "$<"


sfunc_RW_RX.obj : $(START_DIR)/component_communication/sfunc_RW_RX.c
	$(CC) $(CFLAGS) -o"$@" "$<"


sfunc_RW_TX.obj : $(START_DIR)/component_communication/sfunc_RW_TX.c
	$(CC) $(CFLAGS) -o"$@" "$<"


sfunc_STT.obj : $(START_DIR)/component_communication/sfunc_STT.c
	$(CC) $(CFLAGS) -o"$@" "$<"


sfunc_nrlmsise00.obj : $(START_DIR)/library/sfunc_nrlmsise00/sfunc_nrlmsise00.c
	$(CC) $(CFLAGS) -o"$@" "$<"


veristand_model_capi.obj : C:/Users/hapham/AppData/Roaming/MATHWO~1/MATLAB~1/TOOLBO~1/VERIST~1/RUNTIM~1/veristand_model_capi.cpp
	$(CPP) $(CPPFLAGS) -o"$@" "$<"


###########################################################################
## DEPENDENCIES
###########################################################################

$(ALL_OBJS) : rtw_proj.tmw $(COMPILER_COMMAND_FILE) $(MAKEFILE)


###########################################################################
## MISCELLANEOUS TARGETS
###########################################################################

info : 
	@echo "### PRODUCT = $(PRODUCT)"
	@echo "### PRODUCT_TYPE = $(PRODUCT_TYPE)"
	@echo "### BUILD_TYPE = $(BUILD_TYPE)"
	@echo "### INCLUDES = $(INCLUDES)"
	@echo "### DEFINES = $(DEFINES)"
	@echo "### ALL_SRCS = $(ALL_SRCS)"
	@echo "### ALL_OBJS = $(ALL_OBJS)"
	@echo "### LIBS = $(LIBS)"
	@echo "### MODELREF_LIBS = $(MODELREF_LIBS)"
	@echo "### SYSTEM_LIBS = $(SYSTEM_LIBS)"
	@echo "### TOOLCHAIN_LIBS = $(TOOLCHAIN_LIBS)"
	@echo "### CFLAGS = $(CFLAGS)"
	@echo "### LDFLAGS = $(LDFLAGS)"
	@echo "### SHAREDLIB_LDFLAGS = $(SHAREDLIB_LDFLAGS)"
	@echo "### CPPFLAGS = $(CPPFLAGS)"
	@echo "### CPP_LDFLAGS = $(CPP_LDFLAGS)"
	@echo "### CPP_SHAREDLIB_LDFLAGS = $(CPP_SHAREDLIB_LDFLAGS)"
	@echo "### ARFLAGS = $(ARFLAGS)"
	@echo "### MEX_CFLAGS = $(MEX_CFLAGS)"
	@echo "### MEX_CPPFLAGS = $(MEX_CPPFLAGS)"
	@echo "### MEX_LDFLAGS = $(MEX_LDFLAGS)"
	@echo "### MEX_CPPLDFLAGS = $(MEX_CPPLDFLAGS)"
	@echo "### DOWNLOAD_FLAGS = $(DOWNLOAD_FLAGS)"
	@echo "### EXECUTE_FLAGS = $(EXECUTE_FLAGS)"
	@echo "### MAKE_FLAGS = $(MAKE_FLAGS)"


clean : 
	$(ECHO) "### Deleting all derived files..."
	$(RM) $(subst /,\,$(PRODUCT))
	$(RM) $(subst /,\,$(ALL_OBJS))
	$(ECHO) "### Deleted all derived files."


