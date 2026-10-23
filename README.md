# C++ Object-Oriented RPG Battle Simulator

![RPG Demo](DEMO.gif)

## 專案簡介 (Introduction)
這是一個使用 C++Builder 開發的 RPG 戰鬥模擬器。專案核心著重於**底層物件導向 (OOP) 架構設計**，跳脫單純的 UI 刻板操作，運用類別設計處理遊戲角色屬性、戰鬥數值結算與回合制事件觸發。

完整系統分析與架構設計過程，請參閱本專案附帶之 [Project_Report.pdf](./Project_Report.pdf)。

## 開發技術 (Tech Stack)
* **程式語言：** C++
* **開發環境：** C++Builder (VCL 架構)
* **核心概念：** 物件導向程式設計 (OOP)、事件驅動開發

## 核心架構與亮點 (Features & Architecture)

### 1. 嚴謹的物件導向實作
* **繼承 (Inheritance)：** 建立基礎 `Character` 父類別，統整 HP、攻擊力等共用屬性，並由此衍生出 `Player` 與 `Monster` 子類別，提高程式碼的重用性。
* **多型 (Polymorphism)：** 運用虛擬函式 (Virtual Function) 實作多型，使不同角色物件在呼叫相同的 `attack()` 攻擊指令時，能產生截然不同的傷害運算邏輯。
* **組合 (Composition)：** 將武器與裝備獨立設計為 `Weapon` 類別，透過物件組合的方式賦予角色額外數值，維持高內聚低耦合的系統彈性。

### 2. VCL 事件驅動與狀態控制
* **非同步節奏控制：** 導入 `TTimer` 元件精準掌控回合制的戰鬥延遲與節奏運算。
* **狀態即時反饋：** 綁定 `TProgressBar` 與 `TButton` 狀態，即時反映雙方血量變化，並防範玩家在敵方回合進行非法操作，確保遊戲邏輯的嚴密性。