
public class Main {

	public static void main(String[] args) {
		// TODO 自动生成的方法存根
		CubbyHole db=new CubbyHole();//缓冲区

		Reader r1=new Reader(1,db);//定义读者r1

		Reader r2=new Reader(2,db);//定义读者r2

		Writer w1=new Writer(1,db);//定义写者w1

		r1.start();

		r2.start();

		w1.start();
	}

}
