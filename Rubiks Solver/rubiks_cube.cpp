#include "rubiks_cube.hpp"

CubePiece::CubePiece()
{
	this->color = PieceColor::WHITE;
}

CubePiece::CubePiece(PieceColor initial_color)
{
	this->color = initial_color;
}

CubePiece::~CubePiece()
{
}

void CubePiece::SetColor(PieceColor new_color)
{
	this->color = new_color;
}

PieceColor CubePiece::GetColor()
{
	return this->color;
}

char CubePiece::GetColorChar()
{
	switch (this->color)
	{
		case PieceColor::WHITE:
		{
			return 'W';
		}

		case PieceColor::YELLOW:
		{
			return 'Y';
		}

		case PieceColor::RED:
		{
			return 'R';
		}

		case PieceColor::BLUE:
		{
			return 'B';
		}

		case PieceColor::ORANGE:
		{
			return 'O';
		}

		case PieceColor::GREEN:
		{
			return 'G';
		}

		default:
		{
			return '?';
		}
	}
}

PieceType CubePiece::GetPieceType()
{
	return PieceType::MIDDLE;
}

MiddlePiece::MiddlePiece()
{
}

MiddlePiece::MiddlePiece(PieceColor initial_color)
{
	this->SetColor(initial_color);
}

PieceType MiddlePiece::GetPieceType()
{
	return PieceType::MIDDLE;
}

MiddlePiece::~MiddlePiece()
{
}

EdgePiece::EdgePiece()
{
	this->other_side_color = PieceColor::WHITE;
}

EdgePiece::EdgePiece(PieceColor initial_color)
{
	this->SetColor(initial_color);
	this->other_side_color = PieceColor::WHITE;
}

EdgePiece::EdgePiece(PieceColor initial_color, PieceColor other_color)
{
	this->SetColor(initial_color);
	this->other_side_color = other_color;
}

EdgePiece::~EdgePiece()
{
}

void EdgePiece::SetOtherColor(PieceColor other_color)
{
	this->other_side_color = other_color;
}

PieceColor EdgePiece::GetOtherColor()
{
	return this->other_side_color;
}

PieceType EdgePiece::GetPieceType()
{
	return PieceType::EDGE;
}

CornerPiece::CornerPiece()
{
	this->left_corner_color = PieceColor::WHITE;
	this->right_corner_color = PieceColor::WHITE;
}

CornerPiece::CornerPiece(PieceColor initial_color)
{
	this->SetColor(initial_color);
	this->left_corner_color = PieceColor::WHITE;
	this->right_corner_color = PieceColor::WHITE;
}

CornerPiece::CornerPiece(PieceColor initial_color, PieceColor left_color, PieceColor right_color)
{
	this->SetColor(initial_color);
	this->left_corner_color = left_color;
	this->right_corner_color = right_color;
}

void CornerPiece::SetOtherColors(PieceColor left, PieceColor right)
{
	this->left_corner_color = left;
	this->right_corner_color = right;
}

PieceColor CornerPiece::GetOtherColorLeft()
{
	return this->left_corner_color;
}

PieceColor CornerPiece::GetOtherColorRight()
{
	return this->right_corner_color;
}

PieceType CornerPiece::GetPieceType()
{
	return PieceType::CORNER;
}

CubeFace::CubeFace()
{
	for (int row = 0; row < ARRAYSIZE(this->pieces); row++)
	{
		for (int column = 0; column < ARRAYSIZE(this->pieces[0]); column++)
		{
			this->pieces[row][column] = new CubePiece();
		}
	}

	this->id = FaceId::UP;
}

CubeFace::CubeFace(FaceId initial_id)
{
	for (int row = 0; row < ARRAYSIZE(this->pieces); row++)
	{
		for (int column = 0; column < ARRAYSIZE(this->pieces[0]); column++)
		{
			this->pieces[row][column] = new CubePiece();
		}
	}

	this->id = initial_id;
}

CubeFace::~CubeFace()
{
}

std::pair<int, int> CubeFace::GetDimensions()
{
	return { ARRAYSIZE(this->pieces), ARRAYSIZE(this->pieces[0]) };
}

void CubeFace::SetFaceId(FaceId new_id)
{
	this->id = new_id;
}

FaceId CubeFace::GetFaceId()
{
	return this->id;
}

