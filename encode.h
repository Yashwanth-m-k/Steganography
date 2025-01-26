#ifndef ENCODE_H
#define ENCODE_H

#include "types.h" // Contains user defined types

/* 
 * Structure to store information required for
 * encoding secret file to source Image
 * Info about output and intermediate data is
 * also stored
 */

//#define MAX_SECRET_BUF_SIZE 1
//#define MAX_IMAGE_BUF_SIZE (MAX_SECRET_BUF_SIZE * 8)
//#define MAX_FILE_SUFFIX 4

typedef struct _EncodeInfo
{
    /* Source Image info */
    char *src_image_fname; //stor the src_image_fname
    FILE *fptr_src_image; //file pointer for src_image
    uint image_capacity;//store the scr_image_filesize
    FILE *fptr_image;
   // uint bits_per_pixel;
   // char image_data[MAX_IMAGE_BUF_SIZE];
  

    /* Secret File Info */
    char *secret_fname;//store the src_img_fname
    FILE *fptr_secret;// file pointer for secret_fname
    char extn_secret_file[5];
   int  size_src_image_file;
    
    //char secret_data[MAX_SECRET_BUF_SIZE];
    long  size_secret_file;

    


    /* Stego Image Info */
    char *stego_image_fname; //stego image file name
    FILE *fptr_stego_image;  //stego file
    

} EncodeInfo;


/*   ------------Encoding function prototype -------------------*/

/* Check operation type */
OperationType check_operation_type(int argc,char *argv[]);

/* Read and validate Encode args from argv */
Status read_and_validate_encode_args(int argc,char *argv[], EncodeInfo *encInfo);

/* Perform the encoding */
Status do_encoding(EncodeInfo *encInfo);
//call open file
/* Get File pointers for i/p and o/p files */
Status open_files(char *src_image_fname,EncodeInfo *encInfo);
//call this fun in do encode
/* check capacity */
Status check_capacity(EncodeInfo *encInfo);

/* Get image size */
uint get_image_size_for_bmp(FILE *fptr_image);

/* Get file size */
uint get_file_size(FILE *fptr); //()

/* Copy bmp image header */
Status copy_bmp_header(FILE *fptr_src_image, FILE *fptr_dest_image);

/* Store Magic String */
Status encode_magic_string(const char *magic_string, EncodeInfo *encInfo);
//4th function call inside do_encode function for encode magic string 

/* Encode secret file extenstion */
Status encode_secret_file_extn(const char *file_extn, EncodeInfo *encInfo);
//5th function call inside do_encode function for encode extention of secret file
/* Encode secret file size */
Status encode_secret_file_size(long file_size, EncodeInfo *encInfo);

/* Encode secret file data*/
Status encode_secret_file_data(long size_secret_file,EncodeInfo *encInfo);

/* Encode function, which does the real encoding */
Status encode_data_to_image(const char *data, int size, FILE *fptr_src_image, FILE *fptr_stego_image);
//calling this function in encode magic string to perform encode data of magic string AND copy to stego_image file(fptr_stego_image)
 
/* Encode a byte into LSB of image data array */
Status encode_byte_to_lsb(char data, char *image_buffer);

/* Copy remaining image bytes from src to stego image after encoding */
Status copy_remaining_img_data(FILE *fptr_src, FILE *fptr_dest);

Status encode_secret_file_extn_size(int extn_size, EncodeInfo *encInfo);//new added fun
//encode secret file extn size 
Status encode_size_to_lsb(int data,char *buffer);//new added 
//encode secret file data at the time of encode secret file extn size





#endif
