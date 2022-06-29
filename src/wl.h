#ifndef _WL_H_
#define _WL_H_

#define BYTE unsigned char

class CharImage;
class PictImage;

struct IL{
void Error(char* msg);
void Warning(char* msg);
};


class CharImage:public IL{
public:
	BYTE* pBuffer;
	int WidthOfImage;
	int HeightOfImage;
		
	CharImage(int width = 176, int height = 144);
	CharImage(char* FileName, int width = 176, int height = 144);
	CharImage& operator=(CharImage& CI);
	
	~CharImage();
	
	BYTE& pixel(int X,int Y){
		if(X<0) X=0;
		else if(X>WidthOfImage-1) X=WidthOfImage-1;
		if(Y<0) Y=0;
		else if(Y>HeightOfImage-1) Y = HeightOfImage-1;
		
		return *(pBuffer+Y*WidthOfImage+X);
	}
	
	int GetWidthOfImage(){ return WidthOfImage; }
	int GetHeightOfImage(){ return HeightOfImage; }
	BYTE* GetBuffer(){ return pBuffer; }
	
	void clean();
	void Load(char* FileName, int width = 176, int height = 144, int offset=0);
	void Save(char* FileName, int append=0);
};


class PictImage :public CharImage{
public:
  CharImage Y;
  CharImage U;
  CharImage V;
  
  PictImage(char *filename, int width=176, int height=144);
  PictImage(int width = 176, int height=144);
  PictImage& operator=(PictImage& CI);
  
  void clean(){
    Y.clean();
    U.clean();
    V.clean();
  };
  void Load(char *fileName, int width = 176, int height = 144, int frame_no=0);
  void Save(char *filename, int append = 0);
};

float psnr(CharImage& A, CharImage& B);

#endif
