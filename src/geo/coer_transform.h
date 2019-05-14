//
//  coer_transform.h
//  coer
//
//  Created by vs on 12/25/18.
//  Copyright © 2018 ruminant. All rights reserved.
//

#ifndef coer_transform_h
#define coer_transform_h

#include <deps/gl-matrix/gl-matrix.h>

typedef struct
{
	vec3_t anchor;
	vec3_t position;
	vec3_t rotation;
	vec3_t scale;
	double opacity;
	// WVec3d position;
	// WVec3d rotation;
	// WVec3d scale;
	// double opacity;
} CTransform;

void coer_transform_create(CTransform* t);
void coer_transform_destroy(CTransform* t);
void coer_transform_reset(CTransform* t);

#endif /* coer_transform_h */
