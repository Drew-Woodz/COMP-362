#include "message.h"

int main(int argc, char *argv[])
{
	int numberOfNodes;

	//ensure the command has all necessary elements
	//checks: at least 3 args, numberOfNodes must match number of starting node temperatures
	if (argc < 3 || (numberOfNodes = strtol(argv[2], NULL, 10)) != (argc - 3))
	{
		printf("Usage: ./monitor <initial monitor temperature> <number of nodes> <node temp 1> ... <node temp n>\n");
		exit(1);
	}

	//create array to keep track of each node and its previous temperature
	TEMPERATURE nodeData[numberOfNodes];

	//establish queue descriptors, messages, type
	mqd_t in_mqid, out_mqid;
	MESSG msg_rcvd, msg_send;
	unsigned int type;

	//remove monitor queue that may remain after an abnormal termination
	if (mq_unlink(MONITOR_QUEUE) == 0)
		printf("MONITOR: Message queue %s removed.\n", MONITOR_QUEUE);


	// initialize the queue attributes
	struct mq_attr attr;

	attr.mq_maxmsg = 10;
	attr.mq_msgsize = MAX_MSG_SIZE;
	attr.mq_curmsgs = 0;
	attr.mq_flags = 0;

	//create and configure incoming message queue
	if ((in_mqid = mq_open(MONITOR_QUEUE, O_RDONLY | O_CREAT, S_IWUSR | S_IRUSR, &attr)) < 0)
		oops("MONITOR: Error opening a server queue.", errno);

	printf("MONITOR: Message queue %s created.\n", MONITOR_QUEUE);

	//create a outgoing message queue for each node, fork each node, execlp each node
	char *nodeName = (char *) malloc(sizeof(char) * MAX_NAME_LENGTH);
	pid_t pid;
	for (int i = 0; i < numberOfNodes; i++)
	{
		//create name for new incoming queue
		snprintf(nodeName, sizeof(nodeName), "/%s%d", NODE_NAME_PREFIX, i); //eg: /NODE_0

		//remove node message queues that may remain after abnormal termination
		//Note that the only queues clear are those < numberOfNodes
		if (mq_unlink(nodeName) == 0)
			printf("MONITOR: Message queue %s removed.\n", nodeName);

		//attempt to open queue under said name
		if ((out_mqid = mq_open(nodeName, O_WRONLY | O_CREAT, S_IWUSR | S_IRUSR, &attr)) < 0)
			oops("MONITOR: Error opening a client's queue", errno);

		printf("MONITOR: Message queue %s created.\n", nodeName);

		//populate nodeData array
		nodeData[i] = (TEMPERATURE) {
			.msqid = out_mqid,
			 .currentTemperature = strtof(argv[i + 3], NULL),
			  .stable = false
		};

		//fork and execlp each node
		pid = fork();

		//fork failed
		if (pid < 0)
			oops("Fork %d Failed!", i);

		//child
		if (pid == 0)
			if (execlp("./node", "node", (nodeName + 6), argv[i + 3], NULL) < 0) //nodeName + 6 is just the number that the node wants
				oops("Execlp %d Failed", i);

	}


	//main loop
	float new_integrated_temp = strtof(argv[1], NULL);
	printf("MONITOR TEMPERATURE: %.4f\n", new_integrated_temp); //output initial temperature
	float previous_integrated_temp = 0.0;
	float sum_of_client_temps;
	int number_of_unchanged_nodes = 0; //number of nodes that have been stabilized
	bool isFirstCycle = true; //determine if current cycle is the first one (has no previous temperature)
	bool continueCycling = true; //determine if more monitoring needs to occur
	msg_send.stable = false; //default stable to false
	while (continueCycling)
	{


		//reset data for new cycle
		sum_of_client_temps  = 0.0;

		//recieve all messages and sum temperatures (wait for 1 less message for each stable node)
		for (int i = 0; i < (numberOfNodes - number_of_unchanged_nodes); i++)
		{
			//read reports from all nodes
			if (mq_receive(in_mqid, (char *) &msg_rcvd, MAX_MSG_SIZE, &type) >= 0)
			{
				//keep record of reported temperatures
				nodeData[msg_rcvd.nodeId].previousTemperature = nodeData[msg_rcvd.nodeId].currentTemperature; //move previous temperature into previous variable
				nodeData[msg_rcvd.nodeId].currentTemperature = msg_rcvd.temperature; //get new temperature into current temperature
				sum_of_client_temps += msg_rcvd.temperature; //add to sum
			}
			else
				oops("\nMONITOR: Error reveiving data from node!", errno);
		}

		//NodeId does not matter to nodes, since they already know who they are; -1 is arbitrarily incorrect on purpose
		msg_send.nodeId = -1;

		//update temperatures
		previous_integrated_temp = new_integrated_temp;
		new_integrated_temp = (2 * previous_integrated_temp + sum_of_client_temps) / 6;
		msg_send.temperature = new_integrated_temp;

		//output temperature
		printf("\nMONITOR TEMPERATURE: %.4f\n", new_integrated_temp);

		//send messages to all nodes TODO
		for (int i = 0; i < numberOfNodes; i++)
		{
			//only send message to non-stable nodes
			if (!nodeData[i].stable)
			{
				//check stability if on 2nd cycle or later
				if (isFirstCycle)
				{
					if (i == numberOfNodes - 1) //change so next cycle will check stability (only change on last iteration of loop)
					{
						isFirstCycle = false;
					}
				}
				else if ((fabsf(nodeData[i].currentTemperature - nodeData[i].previousTemperature) < MIN_CHANGE_THRESHOLD))
				{

					msg_send.stable = true; //for nodes
					nodeData[i].stable = true; //for monitor
					number_of_unchanged_nodes++;
				}
				else
					msg_send.stable = false;

				//send new info to all nodes
				if (mq_send(nodeData[i].msqid, (const char *) &msg_send, sizeof(msg_send), (unsigned int) TYPE) < 0)
					oops("MONITOR: Error sending data to node!", errno);
			}
		}

		continueCycling = (number_of_unchanged_nodes != numberOfNodes);
	}

	printf("STABLE TERMPERATURE DETECTED.\nMONITOR TERMINATING...\n");


	//remove all outgoing queues
	for (int i = 0; i < numberOfNodes; i++)
	{
		//create name for queue to remove
		snprintf(nodeName, sizeof(nodeName), "/%s%d", NODE_NAME_PREFIX, i); //eg: /NODE_0

		//remove node message queues that may remain after abnormal termination
		if (mq_unlink(nodeName) == 0)
			printf("MONITOR: Message queue %s removed.\n", nodeName);
	}

	//remove incoming queue
	mq_unlink(MONITOR_QUEUE);

	//over and out
	free(nodeName);
	exit(EXIT_SUCCESS);
}
