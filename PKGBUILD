# Maintainer: You <you@example.com>
pkgname=yasumi
pkgver=1.0.0
pkgrel=3
pkgdesc="Sane-break style tray app: timed full-screen break seizure for Wayland (Hyprland)"
arch=('x86_64')
url="https://github.com/yourusername/yasumi"
license=('GPL-3.0-or-later')
depends=(
    'qt6-base'
    'qt6-declarative'
    'qt6-wayland'
    'wayland'
)
makedepends=(
    'qt6-base'
    'qt6-declarative'
    'qt6-wayland'
)
source=('source.tar.gz')
md5sums=('SKIP')

build() {
    cd "$srcdir"
    mkdir -p build
    tar xzf source.tar.gz
    cd build
    qmake6 ../yasumi.pro
    make -j$(nproc)
}

package() {
    cd "$srcdir/build"
    # qmake honors INSTALL_ROOT as the staging prefix (not DESTDIR)
    make install INSTALL_ROOT="$pkgdir"
}
