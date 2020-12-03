#pragma once
#include <vector>
#include <string>

const enum PIXEL {
	PIXEL_SOLID = 0x2588,
	PIXEL_THREEQUARTERS = 0x2593,
	PIXEL_HALF = 0x2592,
	PIXEL_QUARTER = 0x2591,
};

const enum COLOR {
	FG_BLACK = 0x0000,
	FG_DARK_BLUE = 0x0001,
	FG_DARK_GREEN = 0x0002,
	FG_DARK_CYAN = 0x0003,
	FG_DARK_RED = 0x0004,
	FG_DARK_MAGENTA = 0x0005,
	FG_DARK_YELLOW = 0x0006,
	FG_GRAY = 0x0007,
	FG_DARK_GRAY = 0x0008,
	FG_BLUE = 0x0009,
	FG_GREEN = 0x000A,
	FG_CYAN = 0x000B,
	FG_RED = 0x000C,
	FG_MAGENTA = 0x000D,
	FG_YELLOW = 0x000E,
	FG_WHITE = 0x000F,
	BG_BLACK = 0x0000,
	BG_DARK_BLUE = 0x0010,
	BG_DARK_GREEN = 0x0020,
	BG_DARK_CYAN = 0x0030,
	BG_DARK_RED = 0x0040,
	BG_DARK_MAGENTA = 0x0050,
	BG_DARK_YELLOW = 0x0060,
	BG_GRAY = 0x0070,
	BG_DARK_GRAY = 0x0080,
	BG_BLUE = 0x0090,
	BG_GREEN = 0x00A0,
	BG_CYAN = 0x00B0,
	BG_RED = 0x00C0,
	BG_MAGENTA = 0x00D0,
	BG_YELLOW = 0x00E0,
	BG_WHITE = 0x00F0,
};

constexpr int keyDown = 2;
constexpr int keyPressed = 1;
constexpr int keyUp = -1;
constexpr int keyUnpressed = 0;

const std::vector<std::string> commandLists[4][3] = {
	{
		{
			"i1+", "k1+", "k1-", "i1-",
			"k2+", "k2-", "i0+", "i0-",
			"i2+", "i2-", "k0+", "k0-",
		},
		{
			"i1+", "j1+", "j1-", "i1-",
			"j2+", "j2-", "i0+", "i0-",
			"i2+", "i2-", "j0+", "j0-",
		},
		{
			"i1+", "k1-", "k1+", "i1-",
			"k0-", "k0+", "i0+", "i0-",
			"i2+", "i2-", "k2-", "k2+",
		},
	},
	{
		{
			"k1+", "i1-", "i1+", "k1-",
			"i0-", "i0+", "k0+", "k0-",
			"k2+", "k2-", "i2-", "i2+",
		},
		{
			"k1+", "j1+", "j1-", "k1-",
			"j2+", "j2-", "k0+", "k0-",
			"k2+", "k2-", "j0+", "j0-",
		},
		{
			"k1+", "i1+", "i1-", "k1-",
			"i2+", "i2-", "k0+", "k0-",
			"k2+", "k2-", "i0+", "i0-",
		},
	},
	{
		{
			"i1-", "k1-", "k1+", "i1+",
			"k0-", "k0+", "i2-", "i2+",
			"i0-", "i0+", "k2-", "k2+",
		},
		{
			"i1-", "j1+", "j1-", "i1+",
			"j2+", "j2-", "i2-", "i2+",
			"i0-", "i0+", "j0+", "j0-",
		},
		{
			"i1-", "k1+", "k1-", "i1+",
			"k2+", "k2-", "i2-", "i2+",
			"i0-", "i0+", "k0+", "k0-",
		},
	},
	{
		{
			"k1-", "i1+", "i1-", "k1+",
			"i2+", "i2-", "k2-", "k2+",
			"k0-", "k0+", "i0+", "i0-",
		},
		{
			"k1-", "j1+", "j1-", "k1+",
			"j2+", "j2-", "k2-", "k2+",
			"k0-", "k0+", "j0+", "j0-",
		},
		{
			"k1-", "i1-", "i1+", "k1+",
			"i0-", "i0+", "k2-", "k2+",
			"k0-", "k0+", "i2-", "i2+",
		},
	},
};