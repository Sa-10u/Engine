#pragma once
#include "Engine/GOBJ.h"

class Stage : public GOBJ
{
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	Stage(GOBJ* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;

protected:
	int model_;
};
