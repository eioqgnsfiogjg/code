
class Reader extends Thread{//������̣߳��̳�Thread�࣬��дrun����

private CubbyHole C;

private int readerNum;

public Reader(int r,CubbyHole db) {

readerNum=r;

C=db;

}

public void run(){

int c;

//while(true)

for ( int i = 0 ; i < 5 ; i++)

{

System.out.println("reader "+readerNum+" wants to read");

c=C.startRead();

System.out.println("reader "+readerNum+" is reading. readerCount="+c);

c=C.endReading();

System.out.println("It is reader "+readerNum+" who has done reading. readercount="+c);

}

}

}