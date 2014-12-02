
#ifndef Block_H
#define Block_H

class Block{
	public:
		Block(); //Make new block without vars!
		Block(int id, int num, bool hasMerged); //Make new Block!
		void editBlock(int id, int num, bool hasMerged); //edit block
		void setID(int ID); //Set location ID
		int getID(); //get location ID
		int getNum(); //get num
		bool getHasMerged(); //get merged?
	private:
		int id; //Blocks Location ID
		int num; //Number of Block
		bool hasMerged; //Has it merged during move?
};

#endif