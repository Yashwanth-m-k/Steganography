#ifndef DECODE_H
#define DECODE_H

#include "types.h"
/*   ------------Decoding function prototype -------------------*/
typedef struct decode
{
    char *stego_dimage_fname;
    FILE *fptr_bmp_image;

    char *secret_fname;
    FILE *fptr_secret_image;

    int secret_exten_size;
    char *secret_file_exten;
   int secret_file_size;
   

} DecodeInfo;

/*   ------------Decoding function prototype -------------------*/

Status read_and_validate_decode_args(int argc,char *argv[],char *secret_fname, DecodeInfo *decInfo);
//
Status do_Decoding(DecodeInfo *decInfo);
//
Status open_bmp_stego_file(FILE *fptr_bmp_image,char *stego_dimage_fname,DecodeInfo *decInfo);
//open only bmp stego file 1st time
Status Skip_bmp_header(FILE *fptr_bmp_image);
//

Status decode_magic_string(FILE *fptr_bmp_image,FILE *fptr_secret_image,DecodeInfo *decInfo);
//s
char decode_byte_from_LSB(char *buffer);
//
Status decode_secret_file_extn_size(int secret_exten_size,DecodeInfo *decInfo);
//
int decode_size_from_lsb(char *buffer);
//
Status decode_secret_file_extn(char *secret_fname,int secret_exten_sizechar,char *secret_file_exten, DecodeInfo *decInfo);
//
Status decode_secret_file_size(DecodeInfo *decInfo);
//
Status decode_secret_file_data(DecodeInfo *decInfo);
//
#endif
