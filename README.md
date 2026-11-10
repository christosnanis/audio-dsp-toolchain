# audio-dsp-toolchain
A build-from-source audio DSP toolchain installation guide

### Start installing toolchain from binary sources in the order given below

#### LIBOGG
```bash
wget https://ftp.osuosl.org/pub/xiph/releases/ogg/libogg-1.3.6.tar.gz
tar -xzvf libogg-1.3.6.tar.gz
cd libogg-1.3.6/
mkdir build
cd build

CXXFLAGS="$CXXFLAGS -fPIC" cmake -S .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/usr -DBUILD_SHARED_LIBS=ON -DCMAKE_CXX_FLAGS="-fPIC -I/usr/include"

make -j8
sudo make install
```

#### LIBVORBIS (linked with libogg)
```bash
wget https://ftp.osuosl.org/pub/xiph/releases/vorbis/libvorbis-1.3.7.tar.gz
tar -xzvf libvorbis-1.3.7.tar.gz
cd libvorbis-1.3.7/
mkdir build
cd build
cmake -S .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/usr -DBUILD_SHARED_LIBS=ON -DCMAKE_CXX_FLAGS="-fPIC -I/usr/include" -DCMAKE_LD_FLAGS="-L/usr/lib" -DCMAKE_POLICY_VERSION_MINIMUM=3.5
make -j8
sudo make install
```
##### check if linked correctly to libogg with: 
```bash
ldd /usr/lib/libvorbis.so
```

#### LIBFLAC (linked with libogg)
```bash
wget https://ftp.osuosl.org/pub/xiph/releases/flac/flac-1.5.0.tar.xz
tar -xf flac-1.5.0.tar.xz
cd flac-1.5.0/
mkdir build
cd build
cmake -S .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/usr -DBUILD_SHARED_LIBS=ON -DCMAKE_CXX_FLAGS="-fPIC -I/usr/include" -DCMAKE_LD_FLAGS="-L/usr/lib" -DCMAKE_POLICY_VERSION_MINIMUM=3.5
make -j8
sudo make install
```
##### check if linked correctly to libogg
```bash
ldd /usr/lib/libFLAC.so
```
#### LIBOPUS
```bash
wget https://ftp.osuosl.org/pub/xiph/releases/opus/opus-1.5.2.tar.gz
tar -xzvf opus-1.5.2.tar.gz
cd opus-1.5.2/
mkdir build
cd build
cmake -S .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/usr -DBUILD_SHARED_LIBS=ON -DCMAKE_CXX_FLAGS="-fPIC -I/usr/include" -DCMAKE_LD_FLAGS="-L/usr/lib" -DCMAKE_POLICY_VERSION_MINIMUM=3.5
make -j8
sudo make install
```
#### LIBMP3LAME
```bash
wget https://sourceforge.net/projects/lame/files/lame/3.100/lame-3.100.tar.gz
tar -xzvf lame-3.100.tar.gz
cd lame-3.100/
CXXFLAGS="$CXXFLAGS -fPIC -I/usr/include" ./configure --prefix=/usr --enable-mp3rtp --disable-static LDFLAGS="-L/usr/lib"
make -j4
make check -j4
sudo make install
```
##### check if installed correctly with:
```bash
ldconfig -p | grep mp3lame
```

#### LIBMPG123
```bash
wget https://sourceforge.net/projects/mpg123/files/mpg123/1.33.0/mpg123-1.33.0.tar.bz2
tar -xf mpg123-1.33.0.tar.bz2
cd mpg123-1.33.0/
CXXFLAGS="$CXXFLAGS -fPIC -I/usr/include" ./configure --prefix=/usr --disable-static LDFLAGS="-L/usr/lib"
make -j4
make check -j4
sudo make install
```

#### LIBSPEEX
```bash
wget https://ftp.osuosl.org/pub/xiph/releases/speex/speex-1.2.1.tar.gz
tar -xf speex-1.2.1.tar.gz
cd speex-1.2.1/
CXXFLAGS="$CXXFLAGS -fPIC -I/usr/include" ./configure --prefix=/usr --disable-static LDFLAGS="-L/usr/lib"
make -j4
make check -j4
sudo make install
```
####LIBSPEEXDSP
```bash
wget https://ftp.osuosl.org/pub/xiph/releases/speex/speexdsp-1.2.1.tar.gz
tar -xf speexdsp-1.2.1.tar.gz
cd speexdsp-1.2.1/
CXXFLAGS="$CXXFLAGS -fPIC -I/usr/include" ./configure --prefix=/usr --disable-static LDFLAGS="-L/usr/lib"
make -j4
make check -j4
sudo make install
```

#### LIBSNDFILE
```bash
wget https://github.com/libsndfile/libsndfile/releases/download/1.2.2/libsndfile-1.2.2.tar.xz
tar -xf libsndfile-1.2.2.tar.xz
cd libsndfile-1.2.2/
mkdir build
cd build

### check what deps are there for this lib do inside the build folder: 
### e.g. for libogg:
cmake .. -LA -DCMAKE_POLICY_VERSION_MINIMUM=3.5 | grep -i ogg 

cmake -S .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/usr -DBUILD_SHARED_LIBS=ON -DCMAKE_CXX_FLAGS="-fPIC -I/usr/include" -DCMAKE_LD_FLAGS="-L/usr/lib" -DCMAKE_POLICY_VERSION_MINIMUM=3.5
make -j8
sudo make install
```
##### verify linkage with:
```bash
ldconfig -p | grep libsndfile
```

