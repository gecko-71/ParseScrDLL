unit u03;

interface

type

  PVariable=^TVariable;
  TVariable = record
    error:integer;
    errorStr: PAnsiChar;
    varName: PAnsiChar;
    typevar:integer;
    varStr: PAnsiChar;
    varBoolean: integer;
    varNumeric: double;
    nextRecored:PVariable;
  end;

  TParseExpression = function (input:  PAnsiChar; var output: TVariable;
                               var variable:TVariable): integer ;stdcall;

   TParseExpress = class
   private
     errorstr: string;
     error: Boolean;
     Variable:PVariable;
     procedure FreeVar(var variableNew : PVariable);
     function GetVar(namevar: string; VariableNew:PVariable):PVariable;
   public
     output: TVariable;
     procedure AddVariableNum(namevar: string; value: double);
     procedure AddVariableStr(namevar: string; value: string);
     procedure AddVariableB(namevar: string; value: boolean);
     procedure AddVariable(value: PVariable);
     function GetVariableValue(namevar: string):PVariable;
     function GetResultStr(): string;
     constructor Create();
     destructor Destroy; override;
     function Calculate(exp: string; var merrorstr: string) : boolean;
   end;

const
  NUMERICVAR = 0;
  BOOLEANVAR = 1;
  STRINGVAR  = 2;

implementation

uses System.AnsiStrings, Winapi.Windows, u02;

constructor TParseExpress.Create();
begin
  Variable := nil;
  error:= false;
  output.varStr := AnsiStrAlloc(1000);
  output.errorStr := AnsiStrAlloc(1000);
end;

destructor TParseExpress.Destroy();
begin
  FreeVar(Variable);
  StrDispose(output.varStr);
  StrDispose(output.errorStr);
  inherited;
end;

function  TParseExpress.GetVariableValue(namevar: string):PVariable;
begin
  result := GetVar(namevar, Variable);
end;

procedure  TParseExpress.AddVariable(value: PVariable);
begin
  if value.typevar = STRINGVAR then
     AddVariableStr(value.varName, value.varStr)
  else if value.typevar = NUMERICVAR then
       AddVariableNum(value.varName, value.varNumeric)
  else if value.typevar = BOOLEANVAR then
  begin
    if value.varBoolean = 1 then
      AddVariableB(value.varName, True)
    else
      AddVariableB(value.varName, False);
  end;
end;

function TParseExpress.GetVar(namevar: string; VariableNew:PVariable):PVariable;
begin
  if VariableNew = nil then
  begin
     result := nil;
     exit;
  end;
  if VariableNew.varName = namevar then
  begin
    result := VariableNew;
  end else
    result := GetVar(namevar, VariableNew.nextRecored);
end;

procedure TParseExpress.AddVariableNum(namevar: string; value: double);
var
  variableNew:PVariable;
begin
  if Variable = nil then
  begin
     New(variable);
     variable.nextRecored:= nil;
  end
  else
  begin
     New(variableNew);
     variableNew.nextRecored:=variable;
     variable := variableNew;
  end ;
  variable.varStr :=  AnsiStrAlloc(1000);
  variable.varName :=  AnsiStrAlloc(100);
  StrLCopy(variable.varName, PAnsiChar(AnsiString(namevar)),Length(namevar));
  variable.typevar := NUMERICVAR;
  variable.varNumeric := value;
end;

procedure TParseExpress.AddVariableStr(namevar: string; value: string);
var
  variableNew:PVariable;
begin
  if Variable = nil then
  begin
     New(variable);
     variable.nextRecored:= nil;
  end
  else
  begin
     New(variableNew);
     variableNew.nextRecored:=variable;
     variable := variableNew;
  end ;
  variable.varName :=  AnsiStrAlloc(100);
  StrLCopy(variable.varName, PAnsiChar(AnsiString(namevar)),Length(namevar));
  variable.typevar := STRINGVAR;
  variable.varStr :=  AnsiStrAlloc(1000);
  StrLCopy(variable.varStr, PAnsiChar(AnsiString(value)), Length(value));
end;

procedure TParseExpress.AddVariableB(namevar: string; value: boolean);
var
  variableNew:PVariable;
begin
  if Variable = nil then
  begin
     New(variable);
     variable.nextRecored:= nil;
  end
  else
  begin
     New(variableNew);
     variableNew.nextRecored:=variable;
     variable := variableNew;
  end ;
  variable.varStr :=  AnsiStrAlloc(1000);
  variable.varName :=  AnsiStrAlloc(100);
  StrLCopy(variable.varName, PAnsiChar(AnsiString(namevar)),Length(namevar));
  variable.typevar := BOOLEANVAR;
  if value then
     variable.varBoolean:= 1
  else
     variable.varBoolean:= 0;
end;

procedure TParseExpress.FreeVar(var variableNew : PVariable);
begin
  if not Assigned(variableNew) then
     exit;
  StrDispose(variableNew.varName);
  StrDispose(variableNew.varStr);
  if Assigned(variableNew.nextRecored) then
     FreeVar(variableNew.nextRecored);
  Dispose(variableNew);
end;

function TParseExpress.GetResultStr(): string;
var
  str : string;
begin
  str := '';
  if output.typevar = STRINGVAR then
    str := 'STRINGVAR result = ' + output.varStr
  else
  if output.typevar = NUMERICVAR then
    str := 'NUMERICVAR result = ' + _FloatToStr(output.varNumeric)
  else
  if output.typevar = BOOLEANVAR then
  begin
    if output.varBoolean =1 then
      str := 'BOOLEANVAR result = T.'
    else
      str := 'BOOLEANVAR result = F.';
  end;
  result := str;
end;

function TParseExpress.Calculate(exp: string; var merrorstr: string) : boolean;
var
  ParserLib: HMODULE;
  ParseExpression: TParseExpression;
  ResultStruct: integer;
  input:PAnsiChar;
  size :integer;
  s:string;
begin
  result := False;
  ParserLib := LoadLibrary('ParseScrDLL.dll');
  if ParserLib <> 0 then
  begin
    try
      @ParseExpression := GetProcAddress(ParserLib, 'ParseExpression');
      if Assigned(ParseExpression) then
      begin
        input := AnsiStrAlloc(1000);
        try
          StrLCopy(input, PAnsiChar(AnsiString(exp)), Length(exp));
          output.error:=0;
          try
            ResultStruct := ParseExpression( input, output, variable^);
            if output.error = 0 then
            begin
               errorstr:='';
               error := False;
               result := True;
            end else
            begin
              errorstr:=output.errorStr;
              merrorstr := errorstr;
              error := True;
              result := false;
            end;
          except
            errorstr:='error parse';
            merrorstr := errorstr;
            error := True;
            result := false;
          end;
        finally
          StrDispose(input);
        end;
      end
      else
      begin
        errorstr:='Failed to get function pointer';
        merrorstr := errorstr;
        error := True;
        result := false;
      end;
    finally
      FreeLibrary(ParserLib);
    end;
  end
  else
  begin
    errorstr:='Failed to load DLL';
    merrorstr := errorstr;
    error := True;
    result := false;
  end;
end;


end.
