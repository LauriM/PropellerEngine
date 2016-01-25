// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#ifndef ENGINE_MATH_MATRIX_H
#define ENGINE_MATH_MATRIX_H

#include "engine/preprocessor/macros.h"

#include "engine/stream/Serializable.h"
#include "engine/math/Vector.h"

namespace engine {
namespace math {

#define DEFINE_USING_MATRIX_BASECLASS \
	using BaseClass::operator ==;

	template <typename T, typename FinalT, unsigned X, unsigned Y>
	class MatrixBase
	{
	public:
		union {
			T v[Y * X];
			T m[Y][X];
		};

	protected:
		typedef T Type;

	public:
		MatrixBase()
		{
			for (unsigned i = 0; i < elementCount(v); ++i)
				v[i] = T(0);
		}

		inline bool operator == (const FinalT &other)
		{
			for (unsigned i = 0; i < elementCount(v); ++i)
				if (v[i] != other.v[i])
					return false;

			return true;
		}

		inline bool operator != (const FinalT &other)
		{
			return !(*this == other);
		}

		//TODO: return values!

		// operations for value

		inline void operator *= (const T &value)
		{
			for (unsigned i = 0; i < elementCount(v); ++i)
				v[i] *= value;
		}

		inline void operator /= (const T &value)
		{
			for (unsigned i = 0; i < elementCount(v); ++i)
				v[i] /= value;
		}

		inline void operator += (const T &value)
		{
			for (unsigned i = 0; i < elementCount(v); ++i)
				v[i] += value;
		}

		inline void operator -= (const T &value)
		{
			for (unsigned i = 0; i < elementCount(v); ++i)
				v[i] -= value;
		}

		void save(stream::OutputStream<stream::SerializationEndian> &strm) const
		{
			for (size_t i = 0; i < (X * Y); ++i)
				strm.write(v[i]);
		}

		void load(stream::InputStream<stream::SerializationEndian> &strm)
		{
			for (size_t i = 0; i < (X * Y); ++i)
				strm.read(v[i]);
		}
	};

	// Generic implementation
	template <typename T, unsigned X, unsigned Y>
	class Matrix : public MatrixBase<T, Matrix<T, X, Y>,  X, Y>
	{
	private:
		typedef MatrixBase<T, Matrix<T, X, Y>, X, Y> BaseClass;

	public:
		DEFINE_USING_MATRIX_BASECLASS;

		using BaseClass::Type;
		using BaseClass::m;
		using BaseClass::v;

		Matrix()
			: BaseClass()
		{ }

	};

	// 2x2 implementation
	template <typename T>
	class Matrix<T, 2, 2> : public MatrixBase<T, Matrix<T, 2, 2>, 2, 2 >
	{
	private:
		typedef MatrixBase<T, Matrix<T, 2, 2>, 2, 2> BaseClass;

	public:
		DEFINE_USING_MATRIX_BASECLASS;

		using BaseClass::m;
		using BaseClass::v;

		Matrix()
			: BaseClass()
		{ }

		Matrix( T m1, T m2, T m3, T m4 )
		{ 
			v[0] = m1;
			v[1] = m2;
			v[2] = m3;
			v[3] = m4;
		}

		inline const math::Vector<T, 2> operator * (const math::Vector<T, 2> &vector)
		{
			math::Vector<T, 2> ret;

			// vec.x | v0  v1
			// vec.y | v2  v3

			ret.x = v[0] * vector.x + v[1] * vector.y;
			ret.y = v[2] * vector.x + v[3] * vector.y;

			return ret;
		}

	};

	// 4x4 implementation
	template <typename T>
	class Matrix<T, 4, 4> : public MatrixBase<T, Matrix<T, 4, 4>, 4, 4 >
	{
	private:
		typedef MatrixBase<T, Matrix<T, 4, 4>, 4, 4> BaseClass;

	public:
		DEFINE_USING_MATRIX_BASECLASS;

		using BaseClass::m;
		using BaseClass::v;

		Matrix()
		{ 
			v[0] = 0;
			v[1] = 2;
			v[2] = 3;
			v[3] = 4;
			v[4] = 5;
			v[5] = 6;
			v[6] = 7;
			v[7] = 8;
			v[8] = 9;
			v[9] = 10;
			v[10] = 11;
			v[11] = 12;
			v[12] = 13;
			v[13] = 14;
			v[14] = 15;
			v[15] = 16;
		}

		Matrix(
				T m1, T m2, T m3, T m4,
				T m5, T m6, T m7, T m8,
				T m9, T m10, T m11, T m12,
				T m13, T m14, T m15, T m16
			)
		{ 
			v[0] = m1;
			v[1] = m2;
			v[2] = m3;
			v[3] = m4;
			v[4] = m5;
			v[5] = m6;
			v[6] = m7;
			v[7] = m8;
			v[8] = m9;
			v[9] = m10;
			v[10] = m11;
			v[11] = m12;
			v[12] = m13;
			v[13] = m14;
			v[14] = m15;
			v[15] = m16;
		}

