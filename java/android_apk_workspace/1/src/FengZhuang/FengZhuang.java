package FengZhuang;
class Man{
	private int age;
	private String name;
	private String sex;
	
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
public class FengZhuang {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Man me = new Man();
		me.setAge(24);
		me.setName("王涵");
		me.setSex("男");
		System.out.println("年龄："+me.getAge());
		System.out.println("姓名："+me.getName());
		System.out.println("性别："+me.getSex());
	}

}