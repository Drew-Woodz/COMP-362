#include "message.h"

int main(int argc, char *argv[])
{
	if (argc < 3)
	{
		printf("Usage: ./node <nodeID> <initialTemp>\n");
		exit(1);
	}

	int nodeId = strtol(argv[1], NULL, 10);
	float currentTemperature = strtof(argv[2], NULL);
	float previousTemperature;

	mqd_t monitor_mqid, in_mqid; //mq goes to monitor and node, respectively
	MESSG msg_rcvd, msg_send;
	unsigned int type;

	msg_send.stable = false;
	msg_send.nodeId = nodeId;

	//open queues on node process
	char *nodeName = (char *) malloc(sizeof(char) * MAX_NAME_LENGTH);
	snprintf(nodeName, sizeof(nodeName), "/%s%d", NODE_NAME_PREFIX, nodeId); //eg: /NODE_0

	//attempt to open incoming queue under said name
	if ((in_mqid = mq_open(nodeName, O_RDONLY)) < 0)
		oops("NODE: Error opening a nodes's queue", errno);

	// initialize the queue attributes
	struct mq_attr attr;

	attr.mq_maxmsg = 10;
	attr.mq_msgsize = MAX_MSG_SIZE;
	attr.mq_curmsgs = 0;
	attr.mq_flags = 0;

	//attempt to open outgoing queue to monitor
	if ((monitor_mqid = mq_open(MONITOR_QUEUE, O_WRONLY, S_IWUSR, &attr)) < 0)
		oops("NODE: Error opening a monitor queue.", errno);

	//output initial temperature
	printf("NODE %d TEMPERATURE: %.4f\n", nodeId, currentTemperature);

	do
	{
		//report the node's temp (mq_send())
		msg_send.temperature = currentTemperature;
		if (mq_send(monitor_mqid, (const char *) &msg_send, sizeof(msg_send), (unsigned int) TYPE) < 0)
			oops("NODE: Error sending data to monitor!", errno);

		//put old current temp into previous temp before getting the current temperature
		previousTemperature = currentTemperature;

		//obtain feedback (feedback queue)
		if (mq_receive(in_mqid, (char *) &msg_rcvd, MAX_MSG_SIZE, &type) >= 0)
			currentTemperature = (previousTemperature * 3 + 2 * msg_rcvd.temperature) / 5;
		else
			oops("NODE: Error reveiving data from monitor!", errno);

		//output temperature
		printf("NODE %d TEMPERATURE: %.4f\n", nodeId, currentTemperature);

	}
	while (!msg_rcvd.stable); //terminate if stable flag is true

	printf("NODE %d TERMINATING...\n", nodeId);

	exit(EXIT_SUCCESS);
}
