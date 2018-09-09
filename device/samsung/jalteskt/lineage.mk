$(call inherit-product, device/samsung/jalteskt/full_jalteskt.mk)

# Inherit some common Lineage stuff.
$(call inherit-product, vendor/cm/config/common_full_phone.mk)

PRODUCT_NAME := lineage_jalteskt
PRODUCT_DEVICE := jalteskt

PRODUCT_BUILD_PROP_OVERRIDES += \
    PRODUCT_MODEL=SHV-E300S \
    PRODUCT_NAME=jalteskt \
    PRODUCT_DEVICE=jalteskt \
    TARGET_DEVICE=jalteskt \
    BUILD_FINGERPRINT="samsung/jalteskt/jalteskt:5.0.1/LRX22C/E300SKSUGPI1:user/release-keys" \
    PRIVATE_BUILD_DESC="jalteskt-user 5.0.1 LRX22C E300SKSUGPI1 release-keys"
