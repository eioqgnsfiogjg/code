
public class Main {

	public static void main(String[] args) {
		// TODO �Զ����ɵķ������
		CubbyHole db=new CubbyHole();//������

		Reader r1=new Reader(1,db);//�������r1

		Reader r2=new Reader(2,db);//�������r2

		Writer w1=new Writer(1,db);//����д��w1

		r1.start();

		r2.start();

		w1.start();
	}

}
