program ParserTest;

uses
  Vcl.Forms,
  u01 in 'u01.pas' {Form7},
  u02 in 'u02.pas',
  u03 in 'u03.pas';

{$R *.res}

begin
  Application.Initialize;
  Application.MainFormOnTaskbar := True;
  Application.CreateForm(TForm7, Form7);
  Application.Run;
end.
