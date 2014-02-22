# Wind River Workbench generated Makefile.
# Do not edit!!!
#
# The file ".wrmakefile" is the template used by the Wind River Workbench to
# generate the makefiles of this project. Add user-specific build targets and
# make rules only(!) in this project's ".wrmakefile" file. These will then be
# automatically dumped into the makefiles.

WIND_HOME := $(subst \,/,$(WIND_HOME))
WIND_BASE := $(subst \,/,$(WIND_BASE))
WIND_USR := $(subst \,/,$(WIND_USR))
WRVX_COMPBASE := $(subst \,/,$(WRVX_COMPBASE))

all : pre_build main_all post_build

_clean ::
	@echo "make: removing targets and objects of `pwd`"

TRACE=0
TRACEON=$(TRACE:0=@)
TRACE_FLAG=$(TRACEON:1=)

MAKEFILE := Makefile

FLEXIBLE_BUILD := 1

BUILD_SPEC = PPC603diab
DEBUG_MODE = 1
ifeq ($(DEBUG_MODE),1)
MODE_DIR := Debug
else
MODE_DIR := NonDebug
endif
OBJ_DIR := .
WS_ROOT_DIR := Z:/workspace
PRJ_ROOT_DIR := $(WS_ROOT_DIR)/2014Code



#Global Build Macros
PROJECT_TYPE = DKM
DEFINES = 
EXPAND_DBG = 0


#BuildSpec specific Build Macros
VX_CPU_FAMILY = ppc
CPU = PPC603
TOOL_FAMILY = diab
TOOL = diab
TOOL_PATH = 
CC_ARCH_SPEC = -tPPC603FH:vxworks63
LIBPATH = 
LIBS = 
ADDED_C++FLAGS = 

IDE_INCLUDES = -I$(WIND_BASE)/target/h -I$(WIND_BASE)/target/h/wrn/coreip 

IDE_LIBRARIES = 

IDE_DEFINES = 



#BuildTool flags
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C-Compiler = -g
DEBUGFLAGS_C++-Compiler = -g
DEBUGFLAGS_Linker = -g
DEBUGFLAGS_Partial-Image-Linker = 
DEBUGFLAGS_Librarian = 
DEBUGFLAGS_Assembler = -g
else
DEBUGFLAGS_C-Compiler = -XO -Xsize-opt
DEBUGFLAGS_C++-Compiler = -XO -Xsize-opt
DEBUGFLAGS_Linker = -XO -Xsize-opt
DEBUGFLAGS_Partial-Image-Linker = 
DEBUGFLAGS_Librarian = 
DEBUGFLAGS_Assembler = -XO -Xsize-opt
endif


#Project Targets
PROJECT_TARGETS = 2014Code/$(MODE_DIR)/2014Code.out \
	 2014Code_partialImage/$(MODE_DIR)/2014Code_partialImage.o


#Rules

