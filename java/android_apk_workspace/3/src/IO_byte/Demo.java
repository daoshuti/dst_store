package IO_byte;

import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;

public class Demo {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		FileInputStream fin = null;
		FileOutputStream fou = null;
		try {
			fin = new FileInputStream("D:\\note1.txt");
			fou = new FileOutputStream("D:\\note1bak.txt");
			byte[] buffer = new byte[5];
			int len;
			try {
				while((len = fin.read(buffer))!= -1){
					fou.write(buffer, 0, len);
				}
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		} catch (FileNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} finally{
			try {
				fin.close();
				fou.close();
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
		

	}

}
