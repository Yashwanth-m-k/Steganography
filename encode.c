#include <stdio.h>
#include<string.h>
#include "encode.h"
#include "types.h"
#include "common.h"

/* Function Definitions */

/* Get image size
 * Input: Image file ptr
 * Output: width * height * bytes per pixel (3 in our case)
 * Description: In BMP Image, width is stored in offset 18,
 * and height after that. size is 4 bytes
 */
uint get_image_size_for_bmp(FILE *fptr_image)
{
    uint width, height;
    // Seek to 18th byte
    fseek(fptr_image, 18, SEEK_SET);

    // Read the width (an int)
    fread(&width, sizeof(int), 1, fptr_image);   //call this incheck capacity
   

    // Read the height (an int)
    fread(&height, sizeof(int), 1, fptr_image);
   

    // Return image capacity
    return width * height * 3;
}

/* 
 * Get File pointers for i/p and o/p files
 * Inputs: Src Image file, Secret file and
 * Stego Image file
 * Output: FILE pointer for above files
 * Return Value: e_success or e_failure, on file errors
 */
Status open_files(char *src_image_fname,EncodeInfo *encInfo)
{
    // Src Image file
    encInfo->fptr_src_image = fopen(encInfo->src_image_fname, "r");
    // Do Error handling
    
    if (encInfo->fptr_src_image == NULL)
    {
    	perror("fopen");
    	fprintf(stderr, "ERROR: Unable to open file %s\n", encInfo->src_image_fname);

    	return e_failure;
    }

    // Secret file
    encInfo->fptr_secret = fopen(encInfo->secret_fname, "r");
    // Do Error handling
    if (encInfo->fptr_secret == NULL)
    {
    	perror("fopen");
    	fprintf(stderr, "ERROR: Unable to open file %s\n", encInfo->secret_fname);

    	return e_failure;
    }

    // Stego Image file
    encInfo->fptr_stego_image = fopen(encInfo->stego_image_fname, "w");
    // Do Error handling
    if (encInfo->fptr_stego_image == NULL)
    {
    	perror("fopen");
    	fprintf(stderr, "ERROR: Unable to open file %s\n", encInfo->stego_image_fname);

    	return e_failure;
    }

    // No failure return e_success
    return e_success;
}

OperationType check_operation_type(int argc,char *argv[])
{
   int i;
   
    //checking argv[1] if it is "-e" >> then return e_encode
    if((strcmp(argv[1],"-e")==0))
    {
        return e_encode;
    }
    //else if => checking argv[1] is "-d" =>return e_decode
    else if((strcmp(argv[1],"-d")==0))
    {
        return e_decode;
    }
    //else => return e_unsupported
    else
    {
        return e_unsupported;
    }
   
    
    
}
Status read_and_validate_encode_args(int argc,char *argv[], EncodeInfo *encInfo)

