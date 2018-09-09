$(call inherit-product, device/samsung/ja3gchnduos/full_ja3gchnduos.mk)

# Inherit some common Lineage stuff.
$(call inherit-product, vendor/cm/config/common_full_phone.mk)

PRODUCT_NAME := lineage_ja3gchnduos
PRODUCT_DEVICE := ja3gchnduos

PRODUCT_BUILD_PROP_OVERRIDES += \
    PRODUCT_MODEL=GT-I9502 \
    PRODUCT_NAME=ja3gchnduos \
    PRODUCT_DEVICE=ja3gchnduos \
    TARGET_DEVICE=ja3gchnduos \
    BUILD_FINGERPRINT="samsung/ja3gchnduoszn/ja3gchnduos:5.0.1/LRX22C/I9502ZNUJOH2:user/release-keys" \
    PRIVATE_BUILD_DESC="a3gchnduoszn-user 5.0.1 LRX22C I9502ZNUJOH2 release-keys"
