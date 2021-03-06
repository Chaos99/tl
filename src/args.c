/**
 * @file    args.c
 * @brief   Parse and process command line arguments.
 * @author  Ryan Jacobs <ryan.mjacobs@gmail.com>
 * @date    March 19, 2015
 * @bug     No known bugs.
 */

#include "args.h"

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <getopt.h>

enum {
    OPT_VERSION
};

static const char *version_msg =
    "tl v0.03-alpha\n\n"

    "Compiled : "_TL_COMPILE_DATE"\n"
    "  Commit : "_TL_COMMIT_SHA"\n"
    "  Static : "_TL_STATIC_BUILD"\n"

    "  CFLAGS : "_TL_CFLAGS"\n"
    " LDFLAGS : "_TL_LDFLAGS"\n"

    "\n"
    "Copyright (C) 2015 Ryan Jacobs\n";

static const char *help_msg =
    "Usage: %s [-h] [options...]\n"
    "Record and render timelapses.\n\n"
    "  -f,   --frames             Number of frames to record. 0 means infinite\n"
    "  -d,   --delay              Delay in seconds between each screenshot\n"
    "  -r,   --framerate          Set playback fps for the encoded video\n"
    "  -o,   --output             Output filename\n"
    "  -D,   --display            X display name, default is :0\n"
    "  -h,   --help               Display this help and exit\n"
    "        --version            Display version information and exit\n\n"
    "Report bugs to <ryan.mjacobs@gmail.com>\n";

static const struct option long_options[] = {
    { "frames",      optional_argument, NULL, 'f'          },
    { "delay",       optional_argument, NULL, 'd'          },
    { "rate",        optional_argument, NULL, 'r'          },
    { "output",      optional_argument, NULL, 'o'          },
    { "display",     optional_argument, NULL, 'D'          },
    { "help",        optional_argument, NULL, 'h'          },
    { "version",     no_argument,       NULL,  OPT_VERSION },
    { NULL, 0, NULL, 0 }
};

static int file_exists(const char *fname) {
    FILE *fp = fopen(fname, "r");

    if (fp) {
        fclose(fp);
        return 1;
    } else {
        return 0;
    }
}

struct args_t parse_args(int argc, char **argv) {
    struct args_t args = {
        .frames         = 0,       // aka infinite
        .delay          = 1000000, // 1s
        .framerate      = 15,
        .fname          = "timelapse.mp4",
        .x_display_name = ":0"
    };

    /* decide on the default filename */
    if (file_exists(args.fname)) {
        unsigned int i;

        for (i = 1; i < UINT_MAX; i++) {
            int len = snprintf(NULL, 0, "timelapse_%u.mp4", i);
            args.fname = malloc(++len);
            snprintf(args.fname, len, "timelapse_%u.mp4", i);

            if (!file_exists(args.fname))
                break;

            free(args.fname);
        }
    }

    char c;
    while ((c = getopt_long(argc, argv, "f:d:r:o:D:h", long_options, NULL)) != -1) {
        switch (c) {
            case 'f':
                if ((args.frames = atoi(optarg)) < 0) {
                    fprintf(stderr, "error: '%s' is not a valid number of frames\n", optarg);
                    exit(1);
                }
                break;
            case 'd':
                if ((args.delay = (unsigned int) (atof(optarg)*1000000.0)) < 0) {
                    fprintf(stderr, "error: '%s' is not a valid delay interval\n", optarg);
                    exit(1);
                }
                break;
            case 'r':
                if ((args.framerate = atoi(optarg)) <= 0) {
                    fprintf(stderr, "error: '%s' is not a valid framerate\n", optarg);
                    exit(1);
                }
                break;
            case 'o':
                args.fname = optarg;
                break;
            case 'h':
                fprintf(stdout, help_msg, argv[0]);
                exit(0);
                break;
            case 'D':
                args.x_display_name = optarg;
                break;
            case OPT_VERSION:
                fputs(version_msg, stdout);
                exit(0);
                break;
            default:
                fprintf(stderr, "Try `%s --help` for more information.\n", argv[0]);
                exit(1);
                break;
        }
    }

    return args;
}