char CubeFace::GetFaceChar()
{
	switch (this->id)
	{
		case FaceId::UP:
		{
			return 'U';
		}

		case FaceId::DOWN:
		{
			return 'D';
		}

		case FaceId::FRONT:
		{
			return 'F';
		}

		case FaceId::BACK:
		{
			return 'B';
		}

		case FaceId::LEFT:
		{
			return 'L';
		}

		case FaceId::RIGHT:
		{
			return 'R';
		}

		default:
		{
			return '?';
		}
	}
}

void CubeFace::SetPiece(int row, int column, CubePiece* new_piece)
{
	this->pieces[row][column] = new_piece;
}

CubePiece* CubeFace::GetPiece(int row, int column)
{
	return this->pieces[row][column];
}

RubiksCube::RubiksCube()
{
	for (int face = 0; face < ARRAYSIZE(this->faces); face++)
	{
		this->faces[face] = new CubeFace(static_cast<FaceId>(face));
	}
}

RubiksCube::~RubiksCube()
{
}

void RubiksCube::SetFace(FaceId id, CubeFace* new_face)
{
	this->faces[static_cast<int>(id)] = new_face;
}

CubeFace* RubiksCube::GetFace(FaceId id)
{
	for (auto& face : this->faces)
	{
		if (face->GetFaceId() == id)
		{
			return face;
		}
	}

	return nullptr;
}

CubeFace* RubiksCube::GetFace(FaceColor color)
{
	for (auto& face : this->faces)
	{
		// We can cast here because the FaceColor enum lines up with the FaceId enum
		if (face->GetFaceId() == static_cast<FaceId>(color))
		{
			return face;
		}
	}

	return nullptr;
}

PiecePosition RubiksCube::GetPiecePosition(PieceColor color)
{
	// Based on params, we know we are looking for a middle piece

	for (auto& face : this->faces)
	{
		for (int row = 0; row < face->GetDimensions().first; row++)
		{
			for (int column = 0; column < face->GetDimensions().second; column++)
			{
				// Polymorphism
				const auto piece = reinterpret_cast<MiddlePiece*>(face->GetPiece(row, column));;

				if (piece->GetPieceType() != PieceType::MIDDLE) continue;

				if (piece->GetColor() == color)
				{
					return PiecePosition{true, face->GetFaceId(), row, column};
				}
			}
		}
	}

	return {};
}

PiecePosition RubiksCube::GetPiecePosition(PieceColor primary_color, PieceColor secondary_color)
{
	// Based on params, we know we are looking for an edge piece

	for (auto& face : this->faces)
	{
		for (int row = 0; row < face->GetDimensions().first; row++)
		{
			for (int column = 0; column < face->GetDimensions().second; column++)
			{
				// Polymorphism
				const auto piece = reinterpret_cast<EdgePiece*>(face->GetPiece(row, column));

				if (piece->GetPieceType() != PieceType::EDGE) continue;

				if (piece->GetColor() == primary_color && piece->GetOtherColor() == secondary_color)
				{
					return PiecePosition{ true, face->GetFaceId(), row, column };
				}
			}
		}
	}

	return {};
}

PiecePosition RubiksCube::GetPiecePosition(PieceColor primary_color, PieceColor left_color, PieceColor right_color)
{
	// Based on params, we know we are looking for a corner piece

	for (auto& face : this->faces)
	{
		for (int row = 0; row < face->GetDimensions().first; row++)
		{
			for (int column = 0; column < face->GetDimensions().second; column++)
			{
				// Polymorphism
				const auto piece = reinterpret_cast<CornerPiece*>(face->GetPiece(row, column));

				if (piece->GetPieceType() != PieceType::CORNER) continue;

				if (piece->GetColor() == primary_color && piece->GetOtherColorLeft() == left_color && piece->GetOtherColorRight() == right_color)
				{
					return PiecePosition{ true, face->GetFaceId(), row, column };
				}
			}
		}
	}

	return {};
}

void RubiksCube::PrintCube()
{
	for (auto& face : this->faces)
	{
		printf(" -%c-\n", face->GetFaceChar());

		for (int row = 0; row < face->GetDimensions().first; row++)
		{
			for (int column = 0; column < face->GetDimensions().second; column++)
			{
				const auto piece = face->GetPiece(row, column);

				printf("%c ", piece->GetColorChar());
			}

			printf("\n");
		}

		printf("\n\n");
	}
}

