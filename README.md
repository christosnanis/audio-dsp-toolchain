# audio-dsp-toolchain
A build-from-source audio DSP toolchain installation guide (assumes systemd-linux with GCC 16)

### If you have finished with installing from sources, test with:
```bash
# compile with:
g++ test_audio.cpp -o test_audio -lsndfile
# or with: g++ test_audio.cpp -o test_audio $(pkg-config --cflags --libs sndfile)
# and run with:
./test_audio
# it should give:
File created successfully.
```

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


## (OPTIONAL) Install Audacity from sources

### Download Audacity from Linux sources (don't need to choose an AppImage file, just the audacity sources):
```bash
# from:
https://www.fosshub.com/Audacity-old.html

# example:
wget https://github.com/audacity/audacity/releases/download/Audacity-3.7.2/audacity-sources-3.7.2.tar.gz
tar -xzvf audacity-sources-3.7.2.tar.gz
cd audacity-sources-3.7.2
```

### Then extract and do:
```bash
sudo pacman -S nasm
sudo pacman -S --needed wxwidgets-common wxwidgets-gtk3 rapidjson catch2-v2
sudo pacman -S --needed lilv lv2 serd sord sratom suil vamp-plugin-sdk
sudo pacman -S portmidi libid3tag opusfile

python3 -m venv .env
source .env/bin/activate
pip install conan
mkdir build
cd build/

nano ../libraries/lib-note-track/CMakeLists.txt
# and add above audacity_library(...):
find_package(PortMidi CONFIG REQUIRED)
if(TARGET PortMidi::portmidi AND NOT TARGET portmidi::portmidi)
  add_library(portmidi::portmidi ALIAS PortMidi::portmidi)
endif()

cmake -S .. -B build-system -Daudacity_lib_preference=system -Daudacity_use_midi=system -Daudacity_has_vst3=OFF -DCMAKE_C_FLAGS=-DPROTOTYPES -DPortMidi_DIR=/usr/lib/cmake/PortMidi -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/usr -DBUILD_SHARED_LIBS=ON -DCMAKE_CXX_FLAGS="-fPIC -I/usr/include" -DCMAKE_LD_FLAGS="-L/usr/lib" -DCMAKE_PREFIX_PATH="/usr;/lib;/usr/lib" -DCMAKE_POLICY_VERSION_MINIMUM=3.5

cmake --build build-system -j8
sudo cmake --install build-system
audacity
```

#### Possibly Supported Export Types:
- Wav 
- Mp3
- FLAC
- Ogg Vorbis
- M4A (AAC) Files (FFmpeg)
- AC3 Files (FFmpeg)
- AMR (narrowband) Files (FFmpeg)
- WMA (version 2) Files FFmpeg
- Custom FFmpeg Export
- Mp2 Files

#### Channels: 
- Mono 
- Stereo

#### Possibly Supported Sample Rates: 
- 8000Hz 
- 11025Hz 
- 16000Hz 
- 22050Hz 
- 32000Hz 
- 44100Hz 
- 48000Hz 
- 88200Hz 
- 96000Hz 
- 176400Hz 
- 192000Hz 
- 352800Hz 
- 384000Hz

#### Possibly Supported Encodings: 
- Signed 16-bit PCM 
- Signed 24-bit PCM 
- Signed 32-bit PCM 
- Unsinged 8-bit PCM 
- 32-bit float 
- 64-bit float 
- U-LAW 
- A-LAW 
- IMA ADPCM 
- Microsoft ADPCM 
- GSM6.10 
- 32Kbps G721 ADPCM 
- 16Kbps NMS ADPCM 
- 24Kbps ADPCM 
- 32Kbps NMS ADPCM
