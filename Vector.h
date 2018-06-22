#pragma once

#ifdef NDEBUG
#define Assert( _exp ) ((void)0)
#else
#define Assert(x)
#endif

#include <sstream>

#define CHECK_VALID( _v ) 0

#define FastSqrt(x)	(sqrt)(x)

#define M_PI		3.14159265358979323846
#define M_PHI		1.61803398874989484820

#define M_PI_2      (M_PI * 2.f)
#define M_PI_F		((float)(M_PI))

#ifndef RAD2DEG
#define RAD2DEG(x)  ((float)(x) * (float)(180.f / M_PI_F))
#endif

#ifndef DEG2RAD
#define DEG2RAD(x)  ((float)(x) * (float)(M_PI_F / 180.f))
#endif

enum
{
	PITCH = 0,
	YAW,
	ROLL
};

#define VALVE_RAND_MAX 0x7fff
#define ALIGN16 __declspec(align(16))
#define VectorExpand(v) (v).x, (v).y, (v).z

typedef float vec_t;

class Vector
{
public:
	float x, y, z;

	Vector(void);
	Vector(float X, float Y, float Z);

	Vector operator+(float fl) const;

	Vector operator-(float fl) const;

	Vector               Cross(const Vector & vOther) const;
	void                 Init(float ix = 0.0f, float iy = 0.0f, float iz = 0.0f);
	bool                 IsValid() const;
	float                operator[] (int i) const;
	float&               operator[] (int i);
	inline void          Zero();
	bool                 operator== (const Vector& v) const;
	bool                 operator!= (const Vector& v) const;
	inline Vector&	     operator+= (const Vector& v);
	inline Vector&	     operator-= (const Vector& v);
	inline Vector&	     operator*= (const Vector& v);
	inline Vector&	     operator*= (float s);
	inline Vector&	     operator/= (const Vector& v);
	inline Vector&	     operator/= (float s);
	inline Vector&	     operator+= (float fl);
	inline Vector&	     operator-= (float fl);
	inline float	     Length() const;

	inline float LengthSqr(void) const
	{
		CHECK_VALID(*this);
		return (x*x + y * y + z * z);
	}

	bool IsZero(float tolerance = 0.01f) const
	{
		return (x > -tolerance && x < tolerance &&
			y > -tolerance && y < tolerance &&
			z > -tolerance && z < tolerance);
	}

	Vector	             Normalize();
	float	             NormalizeInPlace();
	inline float	     DistTo(const Vector& vOther) const;
	inline float	     DistToSqr(const Vector& vOther) const;
	float	             Dot(const Vector& vOther) const;
	float	             Length2D(void) const;
	float	             Length2DSqr(void) const;
	void	             MulAdd(const Vector& a, const Vector& b, float scalar);
	Vector&              operator= (const Vector &vOther);
	Vector	             operator- (void) const;
	Vector	             operator+ (const Vector& v) const;
	Vector	             operator- (const Vector& v) const;
	Vector	             operator* (const Vector& v) const;
	Vector	             operator/ (const Vector& v) const;
	Vector	             operator* (float fl) const;
	Vector	             operator/ (float fl) const;
	float*               Base();
	float const*         Base() const;

	Vector Normalized() const
	{
		Vector res = *this;
		float l = res.Length();

		if (l != 0.0f)
		{
			res /= l;
		}
		else
		{
			res.x = res.y = res.z = 0.0f;
		}

		return res;
	}

	float Dist(const Vector & vOther) const;
};

inline Vector Vector::operator+(float fl) const
{
	return Vector(x + fl, y + fl, z + fl);
}

inline Vector Vector::operator-(float fl) const
{
	return Vector(x - fl, y - fl, z - fl);
}

inline void CrossProduct(const Vector& a, const Vector& b, Vector& result)
{
	result.x = a.y * b.z - a.z * b.y;
	result.y = a.z * b.x - a.x * b.z;
	result.z = a.x * b.y - a.y * b.x;
}

inline Vector Vector::Cross(const Vector& vOther) const
{
	Vector res;
	CrossProduct(*this, vOther, res);
	return res;
}

inline void Vector::Init(float ix, float iy, float iz)
{
	x = ix; y = iy; z = iz;
	CHECK_VALID(*this);
}

inline Vector::Vector(float X, float Y, float Z)
{
	x = X; y = Y; z = Z;
	CHECK_VALID(*this);
}

inline Vector::Vector(void)
{

}

inline void Vector::Zero()
{
	x = y = z = 0.0f;
}

inline void VectorClear(Vector& a)
{
	a.x = a.y = a.z = 0.0f;
}

inline Vector& Vector::operator= (const Vector& vOther)
{
	CHECK_VALID(vOther);
	x = vOther.x; y = vOther.y; z = vOther.z;
	return *this;
}

inline float& Vector::operator[] (int i)
{
	Assert((i >= 0) && (i < 3));
	return ((float*)this)[i];
}

inline float Vector::operator[] (int i) const
{
	Assert((i >= 0) && (i < 3));
	return ((float*)this)[i];
}

