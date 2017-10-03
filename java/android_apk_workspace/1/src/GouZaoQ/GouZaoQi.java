package GouZaoQ;

class Person{
	private int age;
	private String name;
	private String sex;
	
	public Person (int age){
		this.age = age;
	}
	
	public Person (String name,int age){
		this(age);
		this.name = name;
	}
	
	public Person(String sex,String name,int age){
		this(name,age);
		this.sex = sex;
	}
	
	public int getAge() {
		return age;
	}
	public void setAge(int age) {
		this.age = age;
	}
	public String getName() {
		return name;
	}
	public void setName(String name) {
		this.name = name;
	}
	public String getSex() {
		return sex;
	}
	public void setSex(String sex) {
		this.sex = sex;
	}
	
	
}

public class GouZaoQi {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Person me = new Person("男", "我", 19);
		System.out.println(me.getAge());
		System.out.println(me.getName());
		System.out.println(me.getSex());
	}

}
