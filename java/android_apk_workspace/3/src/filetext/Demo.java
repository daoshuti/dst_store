package filetext;

import java.io.File;
import java.io.IOException;

public class Demo {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
//		File file = new File("D:\\day.txt");
		File fileabc = new File("D:\\os");
		try {
//			file.createNewFile();
			fileabc.createNewFile();
			//开始查询
			findFile(fileabc);
//			System.out.println(file);
//			String[] strs = fileabc.list();
//			for (String string : strs) {
//				System.out.println(string);
//			}
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
	static void findFile(File fileTemp){
		File[] files = fileTemp.listFiles();
		for (File file : files) {
			if(file.isFile()){
				System.out.println(file);
			}else if(file.isDirectory()){
				findFile(file);
			}
		}
		
	}

}
