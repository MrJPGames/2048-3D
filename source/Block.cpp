#include "Block.h"


Block::Block(){
	id = 0;
	num = 0;
	hasMerged = false;
}

Block::Block(int var1, int var2, bool var3){
	editBlock(var1, var2, var3);
}

void Block::setID(int var1){
	id = var1;
}

void Block::editBlock(int var1, int var2, bool var3){
	id = var1;
	num = var2;
	hasMerged = var3;		
}

int Block::getID(){
	return id;
}

int Block::getNum(){
	return num;
}

bool Block::getHasMerged(){
	return hasMerged;
}