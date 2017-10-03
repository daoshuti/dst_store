package GouZaoQi;

class Man{
	private int age;
	private String name;
	private String sex;
	
	public Man(int a,String b,String c){
		age = a;
		name = b;
		sex = c;
	}
	
	public String getSex() {
		return sex;
	}
	public void setSex(String sex) {
		this.sex = sex;
	}
	public void setAge(int a){
		if(a<0 || a>100){
			System.out.println("年龄输入有误");
			System.exit(0);
		}
		age = a;
	}
	public int getAge(){
		return age;
	} 
	public void setName(String b){
		if(b.length() > 4){
			System.out.println("名称输入有误");
			System.exit(0);
		}
		name = b;
	}
	public String getName(){
		return name;
	}
}
public class GouZaoQi {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Man me = new Man(18,"wanghan","man");
		System.out.println(me.getAge());
	}

}
