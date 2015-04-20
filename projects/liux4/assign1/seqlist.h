//
//  sut.h
//  assign1
//
//  Created by LiuXin on 4/18/15.
//  Copyright (c) 2015 apepkuss. All rights reserved.
//

#define ListSize 100

struct Seqlist
{
    int  data[ListSize];
    int length;
};

void Error(char * message);

// Insert new data into the list
void InsertList(struct Seqlist *L, int x, int i);

// Remove a data from the list by the specified index
void DeleteList ( struct Seqlist *L, int i );

// Initialize a list
void Initlist(struct Seqlist *L);