void RubiksCube::SetupCube()
{
	const auto u = this->GetFace(FaceId::UP);
	u->SetPiece(0, 0, new CornerPiece(PieceColor::GREEN));
	u->SetPiece(0, 1, new EdgePiece(PieceColor::ORANGE));
	u->SetPiece(0, 2, new CornerPiece(PieceColor::GREEN));
	u->SetPiece(1, 0, new EdgePiece(PieceColor::YELLOW));
	u->SetPiece(1, 1, new MiddlePiece(PieceColor::WHITE));
	u->SetPiece(1, 2, new EdgePiece(PieceColor::RED));
	u->SetPiece(2, 0, new CornerPiece(PieceColor::ORANGE));
	u->SetPiece(2, 1, new EdgePiece(PieceColor::ORANGE));
	u->SetPiece(2, 2, new CornerPiece(PieceColor::BLUE));

	const auto d = this->GetFace(FaceId::DOWN);
	d->SetPiece(0, 0, new CornerPiece(PieceColor::RED));
	d->SetPiece(0, 1, new EdgePiece(PieceColor::BLUE));
	d->SetPiece(0, 2, new CornerPiece(PieceColor::WHITE));
	d->SetPiece(1, 0, new EdgePiece(PieceColor::YELLOW));
	d->SetPiece(1, 1, new MiddlePiece(PieceColor::YELLOW));
	d->SetPiece(1, 2, new EdgePiece(PieceColor::GREEN));
	d->SetPiece(2, 0, new CornerPiece(PieceColor::ORANGE));
	d->SetPiece(2, 1, new EdgePiece(PieceColor::GREEN));
	d->SetPiece(2, 2, new CornerPiece(PieceColor::GREEN));

	const auto f = this->GetFace(FaceId::FRONT);
	f->SetPiece(0, 0, new CornerPiece(PieceColor::GREEN));
	f->SetPiece(0, 1, new EdgePiece(PieceColor::WHITE));
	f->SetPiece(0, 2, new CornerPiece(PieceColor::RED));
	f->SetPiece(1, 0, new EdgePiece(PieceColor::ORANGE));
	f->SetPiece(1, 1, new MiddlePiece(PieceColor::RED));
	f->SetPiece(1, 2, new EdgePiece(PieceColor::RED));
	f->SetPiece(2, 0, new CornerPiece(PieceColor::BLUE));
	f->SetPiece(2, 1, new EdgePiece(PieceColor::WHITE));
	f->SetPiece(2, 2, new CornerPiece(PieceColor::ORANGE));

	const auto b = this->GetFace(FaceId::BACK);
	b->SetPiece(0, 0, new CornerPiece(PieceColor::ORANGE));
	b->SetPiece(0, 1, new EdgePiece(PieceColor::YELLOW));
	b->SetPiece(0, 2, new CornerPiece(PieceColor::RED));
	b->SetPiece(1, 0, new EdgePiece(PieceColor::GREEN));
	b->SetPiece(1, 1, new MiddlePiece(PieceColor::ORANGE));
	b->SetPiece(1, 2, new EdgePiece(PieceColor::GREEN));
	b->SetPiece(2, 0, new CornerPiece(PieceColor::YELLOW));
	b->SetPiece(2, 1, new EdgePiece(PieceColor::YELLOW));
	b->SetPiece(2, 2, new CornerPiece(PieceColor::YELLOW));

	const auto l = this->GetFace(FaceId::LEFT);
	l->SetPiece(0, 0, new CornerPiece(PieceColor::WHITE));
	l->SetPiece(0, 1, new EdgePiece(PieceColor::RED));
	l->SetPiece(0, 2, new CornerPiece(PieceColor::YELLOW));
	l->SetPiece(1, 0, new EdgePiece(PieceColor::WHITE));
	l->SetPiece(1, 1, new MiddlePiece(PieceColor::GREEN));
	l->SetPiece(1, 2, new EdgePiece(PieceColor::BLUE));
	l->SetPiece(2, 0, new CornerPiece(PieceColor::BLUE));
	l->SetPiece(2, 1, new EdgePiece(PieceColor::BLUE));
	l->SetPiece(2, 2, new CornerPiece(PieceColor::WHITE));

	const auto r = this->GetFace(FaceId::RIGHT);
	r->SetPiece(0, 0, new CornerPiece(PieceColor::YELLOW));
	r->SetPiece(0, 1, new EdgePiece(PieceColor::BLUE));
	r->SetPiece(0, 2, new CornerPiece(PieceColor::WHITE));
	r->SetPiece(1, 0, new EdgePiece(PieceColor::WHITE));
	r->SetPiece(1, 1, new MiddlePiece(PieceColor::BLUE));
	r->SetPiece(1, 2, new EdgePiece(PieceColor::ORANGE));
	r->SetPiece(2, 0, new CornerPiece(PieceColor::BLUE));
	r->SetPiece(2, 1, new EdgePiece(PieceColor::RED));
	r->SetPiece(2, 2, new CornerPiece(PieceColor::RED));

	reinterpret_cast<CornerPiece*>(u->GetPiece(0, 0))->SetOtherColors(b->GetPiece(0, 2)->GetColor(), l->GetPiece(0, 0)->GetColor());
	reinterpret_cast<EdgePiece*>(u->GetPiece(0, 1))->SetOtherColor(b->GetPiece(0, 1)->GetColor());
	reinterpret_cast<CornerPiece*>(u->GetPiece(0, 2))->SetOtherColors(r->GetPiece(0, 2)->GetColor(), b->GetPiece(0, 0)->GetColor());
	reinterpret_cast<EdgePiece*>(u->GetPiece(1, 2))->SetOtherColor(r->GetPiece(0, 1)->GetColor());
	reinterpret_cast<CornerPiece*>(u->GetPiece(2, 0))->SetOtherColors(l->GetPiece(0, 2)->GetColor(), f->GetPiece(0, 0)->GetColor());
	reinterpret_cast<EdgePiece*>(u->GetPiece(2, 1))->SetOtherColor(f->GetPiece(0, 1)->GetColor());
	reinterpret_cast<CornerPiece*>(u->GetPiece(2, 2))->SetOtherColors(f->GetPiece(0, 2)->GetColor(), r->GetPiece(0, 0)->GetColor());
	reinterpret_cast<EdgePiece*>(u->GetPiece(1, 0))->SetOtherColor(l->GetPiece(0, 1)->GetColor());

	reinterpret_cast<CornerPiece*>(d->GetPiece(0, 0))->SetOtherColors(f->GetPiece(2, 0)->GetColor(), l->GetPiece(2, 2)->GetColor());
	reinterpret_cast<EdgePiece*>(d->GetPiece(0, 1))->SetOtherColor(f->GetPiece(2, 1)->GetColor());
	reinterpret_cast<CornerPiece*>(d->GetPiece(0, 2))->SetOtherColors(r->GetPiece(2, 0)->GetColor(), f->GetPiece(2, 2)->GetColor());
	reinterpret_cast<EdgePiece*>(d->GetPiece(1, 2))->SetOtherColor(r->GetPiece(2, 1)->GetColor());
	reinterpret_cast<CornerPiece*>(d->GetPiece(2, 0))->SetOtherColors(l->GetPiece(2, 0)->GetColor(), b->GetPiece(2, 2)->GetColor());
	reinterpret_cast<EdgePiece*>(d->GetPiece(2, 1))->SetOtherColor(b->GetPiece(2, 1)->GetColor());
	reinterpret_cast<CornerPiece*>(d->GetPiece(2, 2))->SetOtherColors(b->GetPiece(2, 0)->GetColor(), r->GetPiece(2, 2)->GetColor());
	reinterpret_cast<EdgePiece*>(d->GetPiece(1, 0))->SetOtherColor(l->GetPiece(2, 1)->GetColor());

	reinterpret_cast<CornerPiece*>(f->GetPiece(0, 0))->SetOtherColors(u->GetPiece(2, 0)->GetColor(), l->GetPiece(0, 2)->GetColor());
	reinterpret_cast<EdgePiece*>(f->GetPiece(0, 1))->SetOtherColor(u->GetPiece(2, 1)->GetColor());
	reinterpret_cast<CornerPiece*>(f->GetPiece(0, 2))->SetOtherColors(r->GetPiece(0, 0)->GetColor(), u->GetPiece(2, 2)->GetColor());
	reinterpret_cast<EdgePiece*>(f->GetPiece(1, 2))->SetOtherColor(r->GetPiece(1, 0)->GetColor());
	reinterpret_cast<CornerPiece*>(f->GetPiece(2, 0))->SetOtherColors(l->GetPiece(2, 2)->GetColor(), d->GetPiece(0, 0)->GetColor());
	reinterpret_cast<EdgePiece*>(f->GetPiece(2, 1))->SetOtherColor(d->GetPiece(0, 1)->GetColor());
	reinterpret_cast<CornerPiece*>(f->GetPiece(2, 2))->SetOtherColors(d->GetPiece(0, 2)->GetColor(), r->GetPiece(0, 0)->GetColor());
	reinterpret_cast<EdgePiece*>(f->GetPiece(1, 0))->SetOtherColor(l->GetPiece(1, 2)->GetColor());

	reinterpret_cast<CornerPiece*>(b->GetPiece(0, 0))->SetOtherColors(u->GetPiece(0, 2)->GetColor(), r->GetPiece(0, 2)->GetColor());
	reinterpret_cast<EdgePiece*>(b->GetPiece(0, 1))->SetOtherColor(u->GetPiece(0, 1)->GetColor());
	reinterpret_cast<CornerPiece*>(b->GetPiece(0, 2))->SetOtherColors(l->GetPiece(0, 0)->GetColor(), u->GetPiece(0, 0)->GetColor());
	reinterpret_cast<EdgePiece*>(b->GetPiece(1, 2))->SetOtherColor(l->GetPiece(1, 0)->GetColor());
	reinterpret_cast<CornerPiece*>(b->GetPiece(2, 0))->SetOtherColors(r->GetPiece(2, 2)->GetColor(), d->GetPiece(2, 2)->GetColor());
	reinterpret_cast<EdgePiece*>(b->GetPiece(2, 1))->SetOtherColor(d->GetPiece(2, 1)->GetColor());
	reinterpret_cast<CornerPiece*>(b->GetPiece(2, 2))->SetOtherColors(d->GetPiece(2, 0)->GetColor(), l->GetPiece(2, 0)->GetColor());
	reinterpret_cast<EdgePiece*>(b->GetPiece(1, 0))->SetOtherColor(r->GetPiece(1, 2)->GetColor());

	reinterpret_cast<CornerPiece*>(l->GetPiece(0, 0))->SetOtherColors(u->GetPiece(0, 0)->GetColor(), b->GetPiece(0, 2)->GetColor());
	reinterpret_cast<EdgePiece*>(l->GetPiece(0, 1))->SetOtherColor(u->GetPiece(1, 0)->GetColor());
	reinterpret_cast<CornerPiece*>(l->GetPiece(0, 2))->SetOtherColors(f->GetPiece(0, 0)->GetColor(), u->GetPiece(2, 0)->GetColor());
	reinterpret_cast<EdgePiece*>(l->GetPiece(1, 2))->SetOtherColor(f->GetPiece(1, 0)->GetColor());
	reinterpret_cast<CornerPiece*>(l->GetPiece(2, 0))->SetOtherColors(b->GetPiece(2, 2)->GetColor(), d->GetPiece(2, 0)->GetColor());
	reinterpret_cast<EdgePiece*>(l->GetPiece(2, 1))->SetOtherColor(d->GetPiece(1, 0)->GetColor());
	reinterpret_cast<CornerPiece*>(l->GetPiece(2, 2))->SetOtherColors(d->GetPiece(0, 0)->GetColor(), f->GetPiece(2, 0)->GetColor());
	reinterpret_cast<EdgePiece*>(l->GetPiece(1, 0))->SetOtherColor(b->GetPiece(1, 2)->GetColor());

	reinterpret_cast<CornerPiece*>(r->GetPiece(0, 0))->SetOtherColors(u->GetPiece(2, 2)->GetColor(), f->GetPiece(0, 2)->GetColor());
	reinterpret_cast<EdgePiece*>(r->GetPiece(0, 1))->SetOtherColor(u->GetPiece(1, 2)->GetColor());
	reinterpret_cast<CornerPiece*>(r->GetPiece(0, 2))->SetOtherColors(b->GetPiece(0, 0)->GetColor(), u->GetPiece(0, 2)->GetColor());
	reinterpret_cast<EdgePiece*>(r->GetPiece(1, 2))->SetOtherColor(b->GetPiece(1, 0)->GetColor());
	reinterpret_cast<CornerPiece*>(r->GetPiece(2, 0))->SetOtherColors(f->GetPiece(2, 2)->GetColor(), d->GetPiece(0, 2)->GetColor());
	reinterpret_cast<EdgePiece*>(r->GetPiece(2, 1))->SetOtherColor(d->GetPiece(1, 2)->GetColor());
	reinterpret_cast<CornerPiece*>(r->GetPiece(2, 2))->SetOtherColors(d->GetPiece(2, 2)->GetColor(), b->GetPiece(2, 0)->GetColor());
	reinterpret_cast<EdgePiece*>(r->GetPiece(1, 0))->SetOtherColor(f->GetPiece(1, 2)->GetColor());
}

