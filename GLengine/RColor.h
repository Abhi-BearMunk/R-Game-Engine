#pragma once
#include <glm/glm.hpp>
struct RColor : public glm::vec4
{
	float r;
	float g;
	float b;
	float a;

public:
	RColor(float _r = 1, float _g = 1, float _b = 1, float _a = 1)
		: glm::vec4(_r, _g, _b, _a), r(_r), g(_g), b(_b), a(_a)
	{

	}
	glm::vec4 ToVec4() const;
	static const RColor FromVec4(glm::vec4 val);
	static const RColor White;
	static const RColor Black;
	static const RColor Red;
	static const RColor Blue;
	static const RColor Green;
	static const RColor Yellow;
	static const RColor Purple;
	static const RColor Orange;
	static const RColor Cyan;
	static const RColor Magenta;
	static const RColor Beige;
	static const RColor Brown;
};


