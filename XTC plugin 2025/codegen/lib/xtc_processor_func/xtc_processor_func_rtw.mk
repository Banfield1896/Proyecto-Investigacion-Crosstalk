###########################################################################
## Makefile generated for component 'xtc_processor_func'. 
## 
## Makefile     : xtc_processor_func_rtw.mk
## Generated on : Tue Sep 09 21:11:23 2025
## Final product: .\xtc_processor_func.lib
## Product type : static-library
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
# MODELLIB                Static library target

PRODUCT_NAME              = xtc_processor_func
MAKEFILE                  = xtc_processor_func_rtw.mk
MATLAB_ROOT               = D:\Archivos de programa\MATLAB\R2021b
MATLAB_BIN                = D:\Archivos de programa\MATLAB\R2021b\bin
MATLAB_ARCH_BIN           = $(MATLAB_BIN)\win64
START_DIR                 = C:\Users\MARTIN~1\OneDrive\41-PRO~1\PROYEC~1\PROYEC~1\XTCPLU~1
TGT_FCN_LIB               = ISO_C++11
SOLVER_OBJ                = 
CLASSIC_INTERFACE         = 0
MODEL_HAS_DYNAMICALLY_LOADED_SFCNS = 
RELATIVE_PATH_TO_ANCHOR   = ..\..\..
COMPILER_COMMAND_FILE     = xtc_processor_func_rtw_comp.rsp
CMD_FILE                  = xtc_processor_func_rtw.rsp
C_STANDARD_OPTS           = 
CPP_STANDARD_OPTS         = 
NODEBUG                   = 1
MODELLIB                  = xtc_processor_func.lib

###########################################################################
## TOOLCHAIN SPECIFICATIONS
###########################################################################

# Toolchain Name:          Microsoft Visual C++ 2019 v16.0 | nmake (64-bit Windows)
# Supported Version(s):    16.0
# ToolchainInfo Version:   2021b
# Specification Revision:  1.0
# 
#-------------------------------------------
# Macros assumed to be defined elsewhere
#-------------------------------------------

# NODEBUG
# cvarsdll
# cvarsmt
# conlibsmt
# ldebug
# conflags
# cflags

#-----------
# MACROS
#-----------

MW_EXTERNLIB_DIR    = $(MATLAB_ROOT)\extern\lib\win64\microsoft
MW_LIB_DIR          = $(MATLAB_ROOT)\lib\win64
CPU                 = AMD64
APPVER              = 5.02
CVARSFLAG           = $(cvarsmt)
CFLAGS_ADDITIONAL   = -D_CRT_SECURE_NO_WARNINGS
CPPFLAGS_ADDITIONAL = -EHs -D_CRT_SECURE_NO_WARNINGS /wd4251
LIBS_TOOLCHAIN      = $(conlibs)

TOOLCHAIN_SRCS = 
TOOLCHAIN_INCS = 
TOOLCHAIN_LIBS = 

#------------------------
# BUILD TOOL COMMANDS
#------------------------

# C Compiler: Microsoft Visual C Compiler
CC = cl

# Linker: Microsoft Visual C Linker
LD = link

# C++ Compiler: Microsoft Visual C++ Compiler
CPP = cl

# C++ Linker: Microsoft Visual C++ Linker
CPP_LD = link

# Archiver: Microsoft Visual C/C++ Archiver
AR = lib

# MEX Tool: MEX Tool
MEX_PATH = $(MATLAB_ARCH_BIN)
MEX = "$(MEX_PATH)\mex"

# Download: Download
DOWNLOAD =

# Execute: Execute
EXECUTE = $(PRODUCT)

# Builder: NMAKE Utility
MAKE = nmake


#-------------------------
# Directives/Utilities
#-------------------------

CDEBUG              = -Zi
C_OUTPUT_FLAG       = -Fo
LDDEBUG             = /DEBUG
OUTPUT_FLAG         = -out:
CPPDEBUG            = -Zi
CPP_OUTPUT_FLAG     = -Fo
CPPLDDEBUG          = /DEBUG
OUTPUT_FLAG         = -out:
ARDEBUG             =
STATICLIB_OUTPUT_FLAG = -out:
MEX_DEBUG           = -g
RM                  = @del
ECHO                = @echo
MV                  = @ren
RUN                 = @cmd /C

#--------------------------------------
# "Faster Runs" Build Configuration
#--------------------------------------

