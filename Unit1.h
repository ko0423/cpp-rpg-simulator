//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
//---------------------------------------------------------------------------
// --- 1. 組合 (Composition)：武器類別 ---
class Weapon {
public:
    AnsiString name;
    int extraDamage;
    Weapon() { name = "空手"; extraDamage = 0; }
    Weapon(AnsiString n, int dmg) { name = n; extraDamage = dmg; }
};

// --- 2. 基礎類別 (Base Class) ---
class Character {
public:
    AnsiString name;
    int hp;
    int maxHp;
    int baseAttack;

    Character(AnsiString n, int mHp, int atk) {
        name = n;
        maxHp = mHp;
        hp = maxHp;
        baseAttack = atk;
    }

    // 多型 (Polymorphism) 準備：虛擬函數，讓子類別改寫攻擊計算
    virtual int attack() {
        return baseAttack;
    }

    // 扣血邏輯
    void takeDamage(int dmg) {
        hp -= dmg;
        if (hp < 0) hp = 0;
    }

    // 判斷生死
    bool isDead() {
        return hp <= 0;
    }

    // --- 3. 多載 (Overloading)：兩種補血方式 ---
    void heal(int amount) {
        hp += amount;
        if (hp > maxHp) hp = maxHp; // 補血不能超過上限
    }

    void heal() {
        hp = maxHp; // 沒傳參數時，預設直接補滿血
    }
};

// --- 4. 繼承 (Inheritance) 與 多型：玩家類別 ---
class Player : public Character {
public:
    int mp;
    Weapon currentWeapon; // 玩家擁有武器 (這就是組合關係)

	Player(AnsiString n, int mHp, int atk, int m) : Character(n, mHp, atk) {
        mp = m;
    }

    // 覆寫 (Override) 攻擊函數，加上武器的附加傷害
    int attack() {
        return baseAttack + currentWeapon.extraDamage;
    }
};

// --- 5. 繼承 (Inheritance) 與 多型：怪物類別 ---
class Monster : public Character {
public:
    Monster(AnsiString n, int mHp, int atk) : Character(n, mHp, atk) {}

    // 覆寫 (Override) 攻擊函數，讓怪物的攻擊帶有隨機浮動值
    int attack() {
        int randomVariant = rand() % 5; // 產生 0~4 的浮動傷害
        return baseAttack + randomVariant;
    }
};
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TProgressBar *barPlayerHP;
	TProgressBar *barMonsterHP;
	TLabel *lblPlayer;
	TLabel *lblMonster;
	TButton *btnAttack;
	TButton *btnMagic;
	TButton *btnHeal;
	TListBox *lstLog;
	TTimer *Timer1;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall btnAttackClick(TObject *Sender);
	void __fastcall Timer1Timer(TObject *Sender);
	void __fastcall btnMagicClick(TObject *Sender);
	void __fastcall btnHealClick(TObject *Sender);
private:	// User declarations
	Player *hero;    // 宣告玩家指標
	Monster *slime;  // 宣告怪物指標
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
