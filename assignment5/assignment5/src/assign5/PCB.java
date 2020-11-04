package assign5;

public class PCB {
	public PCB next, prev;
	public int numCPUBurst, countIOBurst, indexCPU, indexIO, priority, id, done = 0;
	public int CPUBurst[], IOBurst[];
	public long creationTime, rQueueInputTime;
	public long totalWaitingTime = 0,totalUtilization = 0 ;
}
