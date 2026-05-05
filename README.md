# Reversi_2D

一款使用 C++ 與 SDL2 開發的 2D Othello/Reversi 遊戲。

## Demo 影片
[![2D Reversi Demo](https://img.youtube.com/vi/Ty7sr9AN0Ro/maxresdefault.jpg)](https://www.youtube.com/watch?v=Ty7sr9AN0Ro)

## 功能

- **遊戲模式**
  - 玩家對戰（玩家 vs 玩家）
  - 玩家對電腦

- **遊戲動作**
  - 撤銷（Revert to previous move）
  - 前進（Redo 恢復下一動）

## 操作方式
- 點擊有效位置下子，有效落點會自動標示
- 使用 撤銷 / 前進 按鈕 navigate 移動紀錄
- 點擊棋子會顯示提示

## 專案結構

```
2D_reversi_solution/
├── 2D_Reversi/           # 主要程式碼
│   ├── Button.h          # UI 按鈕元件
│   ├── CheckerBoard.h    # 棋盤邏輯
│   └── ...
└── README.md
```

## 環境要求
- C++17 相容編譯器
- SDL2 函式庫

## 組建方式
本專案使用 Visual Studio 開發，開啟 `2D_reversi_solution/2D_Reversi.sln` 即可編譯執行。

## 資料來源
- 所有美術素材（棋盤、棋子、UI圖標等）皆為自行使用 Photoshop 繪製製作