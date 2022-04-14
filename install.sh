#!/bin/sh
here="$PWD"
! [ -f "$here/install.sh" ] && return

doas pacman -S autoconf automake gcc make pkgconf patch fakeroot fd ripgrep \
    alacritty npm pkgstats alsa-utils chromium xclip dmenu maim feh \
    xorg-xinit xorg-xsetroot mpv zathura-cb xf86-video-amdgpu xorg-server \
    zathura-pdf-poppler man-db xorg-xrandr ttf-iosevka-nerd ttf-liberation \
    noto-fonts noto-fonts-cjk noto-fonts-emoji pulseaudio-alsa neovim

git clone "git://git.suckless.org/dwm" "$HOME/dwm"
mkdir "$HOME/dwm/patches"
cd "$HOME/dwm/patches" || return
curl --remote-name-all "https://dwm.suckless.org/patches/{statusallmons/dwm-statusallmons-6.2.diff,attachbottom/dwm-attachbottom-6.2.diff,scratchpad/dwm-scratchpad-6.2.diff,alwayscenter/dwm-alwayscenter-20200625-f04cac6.diff}"
cd "$HOME/dwm" || return
for i in "$HOME/dwm/patches/"*.diff;
    do patch < $i;
done
cp "$here/system/config.h" "$HOME/dwm"
doas make clean install

git clone "https://aur.archlinux.org/nvim-packer-git.git" "$HOME/packer"
cd "$HOME/packer" || return
makepkg -si

git clone "https://aur.archlinux.org/nsxiv.git" "$HOME/nsxiv"
cd "$HOME/nsxiv" || return
makepkg -si

doas install -Dm 655 "$here/system/dwm_run" \
    "/usr/local/bin/"
doas install -Dm 644 "$here/system/vconsole.conf" \
    "/etc/"
doas install -Dm 644 "$here/system/ter-132n.psf.gz" \
    "/usr/share/kbd/consolefonts/"
doas install -Dm 644 "$here/system/50-mouse-acceleration.conf" \
    "/etc/X11/xorg.conf.d/"
doas ln -sf "/run/systemd/resolve/stub-resolv.conf" \
    "/etc/resolv.conf"

mkdir "$HOME/.config"
ln -sf "$here/home/."* "$HOME/"
ln -sf "$here/config/"* "$HOME/.config/"

echo "DONE"