#### LIBFFTW3
```bash
wget https://www.fftw.org/fftw-3.3.10.tar.gz
tar -xzvf fftw-3.3.10.tar.gz
cd fftw-3.3.10/
CXXFLAGS="$CXXFLAGS -fPIC -I/usr/include" ./configure --prefix=/usr --disable-static --enable-threads --enable-sse2 --enable-avx --enable-avx2 LDFLAGS="-L/usr/lib"
make -j4
make check -j4
sudo make install
make clean

CXXFLAGS="$CXXFLAGS -fPIC -I/usr/include" ./configure --prefix=/usr --disable-static --enable-threads --enable-sse2 --enable-avx --enable-avx2 --enable-float LDFLAGS="-L/usr/lib"
make -j4
sudo make install
make clean

CXXFLAGS="$CXXFLAGS -fPIC -I/usr/include" ./configure --prefix=/usr --disable-static --enable-threads --enable-long-double LDFLAGS="-L/usr/lib -L/lib"
make -j4
sudo make install
```
##### verify with:
```bash
ldconfig -p | grep fftw3
```

#### LIBSOXR
```bash
wget https://sourceforge.net/projects/soxr/files/soxr-0.1.3-Source.tar.xz
tar -xf soxr-0.1.3-Source.tar.xz
cd soxr-0.1.3-Source/
mkdir build
cd build
cmake -S .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/usr -DBUILD_SHARED_LIBS=ON -DCMAKE_CXX_FLAGS="-fPIC -I/usr/include" -DCMAKE_LD_FLAGS="-L/usr/lib" -DCMAKE_PREFIX_PATH="/usr;/lib;/usr/lib" -DCMAKE_POLICY_VERSION_MINIMUM=3.5
make -j4
make check -j4
sudo make install
```
##### check with: 
```bash
ldd /usr/lib/libsoxr.so
```

#### LIBPORTAUDIO
```bash
wget https://files.portaudio.com/archives/pa_stable_v190700_20210406.tgz
tar -xf pa_stable_v190700_20210406.tgz
cd portaudio/
cd build
cmake -S .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/usr -DBUILD_SHARED_LIBS=ON -DCMAKE_CXX_FLAGS="-fPIC -I/usr/include" -DCMAKE_LD_FLAGS="-L/usr/lib" -DCMAKE_PREFIX_PATH="/usr;/lib;/usr/lib" -DPA_BUILD_SHARED=ON -DPA_BUILD_STATIC=OFF -DCMAKE_POLICY_VERSION_MINIMUM=3.5
make -j4
sudo make install
```

#### LIBSAMPLERATE
```bash
wget https://github.com/libsndfile/libsamplerate/releases/download/0.2.2/libsamplerate-0.2.2.tar.xz
tar -xf libsamplerate-0.2.2.tar.xz
cd libsamplerate-0.2.2
mkdir build
cd build
cmake -S .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/usr -DBUILD_SHARED_LIBS=ON -DCMAKE_CXX_FLAGS="-fPIC -I/usr/include" -DCMAKE_LD_FLAGS="-L/usr/lib" -DCMAKE_PREFIX_PATH="/usr;/lib;/usr/lib" -DCMAKE_POLICY_VERSION_MINIMUM=3.5
make -j4
sudo make install
```
##### confirm the main shared lib is in place: 
```bash
ls -l /usr/lib/libsamplerate.so*
```
##### confirm the header file is in place: 
```bash
ls -l /usr/include/samplerate.h
```
##### confirm the pkg-config file:
```bash
cat /usr/lib/pkgconfig/samplerate.pc
```

#### check e.g. libsndfile is includable and linkable with: 
```bash
ldconfig -p | grep libsndfile
ls /usr/include/sndfile.h

dpkg -l | grep libsndfile
# or: pacman -Qi libsndfile
```

#### LIBFFMPEG (full shared build)
```bash
wget https://ffmpeg.org/releases/ffmpeg-7.1.1.tar.xz
tar -xf ffmpeg-7.1.1.tar.xz
cd ffmpeg-7.1.1/
CXXFLAGS="$CXXFLAGS -fPIC -I/usr/include" LDFLAGS="-L/usr -L/lib -L/usr/lib" ./configure --prefix=/usr --disable-static --enable-shared --enable-gpl --disable-nonfree --enable-libsoxr --enable-libmp3lame --enable-libopus --enable-libvorbis --extra-cflags="-march=native"
make -j8
sudo make install
```

#### FFMPEG Licensing Mode Implications
- ***GPL***
  If you use --enable-gpl, your app must be GPL-compatible if redistributed.
- ***Nonfree***
  If you use --enable-nonfree, you can't redistribute FFmpeg binaries at all.
- ***Default (LGPL)***
  No --enable-gpl, no --enable-nonfree = most permissive but limited codec set.
- ***Encode to MP3***
  --enable-libmp3lame + --enable-gpl	Optional, MP3 is GPL-licensed
- ***Encode to AAC (FDK-AAC)***
  --enable-libfdk-aac + --enable-nonfree	Optional, highest quality AAC, non-free
