#ifndef Block_H
#define Block_H

class Block{
	public:
		Block(); //Make new block without vars!
		Block(int val, bool hasMerged); //Make new Block!
		void editBlock(int val, bool hasMerged); //edit block
		int getVal(); //get location ID
		bool getHasMerged(); //get merged?
	private:
		int val; //Number of Block
		bool hasMerged; //Has it merged during move?
};

#endif