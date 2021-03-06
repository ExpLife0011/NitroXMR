cmake_minimum_required(VERSION 3.0)
project(xmrig)

option(WITH_LIBCPUID "Use Libcpuid" ON)
option(WITH_AEON     "CryptoNight-Lite support" ON)


include (CheckIncludeFile)


set(HEADERS
    src/3rdparty/align.h
    src/miner/App.h
    src/miner/Console.h
    src/miner/Cpu.h
    src/miner/interfaces/IClientListener.h
    src/miner/interfaces/IConsoleListener.h
    src/miner/interfaces/IJobResultListener.h
    src/miner/interfaces/ILogBackend.h
    src/miner/interfaces/IStrategy.h
    src/miner/interfaces/IStrategyListener.h
    src/miner/interfaces/IWorker.h
    src/miner/log/ConsoleLog.h
    src/miner/log/FileLog.h
    src/miner/log/Log.h
    src/miner/Mem.h
    src/miner/net/Client.h
    src/miner/net/Job.h
    src/miner/net/JobResult.h
    src/miner/net/Network.h
    src/miner/net/strategies/DonateStrategy.h
    src/miner/net/strategies/FailoverStrategy.h
    src/miner/net/strategies/SinglePoolStrategy.h
    src/miner/net/SubmitResult.h
    src/miner/net/Url.h
    src/miner/Options.h
    src/miner/Platform.h
    src/miner/Summary.h
    src/miner/version.h
    src/miner/workers/DoubleWorker.h
    src/miner/workers/Handle.h
    src/miner/workers/Hashrate.h
    src/miner/workers/SingleWorker.h
    src/miner/workers/Worker.h
    src/miner/workers/Workers.h
   )

set(HEADERS_CRYPTO
    src/miner/crypto/c_blake256.h
    src/miner/crypto/c_groestl.h
    src/miner/crypto/c_jh.h
    src/miner/crypto/c_keccak.h
    src/miner/crypto/c_skein.h
    src/miner/crypto/CryptoNight.h
    src/miner/crypto/CryptoNight_p.h
    src/miner/crypto/CryptoNight_test.h
    src/miner/crypto/groestl_tables.h
    src/miner/crypto/hash.h
    src/miner/crypto/skein_port.h
   )

set(SOURCES
    src/miner/App.cpp
    src/miner/Console.cpp
    src/miner/log/ConsoleLog.cpp
    src/miner/log/FileLog.cpp
    src/miner/log/Log.cpp
    src/miner/Mem.cpp
    src/miner/net/Client.cpp
    src/miner/net/Job.cpp
    src/miner/net/Network.cpp
    src/miner/net/strategies/DonateStrategy.cpp
    src/miner/net/strategies/FailoverStrategy.cpp
    src/miner/net/strategies/SinglePoolStrategy.cpp
    src/miner/net/Url.cpp
    src/miner/Options.cpp
    src/miner/Platform.cpp
    src/miner/Summary.cpp
    src/miner/workers/DoubleWorker.cpp
    src/miner/workers/Handle.cpp
    src/miner/workers/Hashrate.cpp
    src/miner/workers/SingleWorker.cpp
    src/miner/workers/Worker.cpp
    src/miner/workers/Workers.cpp
    src/miner/xmrig.cpp
   )

set(SOURCES_CRYPTO
    src/miner/crypto/c_keccak.c
    src/miner/crypto/c_groestl.c
    src/miner/crypto/c_blake256.c
    src/miner/crypto/c_jh.c
    src/miner/crypto/c_skein.c
    src/miner/crypto/soft_aes.c
    src/miner/crypto/soft_aes.c
    src/miner/crypto/CryptoNight.cpp
   )

if (WIN32)
    set(SOURCES_OS
        res/app.rc
        src/miner/App_win.cpp
        src/miner/Cpu_win.cpp
        src/miner/Mem_win.cpp
        src/miner/Platform_win.cpp
        )

    add_definitions(/DWIN32)
    set(EXTRA_LIBS ws2_32 psapi iphlpapi userenv)
