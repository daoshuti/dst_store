package Final;

final class Abc {

	final int a = 1;
//	int [][] array = new int [3][4];
	final void fun(){
		final int b=10;
//		a = 10;
//		b = 10;
		System.out.println("b:"+b);
	}
	float f = 3.14f;
	String a1 = "Hello";
	String b = "World";
	String c = (1+2) + " ";
	String d = "Hello"+"World!!";

}
class Bcd{
	public void fun(String ... books) {
		for (String string : books) {
			System.out.println(string);
		}
	}
}
public class Final{
	public static void main(String[] args) {
		Bcd f = new Bcd();
		Abc a = new Abc();
		f.fun("nihao","哈喽","hello");
		System.out.println(a.c);
		System.out.println(a.d);
	}
}

