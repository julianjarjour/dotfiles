#!/bin/sh
set -euo pipefail

username='julian'
hostname='aurelius'
timezone='America/New_York'
locale='en_US'
cpucode='intel'
espboot='boot'
rootlabel='ARCH_LINUX'
interface='eno1'
kernel='linux-zen'

ln -sf /usr/share/zoneinfo/$timezone /etc/localtime
hwclock --systohc
echo "$locale.UTF-8 UTF-8" > /etc/locale.gen
locale-gen
echo "LANG=$locale.UTF-8" > /etc/locale.conf
echo "$hostname" > /etc/hostname
useradd -m -U $username
echo "UUID=90841C16841BFD82 /mnt/archive ntfs-3g defaults 0 2" >> /etc/fstab
cat > /etc/security/access.conf << EOF
+:root:LOCAL
+:$username:LOCAL
-:ALL:ALL
EOF
bootctl install
cat > /$espboot/loader/loader.conf << EOF
default         arch.conf
timeout         3
editor          no
EOF
cat > /$espboot/loader/entries/arch.conf << EOF
title   Arch Linux
linux   /vmlinuz-$kernel
initrd  /$cpucode-ucode.img
initrd  /initramfs-$kernel.img
options root="LABEL=$rootlabel" rw quiet
EOF
cat > /etc/systemd/network/20-wired.network << EOF
[Match]
Name=$interface

[Network]
DHCP=yes
EOF
systemctl enable systemd-networkd.service
systemctl enable systemd-resolved.service
echo "-- ALL STEPS FINISHED"
echo "-- Remember to set a PASSWORD for root and $username"
