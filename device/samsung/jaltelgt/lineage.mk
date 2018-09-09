$(call inherit-product, device/samsung/jaltelgt/full_jaltelgt.mk)

# Inherit some common Lineage stuff.
$(call inherit-product, vendor/cm/config/common_full_phone.mk)

PRODUCT_NAME := lineage_jaltelgt
PRODUCT_DEVICE := jaltelgt

PRODUCT_BUILD_PROP_OVERRIDES += \
    PRODUCT_MODEL=SHV-E300L \
    PRODUCT_NAME=jaltelgt \
    PRODUCT_DEVICE=jaltelgt \
    TARGET_DEVICE=jaltelgt \
    BUILD_FINGERPRINT="samsung/jaltelgt/jaltelgt:5.0.1/LRX22C/E300LKLUGPG1:user/release-keys" \
    PRIVATE_BUILD_DESC="jaltelgt-user 5.0.1 LRX22C E300LKLUGPG1 release-keys"
