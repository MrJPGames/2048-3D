#include "Block.h"


Block::Block(){
	val = 0;
	hasMerged = false;
	transparancy=0;
}

Block::Block(int var2, bool var3){
	editBlock(var2, var3);
}

void Block::editBlock(int var2, bool var3){
	val = var2;
	hasMerged = var3;
}

void Block::editBlock(int var2, bool var3, int var1){
	val = var2;
	hasMerged = var3;
	transparancy=var1;
}

int Block::getVal(){
	return val;
}
bool Block::getHasMerged(){
	return hasMerged;
}
int Block::getTransparancy(){
	return transparancy;
}
void Block::setTransparancy(int trans){
	transparancy=trans;
}