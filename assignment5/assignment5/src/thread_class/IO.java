package thread_class;
import assign5.PCB;
import assign5.Prog;

public class IO extends Prog implements Runnable 
{	
	private void ioSystem()
	{
		PCB element = null;
		while(true)
		{
			if(finCPU == 1)
			{
				break;
			}
			try {
				while(!semaphore1.tryAcquire() && finCPU != 1);
				element = queueIO.pop();
				if(element.done != 1)
				{
					if(element.countIOBurst > element.indexIO)
					{
						Thread.sleep(element.IOBurst[element.indexIO]);
						element.indexIO++;
					}	
					mutex0.acquire();
					element.rQueueInputTime = System.currentTimeMillis();
					rQueue.push(element);
					semaphore0.release();
					mutex0.release();
					
				} else {
					semaphore1.release();
				}

			} catch(Exception e) {}
		}
		finIO = 1;
	}
	/*
	 * (non-Javadoc)
	 * @see java.lang.Runnable#run()
	 */
	public void run() 
	{
		ioSystem();
	}
}