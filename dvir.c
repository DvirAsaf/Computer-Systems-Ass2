// 313531113 Dvir Asaf.
#include <stdio.h>
#include "stdlib.h"
#include <string.h>
#define KEEP "-keep"
#define SWAP "-swap"
#define MAC "-mac"
#define MAC_SIGN "\r"
#define UNIX "-unix"
#define UNIX_SIGN "\n"
#define WIN "-win"
#define NULL_SIGN '\0'
#define END_UNIX '\n'
#define END_MAC '\r'
#define NULL_TEMINATOR '\0'
#define SWAP "-swap"
#define KEEP "-keep"

void copyFile(const char *fileName, const char *destFile);

/***************************************************************************************************
 Function Name:swapBytes
 Function input:short int* array
 Function Action:the function get an array of type short int and in each word it
 swap bytes Function output:none
 **************************************************************************************************/
void swapBytes(short int* buff)
{
  char temp;//temp varible
  char *bytesBuff;//pointer of type char in size of one byte
  int i =0;//index for loop
  //as long we didnt finish go over the aray
  for (i = 0; i < sizeof(buff) ; i++){
    //typecast of buff[i] to char pointer
    bytesBuff = (char*)(&(buff[i]));
    //save the first byte in temp
    temp = bytesBuff[0];
    //update first byte
    bytesBuff[0]=bytesBuff[1];
    //finish swap action
    bytesBuff[1]=temp;
  }
}

void SwapCharsBytes(char* buffer){
  char temp = buffer[0];
  buffer[0] = buffer[1];
  buffer[1]=temp;
}
//void swapBytes(char *buff) {
//  char temp;       // temp varible
//  char *bytesBuff; // pointer of type char in size of one byte
//  // as long we didnt finish go over the array
//  for (int i = 0; i < sizeof(buff); i++) {
//    // typecast of buff[i] to char pointer
//    bytesBuff = &(buff[i]);
//    // save the first byte in temp
//    temp = bytesBuff[0];
//    // update first byte
//    bytesBuff[0] = bytesBuff[1];
//    // finish swap action
//    bytesBuff[1] = temp;
//  }
//}

void applyChange(char* needChange, const char* flag ,FILE* dest_file)
{
  //help buffer
  char help[2];
  //to format of unix
  if(strcmp(flag,"-unix")== 0)
  {
    needChange[0] = END_UNIX;
    fwrite(needChange,sizeof(char), 1,dest_file);

  }//to format of mac
  else if(strcmp(flag,"-mac")== 0)
  {
    needChange[0] = END_MAC;
    fwrite(needChange,sizeof(char), 1,dest_file);
  }//to format of windows
  else if(strcmp(flag,"-win")== 0)
  {
    //end line in windows consists of two characters(of two bytes each)
    needChange[0] = END_MAC;
    fwrite(needChange,sizeof(char), 1,dest_file);
    help[0]=NULL_TEMINATOR;
    //in c array containing the characters terminated with a null character
    fwrite(help, sizeof(char),1,dest_file);
    needChange[0] = END_UNIX;
    fwrite(needChange,sizeof(char), 1,dest_file);
  }
}

