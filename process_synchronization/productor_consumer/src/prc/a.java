package prc;

import java.util.Random;

public class a {

	public static void main(String[] args) {
		// TODO 自动生成的方法存根
		int i;
		String[] names= {"liu","wang","zhang"};
		for(String s:names)
			System.out.print(s+", ");
		Random rand =new Random(25);//括号内的数字与生成的随机数无关。
	
		i=rand.nextInt(100);//括号内的数字表示生成的随机数上限。
		System.out.println(i);
	}
	
}
