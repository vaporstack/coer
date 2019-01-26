//
//  coer_anim.h
//  coer
//
//  Created by vs on 1/25/19.
//  Copyright © 2019 ruminant. All rights reserved.
//

#ifndef coer_anim_h
#define coer_anim_h

//#include <stdio.h>
#include <stdbool.h>

enum {
	COER_ANIM_KEY_TYPE_SIGNED,
	COER_ANIM_KEY_TYPE_FLOAT,
	COER_ANIM_KEY_TYPE_DOUBLE,
	COER_ANIM_KEY_TYPE_NONE
};

typedef struct CAnimKeyD1
{
	unsigned index;
	double value;
}CAnimKeyD1;

typedef struct CAnimKeyD2
{
	unsigned index;
	double vx;
	double vy;
}CAnimKeyD2;

typedef struct CAnimKeyD3
{
	unsigned index;
	double vx;
	double vy;
	double vz;
}CAnimKeyD3;

typedef struct CAnimKeyF1
{
	unsigned index;
	float value;
}CAnimKeyF1;

typedef struct CAnimKeyS1
{
	unsigned index;
	signed value;
}CAnimKeyS1;

typedef struct CAnim
{
	bool loop;
	unsigned num;
	void** keys;
}CAnim;

CAnim* coer_anim_create(unsigned type);
void coer_anim_get_frames_for_time(CAnim* anim, double t, unsigned* prev, unsigned* next);


#endif /* coer_anim_h */
