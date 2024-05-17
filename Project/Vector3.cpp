#include "Vector3.hpp"


float Vector3::Magnitude() const {
	return sqrt(x*x + y*y + z*z);
}

Vector3 Vector3::Direction() const {
	return (*this) * (1/this->Magnitude());
}

void Vector3::Normalize() {
	(*this) *= 1/this->Magnitude();
}

float Vector3::dot(Vector3 other) const {
	return this->x * other.x + this->y * other.y + this->z * other.z;
}


Vector3 Vector3::cross(Vector3 other) const {
	return Vector3(
		this->y * other.z - this->z * other.y,
		this->z * other.x - this->x * other.z,
		this->x * other.y - this->y * other.x
	);
}


std::ostream& operator << (std::ostream& os, const Vector3& v)
{
	os << "{" << v.x << "," << v.y << "," << v.z << "}";
	return os;
}