inline bool Vector::operator== (const Vector& src) const
{
	CHECK_VALID(src);
	CHECK_VALID(*this);
	return (src.x == x) && (src.y == y) && (src.z == z);
}

inline bool Vector::operator!= (const Vector& src) const
{
	CHECK_VALID(src);
	CHECK_VALID(*this);
	return (src.x != x) || (src.y != y) || (src.z != z);
}

inline void VectorCopy(const Vector& src, Vector& dst)
{
	CHECK_VALID(src);
	dst.x = src.x;
	dst.y = src.y;
	dst.z = src.z;
}

inline  Vector& Vector::operator+= (const Vector& v)
{
	CHECK_VALID(*this);
	CHECK_VALID(v);
	x += v.x; y += v.y; z += v.z;
	return *this;
}

inline  Vector& Vector::operator-= (const Vector& v)
{
	CHECK_VALID(*this);
	CHECK_VALID(v);
	x -= v.x; y -= v.y; z -= v.z;
	return *this;
}

inline  Vector& Vector::operator*= (float fl)
{
	x *= fl;
	y *= fl;
	z *= fl;
	CHECK_VALID(*this);
	return *this;
}

inline  Vector& Vector::operator*= (const Vector& v)
{
	CHECK_VALID(v);
	x *= v.x;
	y *= v.y;
	z *= v.z;
	CHECK_VALID(*this);
	return *this;
}

inline Vector&	Vector::operator+= (float fl)
{
	x += fl;
	y += fl;
	z += fl;
	CHECK_VALID(*this);
	return *this;
}

inline Vector&	Vector::operator-= (float fl)
{
	x -= fl;
	y -= fl;
	z -= fl;
	CHECK_VALID(*this);
	return *this;
}

inline  Vector& Vector::operator/= (float fl)
{
	Assert(fl != 0.0f);
	float oofl = 1.0f / fl;
	x *= oofl;
	y *= oofl;
	z *= oofl;
	CHECK_VALID(*this);
	return *this;
}

inline  Vector& Vector::operator/= (const Vector& v)
{
	CHECK_VALID(v);
	Assert(v.x != 0.0f && v.y != 0.0f && v.z != 0.0f);
	x /= v.x;
	y /= v.y;
	z /= v.z;
	CHECK_VALID(*this);
	return *this;
}

inline float Vector::Length(void) const
{
	CHECK_VALID(*this);
	float root = 0.0f;
	float sqsr = x * x + y * y + z * z;
	root = sqrt(sqsr);
	return root;
}

inline float Vector::Length2D(void) const
{
	CHECK_VALID(*this);
	float root = 0.0f;
	float sqst = x * x + y * y;
	root = sqrt(sqst);
	return root;
}

inline float Vector::Length2DSqr(void) const
{
	return (x*x + y * y);
}

inline Vector CrossProduct(const Vector& a, const Vector& b)
{
	return Vector(a.y*b.z - a.z*b.y, a.z*b.x - a.x*b.z, a.x*b.y - a.y*b.x);
}

float Vector::DistTo(const Vector& vOther) const
{
	Vector delta;
	delta.x = x - vOther.x;
	delta.y = y - vOther.y;
	delta.z = z - vOther.z;
	return delta.Length();
}

float Vector::DistToSqr(const Vector& vOther) const
{
	Vector delta;
	delta.x = x - vOther.x;
	delta.y = y - vOther.y;
	delta.z = z - vOther.z;
	return delta.LengthSqr();
}

inline Vector Vector::Normalize()
{
	Vector vector;
	float length = this->Length();

	if (length != 0)
	{
		vector.x = x / length;
		vector.y = y / length;
		vector.z = z / length;
	}
	else
	{
		vector.x = vector.y = 0.0f; vector.z = 1.0f;
	}

	return vector;
}

inline float Vector::NormalizeInPlace()
{
	float radius = FastSqrt(x * x + y * y + z * z);
	float iradius = 1.f / (radius + FLT_EPSILON);
	x *= iradius;
	y *= iradius;
	z *= iradius;
	return radius;
}

inline void Vector::MulAdd(const Vector& a, const Vector& b, float scalar)
{
	x = a.x + b.x * scalar;
	y = a.y + b.y * scalar;
	z = a.z + b.z * scalar;
}

inline float VectorNormalize(Vector& v)
{
	Assert(v.IsValid());
	float l = v.Length();

	if (l != 0.0f)
	{
		v /= l;
	}
	else
	{
		v.x = v.y = 0.0f; v.z = 1.0f;
	}

	return l;
}

inline float VectorNormalize(float* v)
{
	return VectorNormalize(*(reinterpret_cast<Vector*>(v)));
}

inline Vector Vector::operator+ (const Vector& v) const
{
	Vector res;
	res.x = x + v.x;
	res.y = y + v.y;
	res.z = z + v.z;
	return res;
}

inline Vector Vector::operator- (const Vector& v) const
{
	Vector res;
	res.x = x - v.x;
	res.y = y - v.y;
	res.z = z - v.z;
	return res;
}

inline Vector Vector::operator* (float fl) const
{
	Vector res;
	res.x = x * fl;
	res.y = y * fl;
	res.z = z * fl;
	return res;
}