void applyChangeSwap(char* needChange, const char* flag ,FILE* dest_file)
{
  //help buffer
  char help[2];
  //to format of unix
  if(strcmp(flag,"-unix")== 0)
  {
    needChange[0] = END_UNIX;
    SwapCharsBytes(needChange);
    fwrite(needChange,sizeof(help), 1,dest_file);

  }//to format of mac
  else if(strcmp(flag,"-mac")== 0)
  {
    needChange[0] = END_MAC;
    SwapCharsBytes(needChange);
    fwrite(needChange,sizeof(help), 1,dest_file);
  }//to format of windows
  else if(strcmp(flag,"-win")== 0)
  {

    help[0] = END_MAC;
    SwapCharsBytes(help);
    fwrite(help,sizeof(help ), 1,dest_file);
//    fread(help, sizeof(help), 1, dest_file);

//    help[0]=NULL_TEMINATOR;
//    SwapCharsBytes(help);
//    fwrite(help, sizeof(needChange),1,dest_file);

//    end line in windows consists of two characters(of two bytes each)
    help[0] = END_UNIX;
    help[1] = 0;
    SwapCharsBytes(help);
    fwrite(help,sizeof(help ), 1,dest_file);

//    exit(1);



    //in c array containing the characters terminated with a null character


//    needChange[0] = END_UNIX;
////    SwapCharsBytes(needChange);
//    fwrite(needChange,sizeof(char ), 1,dest_file);
//
//
//    //end line in windows consists of two characters(of two bytes each)
//    needChange[0] = END_MAC;
////    SwapCharsBytes(needChange);
////    fwrite(needChange,sizeof(needChange ), 1,dest_file);
//    needChange[1]=NULL_TEMINATOR;
//    //in c array containing the characters terminated with a null character
////    SwapCharsBytes(help);
//    fwrite(needChange, sizeof(needChange),1,dest_file);
  }
}
void applyChangeSwap1(char* needChange, const char* flag ,FILE* dest_file)
{
  //help buffer
  char help[2];
  //to format of unix
  if(strcmp(flag,"-unix")== 0)
  {
    needChange[1] = END_UNIX;
    SwapCharsBytes(needChange);
    fwrite(needChange,sizeof(help), 1,dest_file);

  }//to format of mac
  else if(strcmp(flag,"-mac")== 0)
  {
    needChange[1] = END_MAC;
    SwapCharsBytes(needChange);
    fwrite(needChange,sizeof(help), 1,dest_file);
  }//to format of windows
  else if(strcmp(flag,"-win")== 0)
  {

    needChange[1] = END_MAC;
    SwapCharsBytes(needChange);
    fwrite(needChange,sizeof(needChange), 1,dest_file);

//    help[0]=NULL_TEMINATOR;
//    SwapCharsBytes(help);
//    fwrite(help, sizeof(needChange),1,dest_file);

    //end line in windows consists of two characters(of two bytes each)
    needChange[1] = END_UNIX;
    SwapCharsBytes(needChange);
    fwrite(needChange,sizeof(needChange), 1,dest_file);



    //in c array containing the characters terminated with a null character


//    needChange[0] = END_UNIX;
////    SwapCharsBytes(needChange);
//    fwrite(needChange,sizeof(char ), 1,dest_file);
//
//
//    //end line in windows consists of two characters(of two bytes each)
//    needChange[0] = END_MAC;
////    SwapCharsBytes(needChange);
////    fwrite(needChange,sizeof(needChange ), 1,dest_file);
//    needChange[1]=NULL_TEMINATOR;
//    //in c array containing the characters terminated with a null character
////    SwapCharsBytes(help);
//    fwrite(needChange, sizeof(needChange),1,dest_file);
  }
}

int checkEndLine(char* buff,char check,const char* flag2,FILE* dest_file ){
  //check if the current buffer consists new line charcter in binary
  if(buff[0] ==check){
    applyChange(buff,flag2,dest_file);//call applyChange function to thake care of the case//
    return 1;
  }
  return 0;
}

int checkEndLineAndSwap(char* buff,char check,const char* flag2,FILE* dest_file ){
  //check if the current buffer consists new line charcter in binary
  if(buff[0] == check){
    applyChangeSwap(buff,flag2,dest_file);//call applyChange function to thake care of the case//
    return 1;
  }else if(buff[1] == check){
    applyChangeSwap1(buff,flag2,dest_file);
    return 1;
  }
  return 0;
}

void convertAndKeep(const char *fileName, const char *destFile, const char *flag1, const char *flag2) {
  char buff[2];//buffer to save what we read from the file
  char buffCheck[2];//help buffer
  //pointer to the input & output files
  FILE *in, *dest_file;
  in = fopen(fileName,"rb");//open both files in binary mode
//  dest_file = fopen("help", "wb");
  dest_file = fopen(destFile, "wb");
  //as long as we didnt finish reading file we keep reading one element in size of short int (2 bytes) each time
  while ((fread(buff , sizeof(char), 1,in) )> 0){
    //copy from unix to...
    if(strcmp(flag1,"-unix")==0){
      //call checkEndLine function which takes care of the case we need convert to windows format
      if(checkEndLine(buff,END_UNIX,flag2,dest_file)==0){
        //if this is no end line continue copy file
        fwrite(buff,sizeof(char), 1,dest_file);
      }
    }//copy from mac to...
    else if (strcmp(flag1,"-mac")==0){
      //call checkEndLine function which takes care of the case we need convert to windows format
      if(checkEndLine(buff,END_MAC,flag2,dest_file)==0){
        //if this is no end line continue copy file
        fwrite(buff,sizeof(char), 1,dest_file);
      }
    }//from win to
    else if(strcmp(flag1,"-win")==0){
      //check if current byte equals to '\r'
      if(buff[0] == END_MAC){
        //in c array containing the characters terminated with a null character
        fread(buff , sizeof(char), 1,in);//check \0
        //first check if it equals to '/r'
        if(fread(buff , sizeof(char), 1,in) > 0){//now check if there is more bytes to read
          //call checkEndLine function which takes care of the case we need convert to windows format
          if(checkEndLine(buff,END_UNIX,flag2,dest_file)==0){
            buffCheck[0]=END_MAC;
            fwrite(buffCheck,sizeof(char), 1,dest_file);
            //in c array containing the characters terminated with a null character
            buffCheck[0]=NULL_TEMINATOR;
            fwrite(buffCheck,sizeof(char), 1,dest_file);
            //buffCheck[1]=buff[0];
            fwrite(buff,sizeof(char), 1,dest_file);
          }//if this is no end line continue copy file
        }else
          fwrite(buff,sizeof(char), 1,dest_file);

      }else
        fwrite(buff,sizeof(char), 1,dest_file);
    }
  }
  short int buf[2];//buffer
  //as long as we didnt finish reading file
//  while (fread(buf ,sizeof(short int), 1,in)> 0){
//    swapBytes(buf);//call function swapBytes
//    fwrite(buff,sizeof(short int), 1,dest_file);//write to the outfile
//  }
  fclose(in);
  fclose(dest_file);//close both file after we done

}