{
    printf("INFO : Opening Required Files\n");
    char *BMP,*Extn;

    if(BMP=strstr(argv[2],".bmp"))
    {
        if((strcmp(BMP,".bmp")==0))
        {
             encInfo->src_image_fname=argv[2];
             printf("INFO : Opened %s\n",encInfo->src_image_fname);
        }
    }
        else{
            return e_failure;}
    
    if(Extn=strstr(argv[3],"."))
    { 
        if((strcmp(Extn,".txt")==0))//check here
        {
           strcpy(Extn,".txt");
        encInfo->secret_fname=argv[3];
        strcpy(encInfo->extn_secret_file,Extn);
        printf("INFO : Opened %s\n",encInfo->secret_fname);
         
        }
        else if((strcmp(Extn,".c")==0))
        {
            strcpy(Extn,".c");
            encInfo->secret_fname=argv[3];
        strcpy(encInfo->extn_secret_file,Extn);
        printf("INFO : Opened %s\n",encInfo->secret_fname);
        }
        else if((strcmp(Extn,".sh")==0))
        {
                strcpy(Extn,".sh");
            encInfo->secret_fname=argv[3];
        strcpy(encInfo->extn_secret_file,Extn);
        printf("INFO : Opened %s\n",encInfo->secret_fname);
        }
    
        else
        {
            return e_failure;
        }
    }
    
    if(argc==5)
    {
        char *var;
        if(var=strstr(argv[4],".bmp"))
        { 
             if((strcmp(var,".bmp")==0)){
               
         encInfo->stego_image_fname=argv[4];
          printf("INFO : Opened %s\n",encInfo->stego_image_fname);
             }
        }
        else
        {
            return e_failure;
        }
    }
    else
    {
       printf("INFO : Output file not mentioned.creating output.txt as default\n");
        char out_stego[15]="Output.bmp";
        strcpy(encInfo->stego_image_fname,out_stego);
      printf("INFO : Opened %s\n",encInfo->stego_image_fname);
       
    }
    printf("INFO : Done\n");
     return e_success;

}
Status do_encoding(EncodeInfo *encInfo)
{
   
    
    int ret=open_files(encInfo->src_image_fname,encInfo);
     if(ret==e_success)
     {
    
      
            printf("INFO : ## Encoding Procedure Strarted ##\n");
       
    
        int check = check_capacity(encInfo);
        if(check == e_success)
        {
        
             if(copy_bmp_header(encInfo->fptr_src_image,encInfo->fptr_stego_image)==e_success)
             {
                //passing secret image and stego image address to copying
                if(encode_magic_string(MAGIC_STRING,encInfo)==e_success)
                {
                //passing magic string for encode
                    if(encode_secret_file_extn_size(strlen(encInfo->extn_secret_file),encInfo)==e_success)
                    {
                //passing extn secret file to encode extention
                         if(encode_secret_file_extn(encInfo->extn_secret_file,encInfo)==e_success)
                        {
                         //
                        if(encode_secret_file_size(encInfo->size_secret_file,encInfo)==e_success)
                            {
                             //
                             if(encode_secret_file_data(encInfo->size_secret_file,encInfo)==e_success)
                             {
                              //
                              if(copy_remaining_img_data(encInfo->fptr_src_image,encInfo->fptr_stego_image)==e_success)
                                 {
                                    return e_success;
                                 }   
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
else
{
    printf("ERROR : File not opend\n");
    return e_failure;
}
 

}
Status check_capacity(EncodeInfo *encInfo)
{
    printf("INFO : Checking  for %s file Size \n",encInfo->secret_fname);
     encInfo->size_secret_file=get_file_size(encInfo->fptr_secret);
     printf("INFO : %s file Data = %ld\n",encInfo->secret_fname,encInfo->size_secret_file);
     printf("INFO : Done Not Empty\n");


    encInfo->size_src_image_file=get_image_size_for_bmp(encInfo->fptr_src_image);
     
  printf("INFO : Checking for %s  capacity to handle %s\n",encInfo->src_image_fname,encInfo->secret_fname);
  int total_encode_size;
      
     total_encode_size=54 + (2 + 4 +strlen(encInfo->extn_secret_file) + 4 + (encInfo->size_secret_file))*8;
  
    
   

    if(encInfo->size_src_image_file>total_encode_size)
    {

    printf("INFO : Done.Found Ok\n");
       return e_success;
    }
    else
    {
         
       
      return e_failure;
    }
    

}
uint get_file_size(FILE *fptr)
{
    fseek(fptr,0,SEEK_END);
    return ftell(fptr);
}
Status copy_bmp_header(FILE *fptr_src_image, FILE *fptr_stego_image)
{
      printf("INFO : Copying Image Header\n");
    //copy 1st 54 bytes to the destination file (from fptr_src_image to fptr_dest_image)
    //we move the fptr upto EOF in previous get_file_size function

    rewind(fptr_src_image);//get back to 0th position
    char buffer[54];
    fread(buffer,54,1,fptr_src_image);//getting 54 bytes from fptr_src_image and store in temp
    fwrite(buffer,54,1,fptr_stego_image);
    printf("INFO : Done \n");
       return e_success;
}
Status encode_byte_to_lsb(char data, char *image_buffer)
{
    int i;
    for(i=0;i<8;i++)
    {
        int get=(data & 1<<i)>>i; //getting LSB bit from '#' character 
        image_buffer[i]=image_buffer[i]&(~1);
        image_buffer[i]=image_buffer[i] | get;
    }
   
}
Status encode_magic_string(const char *magic_string, EncodeInfo *encInfo)
{
    printf("INFO : Magic String Signature \n");

    
    //call function encode data to image 
 encode_data_to_image(magic_string,strlen(magic_string),encInfo->fptr_src_image,encInfo->fptr_stego_image);
     printf("INFO : Done \n");
     return e_success;
}
Status encode_data_to_image(const char *data, int size, FILE *fptr_src_image, FILE *fptr_stego_image)
{
    
    int i;
    char buffer[8];//reading 1 char at a time char is 1byte=>8 bits=>8 bytes
    //for loop
    for(i=0; i<size; i++)
    {
        fread(buffer,8,1,fptr_src_image);//copying data from serete image file to temp buffer variable
        
        encode_byte_to_lsb(data[i],buffer);//call funtion for encodeing the LSB bits
       

        fwrite(buffer,8,1,fptr_stego_image);//cooping replaced LSB bit(encoded) data to stego_image file
      
    }
   

}

Status encode_secret_file_extn_size(int extn_size, EncodeInfo *encInfo)
{

    printf("INFO : %s file Extension Size \n",encInfo->secret_fname);
    char buffer[32];
    fread(buffer,32,1,encInfo->fptr_src_image);
    encode_size_to_lsb(extn_size,buffer);
    fwrite(buffer,32,1,encInfo->fptr_stego_image);
     printf("INFO : Done \n");
        return e_success;
}
Status encode_size_to_lsb(int data,char *buffer)
{
    int i;
    for(i=0; i<32; i++)
    {
        int get=(data & 1<<i)>>i;  
        buffer[i]=buffer[i]&(~1);
        buffer[i]=buffer[i] | get;
    }
}
Status encode_secret_file_extn(const char *file_extn, EncodeInfo *encInfo)
{
    printf("INFO : %s file Extension \n",encInfo->secret_fname);
   encode_data_to_image(file_extn,strlen(file_extn),encInfo->fptr_src_image,encInfo->fptr_stego_image);
            printf("INFO : Done \n");
            return e_success;

}
Status encode_secret_file_size(long file_size, EncodeInfo *encInfo)
{
    printf("INFO : %s file Size \n",encInfo->secret_fname);
    
    char buffer[32];
    fread(buffer,32,1,encInfo->fptr_src_image);
    encode_size_to_lsb(file_size,buffer);
    fwrite(buffer,32,1,encInfo->fptr_stego_image);

  
  printf("INFO : Done \n");
   return e_success;
   

}
 Status encode_secret_file_data(long size_secret_file,EncodeInfo *encInfo)
{
    printf("INFO : %s file Data \n",encInfo->secret_fname);
   rewind(encInfo->fptr_secret);
  
   
    char file_data[encInfo->size_secret_file];
    fread(file_data,encInfo->size_secret_file,1,encInfo->fptr_secret);
    file_data[encInfo->size_secret_file+1]='\0';

    encode_data_to_image(file_data,encInfo->size_secret_file,encInfo->fptr_src_image,encInfo->fptr_stego_image);

  printf("INFO : Done \n");
   return e_success;
   
}
Status copy_remaining_img_data(FILE *fptr_src_image, FILE *fptr_stego_image)
{
    printf("INFO : Copying Left Over Data\n");
    
      size_t bytesRead;
    char buffer[1]; // Buffer to hold one byte
   
    // Read and write one byte at a time
    while ((bytesRead = fread(&buffer, 1, 1, fptr_src_image)) > 0) {
        
        fwrite(buffer,1,1,fptr_stego_image);
        
    }
    printf("INFO : Done \n");
   
  printf("INFO : ## Encoding Done Successfully ##\n");
   return e_success;

}
