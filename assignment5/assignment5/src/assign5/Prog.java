package assign5;
import java.util.concurrent.Semaphore;
import thread_class.IO;
import thread_class.ReadFile_thread;
import thread_class.CPU;

public class Prog 
{	
	public static DubLinkedList queueIO, rQueue;
	
	public static PrintText PrintText;
	
	public static Semaphore mutex0, mutex1;
	public static Semaphore semaphore0, semaphore1;
	
	public static int finRead, finCPU, finIO, quantum;
	public static int numProc = 0, procFin = 0, totalTurnaround = 0, totalUtilization = 0;
	public static String algorithm;
	
	public static long totalWaitingTime = 0;
	/*
	 * Main Driver
	 */
	public static void main(String[] args) 
	{
		int flagQuantum = 0;
		
		PrintText = new PrintText();
		queueIO = new DubLinkedList();
		rQueue = new DubLinkedList();
		
		semaphore0 = new Semaphore(finCPU);
		semaphore1 = new Semaphore(finCPU);
		mutex0 = new Semaphore(1);
		mutex1 = new Semaphore(1);
		
		finCPU = 0;
		finIO = 0;
		finRead = 0;

		long startTime, endTime;
		long totalTime = 0, cpuUtilization = 0;
		double avgWaitingTime = 0.0, throughput = 0.0, avgTurnaroundTime = 0.0;
		
		String file;
		
		/*
		 * Take care of args.
		 */
		if(args[2].equals("-quantum"))
		{
			algorithm = args[1];
			quantum = Integer.parseInt(args[3]);
			file = args[5];
			flagQuantum = 1;
		} else {
			algorithm = args[1];
			file = args[3];
		}
		
		/*
		 * Check for Round Robin else inform user of required quantum. 
		 */
		if(flagQuantum==0 && algorithm.equals("RR"))
		{
			System.out.println("ROUND ROBIN REQUIRES ALGOIRTHM");
			return;
		}
		if(flagQuantum==1 && !algorithm.equals("RR") )
		{
			System.out.println("ERROR!! This Alg does not take Quantum! " + algorithm + ".");
			return;
		}
			
		/*
		 * Create Threads. 
		 * 
		 */
		ReadFile_thread reads = new ReadFile_thread(file);
		Thread thread1 = new Thread(reads);
		
		CPU cpuComp = new CPU();
		Thread thread2 = new Thread(cpuComp);
		
		IO io = new IO();
		Thread thread3 = new Thread(io);
		
		startTime = System.currentTimeMillis();
		try {
			
			/*
			 * Start the Threads. 
			 */
			thread1.start();
			thread1.join();
			thread2.start();
			thread3.start();
		
			/*
			 * Join Total Threads. 
			 */
			thread1.join();
			thread2.join();
			thread3.join();
			
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
		
		/*
		 * Find Total Time.
		 */
		endTime = System.currentTimeMillis();
		totalTime = endTime - startTime;

		/*
		 * Find CPU Utilization.
		 */
		cpuUtilization = totalTime - totalUtilization;
		
		/*
		 * Find Throughput.
		 */
		throughput = (double)numProc/totalTime;
		
		/*
		 * Find Average Turnaround Time. 
		 */
		avgTurnaroundTime = (double)totalTurnaround/numProc;
	
		/*
		 * Find Average Waiting Time. 
		 */
		avgWaitingTime = (double)totalWaitingTime/numProc;

		PrintText.printStats(file, algorithm, cpuUtilization, throughput, avgTurnaroundTime, avgWaitingTime);
	}
}
