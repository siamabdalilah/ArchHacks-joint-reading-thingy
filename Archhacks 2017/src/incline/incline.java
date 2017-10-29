package incline;

import java.io.*;

import jssc.SerialPortException;

public class incline {
	public static void main(String[] args)
	{
		//double k;
		try {
			BufferedReader in = new BufferedReader(new InputStreamReader (System.in));
			SerialComm port = new SerialComm("/dev/cu.usbserial-DN02AZZ5");
			System.out.println("Flex your joint several times in a slow pace. Once done press any key and enter to exit.");
			
			in.readLine();
			port.writeByte((byte)0x00);
			
//			char c1 = port.readByte();
//			char c2 = port.readByte();
//				
//			int k = (int)(c2 + (c1<<8));
//			System.out.println(k);
			
			while (true)
			{
				if (port.available())
				{
					System.out.println(port.readByte());
				}
			}
			
		
			//FileWriter writer = new FileWriter("data.csv");
			//writer.append(Double.toString(1));
			//writer.close();
		} catch (SerialPortException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (FileNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		};
	}
}
