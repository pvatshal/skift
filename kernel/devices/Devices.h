#pragma once

#include <libsystem/Common.h>

#include "kernel/bus/PCIDevice.h"

typedef enum
{
    BUS_NONE,
    BUS_UNIX,
    BUS_PCI,
} Bus;

typedef enum
{
    UNIX_ZERO,
    UNIX_NULL,
    UNIX_RANDOM,
} UNIXDevice;

typedef struct
{
    UNIXDevice device;
} UNIXDeviceAddress;

typedef struct
{
    Bus bus;

    union {
        UNIXDeviceAddress unix_device;
        PCIDevice pci_device;
    };
} DeviceInfo;

typedef bool (*DeviceDriverInfoMatch)(DeviceInfo info);
typedef void (*DeviceDriverInfoInitialize)(DeviceInfo info);

typedef struct
{
    const char *description;

    Bus bus;
    DeviceDriverInfoMatch match;
    DeviceDriverInfoInitialize initialize;
} DeviceDriverInfo;

typedef IterationDecision (*DeviceIterateCallback)(void *target, DeviceInfo device);

void device_initialize();

const DeviceDriverInfo *device_get_diver_info(DeviceInfo info);

const char *device_to_static_string(DeviceInfo info);

void device_iterate(void *target, DeviceIterateCallback callback);

/* --- Devices -------------------------------------------------------------- */

bool bga_match(DeviceInfo info);
void bga_initialize(DeviceInfo info);

void keyboard_initialize();

void null_initialize();

void proc_initialize();

void random_initialize();

void textmode_initialize();

void zero_initialize();

void serial_initialize();

void mouse_initialize();