void convertAndSwap(const char *fileName, const char *destFile, const char *flag1, const char *flag2) {

  char buff[2];//buffer to save what we read from the file
  char buffCheck[2];//help buffer
  //pointer to the input & output files
  FILE *in, *dest_file;
  in = fopen(fileName,"rb");//open both files in binary mode
//  dest_file = fopen("help", "wb");
  dest_file = fopen(destFile, "wb");
  //as long as we didnt finish reading file we keep reading one element in size of short int (2 bytes) each time
  while ((fread(buff , sizeof(buff), 1,in) )> 0){
    //copy from unix to...
    if(strcmp(flag1,"-unix")==0){
      //call checkEndLine function which takes care of the case we need convert to windows format
      if(checkEndLineAndSwap(buff,END_UNIX,flag2,dest_file)==0){
        //if this is no end line continue copy file
        SwapCharsBytes(buff);
        fwrite(buff,sizeof(buff), 1,dest_file);
      }
    }//copy from mac to...
    else if (strcmp(flag1,"-mac")==0){
      //call checkEndLine function which takes care of the case we need convert to windows format
      if(checkEndLineAndSwap(buff,END_MAC,flag2,dest_file)==0){
        //if this is no end line continue copy file
        SwapCharsBytes(buff);
        fwrite(buff,sizeof(buff), 1,dest_file);
      }
    }//from win to
    else if(strcmp(flag1,"-win")==0){
      //check if current byte equals to '\r'
      if(buff[0] == END_MAC){
        //in c array containing the characters terminated with a null character
        //TODO:
//        fread(buff , sizeof(buff), 1,in);//check \0
        //first check if it equals to '/r'
        if(fread(buff , sizeof(buff), 1,in) > 0){//now check if there is more bytes to read
          //call checkEndLine function which takes care of the case we need convert to windows format
          if(checkEndLineAndSwap(buff,END_UNIX,flag2,dest_file)==0){
//            SwapCharsBytes(buff);
//          fwrite(buff, sizeof(buff), 1, dest_file);
            buffCheck[0]=END_MAC;
            SwapCharsBytes(buffCheck);
            fwrite(buffCheck,sizeof(char ), 1,dest_file);
            //in c array containing the characters terminated with a null character
            buffCheck[0]=NULL_TEMINATOR;
            SwapCharsBytes(buffCheck);
            fwrite(buffCheck,sizeof(char), 1,dest_file);
            //buffCheck[1]=buff[0];
            SwapCharsBytes(buff);
//            fwrite(buff,sizeof(buff), 1,dest_file);
            fwrite(buff,sizeof(buff), 1,dest_file);
          }//if this is no end line continue copy file
        }else {
          SwapCharsBytes(buff);
          fwrite(buff, sizeof(buff), 1, dest_file);
        }

      }else {
        SwapCharsBytes(buff);
        fwrite(buff, sizeof(buff), 1, dest_file);
      }
    }
  }
//  short int buf[2];//buffer
  //as long as we didnt finish reading file
//  while (fread(buf ,sizeof(short int), 1,in)> 0){
//    swapBytes(buf);//call function swapBytes
//    fwrite(buff,sizeof(short int), 1,dest_file);//write to the outfile
//  }
  fclose(in);
  fclose(dest_file);//close both file after we done
}

