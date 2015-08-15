#include <3ds.h>
#include <cstring>
#include <cstdlib>
#include "Block.h"
#include "blocks_bin.h"
#include "bg_bin.h"

Block block[16];
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
void gfxDrawSpriteBlend(gfxScreen_t screen, gfx3dSide_t side, u8* spriteData, u16 width, u16 height, s16 x, s16 y, int alpha)
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
	spriteData+=yOffset*width*3;
	int j, i;
	for(j=yOffset; j<yOffset+heightDrawn; j++)
	{
		u8* fbd=&fbAdr[(x+xOffset)*3];
		u8* data=&spriteData[(xOffset)*3];
		for(i=xOffset; i<xOffset+widthDrawn; i++)
		{
			fbd[0] = ((data[0] * alpha)+(fbd[0] * (255 - alpha))) / 256;
			fbd[1] = ((data[1] * alpha)+(fbd[1] * (255 - alpha))) / 256;
			fbd[2] = ((data[2] * alpha)+(fbd[2] * (255 - alpha))) / 256;
			fbd+=3;
			data+=3;
		}
		fbAdr+=fbWidth*3;
		spriteData+=width*3;
	}
}
void render(){
	gfxDrawSprite(GFX_TOP, GFX_LEFT, (u8*)bg_bin, 240, 400, 0, 0);
	for (int i = 0; i < 4; i++){
		for (int j = 0; j < 4; j++){
			if (block[i*4+j].getTransparancy() < 255){
				gfxDrawSpriteBlend(GFX_TOP, GFX_LEFT, (u8*)blocks_bin+7203*block[i*4+j].getVal(), 49, 49, i*-52+175, j*52+96, block[i*4+j].getTransparancy());
			}else{
				gfxDrawSprite(GFX_TOP, GFX_LEFT, (u8*)blocks_bin+7203*block[i*4+j].getVal(), 49, 49, i*-52+175, j*52+96); 
			}
		}
	}
}
void updateTiles(){
	for (int i=0;i<16;i++){
		if (block[i].getTransparancy() < 255){
			block[i].setTransparancy(block[i].getTransparancy()+5);
		}
	}
}
void addRandomTiles(int amount){
	for (int i = 0; i<amount;i++){
		bool done=false;
		int tries=0;
		while (!done){
			int randpos = rand() %16;
			if (block[randpos].getVal() == 0){
				switch(rand() %10){
					case 0:
						block[randpos].editBlock(2,false, 0);
						break;
					default:
						block[randpos].editBlock(1,false, 0);
						break;
				}
				done=true;
			}
			tries+=1;
			if (tries == 100){
				for (int i = 0;i<16;i++){
					if (block[i].getVal() == 0){
						switch(rand() %10){
							case 0:
								block[i].editBlock(2,false, 0);
								break;
							default:
								block[i].editBlock(1,false, 0);
								break;
						}
						i=16;
					}
				}
				done=true;
			}
		}
	}
}
void endMove(bool moved){
	for (int i = 0; i<=15;i++){
		block[i].editBlock(block[i].getVal(), false);
		block[i].setTransparancy(255);
	}
	if (moved)
		addRandomTiles(1);
}
void resetGame(){
	for (int i=0;i < 16; i++){
		block[i].editBlock(0, false);
	}
	addRandomTiles(2);
}
void moveTilesLeft(){
	int pos;
	bool moved=false;
	for (int y = 0; y < 4; y++){
		for (int j = 4; j > 1; j--){
			for (int i = 1; i < j; i++){
				pos=y*4+i;
				if (!block[pos].getVal() == 0){
					if (block[pos].getVal() == block[pos-1].getVal() && !block[pos-1].getHasMerged() && !block[pos].getHasMerged()){
						block[pos-1].editBlock(block[pos].getVal()+1, true);
						block[pos].editBlock(0, false);
						moved=true;
					}
					if (block[pos-1].getVal() == 0){
						block[pos-1].editBlock(block[pos].getVal(), false);
						block[pos].editBlock(0, false);
						moved=true;
					}
				}
			}
		}
	}
	endMove(moved);
}
void moveTilesRight(){
	int pos;
	bool moved=false;
	for (int y = 0; y < 4; y++){
		for (int j = 0; j < 3; j++){
			for (int i = 2; i >= j; i--){
				pos=y*4+i;
				if (!block[pos].getVal() == 0){
					if (block[pos].getVal() == block[pos+1].getVal() && !block[pos+1].getHasMerged() && !block[pos].getHasMerged()){
						block[pos+1].editBlock(block[pos].getVal()+1, true);
						block[pos].editBlock(0, false);
						moved=true;
					}
					if (block[pos+1].getVal() == 0){
						block[pos+1].editBlock(block[pos].getVal(), false);
						block[pos].editBlock(0, false);
						moved=true;
					}
				}
			}
		}
	}
	endMove(moved);
}
void moveTilesUp(){
	int pos;
	bool moved=false;
	for (int x = 0; x < 4; x++){
		for (int j = 4; j > 1; j--){
			for (int i = 1; i < j; i++){
				pos=x+i*4;
				if (!block[pos].getVal() == 0){
					if (block[pos].getVal() == block[pos-4].getVal() && !block[pos-4].getHasMerged() && !block[pos].getHasMerged()){
						block[pos-4].editBlock(block[pos].getVal()+1, true);
						block[pos].editBlock(0, false);
						moved=true;
					}
					if (block[pos-4].getVal() == 0){
						block[pos-4].editBlock(block[pos].getVal(), false);
						block[pos].editBlock(0, false);
						moved=true;
					}
				}
			}
		}
	}
	endMove(moved);
}
void moveTilesDown(){
	int pos;
	bool moved=false;
	for (int x = 0; x < 4; x++){
		for (int j = 0; j < 3; j++){
			for (int i = 2; i >= j; i--){
				pos=x+i*4;
				if (!block[pos].getVal() == 0){
					if (block[pos].getVal() == block[pos+4].getVal() && !block[pos+4].getHasMerged() && !block[pos].getHasMerged()){
						block[pos+4].editBlock(block[pos].getVal()+1, true);
						block[pos].editBlock(0, false);
						moved=true;
					}
					if (block[pos+4].getVal() == 0){
						block[pos+4].editBlock(block[pos].getVal(), false);
						block[pos].editBlock(0, false);
						moved=true;
					}
				}
			}
		}
	}
	endMove(moved);
}



int main()
{
	// Initialize services
	srvInit();
	aptInit();
	hidInit(NULL);
	gfxInitDefault();
	//gfxSet3D(true);
	resetGame();
	while (aptMainLoop())
	{
		updateTiles();
		hidScanInput();
		u32 kDown = hidKeysDown();
		if (kDown & KEY_START)
			break;
		if (kDown & KEY_LEFT)
			moveTilesLeft();
		if (kDown & KEY_RIGHT)
			moveTilesRight();
		if (kDown & KEY_UP)
			moveTilesUp();
		if (kDown & KEY_DOWN)
			moveTilesDown();
		if (kDown & KEY_X)
			resetGame();
		render();
		// Flush and swap framebuffers
		gfxFlushBuffers();
		gfxSwapBuffers();

		gspWaitForEvent(GSPEVENT_VBlank0, false);
	}

	// Exit services
	gfxExit();
	hidExit();
	aptExit();
	srvExit();
	return 0;
}
