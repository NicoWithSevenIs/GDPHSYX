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
		Vector3(float x, float y, float z): x(x), y(y), z(z){}

	public:
		explicit operator glm::vec3() const{
			
		}

		inline Vector3 operator + (Vector3 other) {
			return Vector3(this->x + other.x, this->y + other.y, this->z + other.z);
		}

		inline Vector3 operator - (Vector3 other) {
			return Vector3(this->x - other.x, this->y - other.y, this->z - other.z);
		}

		inline void operator += (Vector3 other) {
			this->x += other.x;
			this->y += other.y;
			this->z += other.z;
		}

		inline void operator -= (Vector3 other) {
			this->x -= other.x;
			this->y -= other.y;
			this->z -= other.z;
		}

		//Scalar Multiplication
		inline Vector3 operator * (float scalar) {
			return Vector3(this->x * scalar, this->y * scalar, this->z * scalar);
		}

		inline void operator *= (float scalar) {
			this->x *= scalar;
			this->y *= scalar;
			this->z *= scalar;
		}

		float Magnitude();

		//direction
		Vector3 Direction();
		void Normalize();


		float dot(Vector3 other);
		Vector3 cross(Vector3 other);
	
		//component product
		inline Vector3 operator * (Vector3 other) {
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