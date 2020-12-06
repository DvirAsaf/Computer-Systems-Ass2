// 313531113 Dvir Asaf.
#include "string.h"
#include <stdio.h>
#define UNIX_SIGN '\n'
#define MAC_SIGN '\r'
#define WIN "-win"
#define UNIX "-unix"
#define MAC "-mac"
enum endLinePerSystem { Unix, Mac, windows, Illegal };
enum endLinePerSystem getendLine(char *flag);
int needToChangeBytes(char *flag);
void endLineOfWindows(char *in, char *out, enum endLinePerSystem flag1,
                      enum endLinePerSystem flag2);
void changeendLineOfWindows(char *in, char *out, enum endLinePerSystem flag1,
                            enum endLinePerSystem flag2);
char endLineFlag(enum endLinePerSystem flag);
void copyFile(char *in, char *out, int needToSwap);
int isBigEndian(char buff[]);
int isInputValid(char *fileName);
void changeEndLineOfMacAndUnix(char *in, char *out, enum endLinePerSystem flag1,
                               enum endLinePerSystem flag2, int needToChange);
///***************************************************************************************************
// Function Name: main
// Function input: files and flag and action
// Function Action: if given 3 valid argv so go to first case,
//                  if given 5 valid argv so go to second case,
//                  if given 6 valid argv so go to third case.else return 0
// Function output: return 0.
// **************************************************************************************************/
int main(int argc, char *argv[]) {
  switch (argc) {
  case 3:
    if (isInputValid(argv[1]) == 1 && isInputValid(argv[2]) == 1) {
      copyFile(argv[1], argv[2], 0);
    }
    break;
  case 5: {
    enum endLinePerSystem flag1 = getendLine(argv[3]);
    enum endLinePerSystem flag2 = getendLine(argv[4]);
    if (flag1 != Illegal && flag2 != Illegal) {
      if (flag1 != flag2) {
        if (!(flag1 == windows || flag2 == windows)) {
          changeEndLineOfMacAndUnix(argv[1], argv[2], flag1, flag2, 0);
        } else if (flag1 == windows || flag2 == windows) {
          endLineOfWindows(argv[1], argv[2], flag1, flag2);
        }
        break;
      } else {
        copyFile(argv[1], argv[2], 0);
        return 0;
      }
    } else {
      return 0;
    }
  }
  case 6: {
    enum endLinePerSystem flag1 = getendLine(argv[3]);
    enum endLinePerSystem flag2 = getendLine(argv[4]);
    if (flag1 != Illegal && flag2 != Illegal) {
      int needToChange = needToChangeBytes(argv[5]);
      if (needToChange != -1) {
        if (!(flag1 == flag2)) {
          if (flag1 == windows || flag2 == windows) {
            if (flag1 == windows || flag2 == windows) {
              if (!needToChange) {
                endLineOfWindows(argv[1], argv[2], flag1, flag2);
              } else {
                changeendLineOfWindows(argv[1], argv[2], flag1, flag2);
              }
            }
          } else {
            changeEndLineOfMacAndUnix(argv[1], argv[2], flag1, flag2,
                                      needToChange);
          }
          break;
        } else {
          copyFile(argv[1], argv[2], needToChange);
          return 0;
        }
      } else {
        return 0;
      }
    } else {
      return 0;
    }
  }
  }
  return 0;
}
///***************************************************************************************************
// Function Name: copyFile
// Function input: source file, target file and int if need to be swap bytes.
// Function Action: copy from source to target.
// Function output: none.
// **************************************************************************************************/
void copyFile(char *in, char *out, int needToSwap) {
  FILE *source = fopen(in, "rb");
  if (source != NULL) {
    FILE *target = fopen(out, "wb");
    if (target != NULL) {
      char buff[2];
      while ((fread(buff, sizeof(buff), 1, source) != 0)) {
        if (!needToSwap) {
          fwrite(buff, sizeof(buff), 1, target);
        } else {
          char help = buff[0];
          buff[0] = buff[1];
          buff[1] = help;
          fwrite(buff, sizeof(buff), 1, target);
        }
      }
      // close the files
      fclose(target);
      fclose(source);
    }
  }
}
///***************************************************************************************************
// Function Name: endLineFlag
// Function input: flag system
// Function Action: choose the right end line system according to input.
// Function output: return char of end line system
// **************************************************************************************************/
char endLineFlag(enum endLinePerSystem flag) {
  char endLine;
  switch (flag) {
  case Unix:
    endLine = UNIX_SIGN;
    break;
  case Mac:
    endLine = MAC_SIGN;
    break;
  }
  return endLine;
}
///***************************************************************************************************
// Function Name: isInputValid
// Function input: file
// Function Action: if the given file have '.' so its valid else not valid
// Function output: 1 if valid else 0
// **************************************************************************************************/
int isInputValid(char *fileName) {
  int fileNameSize = strlen(fileName);
  for (int i = 0; i < fileNameSize; i++) {
    if (fileName[i] == '.')
      return 1;
  }
  return 0;
}
///***************************************************************************************************
// Function Name: endLinePerSystem
// Function input: flag system
// Function Action: choose the right flag system according to input.
// Function output: the name of flag system
// **************************************************************************************************/
enum endLinePerSystem getendLine(char *flag) {
  enum endLinePerSystem c;
  // make compare between inpute to our enum
  if (strcmp(flag, WIN) == 0) {
    c = windows;
  } else if (strcmp(flag, UNIX) == 0) {
    c = Unix;
  } else if (strcmp(flag, MAC) == 0) {
    c = Mac;
  } else {
    // illegal param
    c = Illegal;
  }
  return c;
}
///***************************************************************************************************
// Function Name: changeEndLineOfMacAndUnix
// Function input: source file, target file, source flag, target flag and int if
// need to swap bytes. Function Action: change the end line from mac to unix or
// unix to mac. Function output: none
// **************************************************************************************************/
void changeEndLineOfMacAndUnix(char *in, char *out, enum endLinePerSystem flag1,
                               enum endLinePerSystem flag2, int needToChange) {
  FILE *source = fopen(in, "rb");
  if (source != NULL) {
    FILE *target = fopen(out, "wb");
    if (target != NULL) {
      char endLine1 = endLineFlag(flag1);
      char endLine2 = endLineFlag(flag2);
      char buff[2];
      int count = 0;
      int endian = 0;
      while ((fread(buff, sizeof(buff), 1, source) != 0)) {
        if (count != 0) {
        } else {
          endian = isBigEndian(buff);
          count++;
        }
        if (!needToChange) {
          if (buff[endian] != endLine1 || buff[!endian] != '\0') {
          } else {
            buff[endian] = endLine2;
            buff[!endian] = '\0';
          }
        } else {
          if (buff[endian] != endLine1 || buff[!endian] != '\0') {
            char temp = buff[0];
            buff[0] = buff[1];
            buff[1] = temp;
          } else {
            buff[!endian] = endLine2;
            buff[endian] = '\0';
          }
        }
        fwrite(buff, sizeof(buff), 1, target);
      }
      fclose(target);
      fclose(source);
    }
  }
}
///***************************************************************************************************
// Function Name: needToChangeBytes.
// Function input: char
// Function Action: if the char is '-swap' return 1 if the char is '-keep'
// return 0. Function output:
// **************************************************************************************************/
int needToChangeBytes(char *flag) {
  return strcmp(flag, "-swap") == 0 ? 1 : strcmp(flag, "-keep") == 0 ? 0 : -1;
}
///***************************************************************************************************
// Function Name: endLineOfWindows
// Function input: source file, target file, source flag, target flag
// Function Action: change end line of source file from windows to mac and unix,
// and from unix and mac to windows.
//                  if the argc[5] is KEEP
// Function output: none
// **************************************************************************************************/

