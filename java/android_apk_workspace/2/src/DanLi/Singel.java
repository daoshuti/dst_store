package DanLi;

public class Singel {

	
	/**
	 * @param args
	 */
	private int a;
	
	private Singel(int a){
		this.a = a;
	}
	public static Singel getA() {
		Singel demo = new Singel(10);
		return demo;
	}
	int get_A(){
		return this.a;
	}
}