# 2014Code
ifeq ($(DEBUG_MODE),1)
2014Code/$(MODE_DIR)/% : DEBUGFLAGS_C-Compiler = -g
2014Code/$(MODE_DIR)/% : DEBUGFLAGS_C++-Compiler = -g
2014Code/$(MODE_DIR)/% : DEBUGFLAGS_Linker = -g
2014Code/$(MODE_DIR)/% : DEBUGFLAGS_Partial-Image-Linker = 
2014Code/$(MODE_DIR)/% : DEBUGFLAGS_Librarian = 
2014Code/$(MODE_DIR)/% : DEBUGFLAGS_Assembler = -g
else
2014Code/$(MODE_DIR)/% : DEBUGFLAGS_C-Compiler = -XO -Xsize-opt
2014Code/$(MODE_DIR)/% : DEBUGFLAGS_C++-Compiler = -XO -Xsize-opt
2014Code/$(MODE_DIR)/% : DEBUGFLAGS_Linker = -XO -Xsize-opt
2014Code/$(MODE_DIR)/% : DEBUGFLAGS_Partial-Image-Linker = 
2014Code/$(MODE_DIR)/% : DEBUGFLAGS_Librarian = 
2014Code/$(MODE_DIR)/% : DEBUGFLAGS_Assembler = -XO -Xsize-opt
endif
2014Code/$(MODE_DIR)/% : IDE_INCLUDES = -I$(WIND_BASE)/target/h -I$(WIND_BASE)/target/h/wrn/coreip 
2014Code/$(MODE_DIR)/% : IDE_LIBRARIES = 
2014Code/$(MODE_DIR)/% : IDE_DEFINES = 
2014Code/$(MODE_DIR)/% : PROJECT_TYPE = DKM
2014Code/$(MODE_DIR)/% : DEFINES = 
2014Code/$(MODE_DIR)/% : EXPAND_DBG = 0
2014Code/$(MODE_DIR)/% : VX_CPU_FAMILY = ppc
2014Code/$(MODE_DIR)/% : CPU = PPC603
2014Code/$(MODE_DIR)/% : TOOL_FAMILY = diab
2014Code/$(MODE_DIR)/% : TOOL = diab
2014Code/$(MODE_DIR)/% : TOOL_PATH = 
2014Code/$(MODE_DIR)/% : CC_ARCH_SPEC = -tPPC603FH:vxworks63
2014Code/$(MODE_DIR)/% : LIBPATH = 
2014Code/$(MODE_DIR)/% : LIBS = 
2014Code/$(MODE_DIR)/% : ADDED_C++FLAGS = 
2014Code/$(MODE_DIR)/% : OBJ_DIR := 2014Code/$(MODE_DIR)

OBJECTS_2014Code = 2014Code_partialImage/$(MODE_DIR)/2014Code_partialImage.o

2014Code/$(MODE_DIR)/2014Code.out : $(OBJECTS_2014Code)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@";rm -f "$@";ddump -Ng $(OBJECTS_2014Code) $(IDE_LIBRARIES) | tclsh $(WIND_BASE)/host/resource/hutils/tcl/munch.tcl -c ppc > $(OBJ_DIR)/ctdt.c; $(TOOL_PATH)dcc $(DEBUGFLAGS_Linker) $(CC_ARCH_SPEC) -Xdollar-in-ident -Xforce-declarations $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(IDE_DEFINES) $(DEFINES)  -o $(OBJ_DIR)/ctdt.o -c $(OBJ_DIR)/ctdt.c; $(TOOL_PATH)dld -tPPC603FH:vxworks63 -X -r5 -r4 -o "$@" $(OBJ_DIR)/ctdt.o $(OBJECTS_2014Code) $(IDE_LIBRARIES) $(LIBPATH) $(LIBS)  $(ADDED_LIBPATH) $(ADDED_LIBS) && if [ "$(EXPAND_DBG)" = "1" ]; then plink "$@";fi

2014Code/$(MODE_DIR)/2014Code_compile_file : $(FILE) ;

_clean :: 2014Code/$(MODE_DIR)/2014Code_clean

2014Code/$(MODE_DIR)/2014Code_clean : 
	$(TRACE_FLAG)if [ -d "2014Code" ]; then cd "2014Code"; rm -rf $(MODE_DIR); fi


