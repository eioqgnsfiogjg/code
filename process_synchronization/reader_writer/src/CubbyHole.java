
class CubbyHole {

private int readerCount;//������

private int writerCount;//д����

private boolean dbReading;//���ź���

private boolean dbWriting;//д�ź���

public CubbyHole() {

readerCount=0;

writerCount=0;

dbReading=false;

dbWriting=false;

}

public synchronized int startRead(){//��ʼ��

while(writerCount>0){

try{

System.out.println("reader is waiting");

wait();//�ȴ�д�߷���notify

}

catch(Exception e){

}

}

++readerCount;

if(readerCount==1){

dbReading=true;

}

return readerCount;

}

public synchronized int endReading(){//������

--readerCount;

if(readerCount==0){//û�ж���

dbReading=false;

}

notifyAll();

System.out.println("one reader is done reading. readerCount="+readerCount);

return readerCount;

}

public synchronized void startWriting(){//��ʼд

++writerCount;

while(dbReading==true||dbWriting==true){

try{

System.out.println("Writer "+writerCount+" is waiting");

wait();//�ȴ����߷���notify

}

catch(Exception e){

}

}

dbWriting =true;

}

public synchronized void endWriting(){//����д

--writerCount;

if(writerCount==0){//û��д��

dbWriting=false;

}

System.out.println("one writer is done writing. writerCount="+writerCount);

notifyAll();

}

}