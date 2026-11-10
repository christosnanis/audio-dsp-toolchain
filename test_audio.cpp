#ifdef __cplusplus
extern "C" {
#endif
#include <stdio.h>
#include <sndfile.h>
#ifdef __cplusplus
}
#endif

int main() {
  SF_INFO sfinfo;
  SNDFILE *sndfile;

  sfinfo.samplerate = 44100;
  sfinfo.channels = 2;
  sfinfo.format = SF_FORMAT_WAV | SF_FORMAT_PCM_16;

  sndfile = sf_open("test.wav", SFM_WRITE, &sfinfo);

  if (sndfile == NULL) {
    printf("Error opening file: %s\n", sf_strerror(NULL));
    return 1;
  }

  sf_close(sndfile);
  printf("File created successfully.\n");
  return 0;
}