void endLineOfWindows(char *in, char *out, enum endLinePerSystem flag1,
                      enum endLinePerSystem flag2) {
  FILE *source = fopen(in, "rb");
  if (source != NULL) {
    FILE *target;
    target = fopen(out, "wb");
    if (target != NULL) {
      char endLine = endLineFlag(flag1);
      char buff[2];
      int count = 0;
      int endian = 0;
      while ((fread(buff, sizeof(buff), 1, source) != 0)) {
        if (count != 0) {
        } else {
          endian = isBigEndian(buff);
          count++;
        }
        // unix\mac to windows
        if (flag1 == windows || flag2 != windows) {
          if (flag1 != windows || flag2 != Unix) {
            if (flag1 == windows && flag2 == Mac) {
              // windows to mac
              if (buff[endian] != UNIX_SIGN || buff[endian] == MAC_SIGN) {
                fwrite(buff, sizeof(buff), 1, target);
              }
            }
          } else {
            // windows to unix
            if (buff[endian] != UNIX_SIGN && buff[endian] == MAC_SIGN)
              continue;
            fwrite(buff, sizeof(buff), 1, target);
          }
        } else {
          // mac to windows
          if (buff[endian] != endLine) {
          } else {
            buff[endian] = UNIX_SIGN;
            buff[!endian] = '\0';
            char help[2];
            help[endian] = MAC_SIGN;
            help[!endian] = '\0';
            fwrite(help, sizeof(help), 1, target);
          }
          fwrite(buff, sizeof(buff), 1, target);
        }
      }
      // close the files
      fclose(target);
      fclose(source);
    }
  }
}
///***************************************************************************************************
// Function Name: changeendLineOfWindows
// Function input: source file, target file, source flag, target flag
// Function Action: change end line of source file from windows to mac and unix,
// and from unix and mac to windows.
//                 if the argc[5] is SWAP
// Function output:
// **************************************************************************************************/
void changeendLineOfWindows(char *in, char *out, enum endLinePerSystem flag1,
                            enum endLinePerSystem flag2) {
  FILE *source = fopen(in, "rb");
  if (source == NULL) {
    return;
  }
  FILE *target = fopen(out, "wb");
  if (target == NULL) {
    return;
  }
  char endLine = endLineFlag(flag1);
  char buff[2];
  int count = 0;
  int endian = 0;
  while ((fread(buff, sizeof(buff), 1, source) != 0)) {
    if (count == 0) {
      endian = isBigEndian(buff);
      count++;
    }
    // unix\mac to windows
    if (flag1 != windows && flag2 == windows) {
      // mac/unix to windows
      if (buff[endian] == endLine) {
        buff[!endian] = UNIX_SIGN;
        buff[endian] = '\0';
        char temp[2];
        temp[!endian] = MAC_SIGN;
        temp[endian] = '\0';
        fwrite(temp, sizeof(temp), 1, target);
      } else {
        // swap other chars
        char temp = buff[0];
        buff[0] = buff[1];
        buff[1] = temp;
      }
      fwrite(buff, sizeof(buff), 1, target);
    } else {
      if (flag1 != windows || flag2 != Unix) {
        if (flag1 == windows && flag2 == Mac) {
          // windows to mac
          if (buff[endian] != UNIX_SIGN || buff[endian] == MAC_SIGN) {
            char temp1 = buff[0];
            buff[0] = buff[1];
            buff[1] = temp1;
            fwrite(buff, sizeof(buff), 1, target);
          }
        }
      } else {
        // windows to unix
        if (buff[endian] == UNIX_SIGN || buff[endian] != MAC_SIGN) {
          char temp = buff[0];
          buff[0] = buff[1];
          buff[1] = temp;
          fwrite(buff, sizeof(buff), 1, target);
        }
      }
    }
  }
  // close the files
  fclose(target);
  fclose(source);
}
///***************************************************************************************************
// Function Name: isBigEndian.
// Function input: buffer.
// Function Action: check if the system is big or little endian.
// Function output: 1 for big and 0 for little.
// **************************************************************************************************/
int isBigEndian(char buff[]) {
  int endian = 0;
  unsigned short int r = (unsigned short int)buff[0];
  if (((unsigned short int)0xfffe == r)) {
    endian = 1;
  }
  return endian;
}
