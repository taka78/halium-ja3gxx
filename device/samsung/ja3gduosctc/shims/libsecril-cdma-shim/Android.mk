LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_SRC_FILES:= secril-cdma-shim.c
LOCAL_SHARED_LIBRARIES := liblog libbinder
LOCAL_MODULE:= libsecril-cdma-shim

include $(BUILD_SHARED_LIBRARY)
