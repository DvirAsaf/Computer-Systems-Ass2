//// 313531113 Dvir Asaf.
//#include <stdio.h>
//#include "string.h"
////define
//#define SIZE 2
////#define 1
////enum encoding
//enum Encoding {Unix, Mac, Win, Illegal};
//
///**
// * getEndLineCharByOsFlag function.
// * @param os - os type.
// * @return - the end line char.
// */
//char getEndLineCharByOsFlag(enum Encoding os){
//  char endLine;
//  switch (os){
//  case Unix:
//    endLine = '\n';
//    break;
//  case Mac:
//    endLine = '\r';
//    break;
//  }
//  return endLine;
//}
//
///**
// * readAndCopy function.
// * reads and copys src file to trg file.
// * @param src - source file.
// * @param trg - target file.
// * @param isSwap - tells if we should change file's endiannes
// */
//void readAndCopy(char* src, char* trg, int isSwap) {
//  FILE* source = fopen(src, "rb");
//  //check if files are fine
//  if (source == NULL) {
//    return;
//  }
//  FILE* target = fopen(trg, "wb");
//  if (target == NULL) {
//    return;
//  }
//  char buffer[SIZE];
//  //read each char by buffer
//  while ((fread(buffer, sizeof(buffer), 1, source)!=0)) {
//    if (!isSwap) {
//      fwrite(buffer, sizeof(buffer), 1, target);
//    } else{
//      //swap in case user asked to do so
//      char temp = buffer[0];
//      buffer[0]=buffer[1];
//      buffer[1]=temp;
//      fwrite(buffer, sizeof(buffer), 1, target);
//    }
//  }
//  //close the files
//  fclose(target);
//  fclose(source);
//}
////TODO: take from last assignment
///**
// * isBigE (endian) function.
// * @param buffer - the readed char.
// * @return 1 if big endiann, o othewise.
// */
//int isBigE(char buffer[]) {
//  int isBig;
//  unsigned short int r = (unsigned short int) buffer[0];
//  if ((r == (unsigned short int)0xfffe)) {
//    isBig = 1;
//  } else if ((r= (unsigned short int) buffer[1])== (unsigned short int)0xfffe){
//    isBig = 0;
//  }
//  return isBig;
//
//}
//
///**
// * updateNewLineEncodingUnixMac function.
// * @param src - source file.
// * @param trg - target file.
// * @param srcEnco - source os.
// * @param trgEnco - target os.
// * @param isSwap - tells if we should change file's endiannes.
// */
//void updateNewLineEncodingUnixMac(char* src, char* trg, enum Encoding srcEnco, enum Encoding trgEnco, int isSwap) {
//  FILE* source = fopen(src, "rb");
//  //check if files are fine
//  if (source == NULL) {
//    return;
//  }
//  FILE* target = fopen(trg, "wb");
//  if (target == NULL) {
//    return;
//  }
//  char endLineSymbolSrc = getEndLineCharByOsFlag(srcEnco);
//  char endLineSymboltrg = getEndLineCharByOsFlag(trgEnco);
//  char buffer[SIZE];
//  int size = sizeof(buffer);
//  int count=0;
//  int isBig =0;
//  while ((fread(buffer, sizeof(buffer), 1, source) != 0)) {
//    if (count == 0) {
//      isBig =isBigE(buffer);
//      count++;
//    }
//    if (!isSwap) {
//      if (buffer[isBig] == endLineSymbolSrc && buffer[!isBig] == '\0') {
//        buffer[isBig] = endLineSymboltrg;
//        buffer[!isBig] = '\0';
//
//      }
//    } else {
//      if (buffer[isBig] == endLineSymbolSrc && buffer[!isBig] == '\0') {
//        buffer[!isBig] = endLineSymboltrg;
//        buffer[isBig] = '\0';
//
//
//      } else {
//        //swap other chars of file
//        char temp = buffer[0];
//        buffer[0] = buffer[1];
//        buffer[1]=temp;
//      }
//    }
//    //write the buffer to target file
//    fwrite(buffer, sizeof(buffer), 1, target);
//
//  }
//  fclose(target);
//  fclose(source);
//
//}
//
///**
// * getEncodingType function.
// * @param strType - os type.
// * @return enum encoding type.
// */
//enum Encoding getEncodingType(char * strType) {
//  enum Encoding type;
//  //make compare between inpute to our enum
//  if (strcmp(strType, "-win") == 0) {
//    type = Win;
//
//  } else if (strcmp(strType, "-unix") == 0) {
//    type = Unix;
//  } else if (strcmp(strType, "-mac") == 0) {
//    type = Mac;
//  } else {
//    //illegal param
//    type = Illegal;
//  }
//  return type;
//}
//
///**
// * updateNewLineEncodingWin function.
// * @param src - source file.
// * @param trg - target file.
// * @param srcEnco - source os.
// * @param trgEnco - target os.
// */
//void updateNewLineEncodingWin(char* src, char* trg, enum Encoding srcEnco, enum Encoding trgEnco) {
//  FILE* source = fopen(src, "rb");
//  //check if files are fine
//  if (source == NULL) {
//    return;
//  }
//  FILE* target = fopen(trg, "wb");
//  if (target == NULL) {
//    return;
//  }
//  char endLineSymbolSrc = getEndLineCharByOsFlag(srcEnco);
//  char buffer[SIZE];
//  int count=0;
//  int isBig=0;
//  while ((fread(buffer, sizeof(buffer), 1, source)!=0)) {
//    if (count == 0) {
//      isBig =isBigE(buffer);
//      count++;
//    }
//    //unix\mac to win
//    if (srcEnco!=Win && trgEnco==Win) {
//      //mac to win
//      if (buffer[isBig] == endLineSymbolSrc) {
//        buffer[isBig] = '\n';
//        buffer[!isBig] = '\0';
//        char tmpBuffer[SIZE];
//        tmpBuffer[isBig] = '\r';
//        tmpBuffer[!isBig] = '\0';
//        fwrite(tmpBuffer, sizeof(tmpBuffer), 1, target);
//      }
//      fwrite(buffer, sizeof(buffer), 1, target);
//    } else if (srcEnco==Win && trgEnco==Unix){
//      //win to unix
//      if (buffer[isBig]=='\n' || buffer[isBig]!='\r') {
//        fwrite(buffer, sizeof(buffer), 1, target);
//      }
//    } else if (srcEnco==Win && trgEnco==Mac){
//      //win to mac
//      if (buffer[isBig]!='\n' || buffer[isBig]=='\r') {
//        fwrite(buffer, sizeof(buffer), 1, target);
//      }
//    }
//  }
//  //close the files
//  fclose(target);
//  fclose(source);
//}
//
///**
// * updateNewLineEncodingWinSwap function.
// * @param src - source file.
// * @param trg - target file.
// * @param srcEnco - source os.
// * @param trgEnco - target os
// */
//void updateNewLineEncodingWinSwap(char* src, char* trg, enum Encoding srcEnco, enum Encoding trgEnco) {
//  FILE* source = fopen(src, "rb");
//  //check if files are fine
//  if (source == NULL) {
//    return;
//  }
//  FILE* target = fopen(trg, "wb");
//  if (target == NULL) {
//    return;
//  }
//  char endLineSymbolSrc = getEndLineCharByOsFlag(srcEnco);
//  char buffer[SIZE];
//  int count=0;
//  int isBig=0;
//  while ((fread(buffer, sizeof(buffer), 1, source)!=0)) {
//    if (count == 0) {
//      isBig =isBigE(buffer);
//      count++;
//    }
//    //unix\mac to win
//    if (srcEnco!=Win && trgEnco==Win) {
//      //mac/unix to win
//      if (buffer[isBig] == endLineSymbolSrc) {
//        buffer[!isBig] = '\n';
//        buffer[isBig] = '\0';
//        char tmpBuffer[SIZE];
//        tmpBuffer[!isBig] = '\r';
//        tmpBuffer[isBig] = '\0';
//        fwrite(tmpBuffer, sizeof(tmpBuffer), 1, target);
//      } else{
//        //swap other chars
//        char temp = buffer[0];
//        buffer[0] = buffer[1];
//        buffer[1]=temp;
//      }
//      fwrite(buffer, sizeof(buffer), 1, target);
//    } else if (srcEnco==Win && trgEnco==Unix){
//      //win to unix
//      if (buffer[isBig]=='\n' || buffer[isBig]!='\r') {
//        char temp = buffer[0];
//        buffer[0] = buffer[1];
//        buffer[1]=temp;
//        fwrite(buffer, sizeof(buffer), 1, target);
//
//      }
//    } else if (srcEnco==Win && trgEnco==Mac){
//      //win to mac
//      if (buffer[isBig]!='\n' || buffer[isBig]=='\r') {
//        char temp = buffer[0];
//        buffer[0] = buffer[1];
//        buffer[1]=temp;
//        fwrite(buffer, sizeof(buffer), 1, target);
//      }
//    }
//  }
//  //close the files
//  fclose(target);
//  fclose(source);
//}
//
///**
// * isSwapBytes function.
// * @param flag - input param (keep\swap)
// * @return 1 if swap is needed, 0 otherwise
// */
//int isSwapBytes(char* flag) {
//  if (strcmp(flag,"-swap")==0) {
//    return 1;
//  } else if (strcmp(flag,"-keep")==0) {
//    return 0;
//  } else {
//    return -1;
//  }
//}
//
///**
// * inputValidation function.
// * @param nameOfTrgFile - target file name
// * @return 1 if the is point in file name, 0 otherwise
// */
//int inputValidation(char * nameOfTrgFile) {
//  int len = strlen(nameOfTrgFile);
//  int i = 0;
//  for (; i < len; i++) {
//    if (nameOfTrgFile[i] == '.') {
//      return 1;
//    }
//  }
//  return 0;
//}
//
///**
// * main function.
// * runs the program.
// * @param argc - number of params.
// * @param argv - arr of input strings (char *)
// * @return o.
// */
//int main(int argc, char* argv[]) {
//
//  switch (argc) {
//  case 3:
//    if (inputValidation(argv[1]) ==1 && inputValidation(argv[2])==1){
//      readAndCopy(argv[1], argv[2],0);
//    }
//    break;
//  case 5: {
//    enum Encoding srcEnco = getEncodingType(argv[3]);
//    enum Encoding trgEncoding = getEncodingType(argv[4]);
//    if (srcEnco == Illegal || trgEncoding == Illegal) {
//      return 0;
//    }
//    if(srcEnco==trgEncoding){
//      readAndCopy(argv[1], argv[2],0);
//      return 0;
//    }
//    if (srcEnco!=Win && trgEncoding!=Win) {
//      updateNewLineEncodingUnixMac(argv[1], argv[2], srcEnco, trgEncoding,0);
//    } else if (srcEnco==Win || trgEncoding ==Win) {
//      updateNewLineEncodingWin(argv[1], argv[2], srcEnco, trgEncoding);
//
//    }
//    break;
//  }
//  case 6: {
//    enum Encoding srcEnco = getEncodingType(argv[3]);
//    enum Encoding trgEncoding = getEncodingType(argv[4]);
//    if (srcEnco == Illegal || trgEncoding == Illegal) {
//      return 0;
//    }
//    int isSwap =isSwapBytes(argv[5]);
//    if (isSwap == -1) {
//      return 0;
//    }
//    if(srcEnco==trgEncoding){
//      readAndCopy(argv[1], argv[2], isSwap);
//      return 0;
//    }
//    if (srcEnco!=Win && trgEncoding!=Win) {
//      updateNewLineEncodingUnixMac(argv[1], argv[2], srcEnco, trgEncoding,isSwap);
//    } else if (srcEnco==Win || trgEncoding ==Win) {
//      if(isSwap) {
//        updateNewLineEncodingWinSwap(argv[1], argv[2], srcEnco, trgEncoding);
//      } else {
//        updateNewLineEncodingWin(argv[1], argv[2], srcEnco, trgEncoding);
//      }
//    }
//    break;
//  }
//  }
//  return 0;
//}
//
////// 313531113 Dvir Asaf.
////#include <stdio.h>
////#include <string.h>
////#define END_UNIX '\n'
////#define END_MAC '\r'
////#define NULL_TEMINATOR '\0'
////#define SWAP "-swap"
////#define KEEP "-keep"
////int checkEndLine(char* buff,char check,const char* flag2,FILE* helper );
////void copyFile(const char *fileName, const char* destFile);
//////int main(int argc, char *argv[]) {
//////  int argument_size = argc;
//////  char buffer[2];
//////  if (argument_size == 3) {
//////    // reading the input given file.
//////    FILE *inPutFile = fopen(argv[1], "rb");
//////    FILE *outPutFile = fopen(argv[2], "wb");
//////    while (fread(buffer, sizeof(buffer), 1, inPutFile)) {
//////      fwrite(buffer, sizeof(buffer), 1, outPutFile);
//////    }
//////    fclose(inPutFile);
//////    fclose(outPutFile);
//////  }
//////  if (argument_size == 5) {
//////    FILE *inPutFile = fopen(argv[1], "rb");
//////    FILE *outPutFile = fopen(argv[2], "wb");
//////    char *argument3 = argv[3];
//////    char *argument4 = argv[4];
//////    // continue
//////    while (fread(buffer, sizeof(buffer), 1, inPutFile)) {
//////      // if the given flag is mac.
//////      if (!(strcmp(argument3, "-mac"))) {
//////        // if the return flag is unix.
//////        if (!(strcmp(argument4, "-unix"))) {
//////          // find \r in the text.
//////          if (!(strcmp(buffer, "\r"))) {
//////            // change \r to \n.
//////            strcpy(buffer, "\n");
//////            // add the \n to the rext.
//////            fwrite(buffer, sizeof(buffer), 1, outPutFile);
//////          }
//////          // if the return flag is win.
//////        } else if (!(strcmp(argument4, "-win"))) {
//////          // find \r in the text.
//////          if (!(strcmp(buffer, "\r"))) {
//////            // change \r to \n\r.
//////            strcpy(buffer, "\r");
//////            // add \r to the text.
//////            fwrite(buffer, sizeof(buffer), 1, outPutFile);
//////            strcpy(buffer, "\n");
//////            // add \n to the text.
//////            fwrite(buffer, sizeof(buffer), 1, outPutFile);
//////          }
//////        }
//////        // if the given flag is unix.
//////      } else if (!(strcmp(argument3, "-unix"))) {
//////        // if the return flag is win.
//////        if (!(strcmp(argument4, "-win"))) {
//////          // find \r in the text.
//////          if (!(strcmp(buffer, "\n"))) {
//////            // change \r to \n\r.
//////            strcpy(buffer, "\r");
//////            // add the \r to the text.
//////            fwrite(buffer, sizeof(buffer), 1, outPutFile);
//////            strcpy(buffer, "\n");
//////            // add \n to the text.
//////            fwrite(buffer, sizeof(buffer), 1, outPutFile);
//////          }
//////          // if the return flag is mac.
//////        } else if (!(strcmp(argument4, "-mac"))) {
//////          // find \n in the text.
//////          if (!(strcmp(buffer, "\n"))) {
//////            // change \n to \r.
//////            strcpy(buffer, "\r");
//////            // add the \r to the text.
//////            fwrite(buffer, sizeof(buffer), 1, outPutFile);
//////          }
//////        }
//////        // if the given flag is win.
//////      } else if (!(strcmp(argument3, "-win"))) {
//////        // if the return flag is mac.
//////        if (!(strcmp(argument4, "-mac"))) {
//////          // find \n\r in the text.
//////          if (!(strcmp(buffer, "\r"))) {
//////            // change \n\r to \r.
//////            strcpy(buffer, "\r");
//////            // add the \r to the text.
//////            fwrite(buffer, sizeof(buffer), 1, outPutFile);
//////          }
//////        }
//////        // if the return flag is unix.
//////        else if (!(strcmp(argument4, "-unix"))) {
//////          // find \n\r in the text.
//////          if (!(strcmp(buffer, "\n\r"))) {
//////            // change \n\r to \n.
//////            strcpy(buffer, "\n");
//////            // add the \n to the rext.
//////            fwrite(buffer, sizeof(buffer), 1, outPutFile);
//////          }
//////        }
//////      }
//////      else{
//////        fwrite(buffer, sizeof(buffer), 1, outPutFile);
//////      }
//////    }
//////    fclose(inPutFile);
//////    fclose(outPutFile);
//////  }
//////  return 0;
//////}
////
/////***************************************************************************************************
//// Function Name:swapBytes
//// Function input:short int* array
//// Function Action:the function get an array of type short int and in each word it swap bytes
//// Function output:none
//// **************************************************************************************************/
////
////void swapBytes(short int* buff) {
////  char temp;//temp varible
////  char *bytesBuff;//pointer of type char in size of one byte
////  int i =0;//index for loop
////  //as long we didnt finish go over the aray
////  for (i = 0; i < sizeof(buff) ; i++) {
////    //typecast of buff[i] to char pointer
////    bytesBuff = (char*)(&(buff[i]));
////    //save the first byte in temp
////    temp = bytesBuff[0];
////    //update first byte
////    bytesBuff[0]=bytesBuff[1];
////    //finish swap action
////    bytesBuff[1]=temp;
////  }
////}
////
/////***************************************************************************************************
//// Function Name:swapFile
//// Function input: name of file, name of dest file,flag of swap
//// Function Action:the function get the source file after convertion to the right format,
////                 then, it swap the order of bytes in each word
//// Function output:none
//// **************************************************************************************************/
////
////void swapFile(const char* helper, const char* destFile,const char* swapOrKeep) {
////  //check if we need to swap or keep
////  if(strcmp(swapOrKeep,KEEP)==0) {
////    copyFile(helper,destFile);//call the regular function and just copy file
////  }
////    //if we need to swap bytes
////  else if((strcmp(swapOrKeep,SWAP)==0)) {
////    //pointers of type FILE
////    FILE *in,*out;
////    //open both files in binary mode
////    out = fopen(destFile, "wb");
////    in=fopen(helper,"rb");
////    short int buff[2];//buffer
////    //as long as we didnt finish reading file
////    while (fread(buff ,sizeof(short int), 1,in)> 0) {
////      swapBytes(buff);//call function swapBytes
////      fwrite(buff,sizeof(short int), 1,out);//write to the outfile
////    }
////    fclose(out); //close both files
////    fclose(in);
////  }
////}
////
/////***************************************************************************************************
//// Function Name:copyAndConvert
//// Function input: input&output files names,input format & output format
//// Function Action:this function copy one file into a new file with the correct name and convert it to to the required format
//// Function output:none
//// **************************************************************************************************/
////
////void copyAndConvert(const char *fileName, const char* destFile,const char *flag1, const char* flag2,const char* swapOrKeep ) {
////  char buff[2];//buffer to save what we read from the file
////  char buffCheck[2];//help buffer
////  //pointer to the input & output files
////  FILE *in, *helper;
////  in = fopen(fileName,"rb");//open both files in binary mode
////  //TODO: change helper name.
//////  helper = fopen("help", "wb");
////  helper = fopen(destFile, "wb");
////  //as long as we didnt finish reading file we keep reading one element in size of short int (2 bytes) each time
////  while ((fread(buff , sizeof(char), 1,in) )> 0) {
////    //copy from unix to...
////    if(strcmp(flag1,"-unix")==0) {
////      //call checkEndLine function which takes care of the case we need convert to windows format
////      if(checkEndLine(buff,END_UNIX,flag2,helper)==0) {
////        //if this is no end line continue copy file
////        fwrite(buff,sizeof(char), 1,helper);
////      }
////    }//copy from mac to...
////    else if (strcmp(flag1,"-mac")==0) {
////      //call checkEndLine function which takes care of the case we need convert to windows format
////      if(checkEndLine(buff,END_MAC,flag2,helper)==0) {
////        //if this is no end line continue copy file
////        fwrite(buff,sizeof(char), 1,helper);
////      }
////    }//from win to
////    else if(strcmp(flag1,"-win")==0) {
////      //check if current byte equals to '\r'
////      if(buff[0] == END_MAC) {
////        //in c array containing the characters terminated with a null character
////        fread(buff , sizeof(char), 1,in);//check \0
////        //first check if it equals to '/r'
////        if(fread(buff , sizeof(char), 1,in) > 0) { //now check if there is more bytes to read//
////          //call checkEndLine function which takes care of the case we need convert to windows format
////          if(checkEndLine(buff,END_UNIX,flag2,helper)==0) {
////            buffCheck[0]=END_MAC;
////            fwrite(buffCheck,sizeof(char), 1,helper);
////            //in c array containing the characters terminated with a null character
////            buffCheck[0]=NULL_TEMINATOR;
////            fwrite(buffCheck,sizeof(char), 1,helper);
////            //buffCheck[1]=buff[0];
////            fwrite(buff,sizeof(char), 1,helper);
////
////          }//if this is no end line continue copy file
////        }
////        else
////          fwrite(buff,sizeof(char), 1,helper);
////      }
////      else
////        fwrite(buff,sizeof(char), 1,helper);
////    }
////  }
////  fclose(in);
////  fclose(helper);//close both file after we done
////  //copyFile("help",destFile);
////  //call swapFile function
//////  swapFile("help", destFile,swapOrKeep);
////}
////
/////***************************************************************************************************
//// Function Name:applyChange
//// Function input:buffer we need to change, flag -> to what format to change, pointer to the file
//// Function Action:this function take care of the case of changing the line drop character according to the desired format
//// Function output:none
//// **************************************************************************************************/
////
////void applyChange(char* needChange, const char* flag ,FILE* helper) {
////  //help buffer
////  char help[2];
////  //to format of unix
////  if(strcmp(flag,"-unix")== 0) {
////    needChange[0] = END_UNIX;
////    fwrite(needChange,sizeof(char), 1,helper);
////
////  }//to format of mac
////  else if(strcmp(flag,"-mac")== 0) {
////    needChange[0] = END_MAC;
////    fwrite(needChange,sizeof(char), 1,helper);
////  }//to format of windows
////  else if(strcmp(flag,"-win")== 0) {
////    //end line in windows consists of two characters(of two bytes each)
////    needChange[0] = END_MAC;
////    fwrite(needChange,sizeof(char), 1,helper);
////    help[0]=NULL_TEMINATOR;
////    //in c array containing the characters terminated with a null character
////    fwrite(help, sizeof(char),1,helper);
////    needChange[0] = END_UNIX;
////    fwrite(needChange,sizeof(char), 1,helper);
////  }
////}
////
/////***************************************************************************************************
//// Function Name:  checkEndLine.
//// Function input: a pointer to a block of memory, the format of \n or \r in binary,  a flag which tells us to which format
////                 conert the file to,and a pointer of type FILE to the output file.
//// Function Action: this function takes care of the case where the file needs to be converted to windows format.
////                  in that case we'll consider the fact that end line in windows consists of two characters(of two bytes each)
//// Function output:the func return 1 if indeed we change to windows,else return 0
//// **************************************************************************************************/
////
////int checkEndLine(char* buff,char check,const char* flag2,FILE* helper )
////{
////  //check if the current buffer consists new line character in binary
////  if(buff[0] ==check)
////  {
////    applyChange(buff,flag2,helper);//call applyChange function to take care of the case//
////    return 1;
////  }
////  return 0;
////}
////
/////***************************************************************************************************
//// Function Name: copyFile
//// Function input: input & output files names
//// Function Action: this function just copy a given file to another
//// Function output:none
//// **************************************************************************************************/
////
////void copyFile(const char *fileName, const char* destFile)
////{
////  //buffer for reading chars
////  char buff[4];
////  //save the value fread function return - number of elements read
////  size_t n;
////  FILE *in, *out;
////  in = fopen(fileName,"rb");//open both files in binary mode
////  out = fopen(destFile, "wb");
////  //as long as we didnt finish reading file
////  while ((n=fread(buff ,1, sizeof(buff),in) )!= 0) {
////    fwrite(buff,1,n,out);//copy what fread read to the dest file
////  }
////  fclose(in);//close both files
////  fclose(out);
////}
////
/////***************************************************************************************************
//// Function Name: firstOption
//// Function input: input & output files names
//// Function Action: function for the first option - create a copy of given file
//// Function output: none
//// **************************************************************************************************/
////
////void firstOption(const char *fileName, const char* destFile)
////{
////  //if copyFile function succeed (the surce file exists)
////  copyFile(fileName,destFile);
////}
////
/////***************************************************************************************************
//// Function Name: secondOption
//// Function input: input & output files names
//// Function Action: function for the first option - create a copy of given file
//// Function output: none
//// **************************************************************************************************/
////
////void secondOption(const char *fileName, const char* destFile,const char *flag1, const char* flag2)
////{
////  copyAndConvert(fileName,destFile,flag1,flag2,KEEP);
////}
////
/////***************************************************************************************************
//// Function Name: thirdOption
//// Function input: input & output files names
//// Function Action: function for the first option - create a copy of given file
//// Function output: none
//// **************************************************************************************************/
////
////void thirdOption(const char *fileName, const char* destFile,const char *flag1,
////                 const char* flag2, const char* swapOrNot)
////{
////  copyAndConvert(fileName,destFile,flag1,flag2,swapOrNot);
////}
////
/////***************************************************************************************************
//// Function Name: isFileExists
//// Function input: the input file name
//// Function Action: check if the file exists
//// Function output:return 1 if the file exist, else return 0
//// **************************************************************************************************/
////
////int isFileExists(const char *fileName)
////{
////  FILE *file;
////  //try to open and read the file
////  if (file = fopen(fileName,"rb")) {
////    fclose(file);
////    return 1;
////  }
////  return 0;
////}
////
////int main(int argc, char **argv) {
////  int size = argc;
////  switch (size) {
////  case 3: firstOption(argv[1], argv[2]);
////    break;
////  case 5: secondOption(argv[1], argv[2], argv[3], argv[4]);
////    break;
////  case 6: thirdOption(argv[1], argv[2], argv[3], argv[4], argv[5]);
////    break;
////  default: isFileExists(argv[1]);
////    break;
////  }
////  return 0;
////}