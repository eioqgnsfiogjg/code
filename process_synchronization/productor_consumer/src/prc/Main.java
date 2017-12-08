package prc;

import java.util.ArrayList;
import java.util.List;
//import java.util.concurrent.ExecutorService;
//import java.util.concurrent.Executors;
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.ReentrantLock;

public class Main {
		public final static int bufferSize = 5;
		public static ReentrantLock lock = new ReentrantLock();
		public static Condition empty = lock.newCondition();
		public static Condition full = lock.newCondition();
		public static void main(String[] args) {
		    List<Goods> queue = new ArrayList<Goods>();
		    int length = 10;
		    Producer p1 = new Producer(queue,length);
		    Producer p2 = new Producer(queue,length);
		    Producer p3 = new Producer(queue,length);
		    Consumer c1 = new Consumer(queue);
		    Consumer c2 = new Consumer(queue);
		    Consumer c3 = new Consumer(queue);
		    
		    /*
		     ExecutorService service = Executors.newCachedThreadPool();
		     service.execute(p1);
		     service.execute(p2);
		     service.execute(p3);
		     service.execute(c1);
		     service.execute(c2);
		     service.execute(c3);
		    */
		    new Thread(p1).start();
		    new Thread(p2).start();
		    new Thread(p3).start();
		    new Thread(c1).start();
		    new Thread(c2).start();
		    new Thread(c3).start();
		  
	}

}
