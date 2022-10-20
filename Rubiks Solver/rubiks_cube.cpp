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
	const auto load_response = MessageBoxA(nullptr, "Would you like to load from cube config?", "Setup", MB_YESNO);

	bool ask_for_save = false;
	if (load_response == IDYES)
	{
		this->LoadConfig();
	}
	else
	{
		ask_for_save = true;
		for (auto& face : this->faces)
		{
			for (int row = 0; row < face->GetDimensions().first; row++)
			{
				for (int column = 0; column < face->GetDimensions().second; column++)
				{
					
					printf("Please enter the color for the %s [%d][%d]: ", face->GetFaceColorName(), row, column);

					std::string color;

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

	if (ask_for_save)
	{
		const auto save_response = MessageBoxA(nullptr, "Would you like to save cube config?", "Setup", MB_YESNO);

		if (save_response == IDYES)
		{
			this->SaveConfig();
		}
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

	std::string color;
	while (input)
	{
		std::getline(input, color);

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

	return true;
}

bool RubiksCube::FirstCrossSolved()
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

void RubiksCube::SolveFirstCrossEdge(PiecePosition current_position, PiecePosition wanted_position)
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

void RubiksCube::SolveFirstCross()
{
	// Check if already solved
	if (this->FirstCrossSolved()) return;

	const auto o_edge = this->GetPiecePosition(PieceColor::WHITE, PieceColor::ORANGE);

	this->SolveFirstCrossEdge(o_edge, PiecePosition{ true, FaceId::UP, 0, 1 });

	if (this->FirstCrossSolved()) return;

	const auto r_edge = this->GetPiecePosition(PieceColor::WHITE, PieceColor::RED);

	this->SolveFirstCrossEdge(r_edge, PiecePosition{ true, FaceId::UP, 2, 1 });

	if (this->FirstCrossSolved()) return;

	const auto g_edge = this->GetPiecePosition(PieceColor::WHITE, PieceColor::GREEN);

	this->SolveFirstCrossEdge(g_edge, PiecePosition{ true, FaceId::UP, 1, 0 });

	if (this->FirstCrossSolved()) return;

	const auto b_edge = this->GetPiecePosition(PieceColor::WHITE, PieceColor::BLUE);

	this->SolveFirstCrossEdge(b_edge, PiecePosition{ true, FaceId::UP, 1, 2 });

	if (!this->FirstCrossSolved())
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
	const auto wrb = reinterpret_cast<CornerPiece*>(white_face->GetPiece(2, 2));

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
		const auto right_piece_position = this->GetPiecePosition(current_piece_other_color_right, current_piece_color, current_piece_other_color_left);
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

	const auto bo_corner = this->GetPiecePosition(PieceColor::WHITE, PieceColor::BLUE, PieceColor::ORANGE);

	this->SolveFirstCorner(bo_corner, PiecePosition{ true, FaceId::UP, 0, 2 });

	if (this->FirstCornersSolved()) return;

	const auto gr_corner = this->GetPiecePosition(PieceColor::WHITE, PieceColor::GREEN, PieceColor::RED);

	this->SolveFirstCorner(gr_corner, PiecePosition{ true, FaceId::UP, 2, 0 });

	if (this->FirstCornersSolved()) return;

	const auto rb_corner = this->GetPiecePosition(PieceColor::WHITE, PieceColor::RED, PieceColor::BLUE);

	this->SolveFirstCorner(rb_corner, PiecePosition{ true, FaceId::UP, 2, 2 });

	if (!this->FirstCornersSolved())
	{
		MessageBoxA(nullptr, "Could not solve for first corners!", "ERROR", MB_OK);
		std::quick_exit(1);
	}
}

bool RubiksCube::MiddleEdgesSolved()
{
	const auto front = this->GetFace(FaceId::FRONT);
	const auto back = this->GetFace(FaceId::BACK);

	const auto fl = reinterpret_cast<EdgePiece*>(front->GetPiece(1, 0));
	const auto fr = reinterpret_cast<EdgePiece*>(front->GetPiece(1, 2));

	const auto bl = reinterpret_cast<EdgePiece*>(back->GetPiece(1, 0));
	const auto br = reinterpret_cast<EdgePiece*>(back->GetPiece(1, 2));

	if (fl->GetColor() == PieceColor::RED && fl->GetOtherColor() == PieceColor::GREEN 
		&& fr->GetColor() == PieceColor::RED && fr->GetOtherColor() == PieceColor::BLUE
		&& bl->GetColor() == PieceColor::ORANGE && bl->GetOtherColor() == PieceColor::BLUE
		&& br->GetColor() == PieceColor::ORANGE && br->GetOtherColor() == PieceColor::GREEN)
	{
		return true;
	}

	return false;
}

void RubiksCube::SolveMiddleEdge(PiecePosition current_position, PiecePosition wanted_position)
{
	// (Left) U' L' U L U F U' F' (Right) U R U' R' U' F' U F

	if (current_position == wanted_position) return;

	const auto current_piece = reinterpret_cast<EdgePiece*>(this->GetFace(current_position.face)->GetPiece(current_position.row, current_position.column));
	const auto current_piece_color = current_piece->GetColor();
	const auto current_piece_other_color = current_piece->GetOtherColor();

	// Check if current position is in a middle edge piece position
	if (current_position.face != FaceId::DOWN && current_position.row == 1)
	{
		const auto current_face = current_position.face;

		const auto other_piece_position = this->GetPiecePosition(current_piece_other_color, current_piece_color);
		const auto other_face = other_piece_position.face;

		const bool use_left = current_position.column == 0;

		this->Move(FaceId::DOWN, true);
		this->Move(use_left ? current_face : other_face, true);
		this->Move(FaceId::DOWN, false);
		this->Move(use_left ? current_face : other_face, false);
		this->Move(FaceId::DOWN, false);
		this->Move(use_left ? other_face : current_face, false);
		this->Move(FaceId::DOWN, true);
		this->Move(use_left ? other_face : current_face, true);
	}

	// Figure out which side is on the bottom and which one is facing outwards to be used for alignment
	auto solve_piece_position = this->GetPiecePosition(current_piece_color, current_piece_other_color);
	auto align_face = static_cast<FaceId>(current_piece_color);

	if (solve_piece_position.face == FaceId::DOWN)
	{
		solve_piece_position = this->GetPiecePosition(current_piece_other_color, current_piece_color);
		align_face = static_cast<FaceId>(current_piece_other_color);
	}

	// Align with correct side
	if (solve_piece_position.face == FaceId::FRONT)
	{
		if (align_face == FaceId::BACK)
		{
			this->Move(FaceId::DOWN, false);
			this->Move(FaceId::DOWN, false);
		}
		else if (align_face == FaceId::LEFT)
		{
			this->Move(FaceId::DOWN, true);
		}
		else if (align_face == FaceId::RIGHT)
		{
			this->Move(FaceId::DOWN, false);
		}
	}
	else if (solve_piece_position.face == FaceId::BACK)
	{
		if (align_face == FaceId::FRONT)
		{
			this->Move(FaceId::DOWN, false);
			this->Move(FaceId::DOWN, false);
		}
		else if (align_face == FaceId::LEFT)
		{
			this->Move(FaceId::DOWN, false);
		}
		else if (align_face == FaceId::RIGHT)
		{
			this->Move(FaceId::DOWN, true);
		}
	}
	else if (solve_piece_position.face == FaceId::LEFT)
	{
		if (align_face == FaceId::RIGHT)
		{
			this->Move(FaceId::DOWN, false);
			this->Move(FaceId::DOWN, false);
		}
		else if (align_face == FaceId::FRONT)
		{
			this->Move(FaceId::DOWN, false);
		}
		else if (align_face == FaceId::BACK)
		{
			this->Move(FaceId::DOWN, true);
		}
	}
	else if (solve_piece_position.face == FaceId::RIGHT)
	{
		if (align_face == FaceId::LEFT)
		{
			this->Move(FaceId::DOWN, false);
			this->Move(FaceId::DOWN, false);
		}
		else if (align_face == FaceId::FRONT)
		{
			this->Move(FaceId::DOWN, true);
		}
		else if (align_face == FaceId::BACK)
		{
			this->Move(FaceId::DOWN, false);
		}
	}

	bool invert_algorithm = false;

	auto wanted_piece = reinterpret_cast<EdgePiece*>(this->GetFace(wanted_position.face)->GetPiece(wanted_position.row, wanted_position.column));
	auto wanted_piece_color = wanted_piece->GetColor();
	auto wanted_piece_other_color = wanted_piece->GetOtherColor();

	auto wanted_other_piece_position = this->GetPiecePosition(wanted_piece_other_color, wanted_piece_color);
	auto move_face = wanted_other_piece_position.face;

	// We know based on if the align face has changed from the og wanted position face
	if (align_face != wanted_position.face)
	{
		if (wanted_position.column == 2)
		{
			invert_algorithm = true;
		}

		wanted_piece = reinterpret_cast<EdgePiece*>(this->GetFace(align_face)->GetPiece(1, wanted_position.column == 0 ? 2 : 0));
		wanted_piece_color = wanted_piece->GetColor();
		wanted_piece_other_color = wanted_piece->GetOtherColor();

		wanted_other_piece_position = this->GetPiecePosition(wanted_piece_other_color, wanted_piece_color);
		move_face = wanted_other_piece_position.face;
	}
	else
	{
		if (wanted_position.column == 0)
		{
			invert_algorithm = true;
		}
	}

	this->Move(FaceId::DOWN, !invert_algorithm);
	this->Move(move_face, !invert_algorithm);
	this->Move(FaceId::DOWN, invert_algorithm);
	this->Move(move_face, invert_algorithm);
	this->Move(FaceId::DOWN, invert_algorithm);
	this->Move(align_face, invert_algorithm);
	this->Move(FaceId::DOWN, !invert_algorithm);
	this->Move(align_face, !invert_algorithm);
}

void RubiksCube::SolveMiddleEdges()
{
	// Check if already solved
	if (this->MiddleEdgesSolved()) return;

	const auto og_edge = this->GetPiecePosition(PieceColor::ORANGE, PieceColor::GREEN);

	this->SolveMiddleEdge(og_edge, PiecePosition{ true, FaceId::BACK, 1, 2 });

	if (this->MiddleEdgesSolved()) return;

	const auto ob_edge = this->GetPiecePosition(PieceColor::ORANGE, PieceColor::BLUE);

	this->SolveMiddleEdge(ob_edge, PiecePosition{ true, FaceId::BACK, 1, 0 });

	if (this->MiddleEdgesSolved()) return;

	const auto rg_edge = this->GetPiecePosition(PieceColor::RED, PieceColor::GREEN);

	this->SolveMiddleEdge(rg_edge, PiecePosition{ true, FaceId::FRONT, 1, 0 });

	if (this->MiddleEdgesSolved()) return;

	const auto rb_edge = this->GetPiecePosition(PieceColor::RED, PieceColor::BLUE);

	this->SolveMiddleEdge(rb_edge, PiecePosition{ true, FaceId::FRONT, 1, 2 });

	if (!this->MiddleEdgesSolved())
	{
		MessageBoxA(nullptr, "Could not solve for middle edges!", "ERROR", MB_OK);
		std::quick_exit(1);
	}
}

bool RubiksCube::LastCrossSolved()
{
	const auto down_face = this->GetFace(FaceId::DOWN);

	const auto top = reinterpret_cast<EdgePiece*>(down_face->GetPiece(0, 1));
	const auto bottom = reinterpret_cast<EdgePiece*>(down_face->GetPiece(2, 1));
	const auto left = reinterpret_cast<EdgePiece*>(down_face->GetPiece(1, 0));
	const auto right = reinterpret_cast<EdgePiece*>(down_face->GetPiece(1, 2));

	if (top->GetColor() == PieceColor::YELLOW && bottom->GetColor() == PieceColor::YELLOW
		&& left->GetColor() == PieceColor::YELLOW && right->GetColor() == PieceColor::YELLOW)
	{
		return true;
	}

	return false;
}

void RubiksCube::SolveLastCross()
{
	// F R U R' U' F'

	if (this->LastCrossSolved()) return;

	for (int counter = 0; counter < 8; counter++)
	{
		// Figure out what pattern we have

		const auto down_face = this->GetFace(FaceId::DOWN);

		const auto top = reinterpret_cast<EdgePiece*>(down_face->GetPiece(0, 1));
		const auto bottom = reinterpret_cast<EdgePiece*>(down_face->GetPiece(2, 1));
		const auto left = reinterpret_cast<EdgePiece*>(down_face->GetPiece(1, 0));
		const auto right = reinterpret_cast<EdgePiece*>(down_face->GetPiece(1, 2));

		if (top->GetColor() == PieceColor::YELLOW && left->GetColor() == PieceColor::YELLOW)
		{
			this->Move(FaceId::DOWN, false);
			this->Move(FaceId::DOWN, false);
		}
		else if (top->GetColor() == PieceColor::YELLOW && right->GetColor() == PieceColor::YELLOW)
		{
			this->Move(FaceId::DOWN, false);
		}
		else if (bottom->GetColor() == PieceColor::YELLOW && left->GetColor() == PieceColor::YELLOW)
		{
			this->Move(FaceId::DOWN, true);
		}
		else if (top->GetColor() == PieceColor::YELLOW && bottom->GetColor() == PieceColor::YELLOW)
		{
			this->Move(FaceId::DOWN, false);
		}

		this->Move(FaceId::FRONT, false);
		this->Move(FaceId::LEFT, false);
		this->Move(FaceId::DOWN, false);
		this->Move(FaceId::LEFT, true);
		this->Move(FaceId::DOWN, true);
		this->Move(FaceId::FRONT, true);

		if (this->LastCrossSolved()) break;
	}

	if (!this->LastCrossSolved())
	{
		MessageBoxA(nullptr, "Could not solve for last cross!", "ERROR", MB_OK);
		std::quick_exit(1);
	}
}

bool RubiksCube::LastEdgesSolved()
{
	const auto front_face = this->GetFace(FaceId::FRONT);
	const auto back_face = this->GetFace(FaceId::BACK);
	const auto left_face = this->GetFace(FaceId::LEFT);
	const auto right_face = this->GetFace(FaceId::RIGHT);

	const auto front_piece = reinterpret_cast<EdgePiece*>(front_face->GetPiece(2, 1));
	const auto back_piece = reinterpret_cast<EdgePiece*>(back_face->GetPiece(2, 1));
	const auto left_piece = reinterpret_cast<EdgePiece*>(left_face->GetPiece(2, 1));
	const auto right_piece = reinterpret_cast<EdgePiece*>(right_face->GetPiece(2, 1));

	if (front_piece->GetColor() == PieceColor::RED && back_piece->GetColor() == PieceColor::ORANGE
		&& left_piece->GetColor() == PieceColor::GREEN && right_piece->GetColor() == PieceColor::BLUE)
	{
		return true;
	}

	return false;
}

void RubiksCube::SolveLastEdges()
{
	// R U R' U R U2 R' U

	if (this->LastEdgesSolved()) return;

	const auto yr = this->GetPiecePosition(PieceColor::YELLOW, PieceColor::RED);
	const auto yo = this->GetPiecePosition(PieceColor::YELLOW, PieceColor::ORANGE);
	const auto yg = this->GetPiecePosition(PieceColor::YELLOW, PieceColor::GREEN);
	const auto yb = this->GetPiecePosition(PieceColor::YELLOW, PieceColor::BLUE);

	// Quickly check to make sure if all the edges are in the correct places but not turned to their spots
	// We can do this by checking if opposite edges are correct since at this point either all 4 are correct or 2 are correct but next to each other

	// Don't need to check if it's red/orange combo because then it would be solved and we wouldn't be here
	if ((yo.row == 0 && yr.row == 2)
		|| (yg.row == 0 && yb.row == 2)
		|| (yb.row == 0 && yg.row == 2))
	{
		// Just need to turn face until solved

		// Using a for-loop in-case any logic is wrong above and we prevent an infinite loop
		for (int counter = 0; counter < 4; counter++)
		{
			this->Move(FaceId::DOWN, false);

			if (this->LastEdgesSolved()) return;
		}
	}

	// Find which edges are next to each other
	const bool rg_together = ((yr.row == 0 && yg.column == 0) || (yr.column == 2 && yg.row == 0) || (yr.row == 2 && yg.column == 2) || (yr.column == 0 && yg.row == 2));
	const bool br_together = ((yb.row == 0 && yr.column == 0) || (yb.column == 2 && yr.row == 0) || (yb.row == 2 && yr.column == 2) || (yb.column == 0 && yr.row == 2));
	const bool ob_together = ((yo.row == 0 && yb.column == 0) || (yo.column == 2 && yb.row == 0) || (yo.row == 2 && yb.column == 2) || (yo.column == 0 && yb.row == 2));
	const bool go_together = ((yg.row == 0 && yo.column == 0) || (yg.column == 2 && yo.row == 0) || (yg.row == 2 && yo.column == 2) || (yg.column == 0 && yo.row == 2));

	auto move_position = PiecePosition{};

	if (rg_together) move_position = yr;
	else if (br_together) move_position = yb;
	else if (ob_together) move_position = yo;
	else if (go_together) move_position = yg;


	if (move_position.valid)
	{
		if (move_position.row == 2)
		{
			this->Move(FaceId::DOWN, false);
		}
		else if (move_position.column == 2)
		{
			this->Move(FaceId::DOWN, false);
			this->Move(FaceId::DOWN, false);
		}
		else if (move_position.row == 0)
		{
			this->Move(FaceId::DOWN, true);
		}
	}

	this->Move(FaceId::LEFT, false);
	this->Move(FaceId::DOWN, false);
	this->Move(FaceId::LEFT, true);
	this->Move(FaceId::DOWN, false);
	this->Move(FaceId::LEFT, false);
	this->Move(FaceId::DOWN, false);
	this->Move(FaceId::DOWN, false);
	this->Move(FaceId::LEFT, true);
	this->Move(FaceId::DOWN, false);

	if (this->LastEdgesSolved()) return;

	// Try to turn until it is solved
	for (int turns = 0; turns < 3; turns++)
	{
		this->Move(FaceId::DOWN, false);

		if (this->LastEdgesSolved()) return;
	}

	if (!this->LastEdgesSolved())
	{
		MessageBoxA(nullptr, "Could not solve for last edges!", "ERROR", MB_OK);
		std::quick_exit(1);
	}
}

bool RubiksCube::LastCornersPositioned()
{
	const auto yrg = this->GetPiecePosition(PieceColor::YELLOW, PieceColor::RED, PieceColor::GREEN);
	const auto ybr = this->GetPiecePosition(PieceColor::YELLOW, PieceColor::BLUE, PieceColor::RED);
	const auto yob = this->GetPiecePosition(PieceColor::YELLOW, PieceColor::ORANGE, PieceColor::BLUE);
	const auto ygo = this->GetPiecePosition(PieceColor::YELLOW, PieceColor::GREEN, PieceColor::ORANGE);

	const bool yrg_positioned = ((yrg.face == FaceId::DOWN && yrg.column == 0 && yrg.row == 0) || (yrg.face == FaceId::FRONT && yrg.column == 0) || (yrg.face == FaceId::LEFT && yrg.column == 2));
	const bool ybr_positioned = ((ybr.face == FaceId::DOWN && ybr.column == 2 && ybr.row == 0) || (ybr.face == FaceId::FRONT && ybr.column == 2) || (ybr.face == FaceId::RIGHT && ybr.column == 0));
	const bool yob_positioned = ((yob.face == FaceId::DOWN && yob.column == 2 && yob.row == 2) || (yob.face == FaceId::BACK && yob.column == 0) || (yob.face == FaceId::RIGHT && yob.column == 2));
	const bool ygo_positioned = ((ygo.face == FaceId::DOWN && ygo.column == 0 && ygo.row == 2) || (ygo.face == FaceId::BACK && ygo.column == 2) || (ygo.face == FaceId::LEFT && ygo.column == 0));

	return (yrg_positioned && ybr_positioned && yob_positioned && ygo_positioned);
}

void RubiksCube::PositionLastCorners()
{
	// U R U' L' U R' U' L

	if (this->LastCornersPositioned()) return;

	for (int counter = 0; counter < 8; counter++)
	{
		const auto ybr = this->GetPiecePosition(PieceColor::YELLOW, PieceColor::BLUE, PieceColor::RED);
		const auto yob = this->GetPiecePosition(PieceColor::YELLOW, PieceColor::ORANGE, PieceColor::BLUE);
		const auto ygo = this->GetPiecePosition(PieceColor::YELLOW, PieceColor::GREEN, PieceColor::ORANGE);

		const bool ybr_positioned = ((ybr.face == FaceId::DOWN && ybr.column == 2 && ybr.row == 0) || (ybr.face == FaceId::FRONT && ybr.column == 2) || (ybr.face == FaceId::RIGHT && ybr.column == 0));
		const bool yob_positioned = ((yob.face == FaceId::DOWN && yob.column == 2 && yob.row == 2) || (yob.face == FaceId::BACK && yob.column == 0) || (yob.face == FaceId::RIGHT && yob.column == 2));
		const bool ygo_positioned = ((ygo.face == FaceId::DOWN && ygo.column == 0 && ygo.row == 2) || (ygo.face == FaceId::BACK && ygo.column == 2) || (ygo.face == FaceId::LEFT && ygo.column == 0));

		if (ybr_positioned)
		{
			this->Move(FaceId::DOWN, true);
		}
		else if (yob_positioned)
		{
			this->Move(FaceId::DOWN, false);
			this->Move(FaceId::DOWN, false);
		}
		else if (ygo_positioned)
		{
			this->Move(FaceId::DOWN, false);
		}

		this->Move(FaceId::DOWN, false);
		this->Move(FaceId::LEFT, false);
		this->Move(FaceId::DOWN, true);
		this->Move(FaceId::RIGHT, true);
		this->Move(FaceId::DOWN, false);
		this->Move(FaceId::LEFT, true);
		this->Move(FaceId::DOWN, true);
		this->Move(FaceId::RIGHT, false);

		if (ybr_positioned)
		{
			this->Move(FaceId::DOWN, false);
		}
		else if (yob_positioned)
		{
			this->Move(FaceId::DOWN, true);
			this->Move(FaceId::DOWN, true);
		}
		else if (ygo_positioned)
		{
			this->Move(FaceId::DOWN, true);
		}

		if (this->LastCornersPositioned()) break;
	}

	if (!this->LastCornersPositioned())
	{
		MessageBoxA(nullptr, "Could not position last corners!", "ERROR", MB_OK);
		std::quick_exit(1);
	}
}

bool RubiksCube::LastCornersSolved()
{
	// Redundant because we could just check if the cube is solved
	// However, this is faster because we are checking less pieces

	const auto yrg = this->GetPiecePosition(PieceColor::YELLOW, PieceColor::RED, PieceColor::GREEN);
	const auto ybr = this->GetPiecePosition(PieceColor::YELLOW, PieceColor::BLUE, PieceColor::RED);
	const auto yob = this->GetPiecePosition(PieceColor::YELLOW, PieceColor::ORANGE, PieceColor::BLUE);
	const auto ygo = this->GetPiecePosition(PieceColor::YELLOW, PieceColor::GREEN, PieceColor::ORANGE);

	const bool yrg_solved = (yrg.face == FaceId::DOWN && yrg.column == 0 && yrg.row == 0);
	const bool ybr_solved = (ybr.face == FaceId::DOWN && ybr.column == 2 && ybr.row == 0);
	const bool yob_solved = (yob.face == FaceId::DOWN && yob.column == 2 && yob.row == 2);
	const bool ygo_solved = (ygo.face == FaceId::DOWN && ygo.column == 0 && ygo.row == 2);

	return yrg_solved && ybr_solved && yob_solved && ygo_solved;
}

void RubiksCube::SolveLastCorners()
{
	if (this->LastCornersSolved()) return;

	for (int turns = 0; turns < 4; turns++)
	{
		for (int counter = 0; counter < 8; counter++)
		{
			const auto current_piece = reinterpret_cast<CornerPiece*>(this->GetFace(FaceId::DOWN)->GetPiece(0, 0));

			if (current_piece->GetColor() == PieceColor::YELLOW) break;

			this->Move(FaceId::LEFT, true);
			this->Move(FaceId::UP, true);
			this->Move(FaceId::LEFT, false);
			this->Move(FaceId::UP, false);
		}

		this->Move(FaceId::DOWN, false);
	}

	if (!this->LastCornersSolved())
	{
		MessageBoxA(nullptr, "Could not solve for last corners!", "ERROR", MB_OK);
		std::quick_exit(1);
	}
}

void RubiksCube::Solve()
{
	this->SolveFirstCross();

	//this->PrintMoves(false);

	//MessageBoxA(nullptr, "Cross completed!", "Step 1", MB_OK);

	this->SolveFirstCorners();

	//this->PrintMoves(false);

	//MessageBoxA(nullptr, "First corners completed!", "Step 2", MB_OK);

	this->SolveMiddleEdges();

	//this->PrintMoves(false);

	//MessageBoxA(nullptr, "Middle edges completed!", "Step 3", MB_OK);

	this->SolveLastCross();

	//this->PrintMoves(false);

	//MessageBoxA(nullptr, "Top cross completed!", "Step 4", MB_OK);

	this->SolveLastEdges();

	//this->PrintMoves(false);

	//MessageBoxA(nullptr, "Last edges completed!", "Step 5", MB_OK);

	this->PositionLastCorners();

	//this->PrintMoves(false);

	//MessageBoxA(nullptr, "Last corners positioned!", "Step 6", MB_OK);

	this->SolveLastCorners();

	//this->PrintMoves(false);

	//MessageBoxA(nullptr, "Last corners completed!", "Step 7", MB_OK);

	this->PrintMoves(false);
	//this->PrintMoves(true);

	MessageBoxA(nullptr, "Cube Solved!!!", "Done", MB_OK);
} 