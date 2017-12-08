package prc;

import java.util.List;
import java.util.Random;

public class Producer implements Runnable {
	static List<Goods> list;
	private int len;

	Producer(List<Goods> list,int len)
	{
		this.list = list;
		this.len = len;
	}
	public void run()
	{	
		while(true)
		{
			if(Thread.currentThread().isInterrupted())
				break;
			
			Random r = new Random();
            //生产者单作业生产
			Goods g = new Goods();
            //
			g.setData(r.nextInt(100));
            Main.lock.lock();
            
            if(list.size() >= len)
            {
                Main.empty.signalAll();//empty信号量-1
                try {
					Main.full.await();//full信号量+1
				} catch (InterruptedException e) {
					// TODO 自动生成的 catch 块
					e.printStackTrace();
				}
            }
            try {
				Thread.sleep(1000);
			} catch (InterruptedException e) {
				// TODO 自动生成的 catch 块
				e.printStackTrace();
			}
            list.add(g);
            
            //多缓冲区的缓冲池
             /*
            int overbuffer = list.size() - Main.bufferSize;
            if(list.size() >= Main.bufferSize)
            {
            	for(int j = 0;j < overbuffer;j++)
            		list.remove(0);
            	continue;
            }*/
            
            Main.lock.unlock();
            System.out.println("生产者ID:"+Thread.currentThread().getId()+" 生产了:"+g.getData());
            
		}
	}
	
	
	

	
}
