//// 313531113 Dvir Asaf.
//#include <stdio.h>
//#include <string.h>
//#define KEEP "-keep"
//#define SWAP "-swap"
//#define MAC "-mac"
//#define MAC_SIGN "\r"
//#define UNIX "-unix"
//#define UNIX_SIGN "\n"
//#define WIN "-win"
//void copyFile(const char *fileName, const char *destFile);
//
///***************************************************************************************************
// Function Name:swapBytes
// Function input:short int* array
// Function Action:the function get an array of type short int and in each word it
// swap bytes Function output:none
// **************************************************************************************************/
//
//void swapBytes(const char *buff) {
//  char temp;       // temp varible
//  char *bytesBuff; // pointer of type char in size of one byte
//  int i = 0;       // index for loop
//  // as long we didnt finish go over the array
//  for (i = 0; i < sizeof(buff); i++) {
//    // typecast of buff[i] to char pointer
//    bytesBuff = (char *)(&(buff[i]));
//    // save the first byte in temp
//    temp = bytesBuff[0];
//    // update first byte
//    bytesBuff[0] = bytesBuff[1];
//    // finish swap action
//    bytesBuff[1] = temp;
//  }
//}
//
//void convert(const char *src, const char *trg, const char *f1, const char *f2,
//             const char *change) {
//  char buff[2];
//  FILE *source = fopen(src, "rb");
//  if (source == NULL) {
//    return;
//  }
//  FILE *target = fopen(trg, "wb");
//  if (target == NULL) {
//    return;
//  }
//  while (fread(buff, sizeof(buff), 1, source)) {
//    if (strcmp(change, SWAP) == 0) {
//      // if the text is not mac or unix sign.
//      if (strcmp(buff, MAC_SIGN) != 0 && strcmp(buff, UNIX_SIGN) != 0) {
//        swapBytes(buff);
//      }
//    } else if (strcmp(change, KEEP) == 0) {
//      continue;
//    }
//    if (strcmp(f1, MAC) == 0) {
//      if (strcmp(f2, UNIX) == 0) {
//        if (strcmp(buff, MAC_SIGN) == 0)
//          strcpy(buff, UNIX_SIGN);
//        fwrite(buff, sizeof(buff), 1, target);
//      } else if (strcmp(f2, WIN) == 0) {
//        if (strcmp(buff, MAC_SIGN) == 0)
//          fwrite(buff, sizeof(buff), 1, target);
//        strcpy(buff, UNIX_SIGN);
//        fwrite(buff, sizeof(buff), 1, target);
//      } else {
//        copyFile(src, trg);
//      }
//    }
//    if (strcmp(f1, UNIX) == 0) {
//      if (strcmp(f2, MAC) == 0) {
//        if (strcmp(buff, UNIX_SIGN) == 0)
//          strcpy(buff, MAC_SIGN);
//        fwrite(buff, sizeof(buff), 1, target);
//      } else if (strcmp(f2, WIN) == 0) {
//        if (strcmp(buff, UNIX_SIGN) == 0)
//          strcpy(buff, MAC_SIGN);
//        fwrite(buff, sizeof(buff), 1, target);
//        strcpy(buff, UNIX_SIGN);
//        fwrite(buff, sizeof(buff), 1, target);
//      } else {
//        copyFile(src, trg);
//      }
//    }
//    // TODO: finish the if condition
//    // convert win sign to mac sign.
//    if (strcmp(f1, WIN) == 0) {
//      if (strcmp(f2, MAC) == 0) {
//        if (strcmp(buff, MAC_SIGN) == 0) {
//          strcpy(buff, MAC_SIGN);
//          fwrite(buff, sizeof(buff), 1, target);
//          strcpy(buff, UNIX_SIGN);
//          fwrite(buff, sizeof(buff), 1, target);
//        }
//      } else if (strcmp(f2, UNIX) == 0) {
//        strcpy(buff, MAC_SIGN);
//        fwrite(buff, sizeof(buff), 1, target);
//        strcpy(buff, UNIX_SIGN);
//        fwrite(buff, sizeof(buff), 1, target);
//      } else {
//        copyFile(src, trg);
//      }
//    }
//  }
//}
//
///***************************************************************************************************
// Function Name: copyFile
// Function input: input & output files names
// Function Action: this function just copy a given file to another
// Function output:none
// **************************************************************************************************/
//
//void copyFile(const char *fileName, const char *destFile) {
//  // buffer for reading chars
//  char buff[4];
//  // save the value fread function return - number of elements read
//  size_t n;
//  FILE *in, *out;
//  in = fopen(fileName, "rb"); // open both files in binary mode
//  out = fopen(destFile, "wb");
//  // as long as we didnt finish reading file
//  while ((n = fread(buff, 1, sizeof(buff), in)) != 0) {
//    fwrite(buff, 1, n, out); // copy what fread read to the dest file
//  }
//  fclose(in); // close both files
//  fclose(out);
//}
//
///***************************************************************************************************
// Function Name: firstOption
// Function input: input & output files names
// Function Action: function for the first option - create a copy of given file
// Function output: none
// **************************************************************************************************/
//
//void firstOption(const char *fileName, const char *destFile) {
//  // if copyFile function succeed (the surce file exists)
//  copyFile(fileName, destFile);
//}
//
///***************************************************************************************************
// Function Name: secondOption
// Function input: input & output files names
// Function Action: function for the first option - create a copy of given file
// Function output: none
// **************************************************************************************************/
//
//void secondOption(const char *fileName, const char *destFile, const char *flag1,
//                  const char *flag2) {
//  convert(fileName, destFile, flag1, flag2, KEEP);
//}
//
///***************************************************************************************************
// Function Name: thirdOption
// Function input: input & output files names
// Function Action: function for the first option - create a copy of given file
// Function output: none
// **************************************************************************************************/
//
//void thirdOption(const char *fileName, const char *destFile, const char *flag1,
//                 const char *flag2, const char *swapOrNot) {
//  convert(fileName, destFile, flag1, flag2, swapOrNot);
//}
//
///***************************************************************************************************
// Function Name: main
// Function input: args is number of user input, when argv[0] is the function name
// Function Action: this is the main function
// Function output: 0 - terminate program
// **************************************************************************************************/
//
//int main(int argc, char **argv) {
//  int size = argc;
//  switch (size) {
//  case 3:
//    firstOption(argv[1], argv[2]);
//    break;
//  case 5:
//    secondOption(argv[1], argv[2], argv[3], argv[4]);
//    break;
//  case 6:
//    thirdOption(argv[1], argv[2], argv[3], argv[4], argv[5]);
//    break;
//  default:
//    break;
//  }
//  return 0;
//}