elseif (APPLE)
    set(SOURCES_OS
        src/miner/App_unix.cpp
        src/miner/Cpu_mac.cpp
        src/miner/Mem_unix.cpp
        src/miner/Platform_mac.cpp
        )
else()
    set(SOURCES_OS
        src/miner/App_unix.cpp
        src/miner/Cpu_unix.cpp
        src/miner/Mem_unix.cpp
        src/miner/Platform_unix.cpp
        )

    set(EXTRA_LIBS pthread)
endif()

add_definitions(/DUNICODE)
#add_definitions(/DAPP_DEBUG)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")

find_package(UV REQUIRED)

if ("${CMAKE_BUILD_TYPE}" STREQUAL "")
    set(CMAKE_BUILD_TYPE Release)
endif()


# https://cmake.org/cmake/help/latest/variable/CMAKE_LANG_COMPILER_ID.html
if (CMAKE_CXX_COMPILER_ID MATCHES GNU)

    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -maes -Wall -Wno-strict-aliasing")
    set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -Ofast -funroll-loops -fvariable-expansion-in-unroller -ftree-loop-if-convert-stores -fmerge-all-constants -fbranch-target-load-optimize2")

    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -maes -Wall -std=c++14 -fno-exceptions -fno-rtti")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Ofast -s -funroll-loops -fvariable-expansion-in-unroller -ftree-loop-if-convert-stores -fmerge-all-constants -fbranch-target-load-optimize2")

    if (WIN32)
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static")
        add_definitions(/D__STDC_FORMAT_MACROS)
    else()
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static-libgcc -static-libstdc++")
    endif()

    add_definitions(/D_GNU_SOURCE)

    #set(CMAKE_C_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -gdwarf-2")

elseif (CMAKE_CXX_COMPILER_ID MATCHES MSVC)

    set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} /Ox /Ot /Oi /MT /GL")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /Ox /Ot /Oi /MT /GL")
    add_definitions(/D_CRT_SECURE_NO_WARNINGS)
    add_definitions(/D_CRT_NONSTDC_NO_WARNINGS)

elseif (CMAKE_CXX_COMPILER_ID MATCHES Clang)

    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -maes -Wall")
    set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -Ofast -funroll-loops -fmerge-all-constants")

    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -maes -Wall -std=c++14 -fno-exceptions -fno-rtti")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Ofast -funroll-loops -fmerge-all-constants")

endif()

if (WITH_LIBCPUID)
    add_subdirectory(src/3rdparty/libcpuid)

    include_directories(src/3rdparty/libcpuid)
    set(CPUID_LIB cpuid)
    set(SOURCES_CPUID src/miner/Cpu.cpp)
else()
    add_definitions(/DXMRIG_NO_LIBCPUID)
    set(SOURCES_CPUID src/miner/Cpu_stub.cpp)
endif()

CHECK_INCLUDE_FILE (syslog.h HAVE_SYSLOG_H)
if (HAVE_SYSLOG_H)
    add_definitions(/DHAVE_SYSLOG_H)
    set(SOURCES_SYSLOG src/miner/log/SysLog.h src/miner/log/SysLog.cpp)
endif()

include_directories(src/miner)
include_directories(src/3rdparty)
include_directories(src/3rdparty/jansson)
include_directories(${UV_INCLUDE_DIR})

add_subdirectory(src/3rdparty/jansson)

add_executable(xmrig ${HEADERS} ${SOURCES} ${SOURCES_OS} ${SOURCES_CPUID} ${HEADERS_CRYPTO} ${SOURCES_CRYPTO} ${SOURCES_SYSLOG})
target_link_libraries(xmrig jansson ${UV_LIBRARIES} ${EXTRA_LIBS} ${CPUID_LIB})
