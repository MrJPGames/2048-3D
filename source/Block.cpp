#include "Block.h"


Block::Block(){
	val = 0;
	hasMerged = false;
}

Block::Block(int var2, bool var3){
	editBlock(var2, var3);
}

void Block::editBlock(int var2, bool var3){
	val = var2;
	hasMerged = var3;
}

int Block::getVal(){
	return val;
}
bool Block::getHasMerged(){
	return hasMerged;
}