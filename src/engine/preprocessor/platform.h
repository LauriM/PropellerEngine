// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#ifndef CORE_PREPROCESSOR_PLATFORM_H
#define CORE_PREPROCESSOR_PLATFORM_H

// Os stuff

//OS_WINDOWS
//OS_LINUX

//TYPE_PC
//TYPE_TABLET
//etc..

#ifdef _WIN32
	#define OS_WINDOWS
	#define TYPE_PC
#endif

#ifdef _WIN64
	#define OS_WINDOWS
	#define TYPE_PC
#endif

#ifdef _LINUX
	#define OS_LINUX
	#define TYPE_PC
#endif

#ifdef _MAC
    #define OS_MAC
    #define TYPE_PC
#endif

#ifdef _ANDROID
	#ifndef OS_ANDROID
		#define OS_ANDROID
	#endif
	#define TYPE_MOBILE
#endif

// CPU types
#define CORE_X86_32 0x00000001
#define CORE_X86_64 0x00000002
#define CORE_ARM    0x00000004
#define CORE_PPC    0x00000008
#define CORE_MIPS   0x00000010

// Combine x86 platforms
#define CORE_X86 (CORE_X86_32 | CORE_X86_64)

// Split by the instruction set type
#define CORE_CISC (CORE_X86)
#define CORE_RISC (CORE_ARM | CORE_PPC | CORE_MIPS)

// Split by the word sizwe
#define CORE_32BIT (CORE_X86_32 | CORE_ARM | CORE_PPC | CORE_MIPS)
#define CORE_64BIT (CORE_X86_64)

// Split by endianess
#define CORE_LITTLE_ENDIAN (CORE_X86 | CORE_ARM)
#define CORE_BIG_ENDIAN    (CORE_PPC | CORE_MIPS)

// Detect platform bits
#if defined __i386__ || defined _M_X86 || defined _M_IX86 
	#define CORE_CPU_VALUE CORE_X86_32
#elif __x86_64__ || __X86_64__ || _M_AMD64 
	#define CORE_CPU_VALUE CORE_X86_64
#elif __arm__ || _M_ARM_FP
	#define CORE_CPU_VALUE CORE_ARM
#elif _M_PPC || _M_MPPC || _ARCH_PPC || __PPC || __PPC__ || __powerpc__
	#define CORE_CPU_VALUE CORE_PPC
#elif __mips__ || _M_MRX000
	#define CORE_CPU_VALUE CORE_MIPS
#else
	#define CORE_CPU_UNKNOWN
#endif

// Check functions
#define CORE_CPU(p_type) (CORE_CPU_VALUE & CORE_ ## p_type)

#endif
