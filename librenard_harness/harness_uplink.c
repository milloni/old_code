#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <errno.h>
#include <string.h>

#include <uplink.h>

int main(int argc, char **argv)
{
    int rc, i;
    FILE *fp;
    sfx_ul_encoded encoded_frame;
    sfx_ul_plain decoded_frame;
    sfx_uld_err sfx_err;
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

    for (i = 0; i < 3; i++) {
        rc = fread(encoded_frame.frame[i], sizeof(uint8_t), SFX_UL_MAX_FRAMELEN, fp);
        if (rc != SFX_UL_MAX_FRAMELEN) {
            fprintf(stderr, "Could not read enough data: %s\n", strerror(errno));
            fclose(fp);
            return 1;
        }
    }
    rc = fread(&encoded_frame.framelen_nibbles, sizeof(uint8_t), 1, fp);
    if (rc != 1) {
        fprintf(stderr, "Could not read enough data: %s\n", strerror(errno));
        fclose(fp);
        return 1;
    }

    info.seqnum = 0x41;
    info.devid = 0xDEADBEEF;
    memset(&info.key, 0, 16 / sizeof(uint8_t));
    sfx_err = sfx_uplink_decode(encoded_frame, &decoded_frame, &info, 0);
    if (sfx_err != SFX_ULD_ERR_NONE) {
        fprintf(stderr, "Invalid frame\n");
        return 1;
    }
    fclose(fp);
    return 0;
}
