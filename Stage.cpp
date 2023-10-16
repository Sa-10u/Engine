#include "Stage.h"
#include "Engine/Model.h"
#include "resource.h"
#include "Engine/DInput.h"
#include <sstream>
#include <algorithm>

Stage::Stage(GOBJ* parent):GOBJ(parent,"Stage"),fstr("Map.map"),buffersize_(20)
{
	cmds = new Command[buffersize_];
	IND_cmd = 0;
	back_ = 0;
	fore_ = 0;
}

struct HitBox
{
	int dir;
	XMINT3 blkpos;
	BLOCKTYPE type;
};

void Stage::Initialize()
{

	string base_ = "assets/";
	string names_[static_cast<int>(BLOCKTYPE::AMMOUNT)] =
	{
		"BoxDefault.fbx",
		"BoxBrick.fbx",
		"BoxGrass.fbx",
		"BoxSand.fbx",
		"BoxWater.fbx"
	};

	for (int i = 0; i < sizeof(names_) / sizeof(names_[0]); i++) {

		model_[i] = Model::Load(base_ + names_[i]);
		assert(model_[i] != -1);
	}

	for (int x = 0; x < XSIZE; x++) {
		for (int z = 0; z < ZSIZE; z++) {
			
			Table[x* XSIZE + z].blk = BLOCKTYPE((x + z) % 5);
			Table[x * XSIZE + z].height = 0 ;
		}
	}
	
	PutCommand();
}

void Stage::Update()
{
	static bool FLG = true;

	if (Input::IsMouseButton(0))
	{
		float w = static_cast<float>(D3D::Width_ / 2);
		float h = static_cast<float>(D3D::Height_ / 2);

		XMMATRIX vp =
		{
			w,	0,	0,	0,
			0, -h,	0,	0,
			0,	0,	1,	0,
			w,	h,	0,	1,
		};

		XMMATRIX inv_vp = XMMatrixInverse(nullptr, vp);
		XMMATRIX inv_proj = XMMatrixInverse(nullptr, CAM::projMat_);
		XMMATRIX inv_view = XMMatrixInverse(nullptr, CAM::viewMat_);

		XMFLOAT3 mousePosFront = {};
		{

			mousePosFront.x = Input::GetMousePosition().x;
			mousePosFront.y = Input::GetMousePosition().y;
			mousePosFront.z = 0.0f;
		}

		XMMATRIX matrix = inv_vp * inv_proj * inv_view;

		XMVECTOR Front = XMLoadFloat3(&mousePosFront);
		Front = XMVector3TransformCoord(Front, (matrix));


		XMFLOAT3 mousePosBack = {};
		{
			mousePosBack.z = 1.0f;

			mousePosBack.x = Input::GetMousePosition().x;
			mousePosBack.y = Input::GetMousePosition().y;
		}

		XMVECTOR Back = XMLoadFloat3(&mousePosBack);
		Back = XMVector3TransformCoord(Back, (matrix));


		

		HitBox rank;
		rank.dir = 9999.9f;
		rank.blkpos.x = -1;
		rank.blkpos.y = -1;
		rank.blkpos.z = -1;

		for (int x = 0; x < XSIZE; x++) {
			for (int z = 0; z < ZSIZE; z++) {
				for (int y = 0; y <= Table[XSIZE * x + z].height; y++) {

					Trans trans;

					trans.pos.x = x;
					trans.pos.z = z;
					trans.pos.y = y;

					RAYCAST_DATA ray = {};
					XMStoreFloat4(&ray.begin, Front);
					XMStoreFloat4(&ray.end, Back - Front);

					Model::SetTrans(&model_[0], &trans);
					Model::RayCast(&model_[0], &ray);

					if (ray.isHit && rank.dir >= ray.distance)
					{
						rank.blkpos.x = x;
						rank.blkpos.z = z;
						rank.blkpos.y = y;
						rank.type = Table[XSIZE * x + z].blk;

						rank.dir = ray.distance;
					}
				}
			}
		}

		if (rank.blkpos.x >= 0 && rank.blkpos.z >= 0 && (rank.blkpos.y >=0 && rank.blkpos.y < 5))
		{
			switch (mode_)
			{
			case MODE::UP:		Table[XSIZE * rank.blkpos.x + rank.blkpos.z].height < 5 && FLG ? Table[XSIZE * rank.blkpos.x + rank.blkpos.z].height++ : NULL; FLG = false; return;
			case MODE::DOWN:	Table[XSIZE * rank.blkpos.x + rank.blkpos.z].height > 0 && FLG ? Table[XSIZE * rank.blkpos.x + rank.blkpos.z].height-- : NULL; FLG = false; return;
			case MODE::CHANGE:	Table[XSIZE * rank.blkpos.x + rank.blkpos.z].blk = select_; return;
			default: return;
			}
			
		}
	}

	if (Input::IsMouseButtonUp(0))
	{
		FLG = true;
		PutCommand();
	}

	{
		if (Input::IsKeyDown(DIK_A) && !Input::IsKey(DIK_LCONTROL))
		{
			for (int x = 0; x < XSIZE; x++) {
				for (int z = 0; z < ZSIZE; z++) {

					if (Table[XSIZE * x + z].height < 5)	Table[x * XSIZE + z].height++;

				}
			}

			PutCommand();
		}

		if (Input::IsKeyDown(DIK_Z) && !Input::IsKey(DIK_LCONTROL))
		{
			for (int x = 0; x < XSIZE; x++) {
				for (int z = 0; z < ZSIZE; z++) {

					if (Table[XSIZE * x + z].height > 0)	Table[x * XSIZE + z].height--;

				}
			}

			PutCommand();
		}
	}

	{
		if (Input::IsKeyDown(DIK_A) && Input::IsKey(DIK_LSHIFT))
		{
			for (int x = 0; x < XSIZE; x++) {
				for (int z = 0; z < ZSIZE; z++) {

					if (Table[XSIZE * x + z].height < 5)	Table[x * XSIZE + z].height = 5;

				}
			}

			PutCommand();
		}

		if (Input::IsKeyDown(DIK_Z) && Input::IsKey(DIK_LSHIFT))
		{
			for (int x = 0; x < XSIZE; x++) {
				for (int z = 0; z < ZSIZE; z++) {

					if (Table[XSIZE * x + z].height > 0)	Table[x * XSIZE + z].height = 0;

				}
			}

			PutCommand();
		}
	}

}