inline Vector Vector::operator* (const Vector& v) const
{
	Vector res;
	res.x = x * v.x;
	res.y = y * v.y;
	res.z = z * v.z;
	return res;
}

inline Vector Vector::operator/ (float fl) const
{
	Vector res;
	res.x = x / fl;
	res.y = y / fl;
	res.z = z / fl;
	return res;
}

inline Vector Vector::operator/ (const Vector& v) const
{
	Vector res;
	res.x = x / v.x;
	res.y = y / v.y;
	res.z = z / v.z;
	return res;
}

inline float Vector::Dot(const Vector& vOther) const
{
	const Vector& a = *this;
	return(a.x*vOther.x + a.y*vOther.y + a.z*vOther.z);
}

inline float VectorLength(const Vector& v)
{
	CHECK_VALID(v);
	return (float)FastSqrt(v.x*v.x + v.y*v.y + v.z*v.z);
}

inline void VectorSubtract(const Vector& a, const Vector& b, Vector& c)
{
	CHECK_VALID(a);
	CHECK_VALID(b);
	c.x = a.x - b.x;
	c.y = a.y - b.y;
	c.z = a.z - b.z;
}

inline void VectorAdd(const Vector& a, const Vector& b, Vector& c)
{
	CHECK_VALID(a);
	CHECK_VALID(b);
	c.x = a.x + b.x;
	c.y = a.y + b.y;
	c.z = a.z + b.z;
}

inline float* Vector::Base()
{
	return (float*)this;
}

inline float const* Vector::Base() const
{
	return (float const*)this;
}

inline void VectorMAInline(const float* start, float scale, const float* direction, float* dest)
{
	dest[0] = start[0] + direction[0] * scale;
	dest[1] = start[1] + direction[1] * scale;
	dest[2] = start[2] + direction[2] * scale;
}

inline void VectorMAInline(const Vector& start, float scale, const Vector& direction, Vector& dest)
{
	dest.x = start.x + direction.x*scale;
	dest.y = start.y + direction.y*scale;
	dest.z = start.z + direction.z*scale;
}

inline void VectorMA(const Vector& start, float scale, const Vector& direction, Vector& dest)
{
	VectorMAInline(start, scale, direction, dest);
}

inline void VectorMA(const float* start, float scale, const float* direction, float* dest)
{
	VectorMAInline(start, scale, direction, dest);
}

class ALIGN16 VectorAligned : public Vector
{
public:
	inline VectorAligned(void)
	{

	};

	inline VectorAligned(float X, float Y, float Z)
	{
		Init(X, Y, Z);
	}

#ifdef VECTOR_NO_SLOW_OPERATIONS

private:
	VectorAligned(const VectorAligned& vOther);
	VectorAligned(const Vector &vOther);

#else
public:
	explicit VectorAligned(const Vector& vOther)
	{
		Init(vOther.x, vOther.y, vOther.z);
	}

	VectorAligned& operator=(const Vector& vOther)
	{
		Init(vOther.x, vOther.y, vOther.z);
		return *this;
	}

#endif
	float w;
};

inline unsigned long& FloatBits(float& f)
{
	return *reinterpret_cast<unsigned long*>(&f);
}

inline bool IsFinite(float f)
{
	return ((FloatBits(f) & 0x7F800000) != 0x7F800000);
}

class Vector2D
{
public:
	float x, y;

	Vector2D(void);
	Vector2D(float X, float Y);
	Vector2D(const float* pFloat);

	void          Init(float ix = 0.0f, float iy = 0.0f);
	bool          IsValid() const;
	float         operator[] (int i) const;
	float&        operator[] (int i);
	float*        Base();
	float const*  Base() const;
	void          Random(float minVal, float maxVal);
	bool          operator== (const Vector2D& v) const;
	bool          operator!= (const Vector2D& v) const;
	Vector2D&     operator+= (const Vector2D& v);
	Vector2D&     operator-= (const Vector2D& v);
	Vector2D&     operator*= (const Vector2D& v);
	Vector2D&     operator*= (float s);
	Vector2D&     operator/= (const Vector2D& v);
	Vector2D&     operator/= (float s);
	void          Negate();
	float         Length() const;
	float         LengthSqr(void) const;

	bool IsZero(float tolerance = 0.01f) const
	{
		return (x > -tolerance && x < tolerance && y > -tolerance && y < tolerance);
	}

	float         Normalize();
	float         NormalizeInPlace();
	bool          IsLengthGreaterThan(float val) const;
	bool          IsLengthLessThan(float    val) const;
	float         DistTo(const Vector2D& vOther) const;
	float         DistToSqr(const Vector2D& vOther) const;
	void          CopyToArray(float* rgfl) const;
	void          MulAdd(const Vector2D& a, const Vector2D& b, float scalar);
	float         Dot(const Vector2D& vOther) const;
	Vector2D&     operator=(const Vector2D& vOther);

#ifndef VECTOR_NO_SLOW_OPERATIONS

	Vector2D(const Vector2D& vOther);

