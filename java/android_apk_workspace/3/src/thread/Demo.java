package thread;

class MyThread extends Thread{
	@Override
	public void run() {
		// TODO Auto-generated method stub
		super.run();
		for (int i = 0; i < 20; i++) {
			try {
				Thread.sleep(500);
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}			
			System.out.println("MyThread i = " + i);			
		}
	}
}

public class Demo {

	/**
	 * @param args
	 * @throws Exception 
	 */
	public static void main(String[] args) throws Exception {
		// TODO Auto-generated method stub
		MyThread mth = new MyThread();
		mth.start();
		for (int i = 0; i < 20; i++) {
			Thread.sleep(500);
			System.out.println("main Thread i = " + i);
		}
	}

}
