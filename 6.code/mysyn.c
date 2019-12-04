
typedef struct __eventStruct//事件结点
{
	int eventNum;//事件号
	wait_queue_head_t *p; //等待队列头
	struct __eventStruct *next; 
}eventNode;

eventNode *myevent_head=NULL;//事件队列头
eventNode *myevent_end=NULL;//事件队列尾


eventNode * scheventNum(int eventNum,eventNode **prev)//prev指向该事件在事件队列中的前一事件，函数返回该事件号的事件结点
{
    eventNode *tmp = myevent_head;//从事件队列头开始查找
    *prev = NULL;
    while(tmp)
    {
        if(tmp->eventNum == eventNum)//事件号相等
                return tmp;//返回该事件
        *prev = tmp;//设置前驱事件
        tmp =tmp->next;
    }
    return NULLL;//未找到该事件
}

void print_event_list(eventNode *head)
{
	printk("event_list:");
	while(head)
	{
		printk(" %d",head->eventNum);
		head=head->next;
	}
	printk("\n");

}

SYSCALL_DEFINE0(eventshow)//0表示系统调用的参数为0个
{
	print_event_list(myevent_head);
}


/*
定义Open同步原语，当Open一个事件的时候，有两种情况：
一是事件已经存在，只需要返回Event事件号即可，
二是事件链表中没有该事件，简单的处理办法直接返回-1，表示事件不存在。
当传递参数0 的时候，将产生一个新事件。*/
SYSCALL_DEFINE1(eventopen,int,eventNum)
{
	eventNode *newNode;
	eventNode *preNode;
	if(eventNum)
		if(!scheventNum(eventNum,&preNode))//不存在该事件
			return -1;
		else//存在，返回事件号
			return eventNum;
	else//传递参数为0 产生一个新事件
    {
    	//创建新事件队列节点
        newNode = (eventNode *)kmalloc(sizeof(eventNode),GFP_KERNEL);
		newNode->p =(wait_queue_head_t *)kmalloc(sizeof(wait_queue_head_t),GFP_KERNEL);//为等待队列头分配空间
		init_waitqueue_head(newNode->p);//初始化等待队列
		newNode->next = NULL;

		newNode->p->task_list.next =&newNode->p->task_list;
		newNode->p->task_list.prev =&newNode->p->task_list;

		if(!myevent_head)//事件队列为空
		{
            newNode->eventNum =2;//命时间号
            myevent_head =myevent_end =newNode;//设为事件队列头和尾
        }
        else //事件队列不为空
        {
       		newNode->eventNum = myevent_end->eventNum + 2;
       		//设为事件队列的尾
            myevent_end->next = newNode;
            myevent_end = newNode;
        }
        return newNode->eventNum;
	}
    return 0;

}

//唤醒所有等待该事件发生的进程。在事件列表上找到该事件，然后调用wake_up()。
do_eventsig(int,eventNum)
{
   eventNode *tmp = NULL;
   eventNode *prev = NULL;
   
   if(!(tmp = scheventNum(eventNum,&prev))//未找到该事件
     	return 0;
   wake_up(tmp->p);//唤挂在该事件上所有的等待事件
   printk("wake up waitqueue\n");
   return 1;
}
SYSCALL_DEFINE1(eventsig,int,eventNum)
{
	return do_eventsig(eventNum);
}


//将一个进程加到他要等待的事件队列中去。
SYSCALL_DEFINE1(eventwait,int,eventNum)
{
   eventNode *tmp;
   eventNode *prev = NULL;
   wait_queue_t  wait;
   unsigned long flags;
   
   if(tmp =scheventNum(eventNum,&prev))//找到该事件
   {	
   		
   		DECLARE_WAITQUEUE(wait, current); // 创建关于当前进程的新的等待队列项
		printk("set state.\n");
		set_current_state(TASK_UNINTERRUPTIBLE); // 将当前进程的状态设置为TASK_UNINTERRUPTIBLE
        printk("add to waitqueue\n");
        write_lock_irqsave(&temp->p->lock,flags);//获取读写锁
        add_wait_queue(tmp->p,&wait);//加入等待队列
        write_unlock_irqrestore(&tmp->p->lock,flags);
       
       printk('schedule\n');
       schedule();//进行进程调度
       
       write_lock_irqsave(&temp->p->lock,flags);//获取读写锁
       remove_wait_queue(tmp->p,&wait);//移出等待队列
       write_unlock_irqrestore(&tmp->p->lock,flags);//释放读写锁
   }    
   else return 0;
}   

/*
至于evntclose()先在事件队列中找到该事件
然后根据事件在该链表中的位置进行特定的处理
之后唤醒所有睡眠在该事件上的事件，最后将这个事件从链表中删除，释放内存。
*/
SYSCALL_DEFINE1(evntclose,int.,eventNum)
{
    eventNode *prev;
    eventNode *releaseItem;
    
    do_evntsig(eventNum);
    printk("before delete:\n");
    print_event_list(myevent_head);

    if(releaseItem = scheventNum(eventNum,&prev))
    {
    	printk("ready to delete:%d\n",eventNum);
        if (releaseItem == myevent_end)
                myevent_end = prev;
        if (releaseItem == myevent_head)
        {
            myevent_head = myevent_head->next;
            goto wake;
        }    
        prev->next = releadeItem->next;
    }    
    wake:
        if(releaseItem)
        {
            kfree(releaseItem);
            return 1;
        }    
    return 0;
}   