	Vector2D operator- (void) const;
	Vector2D operator+ (const Vector2D& v) const;
	Vector2D operator- (const Vector2D& v) const;
	Vector2D operator* (const Vector2D& v) const;
	Vector2D operator/ (const Vector2D& v) const;
	Vector2D operator+ (const int i1) const;
	Vector2D operator+ (const float fl) const;
	Vector2D operator* (const float fl) const;
	Vector2D operator/ (const float fl) const;
	Vector2D Cross(const Vector2D& vOther) const;
	Vector2D Min(const Vector2D& vOther) const;
	Vector2D Max(const Vector2D& vOther) const;

#else
private:
	Vector2D(const Vector2D& vOther);
#endif
};

const Vector2D vec2_origin(0, 0);

void     Vector2DClear(Vector2D& a);
void     Vector2DCopy(const Vector2D& src, Vector2D& dst);
void     Vector2DAdd(const Vector2D& a, const Vector2D& b, Vector2D& result);
void     Vector2DSubtract(const Vector2D& a, const Vector2D& b, Vector2D& result);
void     Vector2DMultiply(const Vector2D& a, float b, Vector2D& result);
void     Vector2DMultiply(const Vector2D& a, const Vector2D& b, Vector2D& result);
void     Vector2DDivide(const Vector2D& a, float b, Vector2D& result);
void     Vector2DDivide(const Vector2D& a, const Vector2D& b, Vector2D& result);
void     Vector2DMA(const Vector2D& start, float s, const Vector2D& dir, Vector2D& result);
void     Vector2DMin(const Vector2D& a, const Vector2D& b, Vector2D& result);
void     Vector2DMax(const Vector2D& a, const Vector2D& b, Vector2D& result);
#define  Vector2DExpand( v ) (v).x, (v).y
float    Vector2DNormalize(Vector2D& v);
float    Vector2DLength(const Vector2D& v);
float    DotProduct2D(const Vector2D& a, const Vector2D& b);
void     Vector2DLerp(const Vector2D& src1, const Vector2D& src2, float t, Vector2D& dest);

inline Vector2D::Vector2D(void)
{
#ifdef _DEBUG
#endif
}

inline Vector2D::Vector2D(float X, float Y)
{
	x = X; y = Y;
	Assert(IsValid());
}

inline Vector2D::Vector2D(const float* pFloat)
{
	Assert(pFloat);
	x = pFloat[0]; y = pFloat[1];
	Assert(IsValid());
}

inline Vector2D::Vector2D(const Vector2D& vOther)
{
	Assert(vOther.IsValid());
	x = vOther.x; y = vOther.y;
}

inline void Vector2D::Init(float ix, float iy)
{
	x = ix; y = iy;
	Assert(IsValid());
}

inline void Vector2D::Random(float minVal, float maxVal)
{
	x = minVal + ((float)rand() / VALVE_RAND_MAX) * (maxVal - minVal);
	y = minVal + ((float)rand() / VALVE_RAND_MAX) * (maxVal - minVal);
}

inline void Vector2DClear(Vector2D& a)
{
	a.x = a.y = 0.0f;
}

inline Vector2D& Vector2D::operator= (const Vector2D& vOther)
{
	Assert(vOther.IsValid());
	x = vOther.x; y = vOther.y;
	return *this;
}

inline float& Vector2D::operator[] (int i)
{
	Assert((i >= 0) && (i < 2));
	return ((float*)this)[i];
}

inline float Vector2D::operator[] (int i) const
{
	Assert((i >= 0) && (i < 2));
	return ((float*)this)[i];
}

inline float* Vector2D::Base()
{
	return (float*)this;
}

inline float const* Vector2D::Base() const
{
	return (float const*)this;
}

inline bool Vector2D::IsValid() const
{
	return IsFinite(x) && IsFinite(y);
}

inline bool Vector2D::operator==(const Vector2D& src) const
{
	Assert(src.IsValid() && IsValid());
	return (src.x == x) && (src.y == y);
}

inline bool Vector2D::operator!=(const Vector2D& src) const
{
	Assert(src.IsValid() && IsValid());
	return (src.x != x) || (src.y != y);
}

inline void Vector2DCopy(const Vector2D& src, Vector2D& dst)
{
	Assert(src.IsValid());
	dst.x = src.x;
	dst.y = src.y;
}

inline void	Vector2D::CopyToArray(float* rgfl) const
{
	Assert(IsValid());
	Assert(rgfl);
	rgfl[0] = x; rgfl[1] = y;
}

inline void Vector2D::Negate()
{
	Assert(IsValid());
	x = -x; y = -y;
}

inline Vector2D& Vector2D::operator+= (const Vector2D& v)
{
	Assert(IsValid() && v.IsValid());
	x += v.x; y += v.y;
	return *this;
}

inline Vector2D& Vector2D::operator-= (const Vector2D& v)
{
	Assert(IsValid() && v.IsValid());
	x -= v.x; y -= v.y;
	return *this;
}

inline Vector2D& Vector2D::operator*= (float fl)
{
	x *= fl;
	y *= fl;
	Assert(IsValid());
	return *this;
}