# 2014Code_partialImage
ifeq ($(DEBUG_MODE),1)
2014Code_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_C-Compiler = -g
2014Code_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_C++-Compiler = -g
2014Code_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_Linker = -g
2014Code_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_Partial-Image-Linker = 
2014Code_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_Librarian = 
2014Code_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_Assembler = -g
else
2014Code_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_C-Compiler = -XO -Xsize-opt
2014Code_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_C++-Compiler = -XO -Xsize-opt
2014Code_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_Linker = -XO -Xsize-opt
2014Code_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_Partial-Image-Linker = 
2014Code_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_Librarian = 
2014Code_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_Assembler = -XO -Xsize-opt
endif
2014Code_partialImage/$(MODE_DIR)/% : IDE_INCLUDES = -I$(WIND_BASE)/target/h -I$(WIND_BASE)/target/h/wrn/coreip 
2014Code_partialImage/$(MODE_DIR)/% : IDE_LIBRARIES = 
2014Code_partialImage/$(MODE_DIR)/% : IDE_DEFINES = 
2014Code_partialImage/$(MODE_DIR)/% : PROJECT_TYPE = DKM
2014Code_partialImage/$(MODE_DIR)/% : DEFINES = 
2014Code_partialImage/$(MODE_DIR)/% : EXPAND_DBG = 0
2014Code_partialImage/$(MODE_DIR)/% : VX_CPU_FAMILY = ppc
2014Code_partialImage/$(MODE_DIR)/% : CPU = PPC603
2014Code_partialImage/$(MODE_DIR)/% : TOOL_FAMILY = diab
2014Code_partialImage/$(MODE_DIR)/% : TOOL = diab
2014Code_partialImage/$(MODE_DIR)/% : TOOL_PATH = 
2014Code_partialImage/$(MODE_DIR)/% : CC_ARCH_SPEC = -tPPC603FH:vxworks63
2014Code_partialImage/$(MODE_DIR)/% : LIBPATH = 
2014Code_partialImage/$(MODE_DIR)/% : LIBS = 
2014Code_partialImage/$(MODE_DIR)/% : ADDED_C++FLAGS = 
2014Code_partialImage/$(MODE_DIR)/% : OBJ_DIR := 2014Code_partialImage/$(MODE_DIR)

2014Code_partialImage/$(MODE_DIR)/Objects/2014Code/.metadata/.plugins/org.eclipse.cdt.make.core/specs.o : $(PRJ_ROOT_DIR)/.metadata/.plugins/org.eclipse.cdt.make.core/specs.c $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(IDE_DEFINES) $(DEFINES) -o "$@" -c "$<"


2014Code_partialImage/$(MODE_DIR)/Objects/2014Code/.metadata/.plugins/org.eclipse.cdt.make.core/specs.o : $(PRJ_ROOT_DIR)/.metadata/.plugins/org.eclipse.cdt.make.core/specs.cpp $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(IDE_DEFINES) $(DEFINES) -o "$@" -c "$<"


2014Code_partialImage/$(MODE_DIR)/Objects/2014Code/Config.o : $(PRJ_ROOT_DIR)/Config.cpp $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(IDE_DEFINES) $(DEFINES) -o "$@" -c "$<"


2014Code_partialImage/$(MODE_DIR)/Objects/2014Code/Console.o : $(PRJ_ROOT_DIR)/Console.cpp $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(IDE_DEFINES) $(DEFINES) -o "$@" -c "$<"


2014Code_partialImage/$(MODE_DIR)/Objects/2014Code/Shooter.o : $(PRJ_ROOT_DIR)/Shooter.cpp $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(IDE_DEFINES) $(DEFINES) -o "$@" -c "$<"


2014Code_partialImage/$(MODE_DIR)/Objects/2014Code/Subsystem.o : $(PRJ_ROOT_DIR)/Subsystem.cpp $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(IDE_DEFINES) $(DEFINES) -o "$@" -c "$<"


2014Code_partialImage/$(MODE_DIR)/Objects/2014Code/WPIObjMgr.o : $(PRJ_ROOT_DIR)/WPIObjMgr.cpp $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(IDE_DEFINES) $(DEFINES) -o "$@" -c "$<"


2014Code_partialImage/$(MODE_DIR)/Objects/2014Code/main.o : $(PRJ_ROOT_DIR)/main.cpp $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only -Xforce-declarations  -Xmake-dependency=0xd $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(IDE_DEFINES) $(DEFINES) -o "$@" -c "$<"


