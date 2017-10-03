package Super;

class Person{
	int age;
	String name;
	public Person() {
		// TODO Auto-generated constructor stub
	}
	public Person(int age,String name){
		this.age = age;
		this.name = name;
	}
}

class Worker extends Person{
	int workAge;
	Worker(){		
	}
	Worker(int age,String name,int workAge){
		super(age,name);
		this.workAge = workAge;
	}
}

public class Demo {
	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		
	}
}