		inline static const Matrix<T, 4, 4> getTranslation(engine::math::Vector<T, 3> vector)
		{
			return Matrix<T, 4, 4>(
				T(1), T(0), T(0), T(0),
				T(0), T(1), T(0), T(0),
				T(0), T(0), T(1), T(0),
				T(vector.x), T(vector.y), T(vector.z), T(1)
				);
		}

		inline static const Matrix<T, 4, 4> getScale(T scale)
		{
			return Matrix<T, 4, 4>(
				T(scale), T(0), T(0), T(0),
				T(0), T(scale), T(0), T(0),
				T(0), T(0), T(scale), T(0),
				T(0), T(0), T(0),     T(1)
				);
		}

		inline static const Matrix<T, 4, 4> getRotationX(T angle)
		{
			return Matrix<T, 4, 4>(
				T(1), T(0), T(0), T(0),
				T(0), cos(angle), -sin(angle), T(0),
				T(0), sin(angle), cos(angle), T(0),
				T(0), T(0), T(0), T(1)
				);
		}

		inline static const Matrix<T, 4, 4> getRotationY(T angle)
		{
			return Matrix<T, 4, 4>(
				cos(angle), T(0), sin(angle), T(0),
				T(0),       T(1), 0,          T(0),
				-sin(angle),T(0), cos(angle), T(0),
				T(0),       T(0), T(0),       T(1)
				);
		}

		inline static const Matrix<T, 4, 4> getRotationZ(T angle)
		{
			return Matrix<T, 4, 4>(
				cos(angle), -sin(angle),  T(0), T(0),
				sin(angle), cos(angle),   T(0), T(0),
				T(0),       T(0),         T(1), T(0),
				T(0),       T(0),         T(0), T(1)
				);
		}

		inline static const Matrix<T, 4, 4> getPerspective(const T fov, const T aspect, const T zNear, const T zFar, const bool leftHanded)
		{
			Matrix<T, 4, 4> ret(
				1, 0, 0, 0,
				0, 1, 0, 0,
				0, 0, 1, 0,
				0, 0, 0, 1);

			if (fov <= 0 || aspect == 0)
				assert(fov > 0 && aspect != 0);

			float frustumDepth = zFar - zNear;
			float oneOverDepth = 1 / frustumDepth;

			ret.m[1][1] = 1 / tan(0.5f * fov);
			ret.m[0][0] = (leftHanded ? 1 : -1) * ret.m[1][1] / aspect;
			ret.m[2][2] = zFar * oneOverDepth;
			ret.m[3][2] = (-zFar * zNear) * oneOverDepth;
			ret.m[2][3] = 1;
			ret.m[3][3] = 0;

			return ret;
		}

		inline static const Matrix<T, 4, 4> getLookAt(Vec3 pos, Vec3 target, Vec3 up)
		{
			Vec3 zAxis = pos - target; zAxis.normalize();
			Vec3 xAxis = up.getCrossProduct(zAxis); xAxis.normalize();
			Vec3 yAxis = zAxis.getCrossProduct(xAxis);

			Matrix<T, 4, 4> orientation(
				xAxis.x, yAxis.x, zAxis.x, 0,
				xAxis.y, yAxis.y, zAxis.y, 0,
				xAxis.z, yAxis.z, zAxis.z, 0,
				0, 0, 0, 1
				);

			return orientation * getTranslation(-Vec3(pos));
		}

		// operations for matrix to matrix operations

		inline const Matrix<T, 4, 4> operator * (const Matrix<T, 4, 4> &other) const
		{
			Matrix<T, 4, 4> ret(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);

			for (size_t i = 0; i<4; ++i)
			for (size_t j = 0; j<4; ++j)
			for (size_t k = 0; k<4; ++k)
				ret.m[i][j] += m[i][k] * other.m[k][j];

			return ret;
		}

		inline const Matrix<T, 4, 4>& operator *= (const Matrix<T, 4, 4> &other)
		{
			*this = *this * other;
			return *this;
		}

		inline const math::Vector<T, 3> operator * (const math::Vector<T, 3> &vector)
		{
			math::Vector<T, 3> ret;

			ret.x = m[0][0] * vector.x + m[0][1] * vector.x + m[0][2] * vector.x + m[0][3] * vector.x;
			ret.y = m[1][0] * vector.y + m[1][1] * vector.y + m[1][2] * vector.y + m[1][3] * vector.y;
			ret.z = m[2][0] * vector.z + m[2][1] * vector.z + m[2][2] * vector.z + m[2][3] * vector.z;

			return ret;
		}

	};

	typedef Matrix<float, 4, 4> Matrix4x4;
	typedef Matrix<unsigned, 4, 4> Matrix4x4u;
	typedef Matrix<int, 4, 4> Matrix4x4i;

	typedef Matrix<float, 2, 2> Matrix2x2;
	typedef Matrix<unsigned, 2, 2> Matrix2x2u;
	typedef Matrix<int, 2, 2> Matrix2x2i;
}
}

#endif