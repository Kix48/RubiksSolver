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
	return { static_cast<int>(ARRAYSIZE(this->pieces)), static_cast<int>(ARRAYSIZE(this->pieces[0])) };
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

const char* CubeFace::GetFaceColorName()
{
	switch (this->id)
	{
	case FaceId::UP:
	{
		return "WHITE";
	}

	case FaceId::DOWN:
	{
		return "YELLOW";
	}

	case FaceId::FRONT:
	{
		return "RED";
	}

	case FaceId::BACK:
	{
		return "ORANGE";
	}

	case FaceId::LEFT:
	{
		return "GREEN";
	}

	case FaceId::RIGHT:
	{
		return "BLUE";
	}

	default:
	{
		return "?";
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
	const auto load_response = MessageBoxA(nullptr, "Setup", "Would you like to load from cube config?", MB_YESNO);

	if (load_response == IDYES)
	{
		this->LoadConfig();
	}
	else
	{
		for (auto& face : this->faces)
		{
			for (int row = 0; row < face->GetDimensions().first; row++)
			{
				for (int column = 0; column < face->GetDimensions().second; column++)
				{
					
					printf("Please enter the color for the %s [%d][%d]: ", face->GetFaceColorName(), row, column);

					std::string color = "";

					std::cin >> color;

					if (!strcmp(color.c_str(), "W") || !strcmp(color.c_str(), "w") || !strcmp(color.c_str(), "White") || !strcmp(color.c_str(), "white") || !strcmp(color.c_str(), "WHITE"))
					{
						this->initial_cube.push_back(PieceColor::WHITE);
					}
					else if (!strcmp(color.c_str(), "Y") || !strcmp(color.c_str(), "y") || !strcmp(color.c_str(), "Yellow") || !strcmp(color.c_str(), "yellow") || !strcmp(color.c_str(), "YELLOW"))
					{
						this->initial_cube.push_back(PieceColor::YELLOW);
					}
					else if (!strcmp(color.c_str(), "R") || !strcmp(color.c_str(), "r") || !strcmp(color.c_str(), "Red") || !strcmp(color.c_str(), "red") || !strcmp(color.c_str(), "RED"))
					{
						this->initial_cube.push_back(PieceColor::RED);
					}
					else if (!strcmp(color.c_str(), "O") || !strcmp(color.c_str(), "o") || !strcmp(color.c_str(), "Orange") || !strcmp(color.c_str(), "orange") || !strcmp(color.c_str(), "ORANGE"))
					{
						this->initial_cube.push_back(PieceColor::ORANGE);
					}
					else if (!strcmp(color.c_str(), "G") || !strcmp(color.c_str(), "g") || !strcmp(color.c_str(), "Green") || !strcmp(color.c_str(), "green") || !strcmp(color.c_str(), "GREEN"))
					{
						this->initial_cube.push_back(PieceColor::GREEN);
					}
					else if (!strcmp(color.c_str(), "B") || !strcmp(color.c_str(), "b") || !strcmp(color.c_str(), "Blue") || !strcmp(color.c_str(), "blue") || !strcmp(color.c_str(), "BLUE"))
					{
						this->initial_cube.push_back(PieceColor::BLUE);
					}
				}
			}
		}
	}

	for (int face_id = 0; face_id < 6; face_id++)
	{
		const auto face = this->GetFace(static_cast<FaceId>(face_id));
		for (int row = 0; row < face->GetDimensions().first; row++)
		{
			for (int column = 0; column < face->GetDimensions().second; column++)
			{
				const auto color = this->initial_cube.at((face_id * 9) + (row * 3) + column);

				if (row == 0)
				{
					if (column == 0 || column == 2)
					{
						face->SetPiece(row, column, new CornerPiece(color));
					}
					else
					{
						face->SetPiece(row, column, new EdgePiece(color));
					}
				}
				else if (row == 1)
				{
					if (column == 0 || column == 2)
					{
						face->SetPiece(row, column, new EdgePiece(color));
					}
					else
					{
						face->SetPiece(row, column, new MiddlePiece(color));
					}
				}
				else
				{
					if (column == 0 || column == 2)
					{
						face->SetPiece(row, column, new CornerPiece(color));
					}
					else
					{
						face->SetPiece(row, column, new EdgePiece(color));
					}
				}
			}
		}
	}

	/*const auto u = this->GetFace(FaceId::UP);
	u->SetPiece(0, 0, new CornerPiece(PieceColor::YELLOW));
	u->SetPiece(0, 1, new EdgePiece(PieceColor::WHITE));
	u->SetPiece(0, 2, new CornerPiece(PieceColor::WHITE));
	u->SetPiece(1, 0, new EdgePiece(PieceColor::RED));
	u->SetPiece(1, 1, new MiddlePiece(PieceColor::WHITE));
	u->SetPiece(1, 2, new EdgePiece(PieceColor::BLUE));
	u->SetPiece(2, 0, new CornerPiece(PieceColor::ORANGE));
	u->SetPiece(2, 1, new EdgePiece(PieceColor::BLUE));
	u->SetPiece(2, 2, new CornerPiece(PieceColor::YELLOW));

	const auto d = this->GetFace(FaceId::DOWN);
	d->SetPiece(0, 0, new CornerPiece(PieceColor::GREEN));
	d->SetPiece(0, 1, new EdgePiece(PieceColor::GREEN));
	d->SetPiece(0, 2, new CornerPiece(PieceColor::RED));
	d->SetPiece(1, 0, new EdgePiece(PieceColor::WHITE));
	d->SetPiece(1, 1, new MiddlePiece(PieceColor::YELLOW));
	d->SetPiece(1, 2, new EdgePiece(PieceColor::WHITE));
	d->SetPiece(2, 0, new CornerPiece(PieceColor::GREEN));
	d->SetPiece(2, 1, new EdgePiece(PieceColor::RED));
	d->SetPiece(2, 2, new CornerPiece(PieceColor::WHITE));

	const auto f = this->GetFace(FaceId::FRONT);
	f->SetPiece(0, 0, new CornerPiece(PieceColor::BLUE));
	f->SetPiece(0, 1, new EdgePiece(PieceColor::RED));
	f->SetPiece(0, 2, new CornerPiece(PieceColor::ORANGE));
	f->SetPiece(1, 0, new EdgePiece(PieceColor::WHITE));
	f->SetPiece(1, 1, new MiddlePiece(PieceColor::RED));
	f->SetPiece(1, 2, new EdgePiece(PieceColor::YELLOW));
	f->SetPiece(2, 0, new CornerPiece(PieceColor::YELLOW));
	f->SetPiece(2, 1, new EdgePiece(PieceColor::ORANGE));
	f->SetPiece(2, 2, new CornerPiece(PieceColor::GREEN));

	const auto b = this->GetFace(FaceId::BACK);
	b->SetPiece(0, 0, new CornerPiece(PieceColor::GREEN));
	b->SetPiece(0, 1, new EdgePiece(PieceColor::BLUE));
	b->SetPiece(0, 2, new CornerPiece(PieceColor::BLUE));
	b->SetPiece(1, 0, new EdgePiece(PieceColor::BLUE));
	b->SetPiece(1, 1, new MiddlePiece(PieceColor::ORANGE));
	b->SetPiece(1, 2, new EdgePiece(PieceColor::ORANGE));
	b->SetPiece(2, 0, new CornerPiece(PieceColor::RED));
	b->SetPiece(2, 1, new EdgePiece(PieceColor::YELLOW));
	b->SetPiece(2, 2, new CornerPiece(PieceColor::YELLOW));

	const auto l = this->GetFace(FaceId::LEFT);
	l->SetPiece(0, 0, new CornerPiece(PieceColor::RED));
	l->SetPiece(0, 1, new EdgePiece(PieceColor::GREEN));
	l->SetPiece(0, 2, new CornerPiece(PieceColor::WHITE));
	l->SetPiece(1, 0, new EdgePiece(PieceColor::YELLOW));
	l->SetPiece(1, 1, new MiddlePiece(PieceColor::GREEN));
	l->SetPiece(1, 2, new EdgePiece(PieceColor::GREEN));
	l->SetPiece(2, 0, new CornerPiece(PieceColor::ORANGE));
	l->SetPiece(2, 1, new EdgePiece(PieceColor::RED));
	l->SetPiece(2, 2, new CornerPiece(PieceColor::RED));

	const auto r = this->GetFace(FaceId::RIGHT);
	r->SetPiece(0, 0, new CornerPiece(PieceColor::BLUE));
	r->SetPiece(0, 1, new EdgePiece(PieceColor::ORANGE));
	r->SetPiece(0, 2, new CornerPiece(PieceColor::ORANGE));
	r->SetPiece(1, 0, new EdgePiece(PieceColor::GREEN));
	r->SetPiece(1, 1, new MiddlePiece(PieceColor::BLUE));
	r->SetPiece(1, 2, new EdgePiece(PieceColor::YELLOW));
	r->SetPiece(2, 0, new CornerPiece(PieceColor::WHITE));
	r->SetPiece(2, 1, new EdgePiece(PieceColor::ORANGE));
	r->SetPiece(2, 2, new CornerPiece(PieceColor::BLUE));*/

	const auto save_response = MessageBoxA(nullptr, "Setup", "Would you like to save cube config?", MB_YESNO);

	if (save_response == IDYES)
	{
		this->SaveConfig();
	}

	system("cls");

	const auto u = this->GetFace(FaceId::UP);
	const auto d = this->GetFace(FaceId::DOWN);
	const auto f = this->GetFace(FaceId::FRONT);
	const auto b = this->GetFace(FaceId::BACK);
	const auto l = this->GetFace(FaceId::LEFT);
	const auto r = this->GetFace(FaceId::RIGHT);

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

	CornerPiece* top_l = nullptr;
	EdgePiece* top_m = nullptr;
	CornerPiece* top_r = nullptr;
	CornerPiece* bottom_l = nullptr;
	EdgePiece* bottom_m = nullptr;
	CornerPiece* bottom_r = nullptr;
	CornerPiece* left_l = nullptr;
	EdgePiece* left_m = nullptr;
	CornerPiece* left_r = nullptr;
	CornerPiece* right_l = nullptr;
	EdgePiece* right_m = nullptr;
	CornerPiece* right_r = nullptr;

	switch (id)
	{
		case FaceId::UP:
		{
			top_face = this->GetFace(FaceId::BACK);
			bottom_face = this->GetFace(FaceId::FRONT);
			left_face = this->GetFace(FaceId::LEFT);
			right_face = this->GetFace(FaceId::RIGHT);

			top_l = reinterpret_cast<CornerPiece*>(top_face->GetPiece(0, 0));
			top_m = reinterpret_cast<EdgePiece*>( top_face->GetPiece(0, 1));
			top_r = reinterpret_cast<CornerPiece*>(top_face->GetPiece(0, 2));

			bottom_l = reinterpret_cast<CornerPiece*>(bottom_face->GetPiece(0, 0));
			bottom_m = reinterpret_cast<EdgePiece*>( bottom_face->GetPiece(0, 1));
			bottom_r = reinterpret_cast<CornerPiece*>(bottom_face->GetPiece(0, 2));

			left_l = reinterpret_cast<CornerPiece*>(left_face->GetPiece(0, 0));
			left_m = reinterpret_cast<EdgePiece*>( left_face->GetPiece(0, 1));
			left_r = reinterpret_cast<CornerPiece*>(left_face->GetPiece(0, 2));

			right_l = reinterpret_cast<CornerPiece*>(right_face->GetPiece(0, 0));
			right_m = reinterpret_cast<EdgePiece*>( right_face->GetPiece(0, 1));
			right_r = reinterpret_cast<CornerPiece*>(right_face->GetPiece(0, 2));
			break;
		}

		case FaceId::DOWN:
		{
			top_face = this->GetFace(FaceId::FRONT);
			bottom_face = this->GetFace(FaceId::BACK);
			left_face = this->GetFace(FaceId::LEFT);
			right_face = this->GetFace(FaceId::RIGHT);

			top_l = reinterpret_cast<CornerPiece*>(top_face->GetPiece(2, 2));
			top_m = reinterpret_cast<EdgePiece*>( top_face->GetPiece(2, 1));
			top_r = reinterpret_cast<CornerPiece*>(top_face->GetPiece(2, 0));

			bottom_l = reinterpret_cast<CornerPiece*>(bottom_face->GetPiece(2, 2));
			bottom_m = reinterpret_cast<EdgePiece*>( bottom_face->GetPiece(2, 1));
			bottom_r = reinterpret_cast<CornerPiece*>(bottom_face->GetPiece(2, 0));

			left_l = reinterpret_cast<CornerPiece*>(left_face->GetPiece(2, 2));
			left_m = reinterpret_cast<EdgePiece*>( left_face->GetPiece(2, 1));
			left_r = reinterpret_cast<CornerPiece*>(left_face->GetPiece(2, 0));

			right_l = reinterpret_cast<CornerPiece*>(right_face->GetPiece(2, 2));
			right_m = reinterpret_cast<EdgePiece*>( right_face->GetPiece(2, 1));
			right_r = reinterpret_cast<CornerPiece*>(right_face->GetPiece(2, 0));
			break;
		}

		case FaceId::FRONT:
		{
			top_face = this->GetFace(FaceId::UP);
			bottom_face = this->GetFace(FaceId::DOWN);
			left_face = this->GetFace(FaceId::LEFT);
			right_face = this->GetFace(FaceId::RIGHT);

			top_l = reinterpret_cast<CornerPiece*>(top_face->GetPiece(2, 2));
			top_m = reinterpret_cast<EdgePiece*>( top_face->GetPiece(2, 1));
			top_r = reinterpret_cast<CornerPiece*>(top_face->GetPiece(2, 0));

			bottom_l = reinterpret_cast<CornerPiece*>(bottom_face->GetPiece(0, 0));
			bottom_m = reinterpret_cast<EdgePiece*>( bottom_face->GetPiece(0, 1));
			bottom_r = reinterpret_cast<CornerPiece*>(bottom_face->GetPiece(0, 2));

			left_l = reinterpret_cast<CornerPiece*>(left_face->GetPiece(0, 2));
			left_m = reinterpret_cast<EdgePiece*>( left_face->GetPiece(1, 2));
			left_r = reinterpret_cast<CornerPiece*>(left_face->GetPiece(2, 2));

			right_l = reinterpret_cast<CornerPiece*>(right_face->GetPiece(2, 0));
			right_m = reinterpret_cast<EdgePiece*>( right_face->GetPiece(1, 0));
			right_r = reinterpret_cast<CornerPiece*>(right_face->GetPiece(0, 0));
			break;
		}

		case FaceId::BACK:
		{
			top_face = this->GetFace(FaceId::UP);
			bottom_face = this->GetFace(FaceId::DOWN);
			left_face = this->GetFace(FaceId::RIGHT);
			right_face = this->GetFace(FaceId::LEFT);

			top_l = reinterpret_cast<CornerPiece*>(top_face->GetPiece(0, 0));
			top_m = reinterpret_cast<EdgePiece*>( top_face->GetPiece(0, 1));
			top_r = reinterpret_cast<CornerPiece*>(top_face->GetPiece(0, 2));

			bottom_l = reinterpret_cast<CornerPiece*>(bottom_face->GetPiece(2, 2));
			bottom_m = reinterpret_cast<EdgePiece*>( bottom_face->GetPiece(2, 1));
			bottom_r = reinterpret_cast<CornerPiece*>(bottom_face->GetPiece(2, 0));

			left_l = reinterpret_cast<CornerPiece*>(left_face->GetPiece(0, 2));
			left_m = reinterpret_cast<EdgePiece*>( left_face->GetPiece(1, 2));
			left_r = reinterpret_cast<CornerPiece*>(left_face->GetPiece(2, 2));

			right_l = reinterpret_cast<CornerPiece*>(right_face->GetPiece(2, 0));
			right_m = reinterpret_cast<EdgePiece*>( right_face->GetPiece(1, 0));
			right_r = reinterpret_cast<CornerPiece*>(right_face->GetPiece(0, 0));
			break;
		}

		case FaceId::LEFT:
		{
			top_face = this->GetFace(FaceId::UP);
			bottom_face = this->GetFace(FaceId::DOWN);
			left_face = this->GetFace(FaceId::BACK);
			right_face = this->GetFace(FaceId::FRONT);

			top_l = reinterpret_cast<CornerPiece*>(top_face->GetPiece(2, 0));
			top_m = reinterpret_cast<EdgePiece*>( top_face->GetPiece(1, 0));
			top_r = reinterpret_cast<CornerPiece*>(top_face->GetPiece(0, 0));

			bottom_l = reinterpret_cast<CornerPiece*>(bottom_face->GetPiece(2, 0));
			bottom_m = reinterpret_cast<EdgePiece*>( bottom_face->GetPiece(1, 0));
			bottom_r = reinterpret_cast<CornerPiece*>(bottom_face->GetPiece(0, 0));

			left_l = reinterpret_cast<CornerPiece*>(left_face->GetPiece(0, 2));
			left_m = reinterpret_cast<EdgePiece*>( left_face->GetPiece(1, 2));
			left_r = reinterpret_cast<CornerPiece*>(left_face->GetPiece(2, 2));

			right_l = reinterpret_cast<CornerPiece*>(right_face->GetPiece(2, 0));
			right_m = reinterpret_cast<EdgePiece*>( right_face->GetPiece(1, 0));
			right_r = reinterpret_cast<CornerPiece*>(right_face->GetPiece(0, 0));
			break;
		}

		case FaceId::RIGHT:
		{
			top_face = this->GetFace(FaceId::UP);
			bottom_face = this->GetFace(FaceId::DOWN);
			left_face = this->GetFace(FaceId::FRONT);
			right_face = this->GetFace(FaceId::BACK);

			top_l = reinterpret_cast<CornerPiece*>(top_face->GetPiece(0, 2));
			top_m = reinterpret_cast<EdgePiece*>( top_face->GetPiece(1, 2));
			top_r = reinterpret_cast<CornerPiece*>(top_face->GetPiece(2, 2));

			bottom_l = reinterpret_cast<CornerPiece*>(bottom_face->GetPiece(0, 2));
			bottom_m = reinterpret_cast<EdgePiece*>( bottom_face->GetPiece(1, 2));
			bottom_r = reinterpret_cast<CornerPiece*>(bottom_face->GetPiece(2, 2));

			left_l = reinterpret_cast<CornerPiece*>(left_face->GetPiece(0, 2));
			left_m = reinterpret_cast<EdgePiece*>( left_face->GetPiece(1, 2));
			left_r = reinterpret_cast<CornerPiece*>(left_face->GetPiece(2, 2));

			right_l = reinterpret_cast<CornerPiece*>(right_face->GetPiece(2, 0));
			right_m = reinterpret_cast<EdgePiece*>( right_face->GetPiece(1, 0));
			right_r = reinterpret_cast<CornerPiece*>(right_face->GetPiece(0, 0));
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
		reinterpret_cast<CornerPiece*>(move_face->GetPiece(0, 0))->SetOtherColors(right_r_color, top_l_color);
		move_face->GetPiece(0, 1)->SetColor(move_face_mr);
		reinterpret_cast<EdgePiece*>(move_face->GetPiece(0, 1))->SetOtherColor(right_m_color);
		move_face->GetPiece(0, 2)->SetColor(move_face_br);
		reinterpret_cast<CornerPiece*>(move_face->GetPiece(0, 2))->SetOtherColors(bottom_r_color, right_l_color);
		move_face->GetPiece(1, 0)->SetColor(move_face_tm);
		reinterpret_cast<EdgePiece*>(move_face->GetPiece(1, 0))->SetOtherColor(top_m_color);
		move_face->GetPiece(1, 2)->SetColor(move_face_bm);
		reinterpret_cast<EdgePiece*>(move_face->GetPiece(1, 2))->SetOtherColor(bottom_m_color);
		move_face->GetPiece(2, 0)->SetColor(move_face_tl);
		reinterpret_cast<CornerPiece*>(move_face->GetPiece(2, 0))->SetOtherColors(top_r_color, left_l_color);
		move_face->GetPiece(2, 1)->SetColor(move_face_ml);
		reinterpret_cast<EdgePiece*>(move_face->GetPiece(2, 1))->SetOtherColor(left_m_color);
		move_face->GetPiece(2, 2)->SetColor(move_face_bl);
		reinterpret_cast<CornerPiece*>(move_face->GetPiece(2, 2))->SetOtherColors(left_r_color, bottom_l_color);

		top_l->SetColor(right_l_color);
		top_l->SetOtherColors(move_face_br, bottom_r_color);
		top_m->SetColor(right_m_color);
		top_m->SetOtherColor(move_face_mr);
		top_r->SetColor(right_r_color);
		top_r->SetOtherColors(top_l_color, move_face_tr);

		bottom_l->SetColor(left_l_color);
		bottom_l->SetOtherColors(move_face_tl, top_r_color);
		bottom_m->SetColor(left_m_color);
		bottom_m->SetOtherColor(move_face_ml);
		bottom_r->SetColor(left_r_color);
		bottom_r->SetOtherColors(bottom_l_color, move_face_bl);

		left_l->SetColor(top_l_color);
		left_l->SetOtherColors(move_face_tr, right_r_color);
		left_m->SetColor(top_m_color);
		left_m->SetOtherColor(move_face_tm);
		left_r->SetColor(top_r_color);
		left_r->SetOtherColors(left_l_color, move_face_tl);

		right_l->SetColor(bottom_l_color);
		right_l->SetOtherColors(move_face_bl, left_r_color);
		right_m->SetColor(bottom_m_color);
		right_m->SetOtherColor(move_face_bm);
		right_r->SetColor(bottom_r_color);
		right_r->SetOtherColors(right_l_color, move_face_br);
	}
	else
	{
		move_face->GetPiece(0, 0)->SetColor(move_face_bl);
		reinterpret_cast<CornerPiece*>(move_face->GetPiece(0, 0))->SetOtherColors(left_r_color, bottom_l_color);
		move_face->GetPiece(0, 1)->SetColor(move_face_ml);
		reinterpret_cast<EdgePiece*>(move_face->GetPiece(0, 1))->SetOtherColor(left_m_color);
		move_face->GetPiece(0, 2)->SetColor(move_face_tl);
		reinterpret_cast<CornerPiece*>(move_face->GetPiece(0, 2))->SetOtherColors(top_r_color, left_l_color);
		move_face->GetPiece(1, 0)->SetColor(move_face_bm);
		reinterpret_cast<EdgePiece*>(move_face->GetPiece(1, 0))->SetOtherColor(bottom_m_color);
		move_face->GetPiece(1, 2)->SetColor(move_face_tm);
		reinterpret_cast<EdgePiece*>(move_face->GetPiece(1, 2))->SetOtherColor(top_m_color);
		move_face->GetPiece(2, 0)->SetColor(move_face_br);
		reinterpret_cast<CornerPiece*>(move_face->GetPiece(2, 0))->SetOtherColors(bottom_r_color, right_l_color);
		move_face->GetPiece(2, 1)->SetColor(move_face_mr);
		reinterpret_cast<EdgePiece*>(move_face->GetPiece(2, 1))->SetOtherColor(right_m_color);
		move_face->GetPiece(2, 2)->SetColor(move_face_tr);
		reinterpret_cast<CornerPiece*>(move_face->GetPiece(2, 2))->SetOtherColors(right_r_color, top_l_color);

		top_l->SetColor(left_l_color);
		top_l->SetOtherColors(move_face_tl, top_r_color);
		top_m->SetColor(left_m_color);
		top_m->SetOtherColor(move_face_ml);
		top_r->SetColor(left_r_color);
		top_r->SetOtherColors(bottom_l_color, move_face_bl);

		bottom_l->SetColor(right_l_color);
		bottom_l->SetOtherColors(move_face_br, bottom_r_color);
		bottom_m->SetColor(right_m_color);
		bottom_m->SetOtherColor(move_face_mr);
		bottom_r->SetColor(right_r_color);
		bottom_r->SetOtherColors(top_l_color, move_face_tr);

		left_l->SetColor(bottom_l_color);
		left_l->SetOtherColors(move_face_bl, left_r_color);
		left_m->SetColor(bottom_m_color);
		left_m->SetOtherColor(move_face_bm);
		left_r->SetColor(bottom_r_color);
		left_r->SetOtherColors(right_l_color, move_face_br);

		right_l->SetColor(top_l_color);
		right_l->SetOtherColors(move_face_tr, right_r_color);
		right_m->SetColor(top_m_color);
		right_m->SetOtherColor(move_face_tm);
		right_r->SetColor(top_r_color);
		right_r->SetOtherColors(left_l_color, move_face_tl);
	}

	this->moves.emplace_back(id, prime);
}

void RubiksCube::PrintMoves(const bool reverse)
{
	if (reverse)
	{
		for (int i = static_cast<int>(this->moves.size()) - 1; i >= 0; i--)
		{
			const auto& move = this->moves.at(i);

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

			if (!move.second)
			{
				printf("'");
			}

			printf(" ");
		}
	}
	else
	{
		for (const auto& move : this->moves)
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
	}

	printf("\n\n");
}

bool RubiksCube::SaveConfig()
{
	std::ofstream output;
	output.open("cube_config.txt");

	if (!output.is_open()) return false;

	for (auto& face : this->faces)
	{
		for (int row = 0; row < face->GetDimensions().first; row++)
		{
			for (int column = 0; column < face->GetDimensions().second; column++)
			{
				const auto piece = face->GetPiece(row, column);

				output << piece->GetColorChar() << std::endl;
			}
		}
	}

	output.close();

	return true;
}

bool RubiksCube::LoadConfig()
{
	std::ifstream input;
	input.open("cube_config.txt");

	if (!input.is_open()) return false;

	std::string content = "";
	while (std::getline(input, content))
	{
		printf("%s\n", content);
	}

	return true;
}

bool RubiksCube::CrossSolved()
{
	const auto white_face = this->GetFace(FaceColor::WHITE);
	const auto wr = reinterpret_cast<EdgePiece*>(white_face->GetPiece(2, 1));
	const auto wo = reinterpret_cast<EdgePiece*>(white_face->GetPiece(0, 1));
	const auto wg = reinterpret_cast<EdgePiece*>(white_face->GetPiece(1, 0));
	const auto wb = reinterpret_cast<EdgePiece*>(white_face->GetPiece(1, 2));

	if (wr->GetColor() == PieceColor::WHITE && wr->GetOtherColor() == PieceColor::RED
		&& wo->GetColor() == PieceColor::WHITE && wo->GetOtherColor() == PieceColor::ORANGE
		&& wg->GetColor() == PieceColor::WHITE && wg->GetOtherColor() == PieceColor::GREEN
		&& wb->GetColor() == PieceColor::WHITE && wb->GetOtherColor() == PieceColor::BLUE)
	{
		return true;
	}

	return false;
}

void RubiksCube::SolveCrossEdge(PiecePosition current_position, PiecePosition wanted_position)
{
	if (current_position == wanted_position) return;

	const auto current_piece = reinterpret_cast<EdgePiece*>(this->GetFace(current_position.face)->GetPiece(current_position.row, current_position.column));

	// Save colors because these will change as we move faces of the cube if we were to just use the piece member functions
	const auto current_piece_color = current_piece->GetColor();
	const auto current_piece_other_color = current_piece->GetOtherColor();

	auto current_other_piece_position = this->GetPiecePosition(current_piece_other_color, current_piece_color);

	const auto wanted_piece = reinterpret_cast<EdgePiece*>(this->GetFace(wanted_position.face)->GetPiece(wanted_position.row, wanted_position.column));
	const auto wanted_other_piece_position = this->GetPiecePosition(wanted_piece->GetOtherColor(), wanted_piece->GetColor());

	// Our goal is to get the wanted piece into the DOWN face
	if (current_position.face == FaceId::UP)
	{
		this->Move(current_other_piece_position.face, false);
		this->Move(current_other_piece_position.face, false);
	}
	else if (current_position.face != FaceId::DOWN) 
	{
		if (current_position.column == 0) // Left of face
		{
			// Move into bottom
			this->Move(current_other_piece_position.face, false);

			// Move out of the way
			this->Move(FaceId::DOWN, false);
			this->Move(FaceId::DOWN, false);

			// Revert our move
			this->Move(current_other_piece_position.face, true);
		}
		else if (current_position.column == 2) // Right of face
		{
			// Move into bottom
			this->Move(current_other_piece_position.face, true);

			// Move out of the way
			this->Move(FaceId::DOWN, false);
			this->Move(FaceId::DOWN, false);

			// Revert our move
			this->Move(current_other_piece_position.face, false);
		}
		else // Center of face
		{
			// Move into bottom
			this->Move(current_position.face, false);
			current_other_piece_position = this->GetPiecePosition(current_piece_other_color, current_piece_color);

			const auto move_prime = current_other_piece_position.column == 0;
			this->Move(current_other_piece_position.face, move_prime);

			// Move out of the way
			this->Move(FaceId::DOWN, false);
			this->Move(FaceId::DOWN, false);

			// Revert our moves
			this->Move(current_other_piece_position.face, !move_prime);
			this->Move(current_position.face, true);
		}
	}

	// Re-calc this in-case of any changes as a result of other moves
	current_other_piece_position = this->GetPiecePosition(current_piece_other_color, current_piece_color);

	// Solve for piece that is in DOWN face

	// Move piece under its desired position
	if (current_other_piece_position.face == FaceId::FRONT)
	{
		if (wanted_other_piece_position.face == FaceId::LEFT)
		{
			this->Move(FaceId::DOWN, true);
		}
		else if (wanted_other_piece_position.face == FaceId::RIGHT)
		{
			this->Move(FaceId::DOWN, false);
		}
		else if (wanted_other_piece_position.face == FaceId::BACK)
		{
			this->Move(FaceId::DOWN, false);
			this->Move(FaceId::DOWN, false);
		}
	}
	else if (current_other_piece_position.face == FaceId::BACK)
	{
		if (wanted_other_piece_position.face == FaceId::LEFT)
		{
			this->Move(FaceId::DOWN, false);
		}
		else if (wanted_other_piece_position.face == FaceId::RIGHT)
		{
			this->Move(FaceId::DOWN, true);
		}
		else if (wanted_other_piece_position.face == FaceId::FRONT)
		{
			this->Move(FaceId::DOWN, false);
			this->Move(FaceId::DOWN, false);
		}
	}
	else if (current_other_piece_position.face == FaceId::LEFT)
	{
		if (wanted_other_piece_position.face == FaceId::FRONT)
		{
			this->Move(FaceId::DOWN, false);
		}
		else if (wanted_other_piece_position.face == FaceId::BACK)
		{
		this->Move(FaceId::DOWN, true);
		}
		else if (wanted_other_piece_position.face == FaceId::RIGHT)
		{
		this->Move(FaceId::DOWN, false);
		this->Move(FaceId::DOWN, false);
		}
	}
	else if (current_other_piece_position.face == FaceId::RIGHT)
	{
	if (wanted_other_piece_position.face == FaceId::FRONT)
	{
		this->Move(FaceId::DOWN, true);
	}
	else if (wanted_other_piece_position.face == FaceId::BACK)
	{
		this->Move(FaceId::DOWN, false);
	}
	else if (wanted_other_piece_position.face == FaceId::LEFT)
	{
		this->Move(FaceId::DOWN, false);
		this->Move(FaceId::DOWN, false);
	}
	}

	// Move piece up into desired position
	this->Move(wanted_other_piece_position.face, false);
	this->Move(wanted_other_piece_position.face, false);
}

void RubiksCube::SolveCross()
{
	// Check if already solved
	if (this->CrossSolved()) return;

	const auto o_edge = this->GetPiecePosition(PieceColor::WHITE, PieceColor::ORANGE);

	this->SolveCrossEdge(o_edge, PiecePosition{ true, FaceId::UP, 0, 1 });

	if (this->CrossSolved()) return;

	const auto r_edge = this->GetPiecePosition(PieceColor::WHITE, PieceColor::RED);

	this->SolveCrossEdge(r_edge, PiecePosition{ true, FaceId::UP, 2, 1 });

	if (this->CrossSolved()) return;

	const auto g_edge = this->GetPiecePosition(PieceColor::WHITE, PieceColor::GREEN);

	this->SolveCrossEdge(g_edge, PiecePosition{ true, FaceId::UP, 1, 0 });

	if (this->CrossSolved()) return;

	const auto b_edge = this->GetPiecePosition(PieceColor::WHITE, PieceColor::BLUE);

	this->SolveCrossEdge(b_edge, PiecePosition{ true, FaceId::UP, 1, 2 });

	if (!this->CrossSolved())
	{
		MessageBoxA(nullptr, "Could not solve for cross!", "ERROR", MB_OK);
		std::quick_exit(1);
	}
}

bool RubiksCube::FirstCornersSolved()
{
	const auto white_face = this->GetFace(FaceColor::WHITE);
	const auto wog = reinterpret_cast<CornerPiece*>(white_face->GetPiece(0, 0));
	const auto wbo = reinterpret_cast<CornerPiece*>(white_face->GetPiece(0, 2));
	const auto wgr = reinterpret_cast<CornerPiece*>(white_face->GetPiece(2, 0));
	const auto wrb = reinterpret_cast<CornerPiece*>(white_face->GetPiece(0, 2));

	if (wog->GetColor() == PieceColor::WHITE && wog->GetOtherColorLeft() == PieceColor::ORANGE && wog->GetOtherColorRight() == PieceColor::GREEN
		&& wbo->GetColor() == PieceColor::WHITE && wbo->GetOtherColorLeft() == PieceColor::BLUE && wbo->GetOtherColorRight() == PieceColor::ORANGE
		&& wgr->GetColor() == PieceColor::WHITE && wgr->GetOtherColorLeft() == PieceColor::GREEN && wgr->GetOtherColorRight() == PieceColor::RED
		&& wrb->GetColor() == PieceColor::WHITE && wrb->GetOtherColorLeft() == PieceColor::RED && wrb->GetOtherColorRight() == PieceColor::BLUE)
	{
		return true;
	}

	return false;
}

void RubiksCube::SolveFirstCorner(PiecePosition current_position, PiecePosition wanted_position)
{
	if (current_position == wanted_position) return;

	const auto current_piece = reinterpret_cast<CornerPiece*>(this->GetFace(current_position.face)->GetPiece(current_position.row, current_position.column));
	const auto wanted_piece = reinterpret_cast<CornerPiece*>(this->GetFace(wanted_position.face)->GetPiece(wanted_position.row, wanted_position.column));

	// Save colors because these will change as we move faces of the cube if we were to just use the piece member functions
	const auto current_piece_color = current_piece->GetColor();
	const auto current_piece_other_color_left = current_piece->GetOtherColorLeft();
	const auto current_piece_other_color_right = current_piece->GetOtherColorRight();

	const auto wanted_piece_color = wanted_piece->GetColor();
	const auto wanted_piece_other_color_left = wanted_piece->GetOtherColorLeft();
	const auto wanted_piece_other_color_right = wanted_piece->GetOtherColorRight();

	// Do we need to move down
	if (current_position.face == FaceId::UP)
	{
		const auto right_piece_position = this->GetPiecePosition(current_piece_other_color_right, current_piece_color, current_piece_other_color_left);

		this->Move(right_piece_position.face, true);
		this->Move(FaceId::DOWN, true);
		this->Move(right_piece_position.face, false);
		this->Move(FaceId::DOWN, false);
	}
	else if ((current_position.face == FaceId::FRONT || current_position.face == FaceId::BACK || current_position.face == FaceId::LEFT || current_position.face == FaceId::RIGHT) && current_position.row == 0)
	{
		if (current_position.column == 0)
		{
			this->Move(current_position.face, true);
			this->Move(FaceId::DOWN, true);
			this->Move(current_position.face, false);
			this->Move(FaceId::DOWN, false);
		}
		else if (current_position.column == 2)
		{
			const auto left_piece_position = this->GetPiecePosition(current_piece_other_color_left, current_piece_other_color_right, current_piece_color);

			this->Move(left_piece_position.face, true);
			this->Move(FaceId::DOWN, true);
			this->Move(left_piece_position.face, false);
			this->Move(FaceId::DOWN, false);
		}
	}

	// Move under wanted corner position
	current_position = this->GetPiecePosition(current_piece_color, current_piece_other_color_left, current_piece_other_color_right);

	if (current_position.face == FaceId::DOWN)
	{
		// Left side needs to align with right side of wanted corner position
		const auto left_piece_position = this->GetPiecePosition(current_piece_other_color_left, current_piece_other_color_right, current_piece_color);
		const auto wanted_right_piece_position = this->GetPiecePosition(wanted_piece_other_color_right, wanted_piece_color, wanted_piece_other_color_left);

		if (left_piece_position.face == FaceId::FRONT)
		{
			if (wanted_right_piece_position.face == FaceId::BACK)
			{
				this->Move(FaceId::DOWN, false);
				this->Move(FaceId::DOWN, false);
			}
			else if (wanted_right_piece_position.face == FaceId::LEFT)
			{
				this->Move(FaceId::DOWN, true);
			}
			else if (wanted_right_piece_position.face == FaceId::RIGHT)
			{
				this->Move(FaceId::DOWN, false);
			}
		}
		else if (left_piece_position.face == FaceId::BACK)
		{
			if (wanted_right_piece_position.face == FaceId::FRONT)
			{
				this->Move(FaceId::DOWN, false);
				this->Move(FaceId::DOWN, false);
			}
			else if (wanted_right_piece_position.face == FaceId::LEFT)
			{
				this->Move(FaceId::DOWN, false);
			}
			else if (wanted_right_piece_position.face == FaceId::RIGHT)
			{
				this->Move(FaceId::DOWN, true);
			}
		}
		else if (left_piece_position.face == FaceId::LEFT)
		{
			if (wanted_right_piece_position.face == FaceId::RIGHT)
			{
				this->Move(FaceId::DOWN, false);
				this->Move(FaceId::DOWN, false);
			}
			else if (wanted_right_piece_position.face == FaceId::FRONT)
			{
				this->Move(FaceId::DOWN, false);
			}
			else if (wanted_right_piece_position.face == FaceId::BACK)
			{
				this->Move(FaceId::DOWN, true);
			}
		}
		else if (left_piece_position.face == FaceId::RIGHT)
		{
			if (wanted_right_piece_position.face == FaceId::LEFT)
			{
				this->Move(FaceId::DOWN, false);
				this->Move(FaceId::DOWN, false);
			}
			else if (wanted_right_piece_position.face == FaceId::FRONT)
			{
				this->Move(FaceId::DOWN, true);
			}
			else if (wanted_right_piece_position.face == FaceId::BACK)
			{
				this->Move(FaceId::DOWN, false);
			}
		}
	}
	else if (current_position.column == 0)
	{
		// Current side needs to align with right side of wanted corner position
		const auto wanted_right_piece_position = this->GetPiecePosition(wanted_piece_other_color_right, wanted_piece_color, wanted_piece_other_color_left);

		if (current_position.face == FaceId::FRONT)
		{
			if (wanted_right_piece_position.face == FaceId::BACK)
			{
				this->Move(FaceId::DOWN, false);
				this->Move(FaceId::DOWN, false);
			}
			else if (wanted_right_piece_position.face == FaceId::LEFT)
			{
				this->Move(FaceId::DOWN, true);
			}
			else if (wanted_right_piece_position.face == FaceId::RIGHT)
			{
				this->Move(FaceId::DOWN, false);
			}
		}
		else if (current_position.face == FaceId::BACK)
		{
			if (wanted_right_piece_position.face == FaceId::FRONT)
			{
				this->Move(FaceId::DOWN, false);
				this->Move(FaceId::DOWN, false);
			}
			else if (wanted_right_piece_position.face == FaceId::LEFT)
			{
				this->Move(FaceId::DOWN, false);
			}
			else if (wanted_right_piece_position.face == FaceId::RIGHT)
			{
				this->Move(FaceId::DOWN, true);
			}
		}
		else if (current_position.face == FaceId::LEFT)
		{
			if (wanted_right_piece_position.face == FaceId::RIGHT)
			{
				this->Move(FaceId::DOWN, false);
				this->Move(FaceId::DOWN, false);
			}
			else if (wanted_right_piece_position.face == FaceId::FRONT)
			{
				this->Move(FaceId::DOWN, false);
			}
			else if (wanted_right_piece_position.face == FaceId::BACK)
			{
				this->Move(FaceId::DOWN, true);
			}
		}
		else if (current_position.face == FaceId::RIGHT)
		{
			if (wanted_right_piece_position.face == FaceId::LEFT)
			{
				this->Move(FaceId::DOWN, false);
				this->Move(FaceId::DOWN, false);
			}
			else if (wanted_right_piece_position.face == FaceId::FRONT)
			{
				this->Move(FaceId::DOWN, true);
			}
			else if (wanted_right_piece_position.face == FaceId::BACK)
			{
				this->Move(FaceId::DOWN, false);
			}
		}
	}
	else if (current_position.column == 2)
	{
		// Right side needs to align with right side of wanted corner position
		const auto right_piece_position = this->GetPiecePosition(current_piece_other_color_right, current_piece_color, current_piece_other_color_right);
		const auto wanted_right_piece_position = this->GetPiecePosition(wanted_piece_other_color_right, wanted_piece_color, wanted_piece_other_color_left);

		if (right_piece_position.face == FaceId::FRONT)
		{
			if (wanted_right_piece_position.face == FaceId::BACK)
			{
				this->Move(FaceId::DOWN, false);
				this->Move(FaceId::DOWN, false);
			}
			else if (wanted_right_piece_position.face == FaceId::LEFT)
			{
				this->Move(FaceId::DOWN, true);
			}
			else if (wanted_right_piece_position.face == FaceId::RIGHT)
			{
				this->Move(FaceId::DOWN, false);
			}
		}
		else if (right_piece_position.face == FaceId::BACK)
		{
			if (wanted_right_piece_position.face == FaceId::FRONT)
			{
				this->Move(FaceId::DOWN, false);
				this->Move(FaceId::DOWN, false);
			}
			else if (wanted_right_piece_position.face == FaceId::LEFT)
			{
				this->Move(FaceId::DOWN, false);
			}
			else if (wanted_right_piece_position.face == FaceId::RIGHT)
			{
				this->Move(FaceId::DOWN, true);
			}
		}
		else if (right_piece_position.face == FaceId::LEFT)
		{
			if (wanted_right_piece_position.face == FaceId::RIGHT)
			{
				this->Move(FaceId::DOWN, false);
				this->Move(FaceId::DOWN, false);
			}
			else if (wanted_right_piece_position.face == FaceId::FRONT)
			{
				this->Move(FaceId::DOWN, false);
			}
			else if (wanted_right_piece_position.face == FaceId::BACK)
			{
				this->Move(FaceId::DOWN, true);
			}
		}
		else if (right_piece_position.face == FaceId::RIGHT)
		{
			if (wanted_right_piece_position.face == FaceId::LEFT)
			{
				this->Move(FaceId::DOWN, false);
				this->Move(FaceId::DOWN, false);
			}
			else if (wanted_right_piece_position.face == FaceId::FRONT)
			{
				this->Move(FaceId::DOWN, true);
			}
			else if (wanted_right_piece_position.face == FaceId::BACK)
			{
				this->Move(FaceId::DOWN, false);
			}
		}
	}

	// Move up into final position

	// There are 6 total outcomes from this algorithm
	for (int count = 0; count < 6; count++)
	{
		// We can cast to FaceId because these enums line up
		this->Move(static_cast<FaceId>(current_piece_other_color_right), true);
		this->Move(FaceId::DOWN, true);
		this->Move(static_cast<FaceId>(current_piece_other_color_right), false);
		this->Move(FaceId::DOWN, false);

		// Solved the corner!
		current_position = this->GetPiecePosition(current_piece_color, current_piece_other_color_left, current_piece_other_color_right);
		if (current_position == wanted_position) break;
	}
}

void RubiksCube::SolveFirstCorners()
{
	// Check if already solved
	if (this->FirstCornersSolved()) return;

	const auto og_corner = this->GetPiecePosition(PieceColor::WHITE, PieceColor::ORANGE, PieceColor::GREEN);

	this->SolveFirstCorner(og_corner, PiecePosition{ true, FaceId::UP, 0, 0 });

	if (this->FirstCornersSolved()) return;

	this->PrintMoves(false);

	MessageBoxA(nullptr, "Break", "OG Finished", MB_OK);

	const auto bo_corner = this->GetPiecePosition(PieceColor::WHITE, PieceColor::BLUE, PieceColor::ORANGE);

	this->SolveFirstCorner(bo_corner, PiecePosition{ true, FaceId::UP, 0, 2 });

	if (this->FirstCornersSolved()) return;

	this->PrintMoves(false);

	MessageBoxA(nullptr, "Break", "BO Finished", MB_OK);

	//const auto gr_corner = this->GetPiecePosition(PieceColor::WHITE, PieceColor::GREEN, PieceColor::RED);

	//this->SolveFirstCorner(gr_corner, PiecePosition{ true, FaceId::UP, 2, 0 });

	//if (this->FirstCornersSolved()) return;

	//const auto rb_corner = this->GetPiecePosition(PieceColor::WHITE, PieceColor::RED, PieceColor::BLUE);

	//this->SolveFirstCorner(rb_corner, PiecePosition{ true, FaceId::UP, 2, 2 });

	//if (!this->FirstCornersSolved())
	//{
	//	MessageBoxA(nullptr, "Could not solve for first corners!", "ERROR", MB_OK);
	//	std::quick_exit(1);
	//}
}

void RubiksCube::Solve()
{
	this->SolveCross();

	this->PrintMoves(false);

	MessageBoxA(nullptr, "Step 1", "Cross completed!", MB_OK);

	this->SolveFirstCorners();

	this->PrintMoves(false);

	MessageBoxA(nullptr, "Step 2", "First corners completed!", MB_OK);

	this->PrintMoves(true);
}