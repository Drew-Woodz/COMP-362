#ifndef _MESSG_H
#define _MESSG_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <mqueue.h>
#include <stdbool.h>
#include <math.h>
#include <unistd.h>

#define MONITOR_QUEUE "/MONITOR" //message queue names must start with '/'
#define NODE_NAME_PREFIX "NODE_" //Add '/' in front still -- just for printing convinience
#define MAX_MSG_SIZE 1024
#define MAX_NAME_LENGTH 32
#define TYPE 1
#define MIN_CHANGE_THRESHOLD 0.001

typedef struct messg
{
	bool stable;
	int nodeId;
	float temperature;
} MESSG;

typedef struct temperature
{
	mqd_t msqid; //this is an outgoing message queue id
	float previousTemperature;
	float currentTemperature;
	bool stable;
} TEMPERATURE;

#define oops(ermsg,erno) {perror(ermsg); exit(erno); }

#endif
