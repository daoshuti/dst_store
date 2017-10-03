package Hashmap;

import java.util.HashMap;

public class Demo {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		HashMap<String, String> map = new HashMap<String, String>();
		//增
		map.put("Mon", "星期一");
		map.put("Sat", "星期六");
		map.put("Sun", "星期日");
		System.out.println(map);
		//删
		map.remove("Sat");
		System.out.println(map);
		//改
		map.put("Sun", "礼拜日");
		System.out.println(map);
		//查
		String str = map.get("Sun");
		System.out.println(str);
	}

}
