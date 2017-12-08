package prc;

import java.util.List;

public class Consumer implements Runnable {
	List<Goods> list;
	Consumer(List<Goods> list)
	{
		this.list = list;
	}
	public void run()
	{
		
		while(true)
		{	
				if(Thread.currentThread().isInterrupted())
					break;
			Goods g = null;
			Main.lock.lock();
			
	        if(list.size() >= 0) {
	        	Main.full.signalAll();//full信号量-1
	        	try {
					Main.empty.await();//empty信号量+1
				} catch (InterruptedException e) {
					// TODO 自动生成的 catch 块
					e.printStackTrace();
				}
	        }
	        //g = list.remove(0);
	        g = list.get(0);
	        list.remove(0);
			Main.lock.unlock();
			System.out.println("消费者：" + Thread.currentThread().getId() + "消费了" + g.getData());
			
		}

	}
}
