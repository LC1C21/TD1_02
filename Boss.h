#pragma once

class Boss
{
public:

	Boss();
	~Boss();
	// ボスの初期化
	void Initialize();
	// ボスの攻撃受けた時(演出)
	void BossDamage();
	// プレイヤーの座標を受け取ってボスを更新する
	void Update(float playerX, float playerY);
	// ボスを描画する
	void Draw();

	//　テストプレイ用の関数ですあとで消すよ
	void TakeDamage(int damage);

private:

	// ボス本体の中心座標
	int x;
	int y;

	// 眼球の座標
	float eyeX;
	float eyeY;
	// 眼球がプレイヤーを追いかける速度
	float eyeSpeed;

	// ボスの体力
	int hp;
	// ボスの最大HP
	int maxHp;

	// ダメージ関連の変数
	int damageTimer;
	int damageDuration;
	int amplitude;

	// シェイク
	float shakeX;
	float shakeY;

	// 点滅
	bool isBlink;

};