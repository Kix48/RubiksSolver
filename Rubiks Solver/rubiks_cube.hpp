#pragma once

#include <Windows.h>
#include <iostream>
#include <vector>

enum class PieceColor
{
	WHITE,
	YELLOW,
	RED,
	BLUE,
	ORANGE,
	GREEN
};

enum class PieceType
{
	MIDDLE,
	EDGE,
	CORNER
};

enum class FaceId
{
	UP,
	DOWN,
	FRONT,
	BACK,
	LEFT,
	RIGHT
};

enum class FaceColor
{
	WHITE,
	YELLOW,
	RED,
	ORANGE,
	GREEN,
	BLUE
};

struct PiecePosition
{
	bool valid;
	FaceId face;
	int row;
	int column;
};

class CubePiece
{
	PieceColor color;

public:
	CubePiece();
	CubePiece(PieceColor initial_color);
	~CubePiece();

	void SetColor(PieceColor new_color);
	PieceColor GetColor();
	char GetColorChar();

	virtual PieceType GetPieceType();
};

class MiddlePiece : public CubePiece
{
public:
	MiddlePiece();
	MiddlePiece(PieceColor initial_color);
	~MiddlePiece();

public:
	PieceType GetPieceType();
};

class EdgePiece : public CubePiece
{
	PieceColor other_side_color;

public:
	EdgePiece();
	EdgePiece(PieceColor initial_color);
	EdgePiece(PieceColor initial_color, PieceColor other_color);
	~EdgePiece();

	void SetOtherColor(PieceColor other_color);
	PieceColor GetOtherColor();

	PieceType GetPieceType();
};

class CornerPiece : public CubePiece
{
	PieceColor left_corner_color;
	PieceColor right_corner_color;

public:
	CornerPiece();
	CornerPiece(PieceColor initial_color);
	CornerPiece(PieceColor initial_color, PieceColor left_color, PieceColor right_color);
	~CornerPiece();

	void SetOtherColors(PieceColor left, PieceColor right);
	PieceColor GetOtherColorLeft();
	PieceColor GetOtherColorRight();

	PieceType GetPieceType();
};

class CubeFace
{
	FaceId id;
	CubePiece* pieces[3][3];

public:
	CubeFace();
	CubeFace(FaceId initial_id);
	~CubeFace();

	std::pair<int, int> GetDimensions();
	FaceId GetFaceId();
	void SetFaceId(FaceId new_id);
	char GetFaceChar();
	void SetPiece(int row, int column, CubePiece* new_piece);
	CubePiece* GetPiece(int row, int column);
};

class RubiksCube
{
	CubeFace* faces[6];
	std::vector<std::pair<FaceId, bool>> moves;

public:
	RubiksCube();
	~RubiksCube();

	// Cube functionality
	void SetFace(FaceId id, CubeFace* new_face);
	CubeFace* GetFace(FaceId id);
	CubeFace* GetFace(FaceColor color);
	PiecePosition GetPiecePosition(PieceColor color);
	PiecePosition GetPiecePosition(PieceColor primary_color, PieceColor secondary_color);
	PiecePosition GetPiecePosition(PieceColor primary_color, PieceColor left_color, PieceColor right_color);

	void PrintCube();
	void SetupCube();
	bool ValidCube();
	void Move(FaceId id, bool prime);
	void PrintMoves(const bool reverse);

	// Solving functions
	bool CrossSolved();
	void SolveCrossEdge(PiecePosition current_position, PiecePosition wanted_position);
	void SolveCross();

	void Solve();
};