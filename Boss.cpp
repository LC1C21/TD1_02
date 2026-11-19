#include <Novice.h>
#include <math.h>
#include "Boss.h"

// コンストラクタ
Boss::Boss()
{
	Initialize();
}

// デストラクタ
Boss::~Boss()
{}

// ボスの初期化処理
void Boss::Initialize()
{
	// ボス本体の位置を設定
	x = 640;
	y = 360;

	// 眼球の初期位置をボスの中心に設定
	eyeX = 640.0f;
	eyeY = 360.0f;

	// 眼球の追尾速度を設定
	eyeSpeed = 0.5f;

	// ボスの最大HP
	maxHp = 500;
	// 現在のHPと同期
	hp = maxHp;

	// ダメージ関連の変数
	damageTimer = 0;
	damageDuration = 20;
	amplitude = 15;

	// シェイク
	shakeX = 0.0f;
	shakeY = 0.0f;

	// 点滅
	isBlink = false;
}

// ボスの眼球移動
void Boss::Update(float playerX, float playerY)
{
	// プレイヤーの方向に眼球を移動させる
	eyeX += (playerX - eyeX) * eyeSpeed;
	eyeY += (playerY - eyeY) * eyeSpeed;

	// ボスの中心から眼球までの距離を計算
	float dx = eyeX - x;
	float dy = eyeY - y;

	// 2点間の距離を計算
	float distance = sqrtf(dx * dx + dy * dy);

	// 眼球が移動できる最大距離
	// 外側の円の半径190 - 眼球の半径78
	float maxDistance = 190.0f - 78.0f;

	// 眼球が移動できる範囲を超えた場合
	if (distance > maxDistance)
	{
		// 距離の比率を計算
		float rate = maxDistance / distance;

		// 眼球を移動できる範囲の端に戻す
		eyeX = x + dx * rate;
		eyeY = y + dy * rate;

	}

	// ダメージ演出
	if (damageTimer > 0 && damageDuration > 0)
	{
		// 今の時間 / 最大時間 = 割合
		float currentTime = (float)damageTimer / damageDuration;

		// 割合 × 揺れ幅
		shakeX = (float)(rand() % (amplitude * 2 + 1) - amplitude) * currentTime;
		shakeY = (float)(rand() % (amplitude * 2 + 1) - amplitude) * currentTime;

		// 3フレームごとに点滅
		isBlink = (damageTimer / 3) % 2 == 0;

		damageTimer--;
	} 
	else
	{
		// 揺れと点滅をリセット
		shakeX = 0.0f;
		shakeY = 0.0f;
		isBlink = false;
	}

}

// ボスにダメージを与える
void Boss::TakeDamage(int damage)
{
	// HPを減らす
	hp -= damage;

	// HPが0より小さくならないようにする
	if (hp < 0)
	{
		hp = 0;
	}

	// ダメージ演出を開始
	damageTimer = damageDuration;
}

