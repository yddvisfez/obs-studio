/******************************************************************************
    Copyright (C) 2013 by Hugh Bailey <obs.jim@gmail.com>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
******************************************************************************/

#include "vec3.h"
#include "quat.h"
#include "axisang.h"
#include "plane.h"
#include "matrix3.h"
#include "math-extra.h"

float vec3_plane_dist(const struct vec3 *v, const struct plane *p)
{
	return vec3_dot(v, &p->dir) - p->dist;
}

void vec3_rotate(struct vec3 *dst, const struct vec3 *v,
		const struct matrix3 *m)
{
	struct vec3 temp;
	vec3_copy(&temp, v);

	dst->x = vec3_dot(&temp, &m->x);
	dst->y = vec3_dot(&temp, &m->y);
	dst->z = vec3_dot(&temp, &m->z);
}

void vec3_transform(struct vec3 *dst, const struct vec3 *v,
		const struct matrix3 *m)
{
	struct vec3 temp;
	vec3_sub(&temp, v, &m->t);

	dst->x = vec3_dot(&temp, &m->x);
	dst->y = vec3_dot(&temp, &m->y);
	dst->z = vec3_dot(&temp, &m->z);
}

void vec3_mirror(struct vec3 *dst, const struct vec3 *v, const struct plane *p)
{
	struct vec3 temp;
	vec3_mulf(&temp, &p->dir, vec3_plane_dist(v, p) * 2.0f);
	vec3_sub(dst, v, &temp);
}

void vec3_mirrorv(struct vec3 *dst, const struct vec3 *v,
		const struct vec3 *vec)
{
	struct vec3 temp;
	vec3_mulf(&temp, vec, vec3_dot(v, vec) * 2.0f);
	vec3_sub(dst, v, &temp);
}

void vec3_rand(struct vec3 *dst, int positive_only)
{
	dst->x = rand_float(positive_only);
	dst->y = rand_float(positive_only);
	dst->z = rand_float(positive_only);
	dst->w = 0.0f;
}
