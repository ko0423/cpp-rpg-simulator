object Form1: TForm1
  Left = 0
  Top = 0
  Caption = 'Form1'
  ClientHeight = 479
  ClientWidth = 598
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = 'Segoe UI'
  Font.Style = []
  OnCreate = FormCreate
  TextHeight = 15
  object lblPlayer: TLabel
    Left = 393
    Top = 38
    Width = 39
    Height = 15
    Caption = #21490#33802#22982
  end
  object lblMonster: TLabel
    Left = 136
    Top = 38
    Width = 26
    Height = 15
    Caption = #21191#32773
  end
  object barPlayerHP: TProgressBar
    Left = 88
    Top = 72
    Width = 150
    Height = 21
    Position = 100
    TabOrder = 0
  end
  object barMonsterHP: TProgressBar
    Left = 344
    Top = 72
    Width = 150
    Height = 21
    Position = 100
    TabOrder = 1
  end
  object btnAttack: TButton
    Left = 115
    Top = 384
    Width = 75
    Height = 25
    Caption = #26222#36890#25915#25802
    TabOrder = 2
    OnClick = btnAttackClick
  end
  object btnMagic: TButton
    Left = 376
    Top = 384
    Width = 75
    Height = 25
    Caption = #39764#27861#25915#25802
    TabOrder = 3
    OnClick = btnMagicClick
  end
  object btnHeal: TButton
    Left = 248
    Top = 384
    Width = 75
    Height = 25
    Caption = #21917#34277#27700
    TabOrder = 4
    OnClick = btnHealClick
  end
  object lstLog: TListBox
    Left = 136
    Top = 128
    Width = 305
    Height = 225
    ItemHeight = 15
    TabOrder = 5
  end
  object Timer1: TTimer
    Enabled = False
    OnTimer = Timer1Timer
    Top = 392
  end
end
