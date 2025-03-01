// Basic ray structure
// Written by Sergey Kosov in 2005 for Rendering Competition
#pragma once

#include "types.h"

class CPrim;

/// Basic ray structure
struct Ray
{
	Vec3f		org;		///< Origin
	Vec3f		dir;		///< Direction
	float		t;		///< Current/maximum hit distance
	const CPrim* 	hit;		///< Pointer to currently closest primitive

	//std::shared_ptr<CPrim> 	hit;
	// from Problem 2.2.3: after intersection with a primitive =>
	// => store primitive's adress
};
