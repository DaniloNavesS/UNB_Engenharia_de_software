program teste;

var input1, input2 : char;
var temp, novaTemp : real;

begin
    readln(input1);
    readln(input2);
    readln(temp);

    if (input1 = 'C') and (input2 = 'K') then
    begin
        novaTemp :=  temp + 273.15;
        writeln(novaTemp:0:2);
    end;

    if (input1 = 'K') and (input2 = 'C') then
    begin
        novaTemp :=  temp - 273.15;
        writeln(novaTemp:0:2);
    end;

    if (input1 = 'C') and (input2 = 'F') then
    begin
        novaTemp :=  (temp * 9/5) + 32;
        writeln(novaTemp:0:2);
    end;

    if (input1 = 'F') and (input2 = 'C') then
    begin
        novaTemp :=  (temp - 32) * 5/9;
        writeln(novaTemp:0:2);
    end;

    if (input1 = 'K') and (input2 = 'F') then
    begin
        novaTemp :=  (temp - 273.15) * 9/5 + 32;
        writeln(novaTemp:0:2);
    end;

    if (input1 = 'F') and (input2 = 'F') then
    begin
        novaTemp :=  (temp - 32) * 5/9 + 273.15;
        writeln(novaTemp:0:2);
    end;

end.

(*
C <-> F;
C <-> K;
F <-> K;

*)