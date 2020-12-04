////314882853 Coral Malachi
//#include <stdio.h>
//#include <string.h>
//#define END_UNIX '\n'
//#define END_MAC '\r'
//#define NULL_TEMINATOR '\0'
//#define SWAP "-swap"
//#define KEEP "-keep"
////forward delecrtion
//void swapFile(const char* helper, const char* destFile,const char* swapOrKeep);
//void swapBytes(short int* buff);
//int checkEndLine(char* buff,char check,const char* flag2,FILE* out );
//void copyAndConvert(const char *fileName, const char* destFile,const char *flag1, const char* flag2,
//                    const char* swapOrKeep );
//void copyFile(const char *fileName, const char* destFile);
//void firstOption(const char *fileName, const char* destFile);
//void secondOption(const char *fileName, const char* destFile,const char *flag1, const char* flag2);
//void thirdOption(const char *fileName, const char* destFile,const char *flag1,
//                 const char* flag2, const char* swapOrNot);
//int isFileExists(const char *fileName);
///***************************************************************************************************
// Function Name: main
// Function input: args is number of user input, when argv[0] is the function name
// Function Action: this is the main function
// Function output: 0 - terminate program
// **************************************************************************************************/
//int main(int argc, char **argv)
//{
//  // if the input contain only one fule name end the program
//  if (argc == 2)
//    return 0;
//  //check if first file exists
//  if ( isFileExists(argv[1]) == 0)
//  {
//    return 0;
//  }
//  //first option -source and dest file
//  if (argc == 3)
//  {
//    firstOption(argv[1],argv[2]);
//  }
//  //second option - source and dest file and 2 flags indicates on convert
//  if (argc == 5)
//  {
//    secondOption(argv[1],argv[2],argv[3],argv[4]);
//
//  }
//  //like option 2 + option of swap bytes
//  if (argc == 6)
//  {
//    thirdOption(argv[1],argv[2],argv[3],argv[4],argv[5]);
//  }
//  return 0;
//}
//
//
///***************************************************************************************************
// Function Name:swapFile
// Function input: name of file, name of dest file,flag of swap
// Function Action:the function get the source file after convertion to the right format,
//                 then, it swap the order of bytes in each word
// Function output:none
// **************************************************************************************************/
//void swapFile(const char* helper, const char* destFile,const char* swapOrKeep)
//{
//
//  //check if we need to swap or keep
//  if(strcmp(swapOrKeep,KEEP)==0)
//  {
//    copyFile(helper,destFile);//call the regular function and just copy file
//  }
//    //if we need to swap bytes
//  else if((strcmp(swapOrKeep,SWAP)==0))
//  {
//    //pointers of type FILE
//    FILE *in,*out;
//    //open both files in binary mode
//    out = fopen(destFile, "wb");
//    in=fopen(helper,"rb");
//    short int buff[2];//buffer
//    //as long as we didnt finish reading file
//    while (fread(buff ,sizeof(short int), 1,in)> 0)
//    {
//      swapBytes(buff);//call function swapBytes
//      fwrite(buff,sizeof(short int), 1,out);//write to the outfile
//    }
//    fclose(out); //close both files
//    fclose(in);
//  }
//}
//
///***************************************************************************************************
// Function Name:applyChange
// Function input:buffer we need to change, flag -> to what format to change, pointer to the file
// Function Action:this function take care of the case of changing the line drop character according
//          to the desired format
// Function output:none
// **************************************************************************************************/
//void applyChange(char* needChange, const char* flag ,FILE* helper)
//{
//  //help buffer
//  char help[2];
//  //to format of unix
//  if(strcmp(flag,"-unix")== 0)
//  {
//    needChange[0] = END_UNIX;
//    fwrite(needChange,sizeof(char), 1,helper);
//
//  }//to format of mac
//  else if(strcmp(flag,"-mac")== 0)
//  {
//    needChange[0] = END_MAC;
//    fwrite(needChange,sizeof(char), 1,helper);
//  }//to format of windows
//  else if(strcmp(flag,"-win")== 0)
//  {
//    //end line in windows consists of two characters(of two bytes each)
//    needChange[0] = END_MAC;
//    fwrite(needChange,sizeof(char), 1,helper);
//    help[0]=NULL_TEMINATOR;
//    //in c array containing the characters terminated with a null character
//    fwrite(help, sizeof(char),1,helper);
//    needChange[0] = END_UNIX;
//    fwrite(needChange,sizeof(char), 1,helper);
//  }
//}
//
///***************************************************************************************************
// Function Name:swapBytes
// Function input:short int* array
// Function Action:the function get an array of type short int and in each word it swap bytes
// Function output:none
// **************************************************************************************************/
//void swapBytes(short int* buff)
//{
//  char temp;//temp varible
//  char *bytesBuff;//pointer of type char in size of one byte
//  int i =0;//index for loop
//  //as long we didnt finish go over the aray
//  for (i = 0; i < sizeof(buff) ; i++)
//  {
//    //typecast of buff[i] to char pointer
//    bytesBuff = (char*)(&(buff[i]));
//    //save the first byte in temp
//    temp = bytesBuff[0];
//    //update first byte
//    bytesBuff[0]=bytesBuff[1];
//    //finish swap action
//    bytesBuff[1]=temp;
//  }
//}
//
///***************************************************************************************************
// Function input:a pointer to a block of memory, the format of \n or \r in binary,
//                a flag which tells us to which format conert the file to,and a pointer
//                oftype FILE to the output file
// Function Action:this function takes care of the case where the file needs to be converted to windows
//                 format. in that case we'll consider the fact that end line in windows consists of
//                 two characters(of two bytes each)
// Function output:the func return 1 if indeed we change to windows,else return 0
// **************************************************************************************************/
//
//int checkEndLine(char* buff,char check,const char* flag2,FILE* helper )
//{
//  //check if the current buffer consists new line charcter in binary
//  if(buff[0] ==check)
//  {
//    applyChange(buff,flag2,helper);//call applyChange function to thake care of the case//
//    return 1;
//  }
//  return 0;
//}
//
///***************************************************************************************************
// Function Name:copyAndConvert
// Function input: input&output files names,input format & output format
// Function Action:this function copy one file into a new file with the correct name and convert it to
//                 to the required format
// Function output:none
// **************************************************************************************************/
//
//void copyAndConvert(const char *fileName, const char* destFile,const char *flag1,
//                    const char* flag2,const char* swapOrKeep )
//{
//
//  char buff[2];//buffer to save what we read from the file
//  char buffCheck[2];//help buffer
//  //pointer to the input & output files
//  FILE *in, *helper;
//  in = fopen(fileName,"rb");//open both files in binary mode
//  helper = fopen("help", "wb");
//  //as long as we didnt finish reading file we keep reading one element in size of short int (2 bytes) each time
//  while ((fread(buff , sizeof(char), 1,in) )> 0)
//  {
//    //copy from unix to...
//    if(strcmp(flag1,"-unix")==0)
//    {
//      //call checkEndLine function which takes care of the case we need convert to windows format
//      if(checkEndLine(buff,END_UNIX,flag2,helper)==0)
//      {
//        //if this is no end line continue copy file
//        fwrite(buff,sizeof(char), 1,helper);
//      }
//
//    }//copy from mac to...
//    else if (strcmp(flag1,"-mac")==0)
//    {
//
//      //call checkEndLine function which takes care of the case we need convert to windows format
//      if(checkEndLine(buff,END_MAC,flag2,helper)==0)
//      {
//        //if this is no end line continue copy file
//        fwrite(buff,sizeof(char), 1,helper);
//      }
//
//
//    }//from win to
//    else if(strcmp(flag1,"-win")==0)
//    {
//      //check if current byte equals to '\r'
//      if(buff[0] == END_MAC)
//      {
//        //in c array containing the characters terminated with a null character
//        fread(buff , sizeof(char), 1,in);//check \0
//        //first check if it equals to '/r'
//        if(fread(buff , sizeof(char), 1,in) > 0)//now check if there is more bytes to read
//        {
//          //call checkEndLine function which takes care of the case we need convert to windows format
//          if(checkEndLine(buff,END_UNIX,flag2,helper)==0)
//          {
//            buffCheck[0]=END_MAC;
//            fwrite(buffCheck,sizeof(char), 1,helper);
//            //in c array containing the characters terminated with a null character
//            buffCheck[0]=NULL_TEMINATOR;
//            fwrite(buffCheck,sizeof(char), 1,helper);
//            //buffCheck[1]=buff[0];
//            fwrite(buff,sizeof(char), 1,helper);
//
//          }//if this is no end line continue copy file
//        }
//        else
//          fwrite(buff,sizeof(char), 1,helper);
//      }
//      else
//        fwrite(buff,sizeof(char), 1,helper);
//    }
//  }
//  fclose(in);
//  fclose(helper);//close both file after we done
//  //copyFile("help",destFile);
//  //call swapFile function
//  swapFile("help", destFile,swapOrKeep);
//}
//
///***************************************************************************************************
// Function Name: copyFile
// Function input: input & output files names
// Function Action: this function just copy a given file to another
// Function output:none
// **************************************************************************************************/
//
//void copyFile(const char *fileName, const char* destFile)
//{
//  //buffer for reading chars
//  char buff[4];
//  //save the value fread function return - number of elements read
//  size_t n;
//  FILE *in, *out;
//  in = fopen(fileName,"rb");//open both files in binary mode
//  out = fopen(destFile, "wb");
//  //as long as we didnt finish reading file
//  while ((n=fread(buff ,1, sizeof(buff),in) )!= 0)
//  {
//    fwrite(buff,1,n,out);//copy what fread read to the dest file
//  }
//  fclose(in);//close both files
//  fclose(out);
//
//}
//
///***************************************************************************************************
// Function Name: firstOption
// Function input: input & output files names
// Function Action: function for the first option - create a copy of given file
// Function output: none
// **************************************************************************************************/
//
//void firstOption(const char *fileName, const char* destFile)
//{
//  //if copyFile function succeed (the surce file exists)
//  copyFile(fileName,destFile);
//}
//
///***************************************************************************************************
// Function Name: secondOption
// Function input: input & output files names
// Function Action: function for the first option - create a copy of given file
// Function output: none
// **************************************************************************************************/
//
//void secondOption(const char *fileName, const char* destFile,const char *flag1, const char* flag2)
//{
//  copyAndConvert(fileName,destFile,flag1,flag2,KEEP);
//}
//
///***************************************************************************************************
// Function Name: thirdOption
// Function input: input & output files names
// Function Action: function for the first option - create a copy of given file
// Function output: none
// **************************************************************************************************/
//
//void thirdOption(const char *fileName, const char* destFile,const char *flag1,
//                 const char* flag2, const char* swapOrNot)
//{
//  copyAndConvert(fileName,destFile,flag1,flag2,swapOrNot);
//}
//
///***************************************************************************************************
// Function Name: isFileExists
// Function input: the input file name
// Function Action: check if the file exists
// Function output:return 1 if the file exist, else return 0
// **************************************************************************************************/
//
//int isFileExists(const char *fileName)
//{
//  FILE *file;
//  //try to open and read the file
//  if (file = fopen(fileName,"rb"))
//  {
//    fclose(file);
//    return 1;
//  }
//  return 0;
//}
//
