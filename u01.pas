unit u01;

interface

uses
  Winapi.Windows, Winapi.Messages,  System.Variants,
  System.Classes, Vcl.Graphics,
  Vcl.Controls, Vcl.Forms, Vcl.Dialogs, Vcl.StdCtrls,
  System.AnsiStrings, u03;

type

  TForm7 = class(TForm)
    Edit1: TEdit;
    Label1: TLabel;
    Memo1: TMemo;
    Label2: TLabel;
    Button1: TButton;
    Label3: TLabel;
    Edit2: TEdit;
    Label4: TLabel;
    ComboBox1: TComboBox;
    Label5: TLabel;
    Edit3: TEdit;
    Button3: TButton;
    Button4: TButton;
    ListBox1: TListBox;
    Button5: TButton;
    Memo2: TMemo;
    Label6: TLabel;
    Button2: TButton;
    procedure Button3Click(Sender: TObject);
    procedure ListBox1Click(Sender: TObject);
    procedure Button4Click(Sender: TObject);
    procedure Button5Click(Sender: TObject);
    procedure Button1Click(Sender: TObject);
    procedure FormDestroy(Sender: TObject);
    function  Exp(value: string): boolean;
    procedure Button2Click(Sender: TObject);
  private
    procedure AddVar(tyepvar: integer; varname: string; varvalue: string);
  public
    { Public declarations }
  end;

var
  Form7: TForm7;

implementation

{$R *.dfm}

uses u02;

procedure TForm7.FormDestroy(Sender: TObject);
var
  i: Integer;
  variableNew:PVariable;
begin
  for i := 0 to ListBox1.Items.Count -1  do
  begin
    variableNew := PVariable(ListBox1.Items.Objects[i]);
    StrDispose(variableNew.varName);
    StrDispose(variableNew.varStr);
    Dispose(variableNew);
  end;
end;


procedure TForm7.Button1Click(Sender: TObject);
begin
  Exp(Edit1.Text);
end;

function TForm7.Exp(value: string): boolean;
var
  parseExpress: TParseExpress;
  i: integer;
  VariableNew : PVariable;
  Variable : PVariable;
  errorstr : string;
begin
  parseExpress := TParseExpress.Create();
  try
    for i := 0 to ListBox1.Items.Count -1 do
    begin
      parseExpress.AddVariable(PVariable(ListBox1.Items.Objects[i]));
    end;
    if parseExpress.Calculate(value, errorstr) then
    begin
      Memo1.Lines.Add('-------------');
      Memo1.Lines.Add(parseExpress.GetResultStr());
      Memo1.Lines.Add('-------------');
      result := true;
    end
    else
    begin
      Memo1.Lines.Add('-------------');
      Memo1.Lines.Add(errorstr);
      Memo1.Lines.Add('-------------');
      result := false;
    end;
    for i := 0 to ListBox1.Items.Count -1 do
    begin
      Variable := parseExpress.GetVariableValue(ListBox1.Items[i]);
      if Variable <> nil then
      begin
        VariableNew := PVariable(ListBox1.Items.Objects[i]);
        VariableNew.typevar := Variable.typevar;
        if Variable.typevar = STRINGVAR then
          StrLCopy(VariableNew.varStr, PAnsiChar(AnsiString(Variable.varStr)), Length(Variable.varStr));
        VariableNew.varBoolean := Variable.varBoolean;
        VariableNew.varNumeric := Variable.varNumeric;
      end;
    end;
  finally
    parseExpress.Free;
  end;
end;


procedure TForm7.Button2Click(Sender: TObject);
var
 i: Integer;
 varis: Boolean;
begin
  for i := 0 to ListBox1.Items.Count -1 do
     if ListBox1.Items[i] = 'AAA' then
        varis := true;
  if not varis then
     AddVar(0,'AAA', '0');
  for i := 0 to ListBox1.Items.Count -1 do
     if ListBox1.Items[i] = 'BBB' then
        varis := true;
  if not varis then
     AddVar(0,'BBB', '0');
  for i := 0 to Memo2.Lines.Count-1 do
     Exp(Memo2.Lines[i]);
end;

procedure TForm7.Button3Click(Sender: TObject);
begin
  AddVar(ComboBox1.ItemIndex,Edit2.Text, Edit3.Text);
end;

procedure TForm7.AddVar(tyepvar: integer; varname: string; varvalue: string);
var
  variableNew:PVariable;
begin
  New(variableNew);
  variableNew.varNumeric :=0;
  variableNew.varBoolean:=0;
  variableNew.typevar := tyepvar;
  variableNew.varStr := AnsiStrAlloc(1000);
  if tyepvar = 0 then
    if Length(varvalue) > 0 then
    begin
      try
        variableNew.varNumeric := _StrToFloat(varvalue);
      finally

      end;
    end
  else if tyepvar = 0 then
  begin
    if varvalue = 'T.' then
       variableNew.varBoolean := 1
    else
        variableNew.varBoolean := 0;
  end else if tyepvar = 2 then
  begin
    StrLCopy(variableNew.varStr, PAnsiChar(AnsiString(varvalue)),
                                Length(varvalue));
  end;

  variableNew.varName :=  AnsiStrAlloc(100);
  StrLCopy(variableNew.varName, PAnsiChar(AnsiString(varname)),
                                Length(varname));
  ListBox1.AddItem(varname, TObject(variableNew)) ;
end;

procedure TForm7.Button4Click(Sender: TObject);
var
  variableNew:PVariable;
begin
  if ListBox1.Items.Count = 0 then
     exit;
  variableNew := PVariable(ListBox1.Items.Objects[ListBox1.ItemIndex]);
  ListBox1.Items.Delete(ListBox1.ItemIndex);
  Dispose(variableNew);
  if ListBox1.Items.Count = 0 then
     exit;
  ListBox1Click(nil);
end;

procedure TForm7.Button5Click(Sender: TObject);
var
  variableNew:PVariable;
begin
  variableNew := PVariable(ListBox1.Items.Objects[ListBox1.ItemIndex]);
  ListBox1.Items.Delete(ListBox1.ItemIndex);
  Dispose(variableNew);
  Button3Click(nil);
end;

procedure TForm7.ListBox1Click(Sender: TObject);
var
  variableNew:PVariable;
begin
  variableNew := PVariable(ListBox1.Items.Objects[ListBox1.ItemIndex]);
  ComboBox1.ItemIndex := variableNew.typevar;
  if ComboBox1.ItemIndex = 0 then
     Edit3.Text:= _FloatToStr(variableNew.varNumeric)
  else if ComboBox1.ItemIndex = 0 then
  begin
    if variableNew.varBoolean = 1  then
       Edit3.Text := 'T.'
    else
        Edit3.Text := 'F.';
  end else if ComboBox1.ItemIndex = 2 then
  begin
    Edit3.Text := variableNew.varStr;
  end;

  Edit2.Text := variableNew.varName ;
end;

end.