//void convertAndSwap(const char *fileName, const char *destFile, const char *flag1, const char *flag2) {
//  char buff[2];//buffer to save what we read from the file
//  char buffCheck[2];//help buffer
//  //pointer to the input & output files
//  FILE *in, *dest_file;
//  in = fopen(fileName,"rb");//open both files in binary mode
////  dest_file = fopen("help", "wb");
//  dest_file = fopen(destFile, "wb");
//  //as long as we didnt finish reading file we keep reading one element in size of short int (2 bytes) each time
//  while ((fread(buff , sizeof(char), 1,in) )> 0){
////    SwapCharsBytes(buff);
//    //copy from unix to...
//    if(strcmp(flag1,"-unix")==0){
//      //call checkEndLine function which takes care of the case we need convert to windows format
//      if(checkEndLineAndSwap(buff,END_UNIX,flag2,dest_file)==0){
//        //if this is no end line continue copy file
//        fwrite(buff,sizeof(char), 1,dest_file);
//      }
//
//    }//copy from mac to...
//    else if (strcmp(flag1,"-mac")==0){
//      //call checkEndLine function which takes care of the case we need convert to windows format
//      if(checkEndLineAndSwap(buff,END_MAC,flag2,dest_file)==0){
//        //if this is no end line continue copy file
//        SwapCharsBytes(buff);
//        fwrite(buff,sizeof(char), 1,dest_file);
//      }
//    }//from win to
//    else if(strcmp(flag1,"-win")==0){
//      //check if current byte equals to '\r'
//      if(buff[0] == END_MAC){
//        //in c array containing the characters terminated with a null character
//        fread(buff , sizeof(char), 1,in);//check \0
//        //first check if it equals to '/r'
//        if(fread(buff , sizeof(char), 1,in) > 0){//now check if there is more bytes to read
//          //call checkEndLine function which takes care of the case we need convert to windows format
//          if(checkEndLineAndSwap(buff,END_UNIX,flag2,dest_file)==0){
//            buffCheck[0]=END_MAC;
//            fwrite(buffCheck,sizeof(char), 1,dest_file);
//            //in c array containing the characters terminated with a null character
//            buffCheck[0]=NULL_TEMINATOR;
//            fwrite(buffCheck,sizeof(char), 1,dest_file);
//            //buffCheck[1]=buff[0];
//            fwrite(buff,sizeof(char), 1,dest_file);
//          }//if this is no end line continue copy file
//        }else{
//          char temp = buff[0];
//        buff[0] = buff[1];
//        buff[1]=temp;
//          fwrite(buff,sizeof(char), 1,dest_file);
//        }
//      }else
//      {
////        SwapCharsBytes(buff);
//        fwrite(buff,sizeof(char), 1,dest_file);
//      }
//    }
//  }
////  short int buf[2];//buffer
////    while (fread(buf ,sizeof(short int), 1,in)> 0){
////    swapBytes(buf);//call function swapBytes
////    fwrite(buff,sizeof(short int), 1,dest_file);//write to the outfile
////  }
//  fclose(in);
//  fclose(dest_file);//close both file after we done
//}