inline Vector2D& Vector2D::operator*= (const Vector2D& v)
{
	x *= v.x;
	y *= v.y;
	Assert(IsValid());
	return *this;
}

inline Vector2D& Vector2D::operator/= (float fl)
{
	Assert(fl != 0.0f);
	float oofl = 1.0f / fl;
	x *= oofl;
	y *= oofl;
	Assert(IsValid());
	return *this;
}

inline Vector2D& Vector2D::operator/= (const Vector2D& v)
{
	Assert(v.x != 0.0f && v.y != 0.0f);
	x /= v.x;
	y /= v.y;
	Assert(IsValid());
	return *this;
}

inline void Vector2DAdd(const Vector2D& a, const Vector2D& b, Vector2D& c)
{
	Assert(a.IsValid() && b.IsValid());
	c.x = a.x + b.x;
	c.y = a.y + b.y;
}

inline void Vector2DAdd(const Vector2D& a, const int b, Vector2D& c)
{
	Assert(a.IsValid());
	c.x = a.x + b;
	c.y = a.y + b;
}

inline void Vector2DAdd(const Vector2D& a, const float b, Vector2D& c)
{
	Assert(a.IsValid());
	c.x = a.x + b;
	c.y = a.y + b;
}

inline void Vector2DSubtract(const Vector2D& a, const Vector2D& b, Vector2D& c)
{
	Assert(a.IsValid() && b.IsValid());
	c.x = a.x - b.x;
	c.y = a.y - b.y;
}

inline void Vector2DMultiply(const Vector2D& a, const float b, Vector2D& c)
{
	Assert(a.IsValid() && IsFinite(b));
	c.x = a.x * b;
	c.y = a.y * b;
}

inline void Vector2DMultiply(const Vector2D& a, const Vector2D& b, Vector2D& c)
{
	Assert(a.IsValid() && b.IsValid());
	c.x = a.x * b.x;
	c.y = a.y * b.y;
}

inline void Vector2DDivide(const Vector2D& a, const float b, Vector2D& c)
{
	Assert(a.IsValid());
	Assert(b != 0.0f);
	float oob = 1.0f / b;
	c.x = a.x * oob;
	c.y = a.y * oob;
}

inline void Vector2DDivide(const Vector2D& a, const Vector2D& b, Vector2D& c)
{
	Assert(a.IsValid());
	Assert((b.x != 0.0f) && (b.y != 0.0f));
	c.x = a.x / b.x;
	c.y = a.y / b.y;
}

inline void Vector2DMA(const Vector2D& start, float s, const Vector2D& dir, Vector2D& result)
{
	Assert(start.IsValid() && IsFinite(s) && dir.IsValid());
	result.x = start.x + s * dir.x;
	result.y = start.y + s * dir.y;
}

inline void	Vector2D::MulAdd(const Vector2D& a, const Vector2D& b, float scalar)
{
	x = a.x + b.x * scalar;
	y = a.y + b.y * scalar;
}

inline void Vector2DLerp(const Vector2D& src1, const Vector2D& src2, float t, Vector2D& dest)
{
	dest[0] = src1[0] + (src2[0] - src1[0]) * t;
	dest[1] = src1[1] + (src2[1] - src1[1]) * t;
}

inline float DotProduct2D(const Vector2D& a, const Vector2D& b)
{
	Assert(a.IsValid() && b.IsValid());
	return(a.x*b.x + a.y*b.y);
}

inline float Vector2D::Dot(const Vector2D& vOther) const
{
	return DotProduct2D(*this, vOther);
}

inline float Vector2DLength(const Vector2D& v)
{
	Assert(v.IsValid());
	return (float)FastSqrt(v.x*v.x + v.y*v.y);
}

inline float Vector2D::LengthSqr(void) const
{
	Assert(IsValid());
	return (x*x + y * y);
}

inline float Vector2D::NormalizeInPlace()
{
	return Vector2DNormalize(*this);
}

inline bool Vector2D::IsLengthGreaterThan(float val) const
{
	return LengthSqr() > val*val;
}

inline bool Vector2D::IsLengthLessThan(float val) const
{
	return LengthSqr() < val*val;
}

inline float Vector2D::Length(void) const
{
	return Vector2DLength(*this);
}

inline void Vector2DMin(const Vector2D &a, const Vector2D& b, Vector2D& result)
{
	result.x = (a.x < b.x) ? a.x : b.x;
	result.y = (a.y < b.y) ? a.y : b.y;
}

inline void Vector2DMax(const Vector2D& a, const Vector2D& b, Vector2D& result)
{
	result.x = (a.x > b.x) ? a.x : b.x;
	result.y = (a.y > b.y) ? a.y : b.y;
}

inline float Vector2DNormalize(Vector2D& v)
{
	Assert(v.IsValid());
	float l = v.Length();

	if (l != 0.0f)
	{
		v /= l;
	}
	else
	{
		v.x = v.y = 0.0f;
	}

	return l;
}

inline float Vector2D::DistTo(const Vector2D& vOther) const
{
	Vector2D delta;
	Vector2DSubtract(*this, vOther, delta);
	return delta.Length();
}