ARFLAGS              = /nologo
CFLAGS               = $(cflags) $(CVARSFLAG) $(CFLAGS_ADDITIONAL) \
                       /O2 /Oy-
CPPFLAGS             = /TP $(cflags) $(CVARSFLAG) $(CPPFLAGS_ADDITIONAL) \
                       /O2 /Oy-
CPP_LDFLAGS          = $(ldebug) $(conflags) $(LIBS_TOOLCHAIN)
CPP_SHAREDLIB_LDFLAGS  = $(ldebug) $(conflags) $(LIBS_TOOLCHAIN) \
                         -dll -def:$(DEF_FILE)
DOWNLOAD_FLAGS       =
EXECUTE_FLAGS        =
LDFLAGS              = $(ldebug) $(conflags) $(LIBS_TOOLCHAIN)
MEX_CPPFLAGS         =
MEX_CPPLDFLAGS       =
MEX_CFLAGS           =
MEX_LDFLAGS          =
MAKE_FLAGS           = -f $(MAKEFILE)
SHAREDLIB_LDFLAGS    = $(ldebug) $(conflags) $(LIBS_TOOLCHAIN) \
                       -dll -def:$(DEF_FILE)



###########################################################################
## OUTPUT INFO
###########################################################################

PRODUCT = .\xtc_processor_func.lib
PRODUCT_TYPE = "static-library"
BUILD_TYPE = "Static Library"

###########################################################################
## INCLUDE PATHS
###########################################################################

INCLUDES_BUILDINFO = 

INCLUDES = $(INCLUDES_BUILDINFO)

###########################################################################
## DEFINES
###########################################################################

DEFINES_CUSTOM = 
DEFINES_STANDARD = -DMODEL=xtc_processor_func

DEFINES = $(DEFINES_CUSTOM) $(DEFINES_STANDARD)

###########################################################################
## SOURCE FILES
###########################################################################

SRCS = $(START_DIR)\codegen\lib\xtc_processor_func\xtc_processor_func_data.cpp $(START_DIR)\codegen\lib\xtc_processor_func\xtc_processor_func_initialize.cpp $(START_DIR)\codegen\lib\xtc_processor_func\xtc_processor_func_terminate.cpp $(START_DIR)\codegen\lib\xtc_processor_func\xtc_processor_func.cpp $(START_DIR)\codegen\lib\xtc_processor_func\transaural_ir3.cpp $(START_DIR)\codegen\lib\xtc_processor_func\ifft.cpp $(START_DIR)\codegen\lib\xtc_processor_func\circshift.cpp $(START_DIR)\codegen\lib\xtc_processor_func\cat.cpp $(START_DIR)\codegen\lib\xtc_processor_func\AsyncBuffercgHelper.cpp $(START_DIR)\codegen\lib\xtc_processor_func\AsyncBuffer.cpp $(START_DIR)\codegen\lib\xtc_processor_func\NoPartitionOS.cpp $(START_DIR)\codegen\lib\xtc_processor_func\FrequencyDomainFIRFilter.cpp $(START_DIR)\codegen\lib\xtc_processor_func\FFTImplementationCallback.cpp

ALL_SRCS = $(SRCS)

###########################################################################
## OBJECTS
###########################################################################

OBJS = xtc_processor_func_data.obj xtc_processor_func_initialize.obj xtc_processor_func_terminate.obj xtc_processor_func.obj transaural_ir3.obj ifft.obj circshift.obj cat.obj AsyncBuffercgHelper.obj AsyncBuffer.obj NoPartitionOS.obj FrequencyDomainFIRFilter.obj FFTImplementationCallback.obj

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

CFLAGS_ = /source-charset:utf-8
CFLAGS_BASIC = $(DEFINES) @$(COMPILER_COMMAND_FILE)

CFLAGS = $(CFLAGS) $(CFLAGS_) $(CFLAGS_BASIC)

#-----------------
# C++ Compiler
#-----------------

CPPFLAGS_ = /source-charset:utf-8
CPPFLAGS_BASIC = $(DEFINES) @$(COMPILER_COMMAND_FILE)

CPPFLAGS = $(CPPFLAGS) $(CPPFLAGS_) $(CPPFLAGS_BASIC)

###########################################################################
## INLINED COMMANDS
###########################################################################


!include $(MATLAB_ROOT)\rtw\c\tools\vcdefs.mak


###########################################################################
## PHONY TARGETS
###########################################################################

