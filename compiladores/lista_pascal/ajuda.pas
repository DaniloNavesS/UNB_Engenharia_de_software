program ajuda;

var n, soma, i, chute : integer;
var valores: array[1..100] of integer;

begin
    i := 0;
    readln(n);
    soma := 0;

    for i := 1 to n do
    begin
          read(valores[i]); 
          soma := soma + valores[i];
      end;

    readln(chute);

    if soma = chute then 
    writeln('Acertou')
    else writeln('Errou');

end.