void Stage::Draw()
{
	for (int x = 0; x < XSIZE; x++) {
		for (int z = 0; z < ZSIZE; z++) {

			Trans sttrans;
			for (int i = 0; i <= Table[x * XSIZE + z].height; i++) {

				sttrans.pos = { (float)x,static_cast<float>(i) ,(float)z };

				auto number = static_cast<int>(Table[x * XSIZE + z].blk);

				Model::Draw(&number, &sttrans, SHADER_TYPE::SHADER_2D);
			}
		}
	}
	
	OutputDebugString(to_string(back_).c_str());
}

void Stage::Release()
{
	delete[] cmds;
}

void Stage::SetBlockType(int x, int y, BLOCKTYPE type)
{
	Table[x * XSIZE + y].blk = type;
}

BLOCKTYPE Stage::GetBlockType(int x, int y)
{
	return static_cast<BLOCKTYPE>(Table[x * XSIZE + y].blk);
}

void Stage::SetHeight(int x, int y, int h)
{
	Table[x * XSIZE + y].height = h;
}

int Stage::GetHeight(int x, int y)
{
	return Table[x * XSIZE + y].height;
}

BOOL Stage::DialogProc(HWND hDlg, UINT msg, WPARAM wp, LPARAM lp)
{
	switch (msg)
	{
	case WM_INITDIALOG	:	SendMessage(GetDlgItem(hDlg, IDR_UP), BM_SETCHECK, BST_CHECKED, NULL);
	{
		LPCSTR names_[static_cast<int>(BLOCKTYPE::AMMOUNT)] =
		{
			"BoxDefault.fbx",
			"BoxBrick.fbx",
			"BoxGrass.fbx",
			"BoxSand.fbx",
			"BoxWater.fbx"
		};
		for (int i = 0; i < static_cast<int>(BLOCKTYPE::AMMOUNT); i++) {
			SendMessage(GetDlgItem(hDlg, IDC_COMBO1), CB_ADDSTRING, NULL, (LPARAM)(names_[i]));
		}
		SendMessage(GetDlgItem(hDlg, IDC_COMBO1), CB_SETCURSEL, 0,NULL);
	}
		return true;	

	 case WM_COMMAND:	select_ = static_cast<BLOCKTYPE>(SendMessage(GetDlgItem(hDlg, IDC_COMBO1), CB_GETCURSEL, NULL, NULL));
						mode_ = static_cast<MODE>(LOWORD(wp) - IDR_UP);
						return true;
	}

	
	return FALSE;
}

