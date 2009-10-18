#include "math/math.hpp"
#include "math/quaternion.hpp"
#include "math/matrix4x4.hpp"
#include "math/vector3d.hpp"
#include "math/plane.hpp"
#include "math/matrix3x3.hpp"
#include "math/vector3d.hpp"
#include "math/vector2d.hpp"

namespace math
{
matrix4x4 QuaternionToMatrix4x4(const quaternion& q)
{
	float mat[16];
	float xx = q.u.x*q.u.x;
	float xy = q.u.x*q.u.y;
	float xz = q.u.x*q.u.z;
	float xw = q.u.x*q.w;

	float yy = q.u.y*q.u.y;
	float yz = q.u.y*q.u.z;
	float yw = q.u.y*q.w;

	float zz = q.u.z*q.u.z;
	float zw = q.u.z*q.w;

	mat[0]  = 1-2*(yy+zz);
	mat[4]  =   2*(xy-zw);
	mat[8]  =   2*(xz+yw);

	mat[1]  =   2*(xy+ zw );
	mat[5]  = 1-2*(xx+ zz );
	mat[9]  =   2*(yz- xw );

	mat[2]  =   2*(xz- yw );
	mat[6]  =   2*(yz+ xw );
	mat[10] = 1-2*(xx+ yy );

	mat[3]  =
		mat[7]  =
			mat[11] =
				mat[12] =
					mat[13] =
						mat[14] = zero;
	mat[15] = unit;

	return matrix4x4(mat);
}

quaternion Matrix4x4ToQuaternion(const matrix4x4& m)
{
	float tr, s, q[4];
	int   i, j, k;
	float w;
	vector3d u;
	const int nxt[3] = {1, 2, 0};

	tr=m.mat[0][0]+m.mat[1][1]+m.mat[2][2];

	if (tr>0.0)
	{
		s=sqrt(tr+1.0);
		w=s/2.0;
		s=0.5/s;
		u.x=(m.mat[1][2]-m.mat[2][1])*s;
		u.y=(m.mat[2][0]-m.mat[0][2])*s;
		u.z=(m.mat[0][1]-m.mat[1][0])*s;
	}
	else
	{
		i = 0;

		if (m.mat[1][1] > m.mat[0][0])
			i=1;
		if (m.mat[2][2] > m.mat[i][i])
			i=2;

		j=nxt[i];
		k=nxt[j];

		s = sqrt((m.mat[i][i] - (m.mat[j][j] + m.mat[k][k])) + 1.0);
		q[i]=s*0.5;


		if(s!=0.0)
			s=0.5/s;

		q[3] = (m.mat[k][j]-m.mat[j][k])*s;
		q[j] = (m.mat[j][i]+m.mat[i][j])*s;
		q[k] = (m.mat[k][i]+m.mat[i][k])*s;

		u.x = q[0];
		u.y = q[1];
		u.z = q[2];
		w = q[3];
	}
	return quaternion(w,u);
}
}
