object wCONF: TwCONF
  Left = 273
  Top = 159
  BorderStyle = bsToolWindow
  Caption = 'Par'#226'metros e Configura'#231#245'es'
  ClientHeight = 316
  ClientWidth = 269
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poDesktopCenter
  OnCloseQuery = FormCloseQuery
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object btnFechar: TBitBtn
    Left = 176
    Top = 288
    Width = 89
    Height = 25
    TabOrder = 0
    Kind = bkOK
  end
  object gbIntelligence: TGroupBox
    Left = 0
    Top = 0
    Width = 265
    Height = 249
    Caption = 'Intelig'#234'ncia'
    TabOrder = 1
    object gbAdvanced: TGroupBox
      Left = 24
      Top = 128
      Width = 233
      Height = 113
      TabOrder = 0
      object lbCrossover: TLabel
        Left = 16
        Top = 16
        Width = 59
        Height = 13
        Caption = 'Cruzamento:'
      end
      object Label11: TLabel
        Left = 72
        Top = 36
        Width = 14
        Height = 13
        Caption = '[%]'
      end
      object lbElitsmo: TLabel
        Left = 103
        Top = 64
        Width = 38
        Height = 13
        Caption = 'Elitismo:'
      end
      object lbIndiv: TLabel
        Left = 159
        Top = 84
        Width = 53
        Height = 13
        Caption = '[individuos]'
      end
      object lbNumIndiv: TLabel
        Left = 104
        Top = 16
        Width = 106
        Height = 13
        Caption = 'N'#250'mero de Individuos:'
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
        Caption = 'Muta'#231#227'o:'
      end
      object ePerCruz: TEdit
        Left = 16
        Top = 32
        Width = 49
        Height = 21
        TabOrder = 0
        Text = '95'
        OnExit = Exit
      end
      object eElite: TEdit
        Left = 103
        Top = 80
        Width = 49
        Height = 21
        TabOrder = 1
        Text = '2'
        OnExit = Exit
      end
      object spinNumIdv: TCSpinEdit
        Left = 104
        Top = 32
        Width = 49
        Height = 22
        Increment = 2
        MaxValue = 1000
        MinValue = 2
        TabOrder = 2
        Value = 10
        OnChange = spinNumIdvChange
      end
      object ePerMut: TEdit
        Left = 16
        Top = 80
        Width = 49
        Height = 21
        TabOrder = 3
        Text = '10'
        OnExit = Exit
      end
    end
    object rbSimple: TRadioButton
      Left = 8
      Top = 24
      Width = 65
      Height = 17
      Caption = 'Simples'
      Checked = True
      TabOrder = 1
      TabStop = True
      OnClick = rbSimpleClick
    end
    object rbAdvanced: TRadioButton
      Left = 8
      Top = 112
      Width = 113
      Height = 17
      Caption = 'Avan'#231'ado'
      TabOrder = 2
      OnClick = rbAdvancedClick
    end
    object gbSimple: TGroupBox
      Left = 24
      Top = 40
      Width = 225
      Height = 65
      TabOrder = 3
      object lbIntlg: TLabel
        Left = 8
        Top = 40
        Width = 208
        Height = 13
        Caption = 'Burro                                                 Experto'
      end
      object tbIntlg: TTrackBar
        Left = 16
        Top = 8
        Width = 193
        Height = 33
        Max = 20
        Orientation = trHorizontal
        Frequency = 1
        Position = 10
        SelEnd = 0
        SelStart = 0
        TabOrder = 0
        ThumbLength = 15
        TickMarks = tmBottomRight
        TickStyle = tsAuto
        OnChange = tbIntlgChange
      end
    end
  end
  object bgLanguage: TGroupBox
    Left = 0
    Top = 256
    Width = 169
    Height = 57
    Caption = 'L'#237'ngua'
    TabOrder = 2
    object cbLanguage: TComboBox
      Left = 8
      Top = 24
      Width = 153
      Height = 21
      Style = csDropDownList
      ItemHeight = 13
      TabOrder = 0
      OnChange = cbLanguageChange
      Items.Strings = (
        'portugues'
        'english')
    end
  end
end
