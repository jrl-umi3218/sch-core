/* 
 * Copyright (c) 2007 Joint Robotics Laboratory       --  Thu Mar  8 2007
 * All rights reserved.
 *
 * Redistribution and use  in source  and binary  forms,  with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 *   1. Redistributions of  source  code must retain the  above copyright
 *      notice, this list of conditions and the following disclaimer.
 *   2. Redistributions in binary form must reproduce the above copyright
 *      notice,  this list of  conditions and the following disclaimer in
 *      the  documentation  and/or  other   materials provided  with  the
 *      distribution.
 *
 * THIS  SOFTWARE IS PROVIDED BY  THE  COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND  ANY  EXPRESS OR IMPLIED  WARRANTIES,  INCLUDING,  BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES  OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR  PURPOSE ARE DISCLAIMED. IN  NO EVENT SHALL THE COPYRIGHT
 * HOLDERS OR      CONTRIBUTORS  BE LIABLE FOR   ANY    DIRECT, INDIRECT,
 * INCIDENTAL,  SPECIAL,  EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF  SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN  CONTRACT, STRICT LIABILITY, OR
 * TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE
 * USE   OF THIS SOFTWARE, EVEN   IF ADVISED OF   THE POSSIBILITY OF SUCH
 * DAMAGE.
 */
#ifndef _CONFIG_MAL_H_
#define _CONFIG_MAL_H_

/*! Use boost for generic NxP matrix implementation. */
#define _BOOST_MATRIX_ 0

/*! Use VNL for generic NxP matrix implementation. */
#define _VNL_MATRIX_ 0

/*! use t3d for rigid body transformations. */
#define _T3D_R3D_V3D_ 0

/*! Uses the default implementation for the small 4x4 matrices */
#define _DEFAULT_MATRIX4x4_ 1

/*! Uses the default implementation for the small 3x3 matrices */
#define _DEFAULT_MATRIX3x3_ 1

/*! Uses the default implementation for the small 3d vector */
#define _DEFAULT_VECTOR3D_ 1

/*! Uses the default implementation for the small 3d vector */
#define _DEFAULT_VECTOR4D_ 1

#endif /* _CONFIG_MAL_H_ */
