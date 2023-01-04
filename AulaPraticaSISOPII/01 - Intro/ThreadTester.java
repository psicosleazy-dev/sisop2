class SimpleThread extends Thread {
	
	private String name;
        private int sleep;
	
	public SimpleThread(String name,int sleep) {
		this.name = name;
   		this.sleep = sleep;
	}

	public void run() {
		int i = 10;
		while (i > 0) {
			System.out.println(name + " executando...");
			
			try { Thread.currentThread().sleep(this.sleep);}
			catch (InterruptedException ie) { ie.printStackTrace(); }
			
			i--;
		}
	}	
}

public class ThreadTester {
	
	public static void main(String args[]) {
		
		SimpleThread thr1 =  new SimpleThread("Joe", 1000);
		SimpleThread thr2 =  new SimpleThread("Paul", 700);
		
		thr1.start();
		thr2.start();
		
		try {
			thr1.join();
			thr2.join();
		} catch (InterruptedException ie) { 
			ie.printStackTrace(); 
		}
		
		System.out.println("Main finalizando...");
	}
}
