package object;
class Person{
	int age;
	String name;
}
class Worker extends Person{
	int workage;
	
	public Worker(int age,String name,int workage) {
		super.age = age;
		super.name = name;
		this.workage = workage; 
	}
	
}

public class Demo {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Worker me = new Worker(18,"王涵",1);
		System.out.println(me);
	}

}
