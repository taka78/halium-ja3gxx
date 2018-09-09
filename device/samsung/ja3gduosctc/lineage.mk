$(call inherit-product, device/samsung/ja3gduosctc/full_ja3gduosctc.mk)

# Inherit some common Lineage stuff.
$(call inherit-product, vendor/cm/config/common_full_phone.mk)


PRODUCT_NAME := lineage_ja3gduosctc
PRODUCT_DEVICE := ja3gduosctc

PRODUCT_BUILD_PROP_OVERRIDES += \
    PRODUCT_MODEL=SCH-I959 \
    PRODUCT_NAME=ja3gduosctc \
    PRODUCT_DEVICE=ja3gduosctc \
    TARGET_DEVICE=ja3gduosctc \
    BUILD_FINGERPRINT="samsung/ja3gduosctc/ja3gduosctc:5.0.1/LRX22C/I959KEUJOH4:user/release-keys" \
    PRIVATE_BUILD_DESC="ja3gduosctc-user 5.0.1 LRX22C I959KEUJOH4 release-keys"
