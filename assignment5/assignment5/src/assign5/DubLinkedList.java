package assign5;

public class DubLinkedList 
{
	int size;
	PCB head, tail;
	public DubLinkedList()
	{
		head = null;
		tail = null;
		size = 0;
	}
	
	/*
	 * check if Empty.
	 * 
	 */
	public boolean isEmpty()
	{
		return size == 0;
	}
	
	/*
	 * Size of list. 
	 * 
	 */
	public int size()
	{
		return size;
	}
	
	/*
	 * Used for temp if Empty.
	 * 
	 */
	public boolean isEmpty2()
	{
		if(head == null)
		{
			return true;
		} else {
			return false;
		}
	}
	
	/*
	 * Push Element
	 * 
	 */
	public void push(PCB element)
	{
		element.prev = null;
		element.next = null;

		if(tail != null)
		{
			tail.next = element;
			element.prev = tail;
			tail = element;
			tail.next = null;
		}
		if(head == null)
		{
			head = element;
			tail = element;
		}
		size++;	
	}
	
	/*
	 * Pop Element.
	 * 
	 */
	public PCB pop()
	{
		PCB temp = head;

		if(head == null)
			return null;
		head = head.next;
		
		if(head != null)
			head.prev = null;
		size--;
		return temp;
	}
	
	/*
	 * Function utilized to get priority element. 
	 * 
	 */
	public PCB getPriority()
	{
		PCB vipPCB = head;
		PCB result = head;
		int upperLimit = head.priority, current;

		while(result != null)
		{
			current = result.priority;
			if(current > upperLimit)
			{
				upperLimit = current;
				vipPCB = result;
			}
			result = result.next;	
		}
		removeElement(vipPCB);
		return vipPCB;
	}
	
	/*
	 * Funciton utilized to get shortest element.
	 * 
	 */
	public PCB getShortest()
	{
		PCB temp = head;
		int index = 1, lowIndex = 1;
		PCB lowerPCB = temp;
		int lowerCPU = temp.CPUBurst[temp.indexCPU];
		while(temp != null)
		{
			int current = temp.CPUBurst[temp.indexCPU];
			if( current < lowerCPU )
			{
				lowIndex = index;
				lowerCPU = current;
				lowerPCB = temp;
			}
			index++;
			temp = temp.next;
		}
		removeElement(lowIndex);
		return lowerPCB;
	}
	
	/*
	 * Utilized to remove Element from list using Element. 
	 * 
	 */
	public void removeElement(PCB element)
	{
		int length = size;
		PCB temp;
		for(int i = 0; i<length; i++)
		{
			temp = pop();
			if(temp != element && temp != null)
			{
				push(temp);
			}
		}
	}
	
	/*
	 * Utilized to remove Element from list using Index. 
	 * 
	 */
	public void removeElement(int index)
	{
		PCB temp;
		int elementRemoval = 0;
		for(int i = 0; i<index; i++)
		{
			temp = pop();
			if((i+1) != index)
			{
				push(temp);
			} else {
				elementRemoval = 1;
			}
		}
	}

	/*
	 * Meant to print double list. 
	 * 
	 */
	public void viewList(String name)
	{
		PCB tmp = head;
		int counter = 1;
		String current = "null", prev = "null", next = "null";

		while(tmp != null)
		{
			prev = "null";
			current = "null";
			next = "null";
			
			try{
				prev = Integer.toString(tmp.prev.id);
			}catch(Exception e){}
			try{
				current = Integer.toString(tmp.id);
			}catch(Exception e){}
			try{
				next = Integer.toString(tmp.next.id);
			}catch(Exception e){ 
				// do nothing.
			}
			System.out.println(counter 
					+ ":    prev: " + prev 
					+ "    cur: " + current 
					+ "    next: " + next);
			tmp = tmp.next;
			counter++;
		}
	}
}
