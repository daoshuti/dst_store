package CongXie;

class Birder{
	void fly(){
		System.out.println("会飞");
	}
}

class TuoNiao extends Birder{
	void fly(){		
		System.out.println("吃胖了，飞不动");
	}
}

public class ChongXie {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		TuoNiao tn = new TuoNiao();
		tn.fly();
	}

}
