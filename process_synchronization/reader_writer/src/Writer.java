class Writer extends Thread{//定义写线程

private CubbyHole C;

private int writerNum;

public Writer(int w,CubbyHole db) {

writerNum=w;

C=db;

}

public void run(){

// while(true)

for ( int i = 0 ; i < 5 ; i++)

{

System.out.println("Writer "+writerNum+" wants to write");

C.startWriting();

System.out.println("Writer "+writerNum+" is writing");

C.endWriting();

System.out.println("It is Writer "+writerNum+" who has done writing .");

}

}

}