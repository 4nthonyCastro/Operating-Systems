package thread_class;
import assign5.PCB;
import assign5.Prog;

public class CPU extends Prog implements Runnable
{
	String alg;
	int cpuBurstTime;
	
	/*
	 * Utilized for CPU Utilization. 
	 */
	long procPriorSleep;
	long procAfterSleep;
	
	/*
	 * CPU set Alg.
	 */
	public CPU()
	{
		alg = algorithm;
	}
	
	/*
	 * Loop to execute given Alg. 
	 */
	private void scheduler()
	{
		while(true)
		{
			
			if(rQueue.isEmpty() && queueIO.isEmpty2() && finRead == 1)
			{
				break;
			}
			if(procFin == numProc)
			{
				break;
			}
			
			try {
				if(alg.equals("FIFO"))
				{
					fifo();
				} else if(alg.equals("SJF")) {
					sjf();
				} else if(alg.equals("PR")) {
					pr();
				} else if(alg.equals("RR")) {
					rr();
				}
			} catch (InterruptedException e) {e.printStackTrace();}
		}
		finCPU = 1;
	}
	
	/*
	 * Utilized for FIFO Alg.
	 * 
	 */
	private void fifo() throws InterruptedException
	{
		PCB element;
		semaphore0.acquire();
		element = rQueue.pop();
		performCalculations(element);	
	}
	
	/*
	 * Utilized for SJF Alg.
	 * 
	 */
	private void sjf() throws InterruptedException
	{
		PCB element;
		semaphore0.acquire();		
		element = rQueue.getShortest();
		performCalculations(element);	
		}
	
	/*
	 * Utilized for PR Alg.
	 * 
	 */
	private void pr() throws InterruptedException
	{
		PCB element;
		semaphore0.acquire();
		element = rQueue.getPriority();
		performCalculations(element);
	}
	
	/*
	 * Utilized for RR Alg.
	 * 
	 */
	private void rr() throws InterruptedException
	{
		PCB element;
		semaphore0.acquire();
		element = rQueue.pop();
		
		/*
		 * Calcualte Time Element is in Ready Status.
		 */
		element.totalWaitingTime += System.currentTimeMillis() - element.rQueueInputTime;
		
		cpuBurstTime = element.CPUBurst[element.indexCPU];
		
		if(cpuBurstTime < quantum){
			procPriorSleep = System.currentTimeMillis();
			Thread.sleep(cpuBurstTime);
			procAfterSleep = System.currentTimeMillis();
			
			/*
			 * Calculate Time thread is in Sleep Status.
			 */
			element.totalUtilization += procAfterSleep - procPriorSleep;
			
			element.indexCPU++;		
		}
		else{
			procPriorSleep = System.currentTimeMillis();
			Thread.sleep(quantum);
			procAfterSleep = System.currentTimeMillis();
			
			/*
			 * Calculating how much time thread spent in sleep. 
			 */
			element.totalUtilization += procAfterSleep - procPriorSleep;
			
			cpuBurstTime -= quantum;
			element.CPUBurst[element.indexCPU] = cpuBurstTime;	
		}

		if(element.indexCPU >= element.numCPUBurst){
			element.done = 1;
			procFin++;
			
			/*
			 * Make sure to set total times then delete last element.
			 */
			totalUtilization += element.totalUtilization;
			totalTurnaround += (System.currentTimeMillis() - element.creationTime);
			totalWaitingTime += element.totalWaitingTime;
			
		}
		else{
			mutex1.acquire();
			queueIO.push(element);
			semaphore1.release();
			mutex1.release();
		}
	}
	
	/*
	 * Utilized for Algorithms. 
	 * FIFO - SJF - PR
	 */
	private void performCalculations(PCB element) throws InterruptedException
	{
		/*
		 * Calculate Time spent in readyQueue
		 */
		element.totalWaitingTime += System.currentTimeMillis() - element.rQueueInputTime;

		/*
		 * Find BurstTime depending on cpuBurst Index.
		 */
		cpuBurstTime = element.CPUBurst[element.indexCPU];
		
		procPriorSleep = System.currentTimeMillis();
		Thread.sleep(cpuBurstTime);
		procAfterSleep = System.currentTimeMillis();
		
		/*
		 * Calculating how much time thread spent in sleep. 
		 */
		element.totalUtilization += procAfterSleep - procPriorSleep;
		
		/*
		 * Update Index.
		 */
		element.indexCPU = element.indexCPU+1;
		
		/*
		 * Check if last cpuBurst.
		 */
		if(element.indexCPU >= element.numCPUBurst)
		{
			element.done = 1;
			procFin++;

			/*
			 * Make sure to set total times then delete last element.
			 */
			totalUtilization += element.totalUtilization;
			totalTurnaround += (System.currentTimeMillis() - element.creationTime);
			totalWaitingTime += element.totalWaitingTime;
		} else {
			mutex1.acquire();
			queueIO.push(element);
			semaphore1.release();
			mutex1.release();
		}
	}
	
	/*
	 * (non-Javadoc)
	 * @see java.lang.Runnable#run()
	 */
	public void run() 
	{
		scheduler();
	}
}