inline float Vector2D::DistToSqr(const Vector2D& vOther) const
{
	Vector2D delta;
	Vector2DSubtract(*this, vOther, delta);
	return delta.LengthSqr();
}

inline void ComputeClosestPoint2D(const Vector2D& vecStart, float flMaxDist, const Vector2D& vecTarget, Vector2D* pResult)
{
	Vector2D vecDelta;
	Vector2DSubtract(vecTarget, vecStart, vecDelta);
	float flDistSqr = vecDelta.LengthSqr();

	if (flDistSqr <= flMaxDist * flMaxDist)
	{
		*pResult = vecTarget;
	}
	else
	{
		vecDelta /= FastSqrt(flDistSqr);
		Vector2DMA(vecStart, flMaxDist, vecDelta, *pResult);
	}
}

#ifndef VECTOR_NO_SLOW_OPERATIONS
#endif

inline Vector2D Vector2D::Min(const Vector2D& vOther) const
{
	return Vector2D(x < vOther.x ? x : vOther.x, y < vOther.y ? y : vOther.y);
}

inline Vector2D Vector2D::Max(const Vector2D& vOther) const
{
	return Vector2D(x > vOther.x ? x : vOther.x, y > vOther.y ? y : vOther.y);
}

inline Vector2D Vector2D::operator- (void) const
{
	return Vector2D(-x, -y);
}

inline Vector2D Vector2D::operator+ (const Vector2D& v) const
{
	Vector2D res;
	Vector2DAdd(*this, v, res);
	return res;
}

inline Vector2D Vector2D::operator- (const Vector2D& v) const
{
	Vector2D res;
	Vector2DSubtract(*this, v, res);
	return res;
}

inline Vector2D Vector2D::operator+ (const int i1) const
{
	Vector2D res;
	Vector2DAdd(*this, i1, res);
	return res;
}

inline Vector2D Vector2D::operator+ (const float fl) const
{
	Vector2D res;
	Vector2DAdd(*this, fl, res);
	return res;
}

inline Vector2D Vector2D::operator* (const float fl) const
{
	Vector2D res;
	Vector2DMultiply(*this, fl, res);
	return res;
}

inline Vector2D Vector2D::operator* (const Vector2D& v) const
{
	Vector2D res;
	Vector2DMultiply(*this, v, res);
	return res;
}

inline Vector2D Vector2D::operator/ (const float fl) const
{
	Vector2D res;
	Vector2DDivide(*this, fl, res);
	return res;
}

inline Vector2D Vector2D::operator/ (const Vector2D& v) const
{
	Vector2D res;
	Vector2DDivide(*this, v, res);
	return res;
}

inline Vector2D operator* (const float fl, const Vector2D& v)
{
	return v * fl;
}

class QAngleByValue;

class QAngle
{
public:
	float x, y, z;

	QAngle NormalizeVec();

	float Length2D(void) const;

	QAngle(void);
	QAngle(float X, float Y, float Z);

	operator QAngleByValue& ()
	{
		return *((QAngleByValue*)(this));
	}

	operator const QAngleByValue& () const
	{
		return *((const QAngleByValue*)(this));
	}

	void            Init(float ix = 0.0f, float iy = 0.0f, float iz = 0.0f);
	void            Random(float minVal, float maxVal);
	bool            IsValid() const;
	void            Invalidate();
	float           operator[] (int i) const;
	float&          operator[] (int i);
	float*          Base();
	float const*    Base() const;
	bool            operator==(const QAngle& v) const;
	bool            operator!=(const QAngle& v) const;
	QAngle&         operator+= (const QAngle& v);
	QAngle&         operator-= (const QAngle& v);
	QAngle&         operator*= (float s);
	QAngle&         operator/= (float s);
	float           Length() const;
	float           LengthSqr() const;
	QAngle&         operator= (const QAngle& src);

#ifndef VECTOR_NO_SLOW_OPERATIONS

	QAngle  operator- (void) const;
	QAngle  operator+ (const QAngle& v) const;
	QAngle  operator- (const QAngle& v) const;
	QAngle  operator* (float fl) const;
	QAngle  operator* (const QAngle& v) const;
	QAngle  operator/ (float fl) const;
#else

private:
	QAngle(const QAngle& vOther);

#endif
};

inline QAngle QAngle::NormalizeVec()
{
	QAngle& vecIn = *this;
	for (int axis = 0; axis < 3; ++axis)
	{
		while (vecIn[axis] > 180.f)
			vecIn[axis] -= 360.f;

		while (vecIn[axis] < -180.f)
			vecIn[axis] += 360.f;

	}

	vecIn[2] = 0.f;
	return vecIn;
}

inline float  QAngle::Length2D(void) const
{
	CHECK_VALID(*this);
	float root = 0.0f;
	float sqst = x * x + y * y;
	root = sqrt(sqst);
	return root;
}

inline QAngle::QAngle(void)
{
#ifdef _DEBUG
#ifdef VECTOR_PARANOIA
	x = y = z = VEC_T_NAN;
#endif
#endif
}

inline QAngle::QAngle(float X, float Y, float Z)
{
	x = X; y = Y; z = Z;
	CHECK_VALID(*this);
}

