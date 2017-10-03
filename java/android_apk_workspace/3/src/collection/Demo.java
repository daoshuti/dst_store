package collection;

import java.util.ArrayList;

public class Demo {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		ArrayList<String> list = new ArrayList<String>();
		//增
		list.add("星期一");
		list.add("星期二");
		list.add("星期日");
		System.out.println(list);
		//删
		list.remove(1);
		System.out.println(list);
		//改
		list.set(1,"礼拜日");
		System.out.println(list);
		//查
		String str = list.get(1);
		System.out.println(str);
	}

}
