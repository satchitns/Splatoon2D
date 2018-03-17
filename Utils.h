#pragma once
enum ColorT
{
	COLOR_INVALID,
	NONE,
	PINK,
	GREEN,
	BLUE,
	ORANGE,
	COLOR_MAX
};

struct ColorStruct
{
	byte R, G, B, A;
};

typedef struct ColorStruct Color;

Color ReturnColorFromEnum(ColorT color);