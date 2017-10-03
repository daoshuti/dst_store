package cn.com.farsign;

/**
 * 1.创建对象
 * 
 */
 class Buyer{
	 void pay(){
		 System.out.println("支付组装电脑的钱");
	 }
	 void move(){
		 System.out.println("搬电脑回家");
	 }
 }
 
 class Expert{
	 void check(){
		 System.out.println("查看配置");
	 }
	 void look(){
		System.out.println("电脑城挑选配件"); 
	 }
	 void zuZhuang(){
		 System.out.println("组装电脑");
	 }
	 
 }

public class XuQiu {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Expert lz = new Expert();
		Buyer me = new Buyer();
		
		lz.check();
		lz.look();
		lz.zuZhuang();
		
		me.pay();
		me.move();
	}

}
