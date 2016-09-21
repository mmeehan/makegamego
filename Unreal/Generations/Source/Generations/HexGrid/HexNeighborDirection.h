#pragma once

UENUM()
enum class EHexNeighborDirection : uint8
{
	Northeast,
	East,
	Southeast,
	Southwest,
	West,
	Northwest,
};

const uint8 HexNeighborDirections = 6;
