#
# Copyright (C) 2013 The CyanogenMod Project
# Copyright (C) 2017 The LineageOS Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#

LOCAL_PATH := device/samsung/ja3gchnduos

BOARD_VENDOR := samsung

# Include path
TARGET_SPECIFIC_HEADER_PATH := $(LOCAL_PATH)/include

# Assert
TARGET_OTA_ASSERT_DEVICE := ja3gchn,ja3gchnduos,i9502,GT-I9502

# Platform
TARGET_SOC := exynos5410

# Kernel
TARGET_KERNEL_CONFIG := lineageos_ja3gchnduos_defconfig

# Bluetooth
BOARD_BLUETOOTH_BDROID_BUILDCFG_INCLUDE_DIR := $(LOCAL_PATH)/bluetooth

# Linker
LINKER_FORCED_SHIM_LIBS := /system/bin/gpsd|libdmitry.so

# Radio
BOARD_GLOBAL_CFLAGS += -DSEC_PRODUCT_FEATURE_RIL_CALL_DUALMODE_CDMAGSM
BOARD_MODEM_TYPE := xmm6360
BOARD_PROVIDES_LIBRIL := true
BOARD_RIL_CLASS := ../../../device/samsung/ja3gchnduos/ril
TARGET_GLOBAL_CFLAGS += -DDISABLE_ASHMEM_TRACKING

# Recovery
TARGET_RECOVERY_FSTAB := $(LOCAL_PATH)/rootdir/etc/fstab.universal5410

# SELinux
BOARD_SEPOLICY_DIRS += \
    device/samsung/ja3gchnduos/sepolicy

# inherit from the proprietary version
-include vendor/samsung/ja3gchnduos/BoardConfigVendor.mk

# inherit common board flags
include device/samsung/exynos5410-common/BoardConfigCommon.mk
