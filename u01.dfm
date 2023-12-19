object Form7: TForm7
  Left = 0
  Top = 0
  Caption = 'Form7'
  ClientHeight = 583
  ClientWidth = 665
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = 'Segoe UI'
  Font.Style = []
  OnDestroy = FormDestroy
  TextHeight = 15
  object Label1: TLabel
    Left = 11
    Top = 204
    Width = 56
    Height = 15
    Caption = 'Expression'
  end
  object Label2: TLabel
    Left = 305
    Top = 2
    Width = 32
    Height = 15
    Caption = 'Result'
  end
  object Label3: TLabel
    Left = 12
    Top = 280
    Width = 74
    Height = 15
    Caption = 'Variable name'
  end
  object Label4: TLabel
    Left = 14
    Top = 313
    Width = 67
    Height = 15
    Caption = 'Variable type'
  end
  object Label5: TLabel
    Left = 15
    Top = 340
    Width = 72
    Height = 15
    Caption = 'Variable value'
  end
  object Label6: TLabel
    Left = 8
    Top = 3
    Width = 61
    Height = 15
    Caption = 'Expressions'
  end
  object Edit1: TEdit
    Left = 10
    Top = 229
    Width = 229
    Height = 28
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -15
    Font.Name = 'Segoe UI'
    Font.Style = []
    ParentFont = False
    TabOrder = 0
    Text = 'AAA:='#39'Ala ma '#39' + '#39' kota'#39
  end
  object Memo1: TMemo
    Left = 305
    Top = 22
    Width = 348
    Height = 549
    TabOrder = 1
  end
  object Button1: TButton
    Left = 248
    Top = 227
    Width = 37
    Height = 25
    Caption = '='
    Font.Charset = EASTEUROPE_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Segoe UI Black'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 2
    OnClick = Button1Click
  end
  object Edit2: TEdit
    Left = 96
    Top = 277
    Width = 145
    Height = 23
    TabOrder = 3
  end
  object ComboBox1: TComboBox
    Left = 97
    Top = 309
    Width = 145
    Height = 23
    Style = csDropDownList
    ItemIndex = 0
    TabOrder = 4
    Text = 'Numeric'
    Items.Strings = (
      'Numeric'
      'Boolean'
      'String')
  end
  object Edit3: TEdit
    Left = 96
    Top = 339
    Width = 145
    Height = 23
    TabOrder = 5
  end
  object Button3: TButton
    Left = 13
    Top = 379
    Width = 41
    Height = 25
    Caption = 'ADD'
    TabOrder = 6
    OnClick = Button3Click
  end
  object Button4: TButton
    Left = 61
    Top = 379
    Width = 41
    Height = 25
    Caption = 'DEL'
    TabOrder = 7
    OnClick = Button4Click
  end
  object ListBox1: TListBox
    Left = 14
    Top = 424
    Width = 266
    Height = 146
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -15
    Font.Name = 'Segoe UI'
    Font.Style = []
    ItemHeight = 20
    ParentFont = False
    TabOrder = 8
    OnClick = ListBox1Click
  end
  object Button5: TButton
    Left = 111
    Top = 379
    Width = 56
    Height = 25
    Caption = 'UPDATE'
    TabOrder = 9
    OnClick = Button5Click
  end
  object Memo2: TMemo
    Left = 10
    Top = 22
    Width = 228
    Height = 179
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -15
    Font.Name = 'Segoe UI'
    Font.Style = []
    Lines.Strings = (
      '3*5-10.50'
      '(356+212)*15/10'
      'AAA:=-200*18-20.5'
      'BBB:=2'
      'BBB:=2 + BBB'
      'BBB:=2 + BBB'
      'BBB:=2 + BBB'
      'BBB:=2 + BBB')
    ParentFont = False
    TabOrder = 10
  end
  object Button2: TButton
    Left = 247
    Top = 22
    Width = 37
    Height = 25
    Caption = '='
    Font.Charset = EASTEUROPE_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Segoe UI Black'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 11
    OnClick = Button2Click
  end
end