bool RubiksCube::ValidCube()
{
	int whites = 0;
	int yellows = 0;
	int reds = 0;
	int blues = 0;
	int oranges = 0;
	int greens = 0;

	for (auto& face : this->faces)
	{
		for (int row = 0; row < face->GetDimensions().first; row++)
		{
			for (int column = 0; column < face->GetDimensions().second; column++)
			{
				const auto piece = face->GetPiece(row, column);

				switch (piece->GetColor())
				{
					case PieceColor::WHITE:
					{
						whites++;
						break;
					}

					case PieceColor::YELLOW:
					{
						yellows++;
						break;
					}

					case PieceColor::RED:
					{
						reds++;
						break;
					}

					case PieceColor::BLUE:
					{
						blues++;
						break;
					}

					case PieceColor::ORANGE:
					{
						oranges++;
						break;
					}

					case PieceColor::GREEN:
					{
						greens++;
						break;
					}
				}
			}
		}
	}

	return whites == 9 && yellows == 9 && reds == 9 && blues == 9 && oranges == 9 && greens == 9;
}

void RubiksCube::Move(FaceId id, bool prime)
{
	CubeFace* move_face = this->GetFace(id);
	CubeFace* top_face = nullptr;
	CubeFace* bottom_face = nullptr;
	CubeFace* left_face = nullptr;
	CubeFace* right_face = nullptr;

	CubePiece* top_l = nullptr;
	CubePiece* top_m = nullptr;
	CubePiece* top_r = nullptr;
	CubePiece* bottom_l = nullptr;
	CubePiece* bottom_m = nullptr;
	CubePiece* bottom_r = nullptr;
	CubePiece* left_l = nullptr;
	CubePiece* left_m = nullptr;
	CubePiece* left_r = nullptr;
	CubePiece* right_l = nullptr;
	CubePiece* right_m = nullptr;
	CubePiece* right_r = nullptr;

	switch (id)
	{
		case FaceId::UP:
		{
			top_face = this->GetFace(FaceId::BACK);
			bottom_face = this->GetFace(FaceId::FRONT);
			left_face = this->GetFace(FaceId::LEFT);
			right_face = this->GetFace(FaceId::RIGHT);

			top_l = top_face->GetPiece(0, 0);
			top_m = top_face->GetPiece(0, 1);
			top_r = top_face->GetPiece(0, 2);

			bottom_l = bottom_face->GetPiece(0, 0);
			bottom_m = bottom_face->GetPiece(0, 1);
			bottom_r = bottom_face->GetPiece(0, 2);

			left_l = left_face->GetPiece(0, 0);
			left_m = left_face->GetPiece(0, 1);
			left_r = left_face->GetPiece(0, 2);

			right_l = right_face->GetPiece(0, 0);
			right_m = right_face->GetPiece(0, 1);
			right_r = right_face->GetPiece(0, 2);
			break;
		}

		case FaceId::DOWN:
		{
			top_face = this->GetFace(FaceId::FRONT);
			bottom_face = this->GetFace(FaceId::BACK);
			left_face = this->GetFace(FaceId::LEFT);
			right_face = this->GetFace(FaceId::RIGHT);

			top_l = top_face->GetPiece(2, 2);
			top_m = top_face->GetPiece(2, 1);
			top_r = top_face->GetPiece(2, 0);

			bottom_l = bottom_face->GetPiece(2, 2);
			bottom_m = bottom_face->GetPiece(2, 1);
			bottom_r = bottom_face->GetPiece(2, 0);

			left_l = left_face->GetPiece(2, 2);
			left_m = left_face->GetPiece(2, 1);
			left_r = left_face->GetPiece(2, 0);

			right_l = right_face->GetPiece(2, 2);
			right_m = right_face->GetPiece(2, 1);
			right_r = right_face->GetPiece(2, 0);
			break;
		}

		case FaceId::FRONT:
		{
			top_face = this->GetFace(FaceId::UP);
			bottom_face = this->GetFace(FaceId::DOWN);
			left_face = this->GetFace(FaceId::LEFT);
			right_face = this->GetFace(FaceId::RIGHT);

			top_l = top_face->GetPiece(2, 2);
			top_m = top_face->GetPiece(2, 1);
			top_r = top_face->GetPiece(2, 0);

			bottom_l = bottom_face->GetPiece(0, 0);
			bottom_m = bottom_face->GetPiece(0, 1);
			bottom_r = bottom_face->GetPiece(0, 2);

			left_l = left_face->GetPiece(0, 2);
			left_m = left_face->GetPiece(1, 2);
			left_r = left_face->GetPiece(2, 2);

			right_l = right_face->GetPiece(2, 0);
			right_m = right_face->GetPiece(1, 0);
			right_r = right_face->GetPiece(0, 0);
			break;
		}

		case FaceId::BACK:
		{
			top_face = this->GetFace(FaceId::UP);
			bottom_face = this->GetFace(FaceId::DOWN);
			left_face = this->GetFace(FaceId::RIGHT);
			right_face = this->GetFace(FaceId::LEFT);

			top_l = top_face->GetPiece(0, 0);
			top_m = top_face->GetPiece(0, 1);
			top_r = top_face->GetPiece(0, 2);

			bottom_l = bottom_face->GetPiece(2, 2);
			bottom_m = bottom_face->GetPiece(2, 1);
			bottom_r = bottom_face->GetPiece(2, 0);

			left_l = left_face->GetPiece(0, 2);
			left_m = left_face->GetPiece(1, 2);
			left_r = left_face->GetPiece(2, 2);

			right_l = right_face->GetPiece(2, 0);
			right_m = right_face->GetPiece(1, 0);
			right_r = right_face->GetPiece(0, 0);
			break;
		}

		case FaceId::LEFT:
		{
			top_face = this->GetFace(FaceId::UP);
			bottom_face = this->GetFace(FaceId::DOWN);
			left_face = this->GetFace(FaceId::BACK);
			right_face = this->GetFace(FaceId::FRONT);

			top_l = top_face->GetPiece(2, 0);
			top_m = top_face->GetPiece(1, 0);
			top_r = top_face->GetPiece(0, 0);

			bottom_l = bottom_face->GetPiece(2, 0);
			bottom_m = bottom_face->GetPiece(1, 0);
			bottom_r = bottom_face->GetPiece(0, 0);

			left_l = left_face->GetPiece(0, 2);
			left_m = left_face->GetPiece(1, 2);
			left_r = left_face->GetPiece(2, 2);

			right_l = right_face->GetPiece(2, 0);
			right_m = right_face->GetPiece(1, 0);
			right_r = right_face->GetPiece(0, 0);
			break;
		}

		case FaceId::RIGHT:
		{
			top_face = this->GetFace(FaceId::UP);
			bottom_face = this->GetFace(FaceId::DOWN);
			left_face = this->GetFace(FaceId::FRONT);
			right_face = this->GetFace(FaceId::BACK);

			top_l = top_face->GetPiece(0, 2);
			top_m = top_face->GetPiece(1, 2);
			top_r = top_face->GetPiece(2, 2);

			bottom_l = bottom_face->GetPiece(0, 2);
			bottom_m = bottom_face->GetPiece(1, 2);
			bottom_r = bottom_face->GetPiece(2, 2);

			left_l = left_face->GetPiece(0, 2);
			left_m = left_face->GetPiece(1, 2);
			left_r = left_face->GetPiece(2, 2);

			right_l = right_face->GetPiece(2, 0);
			right_m = right_face->GetPiece(1, 0);
			right_r = right_face->GetPiece(0, 0);
			break;
		}
	}

	PieceColor move_face_tl = move_face->GetPiece(0, 0)->GetColor();
	PieceColor move_face_tm = move_face->GetPiece(0, 1)->GetColor();
	PieceColor move_face_tr = move_face->GetPiece(0, 2)->GetColor();
	PieceColor move_face_ml = move_face->GetPiece(1, 0)->GetColor();
	PieceColor move_face_mr = move_face->GetPiece(1, 2)->GetColor();
	PieceColor move_face_bl = move_face->GetPiece(2, 0)->GetColor();
	PieceColor move_face_bm = move_face->GetPiece(2, 1)->GetColor();
	PieceColor move_face_br = move_face->GetPiece(2, 2)->GetColor();

	PieceColor top_l_color = top_l->GetColor();
	PieceColor top_m_color = top_m->GetColor();
	PieceColor top_r_color = top_r->GetColor();

	PieceColor bottom_l_color = bottom_l->GetColor();
	PieceColor bottom_m_color = bottom_m->GetColor();
	PieceColor bottom_r_color = bottom_r->GetColor();

	PieceColor left_l_color = left_l->GetColor();
	PieceColor left_m_color = left_m->GetColor();
	PieceColor left_r_color = left_r->GetColor();

	PieceColor right_l_color = right_l->GetColor();
	PieceColor right_m_color = right_m->GetColor();
	PieceColor right_r_color = right_r->GetColor();

	if (prime)
	{
		move_face->GetPiece(0, 0)->SetColor(move_face_tr);
		move_face->GetPiece(0, 1)->SetColor(move_face_mr);
		move_face->GetPiece(0, 2)->SetColor(move_face_br);
		move_face->GetPiece(1, 0)->SetColor(move_face_tm);
		move_face->GetPiece(1, 2)->SetColor(move_face_bm);
		move_face->GetPiece(2, 0)->SetColor(move_face_tl);
		move_face->GetPiece(2, 1)->SetColor(move_face_ml);
		move_face->GetPiece(2, 2)->SetColor(move_face_bl);

		top_l->SetColor(right_l_color);
		top_m->SetColor(right_m_color);
		top_r->SetColor(right_r_color);

		bottom_l->SetColor(left_l_color);
		bottom_m->SetColor(left_m_color);
		bottom_r->SetColor(left_r_color);

		left_l->SetColor(top_l_color);
		left_m->SetColor(top_m_color);
		left_r->SetColor(top_r_color);

		right_l->SetColor(bottom_l_color);
		right_m->SetColor(bottom_m_color);
		right_r->SetColor(bottom_r_color);
	}
	else
	{
		move_face->GetPiece(0, 0)->SetColor(move_face_bl);
		move_face->GetPiece(0, 1)->SetColor(move_face_ml);
		move_face->GetPiece(0, 2)->SetColor(move_face_tl);
		move_face->GetPiece(1, 0)->SetColor(move_face_bm);
		move_face->GetPiece(1, 2)->SetColor(move_face_tm);
		move_face->GetPiece(2, 0)->SetColor(move_face_br);
		move_face->GetPiece(2, 1)->SetColor(move_face_mr);
		move_face->GetPiece(2, 2)->SetColor(move_face_tr);

		top_l->SetColor(left_l_color);
		top_m->SetColor(left_m_color);
		top_r->SetColor(left_r_color);

		bottom_l->SetColor(right_l_color);
		bottom_m->SetColor(right_m_color);
		bottom_r->SetColor(right_r_color);

		left_l->SetColor(bottom_l_color);
		left_m->SetColor(bottom_m_color);
		left_r->SetColor(bottom_r_color);

		right_l->SetColor(top_l_color);
		right_m->SetColor(top_m_color);
		right_r->SetColor(top_r_color);
	}

	this->moves.emplace_back(id, prime);
}

