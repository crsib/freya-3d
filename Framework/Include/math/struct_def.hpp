#ifndef STRUCT_DEF_HPP_
#define STRUCT_DEF_HPP_
namespace math
{
typedef struct VECTOR2F {
  float x;
  float y;
} *PVECTOR2F;

typedef struct VECTOR3F {
  float x;
  float y;
  float z;
} *PVECTOR3F;

typedef struct VECTOR4F {
  float x;
  float y;
  float z;
  float w;
} *PVECTOR4F;

typedef struct MATRIX3X3 {
  static const int m_size = 9;
  union {
    struct {
      float _11, _21, _31;
      float _12, _22, _32;
      float _13, _23, _33;
    };
    float mat_linear[m_size];
    float mat[3][3];
  };
} *PMATRIX3X3;

typedef struct MATRIX4X4 {
  static const int m_size = 16;
  union {
    struct {
      float _11, _21, _31, _41;
      float _12, _22, _32, _42;
      float _13, _23, _33, _43;
      float _14, _24, _34, _44;
    };
    mutable float mat_linear[m_size];
    float mat[4][4];
  };
} *PMATRIX4X4;
}
#endif /*STRUCT_DEF_HPP_*/
