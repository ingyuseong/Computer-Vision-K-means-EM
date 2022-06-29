#include <iostream>
#include <fstream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>          //for exit()
#include <math.h>
#include "wl.h"

inline int min(int a, int b){ return (a<b ? a:b);}

//class IL Member Function
using namespace std;

void IL::Error(char* msg){
	fprintf(stderr,"%s\n",msg);
	exit(1);
}

void IL::Warning(char* msg){
	cout<<msg<<endl;
}


// class CharImage Member Function 

CharImage::CharImage(int width,int height)
{ 
	pBuffer       = new BYTE[width*height];
	WidthOfImage  = width;
	HeightOfImage = height;
	if (!pBuffer) 
		Error("Not enough memory...1");
}

CharImage::CharImage(char* FileName,int width,int height)
{
	ifstream File(FileName,ios::in|ios::binary);
	if( File.bad() ) Error("Cannot open file");
	
	pBuffer = new BYTE[width*height];
	WidthOfImage = width;
	HeightOfImage = height;
	
	if (!pBuffer) 
		Error("Not enough memory...2");
	
	int ImageSize = width * height;
	
	File.read((char*) pBuffer,ImageSize);
}

CharImage::~CharImage(){
	delete pBuffer;
}


void CharImage::clean(){
	int dx, dy;
	
	for(dx=0; dx<WidthOfImage; dx++) for(dy=0; dy<HeightOfImage; dy++)
		this->pixel(dx,dy) = 0;
}

void CharImage::Load(char* filename,int width, int height, int offset){
	FILE *fin = fopen(filename, "rb");
	fseek(fin, offset, SEEK_SET);

	if( width ) WidthOfImage = width;
	if( height ) HeightOfImage = height;
	
	int ImageSize = WidthOfImage*HeightOfImage;
	delete pBuffer;

	pBuffer = new BYTE[ImageSize];
	
	if (!pBuffer)
		Error("Not enough memory...3");
	
	fread(pBuffer, sizeof(BYTE), ImageSize, fin);

	fclose(fin);
}

void CharImage::Save(char* filename, int append){
	FILE *fout;

	if(append)
		fout = fopen(filename, "ab");
	else
		fout = fopen(filename, "wb");
	
	fwrite(pBuffer, sizeof(BYTE), WidthOfImage*HeightOfImage, fout);
	
	fclose(fout);
}

CharImage& CharImage::operator=(CharImage& CI){
	delete pBuffer;
	
	WidthOfImage = CI.GetWidthOfImage();
	HeightOfImage = CI.GetHeightOfImage();
	
	pBuffer = new BYTE[WidthOfImage*HeightOfImage];
	
	for(int x=0; x<WidthOfImage; x++)
		for(int y=0; y<HeightOfImage; y++)
			*(pBuffer+y*WidthOfImage+x) = CI.pixel(x,y);
		
		return *this;
}

// PictImage class member function    
PictImage::PictImage(char *filename, int width, int height){
	CharImage CI;
	
	char str[100];
	sprintf(str, "%s.Y", filename);
	CI.Load(str, width, height);
	Y = CI;
	
	sprintf(str, "%s.U", filename);
	CI.Load(str, width/2, height/2);
	U = CI;
	
	sprintf(str, "%s.V", filename);
	CI.Load(str, width/2, height/2);
	V = CI;
}

void PictImage::Load(char *filename, int width, int height, int frame_no){
	int offset = frame_no * width * height * 3 / 2;

	Y.Load(filename, width, height, offset);
	
	offset += width*height;
	
	U.Load(filename, width/2, height/2, offset);
	
	offset += width*height/4;

	V.Load(filename, width/2, height/2, offset);
}

void PictImage::Save(char *filename, int append){
	Y.Save(filename, append);
	U.Save(filename, 1);
	V.Save(filename, 1);
}

PictImage::PictImage(int width, int height){
	CharImage A(width, height);
	Y = A;
	
	CharImage B(width/2, height/2);
	U = B;
	V = B;
}

PictImage& PictImage::operator=(PictImage& CI){
	Y = CI.Y;
	U = CI.U;
	V = CI.V;
	return *this;
}


float psnr(CharImage& A, CharImage& B)
{
	int width  = A.GetWidthOfImage();
	int height = A.GetHeightOfImage();
	
	if( width != B.GetWidthOfImage() || height != B.GetHeightOfImage() )
	{
		fprintf(stderr, "To compute PSNR, both image must have the same size!!!\n");
		exit(0);
	}
	
	double fnorm = .0;
	
	for(int dx=0; dx<width; dx++) for(int dy=0; dy<height; dy++){
		double temp = double(A.pixel(dx,dy)) - double(B.pixel(dx,dy));
		fnorm += temp*temp;
	}
	
	fnorm /= double(width*height);
	
	double psnr = 10*log(255.*255./fnorm)/log(10.);
	return float(psnr);
}


void InterpolateImage(CharImage& orig, CharImage& inter)
{
	int width  = orig.GetWidthOfImage();
	int height = orig.GetHeightOfImage();
	
	int x,y;
	
	for(y=0; y<height-1; y++){
		for(x=0; x<width-1; x++){
			inter.pixel(2*x,  2*y)   = orig.pixel(x,y);
			inter.pixel(2*x+1,2*y)   = (orig.pixel(x,y) + orig.pixel(x+1,y) + 1)>>1;
			inter.pixel(2*x,  2*y+1) = (orig.pixel(x,y) + orig.pixel(x,y+1) + 1)>>1;
			inter.pixel(2*x+1,2*y+1) = (orig.pixel(x,y) + orig.pixel(x,y+1)
				+ orig.pixel(x+1,y) + orig.pixel(x+1,y+1) + 2)>>2;
		}
		// last pixel in lines
		inter.pixel(2*width-2, 2*y) = orig.pixel(width-1, y);
		inter.pixel(2*width-1, 2*y) = orig.pixel(width-1, y);
		inter.pixel(2*width-2, 2*y+1) = (orig.pixel(width-1, y) + orig.pixel(width-1, y+1) + 1)>>1;
		inter.pixel(2*width-1, 2*y+1) = (orig.pixel(width-1, y) + orig.pixel(width-1, y+1) + 1)>>1;
	}
	
	// last line
	for(x=0; x<width-1; x++){
		inter.pixel(2*x, 2*height-2) = orig.pixel(x, height-1);
		inter.pixel(2*x, 2*height-1) = orig.pixel(x, height-1);
		inter.pixel(2*x+1, 2*height-2) = (orig.pixel(x, height-1) + orig.pixel(x+1, height-1) + 1)>>1; 
		inter.pixel(2*x+1, 2*height-1) = (orig.pixel(x, height-1) + orig.pixel(x+1, height-1) + 1)>>1; 
	}
	
	inter.pixel(2*width-2, 2*height-2) = orig.pixel(width-1, height-1);
	inter.pixel(2*width-1, 2*height-2) = orig.pixel(width-1, height-1);
	inter.pixel(2*width-2, 2*height-1) = orig.pixel(width-1, height-1);
	inter.pixel(2*width-1, 2*height-1) = orig.pixel(width-1, height-1);
}

