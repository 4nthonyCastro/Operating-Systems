package thread_class;

import java.io.FileReader;
import assign5.PCB;
import assign5.Prog;

import java.io.BufferedReader;


public class ReadFile_thread extends Prog implements Runnable 
{
	int totalProcs;
	String fileName;
	
	/*
	 * Main thread. 
	 */
	public ReadFile_thread(String fileName)
	{
		this.fileName = fileName;
		totalProcs = 0;
	}
	
	/*
	 * Method used to Read File given in Java. 
	 * 
	 */
	public void read()
	{
		String stringers[];
		String line = null;
		try {
			
			/*
			 * Create new bufferedReader for file name. 
			 */
			BufferedReader buffRead = new BufferedReader(new FileReader(fileName));
			while((line = buffRead.readLine()) != null)
			{
				stringers = line.split(" +");
				try {
					checkLines(stringers);
				} catch (RuntimeException e)
				{ 
						break;	
				} 
			}
			finRead = 1;
			numProc = totalProcs;
			
			/*
			 * Close Read. 
			 */
			buffRead.close();
		} catch (Exception e) 
		{
			e.printStackTrace();
		}
	}
	
	/*
	 * Check Lines
	 * 
	 */
	public void checkLines(String []line)
	{
		
		if(line[0].equals("proc")) 
		{
			totalProcs++;
			proc(line);
		} else if(line[0].equals("sleep")) {
			sleep(line);
		} else if(line[0].equals("stop")) {
			throw new RuntimeException();
		} else {
			System.out.println("INVALID WORD\"" + line[0] + "\"");
		}
	}

	/*
	 * Given Process Line set values to PCB.
	 * Adds PCB to linked list. 
	 * 
	 */
	private void proc(String line[])
	{
		PCB element = new PCB();
		element.indexCPU = 0;
		element.indexIO = 0;
		element.priority = Integer.parseInt(line[1]);
		int burstNum = Integer.parseInt(line[2]);
		element.numCPUBurst = (burstNum/2) + 1;
		element.countIOBurst = burstNum/2;
		element.CPUBurst = getBurst(element.numCPUBurst, line, "CPU");
		element.IOBurst = getBurst(element.countIOBurst, line, "IO");
		
		element.creationTime = System.currentTimeMillis();
		element.rQueueInputTime = System.currentTimeMillis();
		
		element.id = totalProcs;
		
		rQueue.push(element);
		semaphore0.release();
	}
	
	/*
	 * Sleep Threads. 
	 * 
	 */
	private void sleep(String line[])
	{
		try {
			Thread.sleep(Long.parseLong(line[1]));
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

	/*
	 * Given numbers for IO/CPU returns structure. 
	 * 
	 */
	private int[] getBurst(int num, String[] line, String type)
	{
		int result[] = new int[num];
		int switches = 0, index = 0, begin = 0;
		if(type.equals("CPU")) 
		{
			begin = 3;
		} else if (type.equals("IO")) {
			begin = 4;
		}
		for(int i = begin; i < line.length; i++) 
		{
			if(switches%2 == 0) 
			{
				result[index] = Integer.parseInt(line[i]);
				index++;
			}
			switches++;
		}
		return result;
	}
	
	/*
	 * (non-Javadoc)
	 * @see java.lang.Runnable#run()
	 */
	public void run()
	{	
		read();
	}
}
