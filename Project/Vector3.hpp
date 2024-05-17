#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <cmath>
#include <iostream>
#include <string>
class Vector3 {

	public:
		float x,y,z;

	public:
		Vector3(): x(0), y(0), z(0){}
		Vector3(const float x, const  float y, const float z): x(x), y(y), z(z){}

	public:
		explicit operator glm::vec3() const{
			return glm::vec3(x,y,z);
		}

		inline Vector3 operator + (const Vector3 other) const {
			return Vector3(this->x + other.x, this->y + other.y, this->z + other.z);
		}

		inline Vector3 operator - (const Vector3 other) const {
			return Vector3(this->x - other.x, this->y - other.y, this->z - other.z);
		}

		inline void operator += (const Vector3 other) {
			this->x += other.x;
			this->y += other.y;
			this->z += other.z;
		}

		inline void operator -= (const Vector3 other) {
			this->x -= other.x;
			this->y -= other.y;
			this->z -= other.z;
		}

		//Scalar Multiplication
		inline Vector3 operator * (const float scalar) const {
			return Vector3(this->x * scalar, this->y * scalar, this->z * scalar);
		}

		inline void operator *= (const float scalar) {
			this->x *= scalar;
			this->y *= scalar;
			this->z *= scalar;
		}

		float Magnitude() const;

		//direction
		Vector3 Direction() const;
		void Normalize();


		float dot(Vector3 other) const;
		Vector3 cross(Vector3 other) const;
	
		//component product
		inline Vector3 operator * (Vector3 other) const {
			return Vector3(this->x * other.x, this->y * other.y, this->z * other.z);
		}

		inline void operator *= (Vector3 other) {
			this->x *= other.x;
			this->y *= other.y;
			this->z *= other.z;
		}

		//printing
		friend std::ostream& operator << (std::ostream& os, const Vector3& v);

};