OBJECTS_2014Code_partialImage = 2014Code_partialImage/$(MODE_DIR)/Objects/2014Code/.metadata/.plugins/org.eclipse.cdt.make.core/specs.o \
	 2014Code_partialImage/$(MODE_DIR)/Objects/2014Code/.metadata/.plugins/org.eclipse.cdt.make.core/specs.o \
	 2014Code_partialImage/$(MODE_DIR)/Objects/2014Code/Config.o \
	 2014Code_partialImage/$(MODE_DIR)/Objects/2014Code/Console.o \
	 2014Code_partialImage/$(MODE_DIR)/Objects/2014Code/Shooter.o \
	 2014Code_partialImage/$(MODE_DIR)/Objects/2014Code/Subsystem.o \
	 2014Code_partialImage/$(MODE_DIR)/Objects/2014Code/WPIObjMgr.o \
	 2014Code_partialImage/$(MODE_DIR)/Objects/2014Code/main.o

2014Code_partialImage/$(MODE_DIR)/2014Code_partialImage.o : $(OBJECTS_2014Code_partialImage)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)dld -tPPC603FH:vxworks63 -X -r5  -o "$@" $(OBJECTS_2014Code_partialImage) $(LIBPATH) $(LIBS) $(ADDED_LIBPATH) $(ADDED_LIBS)  && if [ "$(EXPAND_DBG)" = "1" ]; then plink "$@";fi

2014Code_partialImage/$(MODE_DIR)/2014Code_partialImage_compile_file : $(FILE) ;

_clean :: 2014Code_partialImage/$(MODE_DIR)/2014Code_partialImage_clean

2014Code_partialImage/$(MODE_DIR)/2014Code_partialImage_clean : 
	$(TRACE_FLAG)if [ -d "2014Code_partialImage" ]; then cd "2014Code_partialImage"; rm -rf $(MODE_DIR); fi

force : 

DEP_FILES := 2014Code_partialImage/$(MODE_DIR)/Objects/2014Code/.metadata/.plugins/org.eclipse.cdt.make.core/specs.d 2014Code_partialImage/$(MODE_DIR)/Objects/2014Code/.metadata/.plugins/org.eclipse.cdt.make.core/specs.d 2014Code_partialImage/$(MODE_DIR)/Objects/2014Code/Config.d \
	 2014Code_partialImage/$(MODE_DIR)/Objects/2014Code/Console.d 2014Code_partialImage/$(MODE_DIR)/Objects/2014Code/Shooter.d 2014Code_partialImage/$(MODE_DIR)/Objects/2014Code/Subsystem.d \
	 2014Code_partialImage/$(MODE_DIR)/Objects/2014Code/WPIObjMgr.d 2014Code_partialImage/$(MODE_DIR)/Objects/2014Code/main.d
-include $(DEP_FILES)



-include $(PRJ_ROOT_DIR)/*.makefile

-include *.makefile

JOBS?=1
ifeq ($(JOBS),1)
main_all : external_build  $(PROJECT_TARGETS)
	@echo "make: built targets of `pwd`"
else
main_all : external_build 
	@$(MAKE) -f $(MAKEFILE) --jobs $(JOBS) $(MFLAGS) $(PROJECT_TARGETS);\
	echo "make: built targets of `pwd`"
endif 

# entry point for extending the build
external_build ::
	@echo ""

# main entry point for pre processing prior to the build
pre_build :: $(PRE_BUILD_STEP) generate_sources
	@echo ""

# entry point for generating sources prior to the build
generate_sources ::
	@echo ""

# main entry point for post processing after the build
post_build :: $(POST_BUILD_STEP) deploy_output
	@echo ""

# entry point for deploying output after the build
deploy_output ::
	@echo ""

clean :: external_clean $(CLEAN_STEP) _clean

# entry point for extending the build clean
external_clean ::
	@echo ""
