#include <stdio.h>
#include <stdlib.h>
#include "libBitmap.h"
#include "./jpeg-6b/jpeglib.h"

int main (int argc, char **argv)
{
    int screen_width;
    int screen_height;
    int bits_per_pixel;
    int line_length;
    int cols = 0, rows = 0;
	char *data;
	//FrameBuffer init
    if ( fb_init(&screen_width, &screen_height, &bits_per_pixel, &line_length) < 0 )
	{
		printf ("FrameBuffer Init Failed\r\n");
		return 0;
	}
	//Clear FB.
	fb_clear();
	
	
	int i=0;
	while (1)
	for (i=99; i<=3285;i++)
	{
		char filename[200]={0,};
		snprintf(filename,200,"./superm/supermario_%05d.jpg",i);
		//FileRead
		int error=0;
		struct jpeg_decompress_struct cinfo;
		struct jpeg_error_mgr jerr;
	 	cinfo.err = jpeg_std_error(&jerr);
   		jpeg_create_decompress(&cinfo);
		FILE *fp = fopen(filename, "rb");
    	jpeg_stdio_src(&cinfo, fp);
		jpeg_read_header(&cinfo, TRUE); 
		//printf ("JPG %d by %d by %d, %d\n",
		//	cinfo.image_width,cinfo.image_height,cinfo.num_components, cinfo.output_scanline);
		cols = cinfo.image_width;
		rows = cinfo.image_height;

		data = malloc(cols*rows*3);
		int currPoint = 0;
		jpeg_start_decompress(&cinfo);
		while(cinfo.output_scanline < cinfo.output_height) 
		{
			//printf ("CInfoScanlines:%d\r\n",cinfo.output_scanline);
			char *tempPtr=&data[currPoint];
			jpeg_read_scanlines(&cinfo, (JSAMPARRAY)&tempPtr, 1);
			currPoint+=cols*3;
		}
		jpeg_finish_decompress(&cinfo);
		jpeg_destroy_decompress(&cinfo);
		fclose(fp);

		fb_write_reverse(data, cols,rows);
		free(data);

	}
	fb_close();
    return 0;
}
