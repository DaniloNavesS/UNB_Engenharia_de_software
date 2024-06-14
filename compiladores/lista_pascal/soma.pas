program danilo;

var n, i : longint;
var soma, input : longint;

begin
    i := 0;
    readln(n);
    soma := 0;

    while (i < n) do
    begin
        readln(input);
        soma := soma + input;
        i := i + 1;
    end;

    writeln(soma);
end.