inline void QAngle::Init(float ix, float iy, float iz)
{
	x = ix; y = iy; z = iz;
	CHECK_VALID(*this);
}

inline void QAngle::Random(float minVal, float maxVal)
{
	x = minVal + ((float)rand() / RAND_MAX) * (maxVal - minVal);
	y = minVal + ((float)rand() / RAND_MAX) * (maxVal - minVal);
	z = minVal + ((float)rand() / RAND_MAX) * (maxVal - minVal);
	CHECK_VALID(*this);
}

inline QAngle& QAngle::operator= (const QAngle& vOther)
{
	CHECK_VALID(vOther);
	x = vOther.x; y = vOther.y; z = vOther.z;
	return *this;
}

inline bool QAngle::operator== (const QAngle& src) const
{
	CHECK_VALID(src);
	CHECK_VALID(*this);
	return (src.x == x) && (src.y == y) && (src.z == z);
}

inline bool QAngle::operator!= (const QAngle& src) const
{
	CHECK_VALID(src);
	CHECK_VALID(*this);
	return (src.x != x) || (src.y != y) || (src.z != z);
}

inline QAngle& QAngle::operator+= (const QAngle& v)
{
	CHECK_VALID(*this);
	CHECK_VALID(v);
	x += v.x; y += v.y; z += v.z;
	return *this;
}

inline QAngle& QAngle::operator-= (const QAngle& v)
{
	CHECK_VALID(*this);
	CHECK_VALID(v);
	x -= v.x; y -= v.y; z -= v.z;
	return *this;
}

inline QAngle& QAngle::operator*= (float fl)
{
	x *= fl;
	y *= fl;
	z *= fl;
	CHECK_VALID(*this);
	return *this;
}

inline QAngle& QAngle::operator/=(float fl)
{
	Assert(fl != 0.0f);
	float oofl = 1.0f / fl;
	x *= oofl;
	y *= oofl;
	z *= oofl;
	CHECK_VALID(*this);
	return *this;
}

inline float* QAngle::Base()
{
	return (float*)this;
}

inline float const* QAngle::Base() const
{
	return (float const*)this;
}

inline float& QAngle::operator[] (int i)
{
	Assert((i >= 0) && (i < 3));
	return ((float*)this)[i];
}

inline float QAngle::operator[] (int i) const
{
	Assert((i >= 0) && (i < 3));
	return ((float*)this)[i];
}

inline float QAngle::Length() const
{
	CHECK_VALID(*this);
	return (float)FastSqrt(LengthSqr());
}

inline float QAngle::LengthSqr() const
{
	CHECK_VALID(*this);
	return x * x + y * y + z * z;
}

#ifndef VECTOR_NO_SLOW_OPERATIONS

inline QAngle QAngle::operator- (void) const
{
	return QAngle(-x, -y, -z);
}

inline QAngle QAngle::operator+ (const QAngle& v) const
{
	QAngle res;
	res.x = x + v.x;
	res.y = y + v.y;
	res.z = z + v.z;
	return res;
}

inline QAngle QAngle::operator- (const QAngle& v) const
{
	QAngle res;
	res.x = x - v.x;
	res.y = y - v.y;
	res.z = z - v.z;
	return res;
}

inline QAngle QAngle::operator* (float fl) const
{
	QAngle res;
	res.x = x * fl;
	res.y = y * fl;
	res.z = z * fl;
	return res;
}

inline QAngle QAngle::operator* (const QAngle& v) const
{
	QAngle res;
	res.x = x * v.x;
	res.y = y * v.y;
	res.z = z * v.z;
	return res;
}

inline QAngle QAngle::operator/(float fl) const
{
	QAngle res;
	res.x = x / fl;
	res.y = y / fl;
	res.z = z / fl;
	return res;
}

inline QAngle operator* (float fl, const QAngle& v)
{
	return v * fl;
}

#endif

inline void QAngleSubtract(const QAngle& a, const QAngle& b, QAngle& c)
{
	CHECK_VALID(a);
	CHECK_VALID(b);
	c.x = a.x - b.x;
	c.y = a.y - b.y;
	c.z = a.z - b.z;
}

inline void QAngleAdd(const QAngle& a, const QAngle& b, QAngle& c)
{
	CHECK_VALID(a);
	CHECK_VALID(b);
	c.x = a.x + b.x;
	c.y = a.y + b.y;
	c.z = a.z + b.z;
}

inline int UtlMemory_CalcNewAllocationCount(int nAllocationCount, int nGrowSize, int nNewSize, int nBytesItem)
{
	if (nGrowSize)
		nAllocationCount = ((1 + ((nNewSize - 1) / nGrowSize)) * nGrowSize);
	else
	{
		if (!nAllocationCount)
			nAllocationCount = (31 + nBytesItem) / nBytesItem;

		while (nAllocationCount < nNewSize)
			nAllocationCount *= 2;
	}

	return nAllocationCount;
}

template< class T, class I = int >
class CUtlMemory
{
public:
	T & operator[](I i)
	{
		return m_pMemory[i];
	}

