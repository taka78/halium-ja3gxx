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

LOCAL_PATH := device/samsung/jaltelgt

BOARD_VENDOR := samsung

# Include path
TARGET_SPECIFIC_HEADER_PATH := $(LOCAL_PATH)/include

# Assert
TARGET_OTA_ASSERT_DEVICE := jalte,jaltelgt,e300l,SHV-E300L

# Platform
TARGET_SOC := exynos5410

# Kernel
TARGET_KERNEL_CONFIG := lineageos_jaltelgt_defconfig

# Bluetooth
BOARD_BLUETOOTH_BDROID_BUILDCFG_INCLUDE_DIR := $(LOCAL_PATH)/bluetooth

# GPS
TARGET_NO_RPC := true
BOARD_GPS_SET_PRIVACY := true

# Radio
BOARD_PROVIDES_LIBRIL := true
BOARD_MODEM_TYPE := mdm9x35
BOARD_RIL_CLASS := ../../../device/samsung/jaltelgt/ril
TARGET_GLOBAL_CFLAGS += -DDISABLE_ASHMEM_TRACKING

# Recovery
TARGET_RECOVERY_FSTAB := $(LOCAL_PATH)/rootdir/etc/fstab.universal5410

# SELinux
BOARD_SEPOLICY_DIRS += \
    device/samsung/jaltelgt/sepolicy

# inherit from the proprietary version
-include vendor/samsung/jaltelgt/BoardConfigVendor.mk

# inherit common board flags
include device/samsung/exynos5410-common/BoardConfigCommon.mk
