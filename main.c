#include <stdio.h>
#include "encode.h"
#include "types.h"
#include "decode.h"

int main(int argc,char *argv[])
{
    EncodeInfo *encInfo;
    DecodeInfo *decInfo;
    int i;

    if(argc == 1)
    {
         printf("./a.out : Encoding: ./a.out -e <.bmp.file> <.txt.file> [output file]\n");
         printf("./a.out : Decoding: ./a.out -d <.bmp.file> [output file]\n");
         return 0;

    }
   
    //check operation type
    //call the check_operation_type function
    int ret=check_operation_type(argc,argv);
    
           

    if(ret==0)
    {   
        
        if(argc >= 4 && argc<= 5)
        {
            

            //start the encoding
            int check=read_and_validate_encode_args(argc,argv,encInfo);
            if(check == e_success)
            {

              do_encoding(encInfo);
            }
            else{
                printf("./a.out : Encoding: ./a.out -e <.bmp.file> <.txt.file> [output file <.bmp.file> ]\n");
            }
        }
        else{
            printf("./a.out : Encoding: ./a.out -e <.bmp.file> <.txt.file> [output file <.bmp.file>]\n");
            
        }
    }
   // if => e_decode
   if(ret==1)
    {
        if(argc==2)
          {
             printf("./a.out : Decoding: ./a.out -d <.bmp.file> [output file]\n");
          }
        
        if(argc ==4||argc==3 )
        {
            //start the decoding
         
        ret = read_and_validate_decode_args(argc,argv,decInfo->secret_fname,decInfo);
        if(ret==e_success)
        {
                
                 do_Decoding(decInfo);
        
        }
        else{
       
           
            printf("./a.out : Decoding: ./a.out -d <.bmp.file> [output file]\n");
        }
        
    }
    }
    
    
    
   
    return 0;
}
