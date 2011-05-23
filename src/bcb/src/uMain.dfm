object F_Main: TF_Main
  Left = 297
  Top = 113
  Width = 721
  Height = 636
  Caption = 'GAPP'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poDesktopCenter
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object pnlParam: TPanel
    Left = 0
    Top = 0
    Width = 145
    Height = 583
    Align = alLeft
    BevelOuter = bvNone
    TabOrder = 0
    object gbCarro: TGroupBox
      Left = 0
      Top = 281
      Width = 145
      Height = 257
      Caption = 'Carro'
      TabOrder = 2
      object lbRay: TLabel
        Left = 8
        Top = 16
        Width = 25
        Height = 13
        Caption = 'Raio:'
      end
      object lbUnitRay: TLabel
        Left = 56
        Top = 16
        Width = 38
        Height = 13
        Caption = '[ pixels ]'
      end
      object lblRaio: TLabel
        Left = 40
        Top = 16
        Width = 6
        Height = 13
        Caption = '8'
      end
      object gbOrient: TGroupBox
        Left = 8
        Top = 120
        Width = 129
        Height = 60
        Caption = 'Orienta'#231#227'o'
        TabOrder = 1
        object rbOriMan: TRadioButton
          Left = 8
          Top = 40
          Width = 65
          Height = 17
          Caption = 'Manual['#176']'
          TabOrder = 0
        end
        object rbOriAleat: TRadioButton
          Left = 8
          Top = 16
          Width = 65
          Height = 17
          Caption = 'Aleat'#243'ria'
          Checked = True
          TabOrder = 1
          TabStop = True
        end
        object eOrient: TEdit
          Left = 89
          Top = 36
          Width = 33
          Height = 21
          TabOrder = 2
          Text = '0'
          OnExit = Exit
        end
      end
      object gbCarPos: TGroupBox
        Left = 8
        Top = 56
        Width = 129
        Height = 65
        Caption = 'Posi'#231#227'o'
        TabOrder = 0
        object rbPosMan: TRadioButton
          Left = 8
          Top = 40
          Width = 65
          Height = 17
          Caption = 'Manual'
          TabOrder = 0
        end
        object rbPosAleat: TRadioButton
          Left = 8
          Top = 16
          Width = 65
          Height = 17
          Caption = 'Aleat'#243'ria'
          Checked = True
          TabOrder = 1
          TabStop = True
        end
        object eX: TEdit
          Left = 64
          Top = 38
          Width = 27
          Height = 21
          TabOrder = 2
          Text = '0'
          OnExit = Exit
        end
        object eY: TEdit
          Left = 93
          Top = 38
          Width = 27
          Height = 21
          TabOrder = 3
          Text = '0'
          OnExit = Exit
        end
      end
      object tbRaio: TTrackBar
        Left = 8
        Top = 32
        Width = 129
        Height = 17
        Max = 30
        Min = 1
        Orientation = trHorizontal
        Frequency = 1
        Position = 8
        SelEnd = 0
        SelStart = 0
        TabOrder = 2
        ThumbLength = 10
        TickMarks = tmBottomRight
        TickStyle = tsAuto
        OnChange = tbRaioChange
      end
      object gbVarAng: TGroupBox
        Left = 8
        Top = 181
        Width = 129
        Height = 69
        Caption = #194'ngulos Limites'
        TabOrder = 3
        object lbAngRight: TLabel
          Left = 23
          Top = 21
          Width = 43
          Height = 13
          Alignment = taRightJustify
          Caption = 'Direita['#176']:'
        end
        object lbAngLeft: TLabel
          Left = 8
          Top = 45
          Width = 58
          Height = 13
          Alignment = taRightJustify
          Caption = 'Esquerda['#176']:'
        end
        object edAngRight: TEdit
          Left = 72
          Top = 17
          Width = 41
          Height = 21
          TabOrder = 0
          Text = '30'
          OnExit = Exit
        end
        object edAngLeft: TEdit
          Left = 72
          Top = 41
          Width = 41
          Height = 21
          TabOrder = 1
          Text = '-30'
          OnExit = Exit
        end
      end
    end
    object gbGaragem: TGroupBox
      Left = 0
      Top = 136
      Width = 145
      Height = 145
      Caption = 'Garagem'
      TabOrder = 1
      object lbCenGar: TLabel
        Left = 8
        Top = 16
        Width = 95
        Height = 13
        Caption = 'Centro da Garagem:'
      end
      object Label5: TLabel
        Left = 8
        Top = 37
        Width = 10
        Height = 13
        Caption = 'X:'
      end
      object Label6: TLabel
        Left = 63
        Top = 37
        Width = 10
        Height = 13
        Caption = 'Y:'
      end
      object lbTolerance: TLabel
        Left = 8
        Top = 64
        Width = 115
        Height = 13
        Caption = 'Dist'#226'ncia de Toler'#226'ncia:'
      end
      object lbGarStep: TLabel
        Left = 8
        Top = 103
        Width = 32
        Height = 13
        Caption = 'Passo:'
      end
      object eXEst: TEdit
        Left = 24
        Top = 33
        Width = 33
        Height = 21
        TabOrder = 0
        Text = '250'
        OnExit = Exit
      end
      object eYEst: TEdit
        Left = 79
        Top = 33
        Width = 33
        Height = 21
        TabOrder = 1
        Text = '250'
        OnExit = Exit
      end
      object eToler: TEdit
        Left = 8
        Top = 80
        Width = 49
        Height = 21
        TabOrder = 2
        Text = '1'
        OnExit = Exit
      end
      object edGarStep: TEdit
        Left = 8
        Top = 117
        Width = 49
        Height = 21
        TabOrder = 3
        Text = '30'
        OnExit = Exit
      end
    end
    object gbParam: TGroupBox
      Left = 0
      Top = 0
      Width = 145
      Height = 137
      Caption = 'Configura'#231#245'es'
      TabOrder = 0
      object lbDimPlan: TLabel
        Left = 8
        Top = 16
        Width = 95
        Height = 13
        Caption = 'Dimens'#245'e do Plano:'
      end
      object Label8: TLabel
        Left = 61
        Top = 40
        Width = 5
        Height = 13
        Caption = 'x'
      end
      object lbDelay: TLabel
        Left = 8
        Top = 56
        Width = 94
        Height = 13
        Caption = 'Tempo Espera [ms]:'
      end
      object lbStep: TLabel
        Left = 8
        Top = 96
        Width = 32
        Height = 13
        Caption = 'Passo:'
      end
      object spinGridX: TCSpinEdit
        Left = 8
        Top = 32
        Width = 50
        Height = 22
        Increment = 10
        MaxValue = 10000
        MinValue = 10
        TabOrder = 0
        Value = 500
      end
      object spinGridY: TCSpinEdit
        Left = 70
        Top = 32
        Width = 50
        Height = 22
        Increment = 10
        MaxValue = 10000
        MinValue = 10
        TabOrder = 1
        Value = 500
      end
      object eTempoEsp: TEdit
        Left = 8
        Top = 72
        Width = 49
        Height = 21
        TabOrder = 2
        Text = '15'
        OnExit = Exit
      end
      object eStep: TEdit
        Left = 8
        Top = 112
        Width = 49
        Height = 21
        TabOrder = 3
        Text = '5'
        OnExit = Exit
      end
    end
    object btnAGConf: TButton
      Left = 8
      Top = 544
      Width = 129
      Height = 33
      Caption = 'Par'#226'metros'
      TabOrder = 3
      OnClick = AGConfClick
    end
  end
  object pnlGrid: TPanel
    Left = 145
    Top = 0
    Width = 568
    Height = 583
    Align = alClient
    BevelOuter = bvNone
    Color = clSilver
    TabOrder = 1
    object pb: TPaintBox
      Left = 0
      Top = 0
      Width = 568
      Height = 420
      Align = alClient
    end
    object Splitter: TSplitter
      Left = 0
      Top = 420
      Width = 568
      Height = 3
      Cursor = crVSplit
      Align = alBottom
      Beveled = True
      Color = clSilver
      ParentColor = False
      ResizeStyle = rsUpdate
    end
    object pnlBottom: TPanel
      Left = 0
      Top = 423
      Width = 568
      Height = 160
      Align = alBottom
      BevelOuter = bvNone
      TabOrder = 0
      object pgcTabGraf: TPageControl
        Left = 0
        Top = 0
        Width = 493
        Height = 160
        ActivePage = tsTab
        Align = alClient
        TabIndex = 0
        TabOrder = 0
        object tsTab: TTabSheet
          Caption = 'Geral'
          object lvIndivs: TListView
            Left = 0
            Top = 0
            Width = 485
            Height = 132
            Align = alClient
            Columns = <
              item
                Caption = 'Gera'#231#227'o'
                Width = 70
              end
              item
                Caption = 'Ajuste'
                Width = 60
              end
              item
                Caption = 'Orient. Atual'
                Width = 70
              end
              item
                Caption = 'Inc. Angulo'
                Width = 70
              end
              item
                Caption = 'Pos. Atual'
                Width = 120
              end
              item
                Caption = 'Dist'#226'ncia'
                Width = 70
              end>
            GridLines = True
            ReadOnly = True
            RowSelect = True
            TabOrder = 0
            ViewStyle = vsReport
          end
        end
        object tsGraf: TTabSheet
          Caption = 'Dist'#226'ncia'
          ImageIndex = 1
          object chDist: TChart
            Left = 0
            Top = 0
            Width = 475
            Height = 132
            AnimatedZoom = True
            BackWall.Brush.Color = clWhite
            BackWall.Brush.Style = bsClear
            Title.Text.Strings = (
              'TChart')
            Title.Visible = False
            Legend.Visible = False
            Align = alClient
            TabOrder = 0
            object Series1: TLineSeries
              Marks.ArrowLength = 8
              Marks.Visible = False
              SeriesColor = clRed
              Pointer.InflateMargins = True
              Pointer.Style = psRectangle
              Pointer.Visible = False
              XValues.DateTime = False
              XValues.Name = 'X'
              XValues.Multiplier = 1
              XValues.Order = loAscending
              YValues.DateTime = False
              YValues.Name = 'Y'
              YValues.Multiplier = 1
              YValues.Order = loNone
            end
          end
        end
        object tsStat: TTabSheet
          Caption = 'Estatisticas'
          ImageIndex = 2
          object crtStat: TChart
            Left = 0
            Top = 0
            Width = 475
            Height = 132
            BackWall.Brush.Color = clWhite
            BackWall.Brush.Style = bsClear
            MarginBottom = 0
            MarginLeft = 0
            MarginTop = 3
            Title.Text.Strings = (
              '')
            Title.Visible = False
            Legend.Alignment = laBottom
            View3D = False
            Align = alClient
            BevelOuter = bvNone
            TabOrder = 0
            object Series2: TFastLineSeries
              Marks.ArrowLength = 8
              Marks.Visible = False
              SeriesColor = clRed
              Title = 'Fitness Max'
              LinePen.Color = clRed
              XValues.DateTime = False
              XValues.Name = 'X'
              XValues.Multiplier = 1
              XValues.Order = loAscending
              YValues.DateTime = False
              YValues.Name = 'Y'
              YValues.Multiplier = 1
              YValues.Order = loNone
            end
            object Series3: TFastLineSeries
              Marks.ArrowLength = 8
              Marks.Visible = False
              SeriesColor = clGreen
              Title = 'Fitness Med'
              LinePen.Color = clGreen
              XValues.DateTime = False
              XValues.Name = 'X'
              XValues.Multiplier = 1
              XValues.Order = loAscending
              YValues.DateTime = False
              YValues.Name = 'Y'
              YValues.Multiplier = 1
              YValues.Order = loNone
            end
          end
        end
      end
      object pnlRight: TPanel
        Left = 493
        Top = 0
        Width = 75
        Height = 160
        Align = alRight
        BevelOuter = bvNone
        TabOrder = 1
        object btnExecuta: TButton
          Left = 8
          Top = 32
          Width = 60
          Height = 25
          Caption = 'Executar'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
          TabOrder = 0
          OnClick = ExecutarAg
        end
        object btnPause: TButton
          Left = 8
          Top = 64
          Width = 60
          Height = 25
          Caption = 'Parar'
          TabOrder = 1
          OnClick = PararAG
        end
        object btnNew: TButton
          Left = 8
          Top = 96
          Width = 60
          Height = 25
          Caption = 'Limpar'
          TabOrder = 2
          OnClick = Limpar
        end
        object btnExit: TBitBtn
          Left = 8
          Top = 128
          Width = 60
          Height = 25
          Caption = '&Sair'
          TabOrder = 3
          Kind = bkClose
        end
        object cbRealTime: TCheckBox
          Left = 8
          Top = 8
          Width = 65
          Height = 17
          Caption = 'Mostrar'
          Checked = True
          State = cbChecked
          TabOrder = 4
          OnClick = cbRealTimeClick
        end
      end
    end
  end
  object statusbar: TStatusBar
    Left = 0
    Top = 583
    Width = 713
    Height = 19
    Panels = <
      item
        Text = 'Gera'#231#227'o Atual:'
        Width = 130
      end
      item
        Text = 'Dist'#226'ncia Atual:'
        Width = 130
      end
      item
        Text = 'Posi'#231#227'o Atual:'
        Width = 200
      end
      item
        Text = 'Orienta'#231#227'o Atual:'
        Width = 150
      end
      item
        Width = 50
      end>
    SimplePanel = False
  end
end
