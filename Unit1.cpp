//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormCreate(TObject *Sender)
{
    randomize(); // 啟動亂數種子，讓怪物的攻擊每次都不一樣

    // 1. 建立勇者 (名字: 勇者, 血量: 100, 基礎攻擊: 10, 魔力: 50)
    hero = new Player("勇者", 100, 10, 50);
    // 展現組合觀念：為勇者裝備武器 (武器名稱: 鐵劍, 附加攻擊: 5)
    hero->currentWeapon = Weapon("鐵劍", 5);

    // 2. 建立怪物 (名字: 史萊姆, 血量: 100, 基礎攻擊: 8)
    slime = new Monster("史萊姆", 100, 8);

    // 3. 更新畫面上的血條上限與目前血量
    barPlayerHP->Max = hero->maxHp;
    barPlayerHP->Position = hero->hp;
    barMonsterHP->Max = slime->maxHp;
    barMonsterHP->Position = slime->hp;

    // 4. 在對話框印出開場白
    lstLog->Items->Clear(); // 先清空對話框
    lstLog->Items->Add("野生的 " + slime->name + " 出現了！");
    lstLog->Items->Add(hero->name + " 裝備了 " + hero->currentWeapon.name + "，準備戰鬥！");
    lstLog->Items->Add("----------------------------------------");
}
//---------------------------------------------------------------------------
void __fastcall TForm1::btnAttackClick(TObject *Sender)
{
    // 1. 勇者發動攻擊 (這裡完美展現了多型與組合，自動計算基礎攻擊+武器傷害)
    int dmg = hero->attack();
    slime->takeDamage(dmg);

    // 2. 更新畫面血條與對話框
    barMonsterHP->Position = slime->hp;
    lstLog->Items->Add(hero->name + " 揮舞武器，造成了 " + IntToStr(dmg) + " 點傷害！");

    // 3. 判斷怪物死了沒
    if (slime->isDead()) {
		lstLog->Items->Add("恭喜！" + slime->name + " 被擊敗了！");
        // 鎖住所有按鈕
        btnAttack->Enabled = false;
        btnMagic->Enabled = false;
        btnHeal->Enabled = false;
        ShowMessage("勇者獲勝！");
    } else {
        // 怪物還沒死：鎖住按鈕，不讓玩家連按，並啟動計時器換怪物反擊
        btnAttack->Enabled = false;
        btnMagic->Enabled = false;
        btnHeal->Enabled = false;
        Timer1->Enabled = true; // 啟動計時器，1秒後觸發怪物攻擊
    }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Timer1Timer(TObject *Sender)
{
    // 1. 關閉計時器 (只反擊一次，不要讓它一直跳)
    Timer1->Enabled = false;

    // 2. 怪物發動攻擊 (展現多型：史萊姆的攻擊會有亂數浮動)
    int dmg = slime->attack();
    hero->takeDamage(dmg);

    // 3. 更新畫面血條與對話框
    barPlayerHP->Position = hero->hp;
	lstLog->Items->Add(" " + slime->name + " 進行反擊，造成了 " + IntToStr(dmg) + " 點傷害！");

    // 4. 判斷勇者死了沒
    if (hero->isDead()) {
		lstLog->Items->Add("勝敗乃兵家常事，勇者倒下了...");
        ShowMessage("Game Over！");
    } else {
        // 勇者還沒死：解鎖按鈕，換玩家回合
        btnAttack->Enabled = true;
        btnMagic->Enabled = true;
        btnHeal->Enabled = true;
        lstLog->Items->Add("--- 換你的回合 ---");

        // 讓對話框自動捲動到最下面
        lstLog->TopIndex = lstLog->Items->Count - 1;
    }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::btnMagicClick(TObject *Sender)
{
    // 檢查魔力夠不夠 (每次消耗 20 點)
    if (hero->mp >= 20) {
        hero->mp -= 20; // 扣除魔力
        int dmg = hero->attack() * 2; // 魔法攻擊造成兩倍傷害！
        slime->takeDamage(dmg);

        barMonsterHP->Position = slime->hp;
        lstLog->Items->Add(hero->name + " 詠唱魔法，造成 " + IntToStr(dmg) + " 點大傷害！(剩餘 MP: " + IntToStr(hero->mp) + ")");

        if (slime->isDead()) {
            lstLog->Items->Add("恭喜！" + slime->name + " 被擊敗了！");
            btnAttack->Enabled = false;
            btnMagic->Enabled = false;
            btnHeal->Enabled = false;
            ShowMessage("勇者獲勝！");
        } else {
            // 怪物沒死，換怪物反擊
            btnAttack->Enabled = false;
            btnMagic->Enabled = false;
            btnHeal->Enabled = false;
            Timer1->Enabled = true;
        }
    } else {
        // 魔力不足時，跳出警告，並且不扣回合
        ShowMessage("魔力不足！無法施放魔法！");
    }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::btnHealClick(TObject *Sender)
{
    // 呼叫多載函數，喝藥水補 30 滴血
    hero->heal(30);

    // 更新血條
    barPlayerHP->Position = hero->hp;
    lstLog->Items->Add(hero->name + " 喝下藥水，恢復了 30 點生命值！");

    // 喝完藥水也要換怪物攻擊
    btnAttack->Enabled = false;
    btnMagic->Enabled = false;
    btnHeal->Enabled = false;
    Timer1->Enabled = true;
}
//---------------------------------------------------------------------------