.PHONY : all build clean info prebuild download execute set_environment_variables


all : build
	@cmd /C "@echo ### Successfully generated all binary outputs."


build : set_environment_variables prebuild $(PRODUCT)


prebuild : 


download : $(PRODUCT)


execute : download


set_environment_variables : 
	@set INCLUDE=$(INCLUDES);$(INCLUDE)
	@set LIB=$(LIB)


###########################################################################
## FINAL TARGET
###########################################################################

#---------------------------------
# Create a static library         
#---------------------------------

$(PRODUCT) : $(OBJS) $(PREBUILT_OBJS)
	@cmd /C "@echo ### Creating static library "$(PRODUCT)" ..."
	$(AR) $(ARFLAGS) -out:$(PRODUCT) @$(CMD_FILE)
	@cmd /C "@echo ### Created: $(PRODUCT)"


###########################################################################
## INTERMEDIATE TARGETS
###########################################################################

#---------------------
# SOURCE-TO-OBJECT
#---------------------

.c.obj :
	$(CC) $(CFLAGS) -Fo"$@" "$<"


.cpp.obj :
	$(CPP) $(CPPFLAGS) -Fo"$@" "$<"


{$(RELATIVE_PATH_TO_ANCHOR)}.c.obj :
	$(CC) $(CFLAGS) -Fo"$@" "$<"


{$(RELATIVE_PATH_TO_ANCHOR)}.cpp.obj :
	$(CPP) $(CPPFLAGS) -Fo"$@" "$<"


{$(START_DIR)\codegen\lib\xtc_processor_func}.c.obj :
	$(CC) $(CFLAGS) -Fo"$@" "$<"


{$(START_DIR)\codegen\lib\xtc_processor_func}.cpp.obj :
	$(CPP) $(CPPFLAGS) -Fo"$@" "$<"


{$(START_DIR)}.c.obj :
	$(CC) $(CFLAGS) -Fo"$@" "$<"


{$(START_DIR)}.cpp.obj :
	$(CPP) $(CPPFLAGS) -Fo"$@" "$<"


xtc_processor_func_data.obj : $(START_DIR)\codegen\lib\xtc_processor_func\xtc_processor_func_data.cpp
	$(CPP) $(CPPFLAGS) -Fo"$@" $(START_DIR)\codegen\lib\xtc_processor_func\xtc_processor_func_data.cpp


xtc_processor_func_initialize.obj : $(START_DIR)\codegen\lib\xtc_processor_func\xtc_processor_func_initialize.cpp
	$(CPP) $(CPPFLAGS) -Fo"$@" $(START_DIR)\codegen\lib\xtc_processor_func\xtc_processor_func_initialize.cpp


xtc_processor_func_terminate.obj : $(START_DIR)\codegen\lib\xtc_processor_func\xtc_processor_func_terminate.cpp
	$(CPP) $(CPPFLAGS) -Fo"$@" $(START_DIR)\codegen\lib\xtc_processor_func\xtc_processor_func_terminate.cpp


xtc_processor_func.obj : $(START_DIR)\codegen\lib\xtc_processor_func\xtc_processor_func.cpp
	$(CPP) $(CPPFLAGS) -Fo"$@" $(START_DIR)\codegen\lib\xtc_processor_func\xtc_processor_func.cpp


transaural_ir3.obj : $(START_DIR)\codegen\lib\xtc_processor_func\transaural_ir3.cpp
	$(CPP) $(CPPFLAGS) -Fo"$@" $(START_DIR)\codegen\lib\xtc_processor_func\transaural_ir3.cpp


ifft.obj : $(START_DIR)\codegen\lib\xtc_processor_func\ifft.cpp
	$(CPP) $(CPPFLAGS) -Fo"$@" $(START_DIR)\codegen\lib\xtc_processor_func\ifft.cpp


circshift.obj : $(START_DIR)\codegen\lib\xtc_processor_func\circshift.cpp
	$(CPP) $(CPPFLAGS) -Fo"$@" $(START_DIR)\codegen\lib\xtc_processor_func\circshift.cpp


cat.obj : $(START_DIR)\codegen\lib\xtc_processor_func\cat.cpp
	$(CPP) $(CPPFLAGS) -Fo"$@" $(START_DIR)\codegen\lib\xtc_processor_func\cat.cpp


