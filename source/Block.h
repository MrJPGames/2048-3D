#ifndef Block_H
#define Block_H

class Block{
	public:
		Block(); //Make new block without vars!
		Block(int val, bool hasMerged); //Make new Block!
		void editBlock(int val, bool hasMerged); //edit block
		void editBlock(int val, bool hasMerged, int val2); //edit block with transparancy
		int getVal(); //get location ID
		bool getHasMerged(); //get merged?
		int getTransparancy();
		void setTransparancy(int trans);
	private:
		int val; //Number of Block
		bool hasMerged; //Has it merged during move?
		int transparancy;
};

#endif