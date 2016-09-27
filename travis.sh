
export PATH="$PATH:$(pwd)/prebuilts/bin/"
export CROSS_COMPILE="aarch64-linux-android-"
mkdir -p out
make ARCH=arm64 O=out merge_hi3650_defconfig
make ARCH=arm64 O=out -j2

