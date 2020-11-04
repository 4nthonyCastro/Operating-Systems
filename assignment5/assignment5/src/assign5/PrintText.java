package assign5;

import java.text.DecimalFormat;

public class PrintText extends Prog
{
	/*
	 * This class is responsible of printing output for time computation 
	 * Easy implementation. 
	 */
	
	public void printStats(String fileName, String algorithm, long util, double thruPut, double turnAround, double waitTime)
	{
		DecimalFormat numFormat = new DecimalFormat( "0.000");
		double dubs [] = new double[3];
		String viewValues[] = new String[7];
		
		viewValues[0] = fileName;
		viewValues[1] = algorithm;
		viewValues[3] = Long.toString(util);

		int index = 4;
		
		dubs[0] = thruPut;
		dubs[1] = turnAround;
		dubs[2] = waitTime;
		
		for(double stat : dubs)
		{
			viewValues[index] = numFormat.format(stat);
			index++;
		}
		
		if(quantum != 0)
		{
			viewValues[2] = "(" + Integer.toString(quantum) + ")";
		} else {
			viewValues[2] = "";
		}
		
		System.out.printf("\n" + "Input File Name\t\t\t: %s\n" + "CPU Scheduling Alg\t\t: %s %s\n" + "CPU Utilization\t\t\t: %s\n" + "Throughput\t\t\t: %s\n" + "Avg. Turaround Time\t\t: %s\n" + "Avg. Waiting Time in R Queue\t: %s\n" + "\n",
				viewValues[0], viewValues[1], viewValues[2], viewValues[3], viewValues[4], viewValues[5], viewValues[6]);
	}
}