// ボスの描画
void Boss::Draw()
{

	// シェイクを加算したボスの座標
	int bossDrawX = 640 + (int)shakeX;
	int bossDrawY = 360 + (int)shakeY;

	if (!isBlink)
	{
		// 外側の円
		Novice::DrawEllipse
		(
			bossDrawX,
			bossDrawY,
			190,
			190,
			0.0f,
			0xFF2040FF,
			kFillModeWireFrame
		);

		// 白い眼球
		Novice::DrawEllipse
		(
			static_cast<int>(eyeX + shakeX),
			static_cast<int>(eyeY + shakeY),
			78,
			78,
			0.0f,
			WHITE,
			kFillModeSolid
		);

		// 赤い瞳
		Novice::DrawEllipse
		(
			static_cast<int>(eyeX + shakeX),
			static_cast<int>(eyeY + shakeY),
			50,
			50,
			0.0f,
			0xFF2040FF,
			kFillModeSolid
		);

		for (int i = -180; i < 180; i++)
		{
			// 線の始点と終点のX座標
			float x1 = static_cast<float>(i);
			float x2 = static_cast<float>(i + 1);

			// 上下の曲線のY座標を計算
			float y1 = 90.0f * (1.0f - (x1 * x1) / (180.0f * 180.0f));
			float y2 = 90.0f * (1.0f - (x2 * x2) / (180.0f * 180.0f));

			// 目の上下の輪郭
			// 上側の曲線
			Novice::DrawLine
			(
				static_cast<int>(bossDrawX + x1),
				static_cast<int>(bossDrawY - y1),
				static_cast<int>(bossDrawX + x2),
				static_cast<int>(bossDrawY - y2),
				0xFF2040FF
			);

			// 下側の曲線
			Novice::DrawLine
			(
				static_cast<int>(bossDrawX + x1),
				static_cast<int>(bossDrawY + y1),
				static_cast<int>(bossDrawX + x2),
				static_cast<int>(bossDrawY + y2),
				0xFF2040FF
			);
		}
	}

	/* // ボスの外側の円
	Novice::DrawEllipse
	(
		640,
		360,
		190,
		190,
		0.0f,
		0xFF2040FF,
		kFillModeWireFrame
	);

	// 白い眼球
	Novice::DrawEllipse
	(
		static_cast<int>(eyeX),
		static_cast<int>(eyeY),
		78,
		78,
		0.0f,
		WHITE,
		kFillModeSolid
	);

	 // 赤い瞳
	Novice::DrawEllipse
	(
		static_cast<int>(eyeX),
		static_cast<int>(eyeY),
		50,
		50,
		0.0f,
		0xFF2040FF,
		kFillModeSolid
	);

	 // 目の上下の輪郭を描画
	for (int i = -180; i < 180; i++)
	{
		 // 線の始点と終点のX座標
		float x1 = static_cast<float>(i);
		float x2 = static_cast<float>(i + 1);

		 // 上下の曲線のY座標を計算
		float y1 = 90.0f * (1.0f - (x1 * x1) / (180.0f * 180.0f));
		float y2 = 90.0f * (1.0f - (x2 * x2) / (180.0f * 180.0f));

		 // 上側の曲線
		Novice::DrawLine
		(
			static_cast<int>(640 + x1),
			static_cast<int>(360 - y1),
			static_cast<int>(640 + x2),
			static_cast<int>(360 - y2),
			0xFF2040FF
		);

		 // 下側の曲線
		Novice::DrawLine
		(
			static_cast<int>(640 + x1),
			static_cast<int>(360 + y1),
			static_cast<int>(640 + x2),
			static_cast<int>(360 + y2),
			0xFF2040FF
		);
	}*/

	// ------------------------------
	// ボスのHPバー
	// ------------------------------

	// HPバーの位置
	int hpBarX = 120;
	int hpBarY = 40;

	// HPバーの大きさ
	int hpBarWidth = 1200;
	int hpBarHeight = 30;

	// 現在のHPの割合を計算
	float hpRate = static_cast<float>(hp) / maxHp;
	// 現在のHPに合わせてバーの幅を計算
	int currentHpWidth = static_cast<int>(hpBarWidth * hpRate);

	// HPバーの背景（黒）
	Novice::DrawBox
	(
		hpBarX,
		hpBarY,
		hpBarWidth,
		hpBarHeight,
		0.0f,
		BLACK,
		kFillModeSolid
	);

	// HPの残量（赤）
	Novice::DrawBox
	(
		hpBarX,
		hpBarY,
		currentHpWidth,
		hpBarHeight,
		0.0f,
		0xFF2040FF,
		kFillModeSolid
	);

	// HPバーの白い枠線
	Novice::DrawBox
	(
		hpBarX,
		hpBarY,
		hpBarWidth,
		hpBarHeight,
		0.0f,
		WHITE,
		kFillModeWireFrame
	);

}