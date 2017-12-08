
class CubbyHole {

private int readerCount;//读者数

private int writerCount;//写者数

private boolean dbReading;//读信号量

private boolean dbWriting;//写信号量

public CubbyHole() {

readerCount=0;

writerCount=0;

dbReading=false;

dbWriting=false;

}

public synchronized int startRead(){//开始读

while(writerCount>0){

try{

System.out.println("reader is waiting");

wait();//等待写者发出notify

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

public synchronized int endReading(){//结束读

--readerCount;

if(readerCount==0){//没有读者

dbReading=false;

}

notifyAll();

System.out.println("one reader is done reading. readerCount="+readerCount);

return readerCount;

}

public synchronized void startWriting(){//开始写

++writerCount;

while(dbReading==true||dbWriting==true){

try{

System.out.println("Writer "+writerCount+" is waiting");

wait();//等待读者发出notify

}

catch(Exception e){

}

}

dbWriting =true;

}

public synchronized void endWriting(){//结束写

--writerCount;

if(writerCount==0){//没有写者

dbWriting=false;

}

System.out.println("one writer is done writing. writerCount="+writerCount);

notifyAll();

}

}