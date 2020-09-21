#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <errno.h>
#include <string.h>

#include <downlink.h>

int main(int argc, char **argv)
{
    int rc;
    FILE *fp;
    sfx_dl_encoded encoded_frame;
    sfx_dl_plain decoded_frame;
    sfx_commoninfo info;

    if (argc != 2) {
        printf("Usage: %s <path>\n", argv[0]);
        return 1;
    }
    fp = fopen(argv[1], "r");
    if (fp == NULL) {
        fprintf(stderr, "Could not open %s for reading: %s\n", argv[1],
            strerror(errno));
        return 1;
    }

    rc = fread(encoded_frame.frame, sizeof(uint8_t), SFX_DL_FRAMELEN, fp);
    if (rc != SFX_DL_FRAMELEN) {
        fprintf(stderr, "Could not read enough data: %s\n", strerror(errno));
        fclose(fp);
        return 1;
    }

    info.seqnum = 0x41;
    info.devid = 0xDEADBEEF;
    memset(&info.key, 0, 16 / sizeof(uint8_t));
    sfx_downlink_decode(encoded_frame, info, &decoded_frame);
    fclose(fp);
    return 0;
}
