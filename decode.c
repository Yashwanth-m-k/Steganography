#include <stdio.h>
#include<string.h>
#include "decode.h"
#include "types.h"
char out_fname[]="output";
int flag=0;
/*   ------------Decoding function prototype -------------------*/
Status open_bmp_stego_file(FILE *fptr_bmp_image,char *stego_dimage_fname,DecodeInfo *decInfo)
{
   printf("INFO : Opening required files\n");
    decInfo->fptr_bmp_image=fopen(decInfo->stego_dimage_fname,"r");
    if(decInfo->fptr_bmp_image == NULL)
    {
        perror("fopen");
       fprintf(stderr,"ERROR:Unable to open file %s\n",decInfo->stego_dimage_fname);
        return e_failure;
    }
    printf("INFO : Opened  %s\n",decInfo->stego_dimage_fname);
    
    return e_success;

}
Status read_and_validate_decode_args(int argc,char *argv[],char *secret_fname,DecodeInfo *decInfo)
 {
    const char *extension = ".bmp";


    // Check if the number of arguments is valid
    if (argc < 3 || argc > 4) {
        
        return 1; // Exit with error
    }

    // Check if argv[2] ends with ".bmp"
    size_t arg2_len = strlen(argv[2]);
    if (arg2_len >= strlen(extension) && strcmp(argv[2] + arg2_len - strlen(extension), extension) == 0) {
        decInfo->stego_dimage_fname = argv[2];
       
    }
     else
      {
        
        return e_failure; // Exit with error
    }

    // Handle the secret file name
    if (argc == 4) {
        decInfo->secret_fname = argv[3];
        
    } 
    else {
        printf("INFO : Output file not mentioned.creating output.txt as default\n");
           flag=1;
        decInfo->secret_fname=out_fname;// Default value
        
       
    }
    return e_success;

    
}




Status do_Decoding(DecodeInfo *decInfo)
{
     printf("INFO : ## Decoding  Procedure started ##\n");

   if(open_bmp_stego_file(decInfo->fptr_bmp_image,decInfo->stego_dimage_fname,decInfo)==e_success)
   {
  
        if(Skip_bmp_header(decInfo->fptr_bmp_image)==e_success)
         {
             if(decode_magic_string(decInfo->fptr_bmp_image,decInfo->fptr_secret_image,decInfo)==e_success)
             {
                 if(decode_secret_file_extn_size(decInfo->secret_exten_size,decInfo)==e_success)
                {
                  if(decode_secret_file_extn(decInfo->secret_fname,decInfo->secret_exten_size,decInfo->secret_file_exten,decInfo)==e_success)
                 {
                     if(decode_secret_file_size(decInfo)==e_success)
                     {
                         if(decode_secret_file_data(decInfo)==e_success)
                        {
                            return e_success;
                        }
                     }
                 }
                }
             }
         }
   }

   else
   {
    return e_failure;
   }

}
Status Skip_bmp_header(FILE *fptr_bmp_image)
{
   fseek(fptr_bmp_image,54,SEEK_SET);

  
    long fileSize = ftell(fptr_bmp_image);
     return e_success;

}
Status decode_magic_string(FILE *fptr_bmp_image,FILE *fptr_secret_image,DecodeInfo *decInfo)
{
    printf("INFO : Decoding Magic String Signeture \n");
    char magic_string[3],buffer[8];
    int i;
    for(i=0; i<2; i++)
    {
        fread(buffer,8,1,fptr_bmp_image);//copying data from serete image file to temp buffer variable
    
    magic_string[i]=decode_byte_from_LSB(buffer);//call funtion for encodeing the LSB bits
        
    }
    magic_string[i]='\0';
   char str[3];

 printf("       Enter the Magic String : ");
  L1:  scanf("%2s",str);// limited the charactor 2
   
  

   if((strcmp(magic_string,str)==0))
    { 
        printf("INFO : Done\n");
        return e_success;
    }
    else
    {
        printf("You Have Enter wrong Magic String !!!\n");
       printf("-------->Enter the Magic String :");
       goto L1; 
  

    }
         return e_success;

}
char decode_byte_from_LSB(char *buffer)
{
        char ch=0;
        int i;
  
        for(i=0;i<8;i++)
        {
            int get=buffer[i] & 1;
            get =get<<i;
            
            ch=ch | get;
        
        
        }
      //   printf("%x",ch);
        //printf("\n");
        return ch;
}
Status decode_secret_file_extn_size(int secret_exten_size,DecodeInfo *decInfo)
{
   printf("INFO : Decoding Output File Extension Size \n");
    char buffer[32];
    fread(buffer,32,1,decInfo->fptr_bmp_image);
  decInfo->secret_exten_size=decode_size_from_lsb(buffer);
   printf("INFO : Done\n");
    return e_success;
}
int decode_size_from_lsb(char *buffer)
{
   int  data=0;int i;
      for(i=0;i<32;i++)
        {
            int get=buffer[i] & 1;
            get =get<<i;
            
            data=data | get;
            
        }
      
        return data;
        
}
Status decode_secret_file_extn(char *secret_fname,int secret_exten_size,char *secret_file_exten, DecodeInfo *decInfo)
{
    printf("INFO : Decoding output File Extension\n");

   
    char extension[decInfo->secret_exten_size+1];
   
    
   char buffer[8];
  int i;
    for(i=0;i<decInfo->secret_exten_size;i++)
    {
        fread(buffer,8,1,decInfo->fptr_bmp_image);
        extension[i]=decode_byte_from_LSB(buffer);
    }
    extension[i]='\0';
    
   
     
     if(flag==1){
         strcat(out_fname,extension);
     
     strcpy(decInfo->secret_fname,out_fname);
     }
    else{
             strcat(decInfo->secret_fname,extension);
    }
   
   

   decInfo->fptr_secret_image=fopen(decInfo->secret_fname,"w");
    if(decInfo->fptr_secret_image == NULL)
    {
        perror("fopen");
        fprintf(stderr,"ERROR : unable to open file %s\n",decInfo->secret_fname);
        return e_failure;
    }
     printf("INFO : Opened  %s\n",decInfo->secret_fname);
    

     
    return e_success;
}
Status decode_secret_file_size(DecodeInfo *decInfo)
{
    printf("INFO : Decoding Secret File Size \n");
    char buffer[32];
    fread(buffer,32,1,decInfo->fptr_bmp_image);
   decInfo->secret_file_size=decode_size_from_lsb(buffer);
   
    printf("INFO : Done \n");
     return e_success;
}
Status decode_secret_file_data(DecodeInfo *decInfo)
{
      printf("INFO : Decoding Secret File Data \n");
    char ch;
    char buffer[8];
    int i;
    for(i=0;i<decInfo->secret_file_size;i++)
    {
        fread(buffer,8,1,decInfo->fptr_bmp_image);
        ch=decode_byte_from_LSB(buffer);

       
        fwrite(&ch,1,1,decInfo->fptr_secret_image);
         
    }
  
    printf("##  Decoding Data Successfully  ##\n");
    return e_success;

}