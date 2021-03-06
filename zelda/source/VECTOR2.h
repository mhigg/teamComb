#pragma once
class VECTOR2f;
class VECTOR2
{
public:
	//default
	VECTOR2();
	//with data
	VECTOR2(int x, int y);
	VECTOR2(VECTOR2f);
	~VECTOR2();
	int x;
	int y;

	//΅ΝίΪ°ΐ°Μ΅°Κή°Ϋ°Δή
	//γόZq
	VECTOR2& operator = (const VECTOR2& vec);

	//YZq
	int& operator[](int i);

	//δrZq
	//ΕγΜconstΝROΜσ
	bool operator==(const VECTOR2& vec) const;
	bool operator!=(const VECTOR2& vec) const;
	bool operator>=(const VECTOR2& vec) const;
	bool operator<=(const VECTOR2& vec) const;
	bool operator>(const VECTOR2& vec) const;
	bool operator<(const VECTOR2& vec) const;


	//PZq
	//l₯Z
	VECTOR2& operator += (const VECTOR2& vec);
	VECTOR2& operator -= (const VECTOR2& vec);
	VECTOR2& operator *= (int k);
	VECTOR2& operator /= (int k);
	//πΑ¦ι
	VECTOR2  operator+()const;
	VECTOR2  operator-()const;
};

class VECTOR2f
{
public:
	//default
	VECTOR2f();
	//with data
	VECTOR2f(float x, float y);
	VECTOR2f(VECTOR2);
	~VECTOR2f();
	float x;
	float y;

	//΅ΝίΪ°ΐ°Μ΅°Κή°Ϋ°Δή
	//γόZq
	VECTOR2f& operator = (const VECTOR2f& vec);

	//YZq
	float& operator[](float i);

	//δrZq
	//ΕγΜconstΝROΜσ
	bool operator==(const VECTOR2f& vec) const;
	bool operator!=(const VECTOR2f& vec) const;
	bool operator>=(const VECTOR2f& vec) const;
	bool operator<=(const VECTOR2f& vec) const;
	bool operator>(const VECTOR2f& vec) const;
	bool operator<(const VECTOR2f& vec) const;


	//PZq
	//l₯Z
	VECTOR2f& operator += (const VECTOR2f& vec);
	VECTOR2f& operator -= (const VECTOR2f& vec);
	VECTOR2f& operator *= (float k);
	VECTOR2f& operator /= (float k);
	//πΑ¦ι
	VECTOR2f operator+()const;
	VECTOR2f  operator-()const;
};

//ΝήΈΔΩΜZ
//VECTOR2 + int
VECTOR2 operator+(const VECTOR2 &u, int v);

//VECTOR2 - int
VECTOR2 operator-(const VECTOR2 &u, int v);

//VECTOR2 + VECTOR2
VECTOR2 operator+(const VECTOR2 &u, const VECTOR2 &v);

//VECTOR2 - VECTOR2
VECTOR2 operator-(const VECTOR2 &u, const VECTOR2 &v);

//VECTOR2 * int
VECTOR2 operator*(const VECTOR2 &u, int v);

//int * VECTOR2
VECTOR2 operator*(int u, const VECTOR2 &v);

//VECTOR2 * VECTOR2
VECTOR2 operator*(const VECTOR2 &u, const VECTOR2 &v);

//VECTOR2 / int
VECTOR2 operator/(const VECTOR2 &u, int v);

//VECTOR2 / VECTOR2
VECTOR2 operator/(const VECTOR2 &u, const VECTOR2 &v);

//VECTOR2 % int
VECTOR2 operator%(const VECTOR2 &u, int v);

//VECTOR2 % VECTOR2
VECTOR2 operator%(const VECTOR2 &u, const VECTOR2 &v);

//ΝήΈΔΩΜZ
//VECTOR2 + int
VECTOR2f operator+(const VECTOR2f &u, float v);

//VECTOR2 - int
VECTOR2f operator-(const VECTOR2f &u, float v);

//VECTOR2 + VECTOR2
VECTOR2f operator+(const VECTOR2f &u, const VECTOR2f &v);

//VECTOR2 - VECTOR2
VECTOR2f operator-(const VECTOR2f &u, const VECTOR2f &v);

//VECTOR2 * int
VECTOR2f operator*(const VECTOR2f &u, float v);

//int * VECTOR2
VECTOR2f operator*(float u, const VECTOR2f &v);

//VECTOR2 * VECTOR2
VECTOR2f operator*(const VECTOR2f &u, const VECTOR2f &v);

//VECTOR2 / int
VECTOR2f operator/(const VECTOR2f &u, float v);

//VECTOR2 / VECTOR2
VECTOR2f operator/(const VECTOR2f &u, const VECTOR2f &v);

//VECTOR2 % int
VECTOR2f operator%(const VECTOR2f &u, float v);

//VECTOR2 % VECTOR2
VECTOR2f operator%(const VECTOR2f &u, const VECTOR2f &v);
