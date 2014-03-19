#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux-x86
CND_DLIB_EXT=so
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/_ext/1445274692/buffer.o \
	${OBJECTDIR}/_ext/1445274692/common.o \
	${OBJECTDIR}/_ext/2112918630/std_members.o \
	${OBJECTDIR}/_ext/1445274692/error.o \
	${OBJECTDIR}/_ext/1445274692/symtable.o \
	${OBJECTDIR}/_ext/1445274692/types.o \
	${OBJECTDIR}/_ext/1449855206/stdio.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=-g3
CXXFLAGS=-g3

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ../stdio.${CND_DLIB_EXT}

../stdio.${CND_DLIB_EXT}: ${OBJECTFILES}
	${MKDIR} -p ..
	${LINK.cc} -o ../stdio.${CND_DLIB_EXT} ${OBJECTFILES} ${LDLIBSOPTIONS} -shared -fPIC

${OBJECTDIR}/_ext/1445274692/buffer.o: ../../src/buffer.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1445274692
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../../include/cx-debug -I../../include -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1445274692/buffer.o ../../src/buffer.cpp

${OBJECTDIR}/_ext/1445274692/common.o: ../../src/common.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1445274692
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../../include/cx-debug -I../../include -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1445274692/common.o ../../src/common.cpp

${OBJECTDIR}/_ext/2112918630/std_members.o: ../../src/cx-debug/std_members.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/2112918630
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../../include/cx-debug -I../../include -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/2112918630/std_members.o ../../src/cx-debug/std_members.cpp

${OBJECTDIR}/_ext/1445274692/error.o: ../../src/error.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1445274692
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../../include/cx-debug -I../../include -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1445274692/error.o ../../src/error.cpp

${OBJECTDIR}/_ext/1445274692/symtable.o: ../../src/symtable.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1445274692
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../../include/cx-debug -I../../include -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1445274692/symtable.o ../../src/symtable.cpp

${OBJECTDIR}/_ext/1445274692/types.o: ../../src/types.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1445274692
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../../include/cx-debug -I../../include -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1445274692/types.o ../../src/types.cpp

${OBJECTDIR}/_ext/1449855206/stdio.o: ../win32/stdio/stdio.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1449855206
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../../include/cx-debug -I../../include -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1449855206/stdio.o ../win32/stdio/stdio.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ../stdio.${CND_DLIB_EXT}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc