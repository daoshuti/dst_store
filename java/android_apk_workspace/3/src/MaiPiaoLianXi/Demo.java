package MaiPiaoLianXi;

class MyThread implements Runnable {
	static int val = 100;
	static String str = "lock";
	int t;

	@SuppressWarnings("static-access")
	@Override
	public void run() {
		// TODO Auto-generated method stub
		while (true) {
			try {
				Thread.sleep(t);
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			synchronized (str) {
				if(this.val <= 0){
					break;
				}
				this.val--;
				System.out.println(Thread.currentThread().getName()
						+ "买票成功，票数剩余：" + this.val);
			}
		}
	}
}

public class Demo {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		MyThread mth1 = new MyThread();
		mth1.t = 200;
		MyThread mth2 = new MyThread();
		mth2.t = 200;
		Thread td1 = new Thread(mth1);
		Thread td2 = new Thread(mth2);
		td1.start();
		td2.start();
	}

}
