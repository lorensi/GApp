object wCONF: TwCONF
  Left = 313
  Top = 227
  BorderStyle = bsToolWindow
  Caption = 'Parâmetros do Algoritmo Genetico'
  ClientHeight = 148
  ClientWidth = 274
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poDesktopCenter
  OnCloseQuery = FormCloseQuery
  PixelsPerInch = 96
  TextHeight = 13
  object btnFechar: TBitBtn
    Left = 0
    Top = 120
    Width = 273
    Height = 25
    TabOrder = 0
    Kind = bkOK
  end
  object gbParamAG: TGroupBox
    Left = 0
    Top = 0
    Width = 273
    Height = 113
    Caption = 'Configuração'
    TabOrder = 1
    object lbIndiv: TLabel
      Left = 200
      Top = 84
      Width = 53
      Height = 13
      Caption = '[individuos]'
    end
    object lbElitsmo: TLabel
      Left = 144
      Top = 64
      Width = 38
      Height = 13
      Caption = 'Elitismo:'
    end
    object Label12: TLabel
      Left = 72
      Top = 84
      Width = 14
      Height = 13
      Caption = '[%]'
    end
    object lbMut: TLabel
      Left = 16
      Top = 64
      Width = 45
      Height = 13
      Caption = 'Mutação:'
    end
    object Label11: TLabel
      Left = 72
      Top = 36
      Width = 14
      Height = 13
      Caption = '[%]'
    end
    object lbCrossover: TLabel
      Left = 16
      Top = 16
      Width = 59
      Height = 13
      Caption = 'Cruzamento:'
    end
    object Label18: TLabel
      Left = 144
      Top = 16
      Width = 74
      Height = 13
      Caption = 'Fitness Scaling:'
      Enabled = False
    end
    object eElite: TEdit
      Left = 144
      Top = 80
      Width = 49
      Height = 21
      TabOrder = 0
      Text = '2'
      OnExit = Exit
    end
    object ePerMut: TEdit
      Left = 16
      Top = 80
      Width = 49
      Height = 21
      TabOrder = 1
      Text = '10'
      OnExit = Exit
    end
    object ePerCruz: TEdit
      Left = 16
      Top = 32
      Width = 49
      Height = 21
      TabOrder = 2
      Text = '95'
      OnExit = Exit
    end
    object cbScaling: TComboBox
      Left = 144
      Top = 32
      Width = 97
      Height = 21
      Enabled = False
      ItemHeight = 13
      TabOrder = 3
      Text = 'No Scaling'
      Items.Strings = (
        'No Scaling'
        'Linear Scaling')
    end
  end
end