void RubiksCube::PrintMoves()
{
	for (auto& move : this->moves)
	{
		switch (move.first)
		{
			case FaceId::UP:
			{
				printf("U");
				break;
			}

			case FaceId::DOWN:
			{
				printf("D");
				break;
			}

			case FaceId::FRONT:
			{
				printf("F");
				break;
			}

			case FaceId::BACK:
			{
				printf("B");
				break;
			}

			case FaceId::LEFT:
			{
				printf("L");
				break;
			}

			case FaceId::RIGHT:
			{
				printf("R");
				break;
			}
		}

		if (move.second)
		{
			printf("'");
		}

		printf(" ");
	}

	printf("\n\n");
}

bool RubiksCube::CrossSolved()
{
	const auto white_face = this->GetFace(FaceColor::WHITE);
	const auto red_face = this->GetFace(FaceColor::RED);
	const auto blue_face = this->GetFace(FaceColor::BLUE);
	const auto orange_face = this->GetFace(FaceColor::ORANGE);
	const auto green_face = this->GetFace(FaceColor::GREEN);

	if (white_face->GetPiece(0, 1)->GetColor() == PieceColor::WHITE
		&& white_face->GetPiece(1, 0)->GetColor() == PieceColor::WHITE
		&& white_face->GetPiece(1, 2)->GetColor() == PieceColor::WHITE
		&& white_face->GetPiece(2, 1)->GetColor() == PieceColor::WHITE)
	{
		if (red_face->GetPiece(0, 1)->GetColor() == PieceColor::RED
			&& blue_face->GetPiece(0, 1)->GetColor() == PieceColor::BLUE
			&& orange_face->GetPiece(0, 1)->GetColor() == PieceColor::ORANGE
			&& green_face->GetPiece(0, 1)->GetColor() == PieceColor::GREEN)
		{
			return true;
		}
	}

	return false;
}

void RubiksCube::SolveCross()
{
	const auto solve_edge = [this](PiecePosition current_position, PiecePosition wanted_position)
	{
		switch (current_position.face)
		{
			case FaceId::UP:
			{

				break;
			}
		}
	};

	const auto o_edge = this->GetPiecePosition(PieceColor::WHITE, PieceColor::ORANGE);

	solve_edge(o_edge, PiecePosition{ true, FaceId::UP, 0, 1 });
}

void RubiksCube::Solve()
{
	this->SolveCross();

	this->PrintMoves();
}