	T* Base()
	{
		return m_pMemory;
	}

	int NumAllocated() const
	{
		return m_nAllocationCount;
	}

	void Grow(int num = 1)
	{
		if (IsExternallyAllocated())
			return;

		int nAllocationRequested = m_nAllocationCount + num;
		int nNewAllocationCount = UtlMemory_CalcNewAllocationCount(m_nAllocationCount, m_nGrowSize, nAllocationRequested, sizeof(T));

		if ((int)(I)nNewAllocationCount < nAllocationRequested)
		{
			if ((int)(I)nNewAllocationCount == 0 && (int)(I)(nNewAllocationCount - 1) >= nAllocationRequested)
				--nNewAllocationCount;
			else
			{
				if ((int)(I)nAllocationRequested != nAllocationRequested)
					return;

				while ((int)(I)nNewAllocationCount < nAllocationRequested)
					nNewAllocationCount = (nNewAllocationCount + nAllocationRequested) / 2;
			}
		}

		m_nAllocationCount = nNewAllocationCount;

		if (m_pMemory)
			m_pMemory = (T*)realloc(m_pMemory, m_nAllocationCount * sizeof(T));
		else
			m_pMemory = (T*)malloc(m_nAllocationCount * sizeof(T));
	}

	bool IsExternallyAllocated() const
	{
		return m_nGrowSize < 0;
	}

protected:
	T * m_pMemory;
	int  m_nAllocationCount;
	int  m_nGrowSize;
};

template <class T>
inline T* Construct(T* pMemory)
{
	return ::new(pMemory) T;
}

template <class T>
inline void Destruct(T* pMemory)
{
	pMemory->~T();
}

template< class T, class A = CUtlMemory<T> >
class CUtlVector
{
	typedef A CAllocator;
public:
	T & operator[](int i)
	{
		return m_Memory[i];
	}

	T& Element(int i)
	{
		return m_Memory[i];
	}

	T* Base()
	{
		return m_Memory.Base();
	}

	int Count() const
	{
		return m_Size;
	}

	void RemoveAll()
	{
		for (int i = m_Size; --i >= 0; )
			Destruct(&Element(i));

		m_Size = 0;
	}

	int AddToTail()
	{
		return InsertBefore(m_Size);
	}

	int InsertBefore(int elem)
	{
		GrowVector();
		ShiftElementsRight(elem);
		Construct(&Element(elem));
		return elem;
	}

protected:
	void GrowVector(int num = 1)
	{
		if (m_Size + num > m_Memory.NumAllocated())
			m_Memory.Grow(m_Size + num - m_Memory.NumAllocated());

		m_Size += num;
		ResetDbgInfo();
	}

	void ShiftElementsRight(int elem, int num = 1)
	{
		int numToMove = m_Size - elem - num;
		if ((numToMove > 0) && (num > 0))
			memmove(&Element(elem + num), &Element(elem), numToMove * sizeof(T));
	}

	CAllocator   m_Memory;
	int          m_Size;
	T*           m_pElements;

	inline void ResetDbgInfo()
	{
		m_pElements = Base();
	}
};

struct Circle
{
	float radius;
	float iRadius;
	Vector center;
	float direction;

	Circle() : center(Vector(0, 0, 0)), radius(1.f), iRadius(1.f), direction(1.f) {}

	Circle(Vector cent, float rad, float dir)
	{
		center = cent;
		radius = rad;
		direction = dir;
		iRadius = 1.f / radius;
	}

	Circle(Vector A, Vector B, Vector C)
	{
		float yDelta_a = B.y - A.y;
		float xDelta_a = B.x - A.x;
		float yDelta_b = C.y - B.y;
		float xDelta_b = C.x - B.x;
		center = Vector(0, 0, 0);
		float aSlope = yDelta_a / xDelta_a;
		float bSlope = yDelta_b / xDelta_b;
		center.x = (aSlope*bSlope*(A.y - C.y) + bSlope * (A.x + B.x) - aSlope * (B.x + C.x)) / (2 * (bSlope - aSlope));
		center.y = -1 * (center.x - (A.x + B.x) / 2) / aSlope + (A.y + B.y) / 2;
		radius = sqrtf((B.x - center.x) * (B.x - center.x) + (B.y - center.y) * (B.y - center.y));
		float vecMulA = A.y - center.y;
		float vecMulB = B.y - center.y;
		float vecMulA2 = A.x - center.x;
		float vecMulB2 = B.x - center.x;
		float angA1 = RAD2DEG(acosf(vecMulA / (radius * radius)));
		float angA2 = RAD2DEG(acosf(vecMulA2 / (radius * radius)));

		if (angA2 > 90)
			angA1 = 360.f - angA1;

		float angB1 = RAD2DEG(acosf(vecMulB / (radius * radius)));
		float angB2 = RAD2DEG(acosf(vecMulB2 / (radius * radius)));

		if (angB2 > 90)
			angB1 = 360.f - angB1;

		float angDiff = fmodf(angA1 - angB1 + 540, 360.f) - 180.f;
		direction = (angDiff > 0) ? -1 : 1;
		iRadius = 1.f / radius;
	}
};