void convert(const char *src, const char *trg, const char *f1, const char *f2,
             const char *change) {

  if(strcmp(change, KEEP) == 0){
    convertAndKeep(src, trg,f1,f2);
  }
  else if(strcmp(change, SWAP) == 0){
//    convertAndSwap(src, trg,f1,f2);
    convertAndSwap(src, trg,f1,f2);
  }
//  char buff[2];
//  FILE *source = fopen(src, "rb");
//  if (source == NULL) {
//    return;
//  }
//  FILE *target = fopen(trg, "wb");
//  if (target == NULL) {
//    return;
//  }
//
//  while (fread(buff, sizeof(buff), 1, source) != 0) {
//    if (strcmp(change, SWAP) == 0) {
//      // if the buffer word is not mac or unix sign.
//      if (strcmp(buff, MAC_SIGN) != 0 && strcmp(buff, UNIX_SIGN) != 0) {
//        swapBytes(buff);
//        fwrite(buff, sizeof(buff), 1, target);
//      }
//      continue;
//    } else if (strcmp(change, KEEP) == 0) {
//      continue;
//    }
//    if (strcmp(f1, MAC) == 0) {
//      if (strcmp(f2, UNIX) == 0) {
//        if (strcmp(buff, MAC_SIGN) == 0) {
//          strcpy(buff, UNIX_SIGN);
//          fwrite(buff, sizeof(buff), 1, target);
//        }
//      } else if (strcmp(f2, WIN) == 0) {
//        if (strcmp(buff, MAC_SIGN) == 0)
//          fwrite(buff, sizeof(buff), 1, target);
//        strcpy(buff, UNIX_SIGN);
//        fwrite(buff, sizeof(buff), 1, target);
//      } else {
//        fwrite(buff, sizeof(buff), 1, target);
//      }
//    }
//    if (strcmp(f1, UNIX) == 0) {
//      if (strcmp(f2, MAC) == 0) {
//        if (strcmp(buff, UNIX_SIGN) == 0) {
//          strcpy(buff, MAC_SIGN);
//          fwrite(buff, sizeof(buff), 1, target);
//        }
//      } else if (strcmp(f2, WIN) == 0) {
//        if (strcmp(buff, UNIX_SIGN) == 0) {
//          strcpy(buff, MAC_SIGN);
//          fwrite(buff, sizeof(buff), 1, target);
//          strcpy(buff, UNIX_SIGN);
//          fwrite(buff, sizeof(buff), 1, target);
//        }
//      } else {
//        fwrite(buff, sizeof(buff), 1, target);
//      }
//    }
//    // TODO: finish the if condition
//    // convert win sign to mac sign.
//    if (strcmp(f1, WIN) == 0) {
//      if (strcmp(f2, MAC) == 0) {
//        if (strcmp(buff, MAC_SIGN) == 0) {
//          strcpy(buff, MAC_SIGN);
//          fwrite(buff, sizeof(buff), 1, target);
//          fwrite(buff,sizeof(buff), 1, target);
//        }
//      } else if (strcmp(f2, UNIX) == 0) {
//        strcpy(buff, UNIX_SIGN);
//        fwrite(buff, sizeof(buff), 1, target);
//        fwrite(buff,sizeof(buff), 1, target);
//      } else {
//        fwrite(buff, sizeof(buff), 1, target);
//      }
//    }
//    fwrite(buff, sizeof(buff), 1, target);
//  }
//  fclose(source);
//  fclose(target);
}

/***************************************************************************************************
 Function Name: copyFile
 Function input: input & output files names
 Function Action: this function just copy a given file to another
 Function output:none
 **************************************************************************************************/

void copyFile(const char *fileName, const char *destFile) {
  // buffer for reading chars
  char buff[4];
  // save the value fread function return - number of elements read
  size_t n;
  FILE *in, *out;
  in = fopen(fileName, "rb"); // open both files in binary mode
  out = fopen(destFile, "wb");
  // as long as we didnt finish reading file
  while ((n = fread(buff, 1, sizeof(buff), in)) != 0) {
    fwrite(buff, 1, n, out); // copy what fread read to the dest file
  }
  fclose(in); // close both files
  fclose(out);
}

/***************************************************************************************************
 Function Name: firstOption
 Function input: input & output files names
 Function Action: function for the first option - create a copy of given file
 Function output: none
 **************************************************************************************************/

void firstOption(const char *fileName, const char *destFile) {
  // if copyFile function succeed (the surce file exists)
  copyFile(fileName, destFile);
}

/***************************************************************************************************
 Function Name: secondOption
 Function input: input & output files names
 Function Action: function for the first option - create a copy of given file
 Function output: none
 **************************************************************************************************/

void secondOption(const char *fileName, const char *destFile, const char *flag1,
                  const char *flag2) {
  convert(fileName, destFile, flag1, flag2, KEEP);
}

/***************************************************************************************************
 Function Name: thirdOption
 Function input: input & output files names
 Function Action: function for the first option - create a copy of given file
 Function output: none
 **************************************************************************************************/

void thirdOption(const char *fileName, const char *destFile, const char *flag1,
                 const char *flag2, const char *swapOrNot) {
  convert(fileName, destFile, flag1, flag2, swapOrNot);
}

/***************************************************************************************************
 Function Name: main
 Function input: args is number of user input, when argv[0] is the function name
 Function Action: this is the main function
 Function output: 0 - terminate program
 **************************************************************************************************/

int main(int argc, char **argv) {
  int size = argc;
  switch (size) {
  case 3:
    firstOption(argv[1], argv[2]);
    break;
  case 5:
    secondOption(argv[1], argv[2], argv[3], argv[4]);
    break;
  case 6:
    thirdOption(argv[1], argv[2], argv[3], argv[4], argv[5]);
    break;
  default:
    break;
  }
  return 0;
}