unit u02;

interface

function _FloatToStr(value: double):string;
function _StrToFloat(value: string):double;

implementation

uses System.SysUtils;

function _FloatToStr(value: double):string;
begin
  result := FloatToStr(value);
end;

function _StrToFloat(value: string):double;
begin
  result := StrToFloat(value);
end;

end.
