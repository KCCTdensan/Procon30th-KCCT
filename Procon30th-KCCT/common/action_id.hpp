#pragma once


constexpr int numKindsOfAction = 9;

enum class ActionID
{
	ID_Stay,
	ID_TopLeft,
	ID_Top,
	ID_TopRight,
	ID_Left,
	ID_Right,
	ID_BottomLeft,
	ID_Bottom,
	ID_BottomRight,
	ID_None = -1
};