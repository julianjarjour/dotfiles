#!/bin/bash
set -euo pipefail

here="$PWD"
[[ ! -f "$here/install.sh" ]] && exit 1

doas ln -sf "/run/systemd/resolve/stub-resolv.conf" "/etc/resolv.conf"

doas pacman -S base-devel man-db ripgrep fd neovim alacritty mpv maim xclip \
    ttf-iosevka-nerd ttf-liberation noto-fonts noto-fonts-cjk noto-fonts-emoji \
    xorg-server xorg-xinit xorg-xsetroot dmenu zathura-pdf-mupdf zathura-cb feh \
    pipewire-pulse pipewire-jack redshift discord ntfs-3g exa

git clone "https://github.com/tonijarjour/dwm.git" "$HOME/dwm"
ln -s "$here/dwm.h" "$HOME/dwm/config.h"
cd "$HOME/dwm" || exit 1
doas make clean install

git clone "https://aur.archlinux.org/nvim-packer-git.git" "$HOME/packer"
cd "$HOME/packer" || exit 1
makepkg -si

git clone "https://aur.archlinux.org/nsxiv.git" "$HOME/nsxiv"
cd "$HOME/nsxiv" || exit 1
makepkg -si

git clone "https://aur.archlinux.org/spotify.git" "$HOME/spotify"
cd "$HOME/spotify" || exit 1
makepkg -si

doas install -Dm 644 "$here/50-mouse-acceleration.conf" "/etc/X11/xorg.conf.d"
mkdir -p "$HOME/.config"
ln -sf "$here/config/"* "$HOME/.config/"

for f in "$here/home/"*
do
    ln -sf "$f" "$HOME/.${f##*/}"
done

ln -sf "/mnt/archive/Linux/"* "$HOME"
echo "DONE"
