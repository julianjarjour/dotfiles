#!/bin/bash
set -euo pipefail

here="$PWD"
[[ ! -f "$here/install.sh" ]] && exit 1

s() {
  C=''
  for i in "$@"; do 
    i="${i//\\/\\\\}"
    C="$C \"${i//\"/\\\"}\""
  done
  su -c bash -c "$C"
}

echo 'ln -sf "/run/systemd/resolve/stub-resolv.conf" "/etc/resolv.conf"'
s ln -sf "/run/systemd/resolve/stub-resolv.conf" "/etc/resolv.conf"

echo 'install programs with pacman'
s pacman -S fd ripgrep neovim alacritty mpv maim feh sxiv xclip dmenu which \
  ttf-iosevka-nerd ttf-croscore noto-fonts noto-fonts-cjk noto-fonts-emoji \
  xorg-server xorg-xinit xorg-xsetroot zathura-pdf-mupdf zathura-cb redshift \
  pipewire-pulse pipewire-jack arc-solid-gtk-theme man-db texinfo fakeroot \
  gcc autoconf automake pkgconf make patch exa

git clone "https://github.com/tonijarjour/dwm.git" "$HOME/dwm"
ln -s "$here/system/dwm.h" "$HOME/dwm/config.h"
cd "$HOME/dwm" || exit 1
echo 'compile and install dwm'
s make clean install

git clone "https://aur.archlinux.org/nvim-packer-git.git" "$HOME/packer"
cd "$HOME/packer" || exit 1
makepkg -si

git clone "https://aur.archlinux.org/spotify.git" "$HOME/spotify"
cd "$HOME/spotify" || exit 1
makepkg -si

echo 'install -Dm 644 "$here/system/50-mouse-acceleration.conf" "/etc/X11/xorg.conf.d/"'
s install -Dm 644 "$here/system/50-mouse-acceleration.conf" "/etc/X11/xorg.conf.d/"

echo 'install -Dm 644 "$here/system/arabic.conf" "/etc/fonts/local.conf"'
s install -Dm 644 "$here/system/arabic.conf" "/etc/fonts/local.conf"

mkdir -p "$HOME/.config"
ln -sf "$here/config/"* "$HOME/.config/"

for f in "$here/home/"*
do
  ln -sf "$f" "$HOME/.${f##*/}"
done

ln -sf "/mnt/archive/Linux/"* "$HOME"
echo "DONE"
