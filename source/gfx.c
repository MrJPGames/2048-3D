#include "gfx.h"

void gfxDrawSprite(gfxScreen_t screen, gfx3dSide_t side, u8* spriteData, u16 width, u16 height, s16 x, s16 y)
{
	if(!spriteData)return;

	u16 fbWidth, fbHeight;
	u8* fbAdr=gfxGetFramebuffer(screen, side, &fbWidth, &fbHeight);

	if(x+width<0 || x>=fbWidth)return;
	if(y+height<0 || y>=fbHeight)return;

	u16 xOffset=0, yOffset=0;
	u16 widthDrawn=width, heightDrawn=height;

	if(x<0)xOffset=-x;
	if(y<0)yOffset=-y;
	if(x+width>=fbWidth)widthDrawn=fbWidth-x;
	if(y+height>=fbHeight)heightDrawn=fbHeight-y;
	widthDrawn-=xOffset;
	heightDrawn-=yOffset;

	int j;
	for(j=yOffset; j<yOffset+heightDrawn; j++)
	{
		memcpy(&fbAdr[((x+xOffset)+(y+j)*fbWidth)*3], &spriteData[((xOffset)+(j)*width)*3], widthDrawn*3);
	}
}
void gfxDrawSpriteAlpha(gfxScreen_t screen, gfx3dSide_t side, u8* spriteData, u16 width, u16 height, s16 x, s16 y)
{
	if(!spriteData)return;

	u16 fbWidth, fbHeight;
	u8* fbAdr=gfxGetFramebuffer(screen, side, &fbWidth, &fbHeight);

	if(x+width<0 || x>=fbWidth)return;
	if(y+height<0 || y>=fbHeight)return;

	u16 xOffset=0, yOffset=0;
	u16 widthDrawn=width, heightDrawn=height;

	if(x<0)xOffset=-x;
	if(y<0)yOffset=-y;
	if(x+width>=fbWidth)widthDrawn=fbWidth-x;
	if(y+height>=fbHeight)heightDrawn=fbHeight-y;
	widthDrawn-=xOffset;
	heightDrawn-=yOffset;

	//TODO : optimize
	fbAdr+=(y+yOffset)*fbWidth*3;
	spriteData+=yOffset*width*4;
	int j, i;
	for(j=yOffset; j<yOffset+heightDrawn; j++)
	{
		u8* fbd=&fbAdr[(x+xOffset)*3];
		u8* data=&spriteData[(xOffset)*4];
		for(i=xOffset; i<xOffset+widthDrawn; i++)
		{
			if(data[3])
			{
				fbd[0]=data[0];
				fbd[1]=data[1];
				fbd[2]=data[2];
			}
			fbd+=3;
			data+=4;
		}
		fbAdr+=fbWidth*3;
		spriteData+=width*4;
	}
}
void gfxDrawSpriteAlphaBlend(gfxScreen_t screen, gfx3dSide_t side, u8* spriteData, u16 width, u16 height, s16 x, s16 y)
{
	if(!spriteData)return;

	u16 fbWidth, fbHeight;
	u8* fbAdr=gfxGetFramebuffer(screen, side, &fbWidth, &fbHeight);

	if(x+width<0 || x>=fbWidth)return;
	if(y+height<0 || y>=fbHeight)return;

	u16 xOffset=0, yOffset=0;
	u16 widthDrawn=width, heightDrawn=height;

	if(x<0)xOffset=-x;
	if(y<0)yOffset=-y;
	if(x+width>=fbWidth)widthDrawn=fbWidth-x;
	if(y+height>=fbHeight)heightDrawn=fbHeight-y;
	widthDrawn-=xOffset;
	heightDrawn-=yOffset;

	//TODO : optimize
	fbAdr+=(y+yOffset)*fbWidth*3;
	spriteData+=yOffset*width*4;
	int j, i;
	for(j=yOffset; j<yOffset+heightDrawn; j++)
	{
		u8* fbd=&fbAdr[(x+xOffset)*3];
		u8* data=&spriteData[(xOffset)*4];
		for(i=xOffset; i<xOffset+widthDrawn; i++)
		{
			if(data[3])
			{
				u8 alphaSource = data[3];
				fbd[0] = ((data[0] * alphaSource)+(fbd[0] * (255 - alphaSource))) / 256;
				fbd[1] = ((data[1] * alphaSource)+(fbd[1] * (255 - alphaSource))) / 256;
				fbd[2] = ((data[2] * alphaSource)+(fbd[2] * (255 - alphaSource))) / 256;
			}
			fbd+=3;
			data+=4;
		}
		fbAdr+=fbWidth*3;
		spriteData+=width*4;
	}
}
void gfxDrawSpriteAlphaBlendFade(gfxScreen_t screen, gfx3dSide_t side, u8* spriteData, u16 width, u16 height, s16 x, s16 y, u8 fadeValue)
{
	if(!spriteData)return;

	u16 fbWidth, fbHeight;
	u8* fbAdr=gfxGetFramebuffer(screen, side, &fbWidth, &fbHeight);

	if(x+width<0 || x>=fbWidth)return;
	if(y+height<0 || y>=fbHeight)return;

	u16 xOffset=0, yOffset=0;
	u16 widthDrawn=width, heightDrawn=height;

	if(x<0)xOffset=-x;
	if(y<0)yOffset=-y;
	if(x+width>=fbWidth)widthDrawn=fbWidth-x;
	if(y+height>=fbHeight)heightDrawn=fbHeight-y;
	widthDrawn-=xOffset;
	heightDrawn-=yOffset;

	//TODO : optimize
	fbAdr+=(y+yOffset)*fbWidth*3;
	spriteData+=yOffset*width*4;
	int j, i;
	for(j=yOffset; j<yOffset+heightDrawn; j++)
	{
		u8* fbd=&fbAdr[(x+xOffset)*3];
		u8* data=&spriteData[(xOffset)*4];
		for(i=xOffset; i<xOffset+widthDrawn; i++)
		{
			if(data[3])
			{
				u8 alphaSource = (fadeValue * data[3]) / 256;
				fbd[0]=((data[0] * alphaSource) / 256)+((fbd[0] * (255 - alphaSource)) / 256);
				fbd[1]=((data[1] * alphaSource) / 256)+((fbd[1] * (255 - alphaSource)) / 256);
				fbd[2]=((data[2] * alphaSource) / 256)+((fbd[2] * (255 - alphaSource)) / 256);
			}
			fbd+=3;
			data+=4;
		}
		fbAdr+=fbWidth*3;
		spriteData+=width*4;
	}
}

