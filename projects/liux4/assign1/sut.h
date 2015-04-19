//
//  sut.h
//  assign1
//
//  Created by LiuXin on 4/18/15.
//  Copyright (c) 2015 apepkuss. All rights reserved.
//

struct Seqlist
{
    int  data[ListSize];/* 向量data用于存放表结点 */
    int length; /*  当前的表长度 */
};

void Error(char * message);

void InsertList(struct Seqlist *L, int x, int i);

void DeleteList ( struct Seqlist *L, int i );

void Initlist(struct Seqlist *L);