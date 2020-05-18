#include "RColor.h"
const RColor RColor::White = RColor(1, 1, 1);
const RColor RColor::Black = RColor(0, 0, 0);
const RColor RColor::Red = RColor(1, 0, 0);
const RColor RColor::Blue = RColor(0, 0, 1);
const RColor RColor::Green = RColor(0, 1, 0);
const RColor RColor::Yellow = RColor(1, 1, 0);
const RColor RColor::Purple = RColor(0.502f, 0, 0.502f);
const RColor RColor::Orange = RColor(1, 0.647f, 0);
const RColor RColor::Cyan = RColor(0, 1, 1);
const RColor RColor::Magenta = RColor(1, 0, 0.5f);
const RColor RColor::Beige = RColor(0.96f, 0.96f, 0.863f);
const RColor RColor::Brown = RColor(0.396f, 0.263f, 0.129f);

glm::vec4 RColor::ToVec4() const
{
	return glm::vec4(r, g, b, a);
}

const RColor RColor::FromVec4(glm::vec4 val)
{
	return RColor(val.x, val.y, val.z, val.w);
}
