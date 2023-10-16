#pragma once
#include "Engine/GOBJ.h"
#include <fstream>

const int XSIZE{ 15 };
const int ZSIZE{ 15 };
struct Command;

enum class BLOCKTYPE
{
	DEFAULT,
	BRICK,
	GRASS,
	SAND,
	WATER,

	AMMOUNT
};

struct Block
{
public:
	BLOCKTYPE blk;
	int height;
};

class Stage : public GOBJ
{
public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	Stage(GOBJ* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;

	void SetBlockType(int x, int y, BLOCKTYPE type);
	BLOCKTYPE GetBlockType(int x,int y);
	void SetHeight(int x, int y, int h);
	int GetHeight(int x, int y);
	BOOL DialogProc(HWND hDlg, UINT msg, WPARAM wp, LPARAM lp);

	void SetSTG_CMD(Command cmd);

	void Save();
	void Q_Save();
	void Load();
	void Reset();

	void PutCommand();
	Command GetCommand();
	Command ReGetCommand();

protected:
	int model_[5];
	Block Table[XSIZE * ZSIZE];

	enum class MODE
	{
		UP,
		DOWN,
		CHANGE,
	};
	
	int IND_cmd;
	int back_;
	int fore_;
	const int buffersize_;
	Command* cmds;

	MODE mode_;
	BLOCKTYPE select_;

	char fstr[MAX_PATH];
};

//--------

struct Command
{
	Block Table[XSIZE * ZSIZE];
};