// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#ifndef ENGINE_MATH_QUATERNION_H
#define ENGINE_MATH_QUATERNION_H

#include "engine/math/Vector.h"
#include "engine/stream/Serializable.h"

namespace engine {
namespace math {

	template <typename T>
	class Quaternion
	{
	public:

		union
		{
			T v[4];
			struct
			{
				T x;
				T y;
				T z;
				T w;
			};
		};

	public:
		Quaternion()
			: x(0)
			, y(0)
			, z(0)
			, w(1)
		{ }

		Quaternion(T x, T y, T z, T w)
			: x(x)
			, y(y)
			, z(z)
			, w(w)
		{ }

		Quaternion(const math::Vector<T, 3> &dir, T angle)
		{
			angle *= T(0.5);
			w = cos(angle);
			T s = sin(angle);

			x = dir.x * s;
			y = dir.y * s;
			z = dir.z * s;
		}

	public:
		Quaternion operator * (const Quaternion &other) const
		{
			return Quaternion(
				(w * other.x) + (x * other.w) + (y * other.z) - (z * other.y),
				(w * other.y) - (x * other.z) + (y * other.w) + (z * other.x),
				(w * other.z) + (x * other.y) - (y * other.x) + (z * other.w),
				(w * other.w) - (x * other.x) - (y * other.y) - (z * other.z)
				);
		}

		Quaternion(T yaw, T pitch, T roll)
		{
			yaw *= T(0.5);
			pitch *= T(0.5);
			roll *= T(0.5);

			T siny = sin(yaw);
			T sinp = sin(pitch);
			T sinr = sin(roll);
			T cosy = cos(yaw);
			T cosp = cos(pitch);
			T cosr = cos(roll);

			x = sinp * cosy * cosr - cosp * siny * sinr;
			y = cosp * siny * cosr + sinp * cosy * sinr;
			z = cosp * cosy * sinr - sinp * siny * cosr;
			w = cosp * cosy * cosr + sinp * siny * sinr;

			normalize();
		}

		T getSquareLength() const
		{
			return w * w + x * x + y * y + z * z;
		}

		T getLength() const
		{
			return std::sqrt(getSquareLength());
		}

		const Quaternion &normalize()
		{
			T len = getLength();
			x /= len;
			y /= len;
			z /= len;
			w /= len;
			return *this;
		}

		math::Matrix<T, 4, 4> getMatrix() const
		{
			T x2 = x * x;
			T y2 = y * y;
			T z2 = z * z;
			T xy = x * y;
			T xz = x * z;
			T yz = y * z;
			T wx = w * x;
			T wy = w * y;
			T wz = w * z;

			return math::Matrix<T, 4, 4>
				(
					T(1) - T(2) * (y2 + z2), T(2) * (xy - wz), T(2) * (xz + wy), T(0),
					T(2) * (xy + wz), T(1) - T(2) * (x2 + z2), T(2) * (yz - wx), T(0),
					T(2) * (xz - wy), T(2) * (yz + wx), T(1) - T(2) * (x2 + y2), T(0),
					T(0), T(0), T(0), T(1)
				);
		}

		math::Vector<T, 3> rotateVector(const math::Vector<T, 3> &vec) const
		{
			Quaternion ret = *this * Quaternion(vec.x, vec.y, vec.z, T(0)) * this->getInverse();
			return math::Vector<T, 3>(ret.x, ret.y, ret.z);
		}

		const Quaternion &inverse()
		{
			x = -x;
			y = -y;
			z = -z;
			return *this;
		}

		Quaternion getInverse() const
		{
			return Quaternion(*this).inverse();
		}

		void save(stream::OutputStream<stream::SerializationEndian> &strm) const
		{
			for (size_t i = 0; i < 4; ++i)
				strm.write(v[i]);
		}

		void load(stream::InputStream<stream::SerializationEndian> &strm)
		{
			for (size_t i = 0; i < 4; ++i)
				strm.read(v[i]);
		}

	};

	typedef Quaternion<float> Quat;

}
}

#endif