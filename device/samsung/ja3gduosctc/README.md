# LineageOS support of SCH-I959

## Status

CDMA/GSM voice,sms and data is working now.

## Problem

* can't switch mobile data baseband correctly without restart networks.

## How to fetch source

[Spxg/manifest](https://github.com/Spxg/manifest)

## How to build

1. `extract-files.sh` to extract vendor files. Support pull from adb automatically or using path argument to extract.
2. `setup-makefiles.sh` to generate vendor file makefiles.
3. `lunch` & `brunch`

Notice: source in `/overlay` may be **outdated**. The overlay contains modification of Captive Portal and `realcall` parameter setter when audio state is changing.