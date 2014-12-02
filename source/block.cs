public class block{
	
	public void block(int id){
		int this.id = id;
		int this.num = 0;
		bool this.hasMoved = 0;
	}

	public void editBlock(int id, int num, bool hasMoved){
		int this.id = id;
		int this.num = num;
		bool this.hasMoved = hasMoved;		
	}

	int getID(){
		return this.id;
	}

	int getNum(){
		return this.num;
	}

	bool getHasMoved(){
		return this.hasMoved;
	}
}
