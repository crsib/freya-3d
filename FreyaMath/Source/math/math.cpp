#include "math/math.hpp"
#include "math/quaternion.hpp"
#include "math/matrix4x4.hpp"
#include "math/vector3d.hpp"
#include "math/plane.hpp"
#include "math/matrix3x3.hpp"
#include "math/matrix2x2.hpp"
#include "math/vector3d.hpp"
#include "math/vector2d.hpp"
#include "math/vector4d.hpp"

namespace math
{

const matrix2x2	matrix2x2::identity;
const matrix3x3	matrix3x3::identity;
const matrix4x4	matrix4x4::identity;

const vector3d  vector3d::i(1,0,0);
const vector3d  vector3d::j(0,1,0);
const vector3d  vector3d::k(0,0,1);

}
