// 313531113 Dvir Asaf.
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
  int argument_size = argc;
  char buffer[2];
  if (argument_size == 3) {
    // reading the input given file.
    FILE *inPutFile = fopen(argv[1], "rb");
    FILE *outPutFile = fopen(argv[2], "wb");
    while (fread(buffer, sizeof(buffer), 1, inPutFile)) {
      fwrite(buffer, sizeof(buffer), 1, outPutFile);
    }
    fclose(inPutFile);
    fclose(outPutFile);
  }
  if (argument_size == 5) {
    FILE *inPutFile = fopen(argv[1], "rb");
    FILE *outPutFile = fopen(argv[2], "wb");
    char *argument3 = argv[3];
    char *argument4 = argv[4];
    // continue
    while (fread(buffer, sizeof(buffer), 1, inPutFile)) {
      // if the given flag is mac.
      if (!(strcmp(argument3, "-mac"))) {
        // if the return flag is unix.
        if (!(strcmp(argument4, "-unix"))) {
          // find \r in the text.
          if (!(strcmp(buffer, "\r"))) {
            // change \r to \n.
            strcpy(buffer, "\n");
            // add the \n to the rext.
            fwrite(buffer, sizeof(buffer), 1, outPutFile);
          }
          // if the return flag is win.
        } else if (!(strcmp(argument4, "-win"))) {
          // find \r in the text.
          if (!(strcmp(buffer, "\r"))) {
            // change \r to \n\r.
            strcpy(buffer, "\r");
            // add \r to the text.
            fwrite(buffer, sizeof(buffer), 1, outPutFile);
            strcpy(buffer, "\n");
            // add \n to the text.
            fwrite(buffer, sizeof(buffer), 1, outPutFile);
          }
        }
        // if the given flag is unix.
      } else if (!(strcmp(argument3, "-unix"))) {
        // if the return flag is win.
        if (!(strcmp(argument4, "-win"))) {
          // find \r in the text.
          if (!(strcmp(buffer, "\n"))) {
            // change \r to \n\r.
            strcpy(buffer, "\r");
            // add the \r to the text.
            fwrite(buffer, sizeof(buffer), 1, outPutFile);
            strcpy(buffer, "\n");
            // add \n to the text.
            fwrite(buffer, sizeof(buffer), 1, outPutFile);
          }
          // if the return flag is mac.
        } else if (!(strcmp(argument4, "-mac"))) {
          // find \n in the text.
          if (!(strcmp(buffer, "\n"))) {
            // change \n to \r.
            strcpy(buffer, "\r");
            // add the \r to the text.
            fwrite(buffer, sizeof(buffer), 1, outPutFile);
          }
        }
        // if the given flag is win.
      } else if (!(strcmp(argument3, "-win"))) {
        // if the return flag is mac.
        if (!(strcmp(argument4, "-mac"))) {
          // find \n\r in the text.
          if (!(strcmp(buffer, "\r"))) {
            // change \n\r to \r.
            strcpy(buffer, "\r");
            // add the \r to the text.
            fwrite(buffer, sizeof(buffer), 1, outPutFile);
          }
        }
        // if the return flag is unix.
        else if (!(strcmp(argument4, "-unix"))) {
          // find \n\r in the text.
          if (!(strcmp(buffer, "\n\r"))) {
            // change \n\r to \n.
            strcpy(buffer, "\n");
            // add the \n to the rext.
            fwrite(buffer, sizeof(buffer), 1, outPutFile);
          }
        }
      }
      else{
        fwrite(buffer, sizeof(buffer), 1, outPutFile);
      }
    }
    fclose(inPutFile);
    fclose(outPutFile);
  }
  return 0;
}