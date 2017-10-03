package HelloWorld;

public class Hello {
	public static void main(String[] arg){
		
		int[] a = new int[4];
		a[0] = 1;
		a[1] = 2;
		a[2] = 3;
		a[3] = 4;
		System.out.println("HelloWorld");
		System.out.println("a:");
		for (int i : a) {
			System.out.println(i);
		}
	}
}