AsyncBuffercgHelper.obj : $(START_DIR)\codegen\lib\xtc_processor_func\AsyncBuffercgHelper.cpp
	$(CPP) $(CPPFLAGS) -Fo"$@" $(START_DIR)\codegen\lib\xtc_processor_func\AsyncBuffercgHelper.cpp


AsyncBuffer.obj : $(START_DIR)\codegen\lib\xtc_processor_func\AsyncBuffer.cpp
	$(CPP) $(CPPFLAGS) -Fo"$@" $(START_DIR)\codegen\lib\xtc_processor_func\AsyncBuffer.cpp


NoPartitionOS.obj : $(START_DIR)\codegen\lib\xtc_processor_func\NoPartitionOS.cpp
	$(CPP) $(CPPFLAGS) -Fo"$@" $(START_DIR)\codegen\lib\xtc_processor_func\NoPartitionOS.cpp


FrequencyDomainFIRFilter.obj : $(START_DIR)\codegen\lib\xtc_processor_func\FrequencyDomainFIRFilter.cpp
	$(CPP) $(CPPFLAGS) -Fo"$@" $(START_DIR)\codegen\lib\xtc_processor_func\FrequencyDomainFIRFilter.cpp


FFTImplementationCallback.obj : $(START_DIR)\codegen\lib\xtc_processor_func\FFTImplementationCallback.cpp
	$(CPP) $(CPPFLAGS) -Fo"$@" $(START_DIR)\codegen\lib\xtc_processor_func\FFTImplementationCallback.cpp


###########################################################################
## DEPENDENCIES
###########################################################################

$(ALL_OBJS) : rtw_proj.tmw $(COMPILER_COMMAND_FILE) $(MAKEFILE)


###########################################################################
## MISCELLANEOUS TARGETS
###########################################################################

info : 
	@cmd /C "@echo ### PRODUCT = $(PRODUCT)"
	@cmd /C "@echo ### PRODUCT_TYPE = $(PRODUCT_TYPE)"
	@cmd /C "@echo ### BUILD_TYPE = $(BUILD_TYPE)"
	@cmd /C "@echo ### INCLUDES = $(INCLUDES)"
	@cmd /C "@echo ### DEFINES = $(DEFINES)"
	@cmd /C "@echo ### ALL_SRCS = $(ALL_SRCS)"
	@cmd /C "@echo ### ALL_OBJS = $(ALL_OBJS)"
	@cmd /C "@echo ### LIBS = $(LIBS)"
	@cmd /C "@echo ### MODELREF_LIBS = $(MODELREF_LIBS)"
	@cmd /C "@echo ### SYSTEM_LIBS = $(SYSTEM_LIBS)"
	@cmd /C "@echo ### TOOLCHAIN_LIBS = $(TOOLCHAIN_LIBS)"
	@cmd /C "@echo ### CFLAGS = $(CFLAGS)"
	@cmd /C "@echo ### LDFLAGS = $(LDFLAGS)"
	@cmd /C "@echo ### SHAREDLIB_LDFLAGS = $(SHAREDLIB_LDFLAGS)"
	@cmd /C "@echo ### CPPFLAGS = $(CPPFLAGS)"
	@cmd /C "@echo ### CPP_LDFLAGS = $(CPP_LDFLAGS)"
	@cmd /C "@echo ### CPP_SHAREDLIB_LDFLAGS = $(CPP_SHAREDLIB_LDFLAGS)"
	@cmd /C "@echo ### ARFLAGS = $(ARFLAGS)"
	@cmd /C "@echo ### MEX_CFLAGS = $(MEX_CFLAGS)"
	@cmd /C "@echo ### MEX_CPPFLAGS = $(MEX_CPPFLAGS)"
	@cmd /C "@echo ### MEX_LDFLAGS = $(MEX_LDFLAGS)"
	@cmd /C "@echo ### MEX_CPPLDFLAGS = $(MEX_CPPLDFLAGS)"
	@cmd /C "@echo ### DOWNLOAD_FLAGS = $(DOWNLOAD_FLAGS)"
	@cmd /C "@echo ### EXECUTE_FLAGS = $(EXECUTE_FLAGS)"
	@cmd /C "@echo ### MAKE_FLAGS = $(MAKE_FLAGS)"


clean : 
	$(ECHO) "### Deleting all derived files..."
	@if exist $(PRODUCT) $(RM) $(PRODUCT)
	$(RM) $(ALL_OBJS)
	$(ECHO) "### Deleted all derived files."