void gfxFillColor(gfxScreen_t screen, gfx3dSide_t side, u8 rgbColor[3])
{
	u16 fbWidth, fbHeight;
	u8* fbAdr=gfxGetFramebuffer(screen, side, &fbWidth, &fbHeight);

	//TODO : optimize; use GX command ?
	int i;
	for(i=0; i<fbWidth*fbHeight; i++)
	{
		*(fbAdr++)=rgbColor[2];
		*(fbAdr++)=rgbColor[1];
		*(fbAdr++)=rgbColor[0];
	}
}
void gfxFillColorGradient(gfxScreen_t screen, gfx3dSide_t side, u8 rgbColorStart[3], u8 rgbColorEnd[3])
{
	u16 fbWidth, fbHeight;
	u8* fbAdr=gfxGetFramebuffer(screen, side, &fbWidth, &fbHeight);
	u8 colorLine[fbWidth*3];

	//TODO : optimize; use GX command ?
	int i;
	float n;
	float total = (float)(fbWidth - 1);
	// make slightly bigger to prevent gradients from blending around.  SHould be removed and have the gradient color be better later.
	total *= 1.5f;
	for(i=0; i<fbWidth; i++)
	{
		n = (float)i / total;
		colorLine[i*3+0]=(float)rgbColorStart[2] * (1.0f-n) + (float)rgbColorEnd[2] * n;
		colorLine[i*3+1]=(float)rgbColorStart[1] * (1.0f-n) + (float)rgbColorEnd[1] * n;
		colorLine[i*3+2]=(float)rgbColorStart[0] * (1.0f-n) + (float)rgbColorEnd[0] * n;
	}

	for(i=0; i<fbHeight; i++)
	{
		memcpy(fbAdr, colorLine, fbWidth*3);
		fbAdr+=fbWidth*3;
	}
}
