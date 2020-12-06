//// 313531113 Dvir Asaf.
//#include <stdio.h>
//#include <string.h>
//#define KEEP "-keep"
//#define SWAP "-swap"
//#define END_UNIX '\n'
//#define END_MAC '\r'
//#define NULL_TEMINATOR '\0'
//#define SWAP "-swap"
//#define KEEP "-keep"
//
//void copyFile(const char *fileName, const char *destFile);
//
///**
// * isBigEndian function.
// * @param buffer - the readed char.
// * @return 1 if big endiann, o othewise.
// */
//int isBigEndian(char buffer[]) {
//  int isBig = 0;
//  unsigned short int r = (unsigned short int) buffer[0];
//  if ((r == (unsigned short int)0xfffe)) {
//    isBig = 1;
//  }
//  return isBig;
//}
//
///***************************************************************************************************
// Function Name:swapBytes
// Function input:short int* array
// Function Action:the function get an array of type short int and in each word it
// swap bytes Function output:none
// **************************************************************************************************/
//
//void SwapCharsBytes(char* buffer){
//  char temp = buffer[0];
//  buffer[0] = buffer[1];
//  buffer[1] = temp;
//}
//
//void applyChange(char* needChange, const char* flag ,FILE* dest_file) {
//  //help buffer
//  char help[2];
//  //to format of unix
//  if(strcmp(flag,"-unix")== 0) {
//    needChange[0] = END_UNIX;
//    fwrite(needChange,sizeof(char), 1,dest_file);
//  }//to format of mac
//  else if(strcmp(flag,"-mac")== 0) {
//    needChange[0] = END_MAC;
//    fwrite(needChange,sizeof(char), 1,dest_file);
//  }//to format of windows
//  else if(strcmp(flag,"-win")== 0) {
//    //end line in windows consists of two characters(of two bytes each)
//    needChange[0] = END_MAC;
//    fwrite(needChange,sizeof(char), 1,dest_file);
//    help[0]=NULL_TEMINATOR;
//    help[1] = 0;
//    //in c array containing the characters terminated with a null character
//    fwrite(help, sizeof(char),1,dest_file);
//    needChange[0] = END_UNIX;
//    fwrite(needChange,sizeof(char), 1,dest_file);
//  }
//}
//
//void applyChangeSwap(char* needChange, const char* flag ,FILE* dest_file) {
//  //help buffer
//  char help[2];
//  //to format of unix
//  if(strcmp(flag,"-unix")== 0) {
//    needChange[0] = END_UNIX;
//    SwapCharsBytes(needChange);
//    fwrite(needChange,sizeof(help), 1,dest_file);
//  }//to format of mac
//  else if(strcmp(flag,"-mac")== 0) {
//    needChange[0] = END_MAC;
//    SwapCharsBytes(needChange);
//    fwrite(needChange,sizeof(help), 1,dest_file);
//  }//to format of windows
//  else if(strcmp(flag,"-win")== 0) {
//    help[0] = END_MAC;
//    SwapCharsBytes(help);
//    fwrite(help,sizeof(help ), 1,dest_file);
////    end line in windows consists of two characters(of two bytes each)
//    help[0] = END_UNIX;
//    help[1] = 0;
//    SwapCharsBytes(help);
//    fwrite(help,sizeof(help ), 1,dest_file);
//  }
//}
//
//void applyChangeSwap1(char* needChange, const char* flag ,FILE* dest_file) {
//  //help buffer
//  char help[2];
//  //to format of unix
//  if(strcmp(flag,"-unix") == 0) {
//    needChange[1] = END_UNIX;
//    SwapCharsBytes(needChange);
//    fwrite(needChange,sizeof(help), 1,dest_file);
//  }//to format of mac
//  else if(strcmp(flag,"-mac")== 0) {
//    needChange[1] = END_MAC;
//    SwapCharsBytes(needChange);
//    fwrite(needChange,sizeof(help), 1,dest_file);
//  }//to format of windows
//  else if(strcmp(flag,"-win")== 0) {
//    needChange[1] = END_MAC;
//    SwapCharsBytes(needChange);
//    fwrite(needChange,sizeof(help), 1,dest_file);
//    //end line in windows consists of two characters(of two bytes each)
//    needChange[1] = END_UNIX;
//    SwapCharsBytes(needChange);
//    fwrite(needChange,sizeof(help), 1,dest_file);
//  }
//}
//
//int checkEndLine(char* buff,char check,const char* flag2,FILE* dest_file ){
//  //check if the current buffer consists new line charcter in binary
//  if(buff[0] ==check){
//    //call applyChange function to thake care of the case//
//    applyChange(buff,flag2,dest_file);
//    return 1;
//  }
//  return 0;
//}
//
//int checkEndLineAndSwap(char* buff,char check,const char* flag2,FILE* dest_file ) {
//  //check if the current buffer consists new line character in binary
//  if(buff[0] == check) {
//    //call applyChange function to thake care of the case//
//    applyChangeSwap(buff,flag2,dest_file);
//    return 1;
//  }
//  else if(buff[1] == check){
//    applyChangeSwap1(buff,flag2,dest_file);
//    return 1;
//  }
//  return 0;
//}
//
//void convertAndKeep(const char *fileName, const char *destFile, const char *flag1, const char *flag2) {
//  //buffer to save what we read from the file
//  char buff[2];
//  //help buffer
//  char buffCheck[2];
//  int endian = 0;
//  //pointer to the input & output files
//  //open both files in binary mode
//  FILE *source = fopen(fileName,"rb");
//  FILE *target = fopen(destFile, "wb");
//  if (fread(buff, sizeof(buff), 1, source)) {
//      if (isBigEndian(buff)){
//        endian = 1;
//      }
//      else endian = 0;
////    SwapCharsBytes(buff);
//    fwrite(buff, sizeof(buff), 1, target);
//  }
//  //as long as we didnt finish reading file we keep reading one element in size of short int (2 bytes) each time
//  while ((fread(buff , sizeof(char), 1,source) )!= 0){
//    //copy from unix to...
//    if(strcmp(flag1,"-unix")==0) {
//      //call checkEndLine function which takes care of the case we need convert to windows format
//      if(checkEndLine(buff,END_UNIX,flag2,target)==0){
//        //if this is no end line continue copy file
//        if (endian){
//          SwapCharsBytes(buff);
//        }
//        fwrite(buff,sizeof(char), 1,target);
//      }
//    }//copy from mac to...
//    else if (strcmp(flag1,"-mac")==0){
//      //call checkEndLine function which takes care of the case we need convert to windows format
//      if(checkEndLine(buff,END_MAC,flag2,target)==0){
//        //if this is no end line continue copy file
//        if (endian){
//          SwapCharsBytes(buff);
//        }
//        fwrite(buff,sizeof(char), 1,target);
//      }
//    }//from win to
//    else if(strcmp(flag1,"-win")==0){
//      //check if current byte equals to '\r'
//      if(buff[0] == END_MAC){
//        //in c array containing the characters terminated with a null character
//        //TODO:
//        fread(buff , sizeof(char), 1,source);//check \0
//        //first check if it equals to '/r'
//        if(fread(buff , sizeof(char), 1,source) > 0){//now check if there is more bytes to read
//          //call checkEndLine function which takes care of the case we need convert to windows format
//          if(checkEndLine(buff,END_UNIX,flag2,target)==0) {
//            buffCheck[0]=END_MAC;
//            buffCheck[1] = 0;
//            if (endian){
//              SwapCharsBytes(buff);
//            }
//            fwrite(buffCheck,sizeof(char), 1,target);
//            //in c array containing the characters terminated with a null character
//            buffCheck[0]=NULL_TEMINATOR;
//            buffCheck[1] = 0;
//            if (endian){
//              SwapCharsBytes(buff);
//            }
//            fwrite(buffCheck,sizeof(char), 1,target);
//            //buffCheck[1]=buff[0];
//            buff[1] = 0;
//            if (endian){
//              SwapCharsBytes(buff);
//            }
//            fwrite(buff,sizeof(char), 1,target);
//          }//if this is no end line continue copy file
//        }else {
//          buff[1] = 0;
//          if (endian){
//            SwapCharsBytes(buff);
//          }
//          fwrite(buff, sizeof(char), 1, target);
//        }
//      }else {
//        buff[1] = 0;
//        if (endian){
//          SwapCharsBytes(buff);
//        }
//        fwrite(buff, sizeof(char), 1, target);
//      }
//    }
//  }
//  fclose(source);
//  fclose(target);//close both file after we done
//}
//
//void convertAndSwap(const char *fileName, const char *destFile, const char *flag1, const char *flag2) {
//  //buffer to save what we read from the file
//  char buff[2];
//  //help buffer
//  char buffCheck[2];
//  int endian = 0;
//  //pointer to the input & output files
//  FILE *source = fopen(fileName,"rb");//open both files in binary mode
//  FILE *target = fopen(destFile, "wb");
//  if (fread(buff, sizeof(buff), 1, source)) {
//    if (isBigEndian(buff)) {
//      endian = 1;
//    }
//    SwapCharsBytes(buff);
//    fwrite(buff, sizeof(buff), 1, target);
//  }
//  //as long as we didnt finish reading file we keep reading one element in size of short int (2 bytes) each time
//  while ((fread(buff , sizeof(buff), 1,source) ) != 0) {
//    //copy from unix to...
//    if(strcmp(flag1,"-unix")==0){
//      //call checkEndLine function which takes care of the case we need convert to windows format
//      if(checkEndLineAndSwap(buff,END_UNIX,flag2,target)==0) {
//        //if this is no end line continue copy file
//        if (!endian){
//          SwapCharsBytes(buff);
//        }
//        fwrite(buff,sizeof(buff), 1,target);
//      }
//    }//copy from mac to...
//    else if (strcmp(flag1,"-mac")==0) {
//      //call checkEndLine function which takes care of the case we need convert to windows format
//      if(checkEndLineAndSwap(buff,END_MAC,flag2,target)==0) {
//        //if this is no end line continue copy file
//        if (!endian){
//          SwapCharsBytes(buff);
//        }
//        fwrite(buff,sizeof(buff), 1,target);
//      }
//    }//from win to
//    else if(strcmp(flag1,"-win")==0) {
//      //check if current byte equals to '\r'
//      if(buff[0] == END_MAC) {
//        //first check if it equals to '/r'
//        if(fread(buff , sizeof(buff), 1,source) != 0) {//now check if there is more bytes to read
//          //call checkEndLine function which takes care of the case we need convert to windows format
//          if(checkEndLineAndSwap(buff,END_UNIX,flag2,target)==0) {
//            buffCheck[0]=END_MAC;
//            buffCheck[1] = 0;
//            if (!endian){
//              SwapCharsBytes(buffCheck);
//            }
//            fwrite(buffCheck,sizeof(buffCheck), 1,target);
//            //in c array containing the characters terminated with a null character
//            buffCheck[0]=NULL_TEMINATOR;
//            buffCheck[1] = 0;
//            if (!endian){
//              SwapCharsBytes(buffCheck);
//            }
//            fwrite(buffCheck,sizeof(buffCheck), 1,target);
//            if (!endian){
//              SwapCharsBytes(buff);
//            }
//            fwrite(buff,sizeof(buff), 1,target);
//          }//if this is no end line continue copy file
//        }else {
//          if (!endian){
//            SwapCharsBytes(buff);
//          }
//          fwrite(buff, sizeof(buff), 1, target);
//        }
//      }else {
//        if (!endian){
//          SwapCharsBytes(buff);
//        }
//        fwrite(buff, sizeof(buff), 1, target);
//      }
//    }
//  }
//  //close both file after we done
//  fclose(source);
//  fclose(target);
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
//  char buff[2];
//  int endian = 0;
//  // open both files in binary mode
//  FILE *source = fopen(fileName, "rb");
//  FILE *target = fopen(destFile, "wb");
//  if (fread(buff, sizeof(buff), 1, source)) {
//    if (isBigEndian(buff)) {
//      endian = 1;
//    }
//    if (endian){
//      SwapCharsBytes(buff);
//    }
//    fwrite(buff, sizeof(buff), 1, target);
//  }
//  // as long as we didnt finish reading file
//  while (fread(buff, sizeof(buff), 1, source) != 0) {
//    if (endian){
//      SwapCharsBytes(buff);
//    }
//    // copy what fread read to the dest file
//    fwrite(buff, sizeof(buff), 1, target);
//  }
//  fclose(source); // close both files
//  fclose(target);
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
//void secondOption(const char *fileName, const char *destFile, const char *flag1, const char *flag2) {
//  convertAndKeep(fileName, destFile, flag1, flag2);
//}
//
///***************************************************************************************************
// Function Name: thirdOption
// Function input: input & output files names
// Function Action: function for the first option - create a copy of given file
// Function output: none
// **************************************************************************************************/
//
//void thirdOption(const char *fileName, const char *destFile, const char *flag1, const char *flag2, const char *swapOrNot) {
//  if(strcmp(swapOrNot, KEEP) == 0){
//    convertAndKeep(fileName, destFile,flag1,flag2);
//  }
//  else if(strcmp(swapOrNot, SWAP) == 0){
//    convertAndSwap(fileName, destFile,flag1,flag2);
//  }
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