#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

void create();
void insert_by_priority(int data);
void check(int data);

void display_pqueue();

unsigned int pri_que[MAX];

int front, rear;

#endif
