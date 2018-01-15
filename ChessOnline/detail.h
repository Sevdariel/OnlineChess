#pragma once



namespace detail
{
	struct IChessPieceEnums
	{
		enum type { PAWN, KNIGHT, BISHOP, ROOK, QUEEN, KING };
		enum direction {UP = -1, DOWN = 1};
		enum id { WHITE, BLACK };
	};
}