void Stage::SetSTG_CMD(Command cmd)
{
	memcpy(this->Table, cmd.Table, sizeof(Table));
}

void Stage::Save()
{
	OPENFILENAME ofn = {};

	ofn.lStructSize = sizeof(ofn);
	ofn.Flags = OFN_OVERWRITEPROMPT;
	ofn.lpstrFile = fstr;
	ofn.nMaxFile = MAX_PATH;
	ofn.lpstrDefExt = "Map";
	ofn.lpstrFilter = "マップデータ(***.map)\0.map\0\0";

	bool sf;

	sf = GetSaveFileName(&ofn);

	if (sf == false) return;

	fstream fs;
	fs.open(fstr, ios::binary | ios::out);

	for (auto i = 0; i < XSIZE * ZSIZE; ++i) {

		fs.write(reinterpret_cast<char*>(&(Table[i].height)), sizeof(Table[i].height));
		fs.write(reinterpret_cast<char*>(&(Table[i].blk)), sizeof(Table[i].blk));
	}
}

void Stage::Q_Save()
{
	fstream fs;
	fs.open(fstr, ios::binary | ios::out);

	for (auto i = 0; i < XSIZE * ZSIZE; ++i) {

		fs.write(reinterpret_cast<char*>(&(Table[i].height)), sizeof(Table[i].height));
		fs.write(reinterpret_cast<char*>(&(Table[i].blk)), sizeof(Table[i].blk));
	}
}

void Stage::Load()
{
	OPENFILENAME ofn = {};
	

	ofn.lStructSize = sizeof(ofn);
	ofn.Flags = OFN_FILEMUSTEXIST ;
	ofn.lpstrFile = fstr;
	ofn.nMaxFile = MAX_PATH;
	ofn.lpstrDefExt = "dat";

	bool sf;

	sf = GetOpenFileName(&ofn);

	if (sf == false) return;

	fstream fs;
	fs.open(fstr, ios::binary | ios::in);

	for (auto i = 0; i < XSIZE * ZSIZE; ++i) {

		fs.read(reinterpret_cast<char*>(&(Table[i].height)), sizeof(Table[i].height));
		fs.read(reinterpret_cast<char*>(&(Table[i].blk)), sizeof(Table[i].blk));
	}
}

void Stage::Reset()
{

	for (auto i = 0; i < XSIZE * ZSIZE; ++i) {

		Table[i].height = 0;
		Table[i].blk = BLOCKTYPE::BRICK;
	}
}

void Stage::PutCommand()
{
	memcpy(cmds[IND_cmd].Table, (this->Table), sizeof(Table));
	IND_cmd++;	IND_cmd %= buffersize_;
	
	back_++;
	fore_ = 0;

	back_ = std::clamp(back_, 0, buffersize_);
}

Command Stage::GetCommand()
{
	if (back_ > 0)
	{
		IND_cmd--;	
		if (IND_cmd >= 0)
		{
			IND_cmd %= buffersize_;
		}
		else
		{
			IND_cmd += buffersize_;
		}

		back_--;
		fore_++;

		fore_ = std::clamp(fore_, 0, buffersize_);
	}

	return this->cmds[IND_cmd];

}

Command Stage::ReGetCommand()
{
	if (fore_ > 0)
	{
		IND_cmd++;	IND_cmd %= buffersize_;

		back_++;
		fore_--;

		back_ = std::clamp(back_, 0, buffersize_);
	}

	return this->cmds[IND_cmd];
}

