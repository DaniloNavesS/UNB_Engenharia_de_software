#!/bin/bash

# Compilar o programa
g++ program.cpp -o program

# Verificar se a compilação foi bem-sucedida
if [ $? -ne 0 ]; then
	echo "Erro na compilação."
	exit 1
fi

# Pastas de inputs e outputs
input_dir="inputs"
output_dir="outputs"

# Contador de testes
test_count=0
pass_count=0
fail_count=0

# Loop através dos arquivos de entrada
for input_file in "$input_dir"/*.in; do
	test_count=$((test_count + 1))
	base_name=$(basename "$input_file" .in)
	output_file="$output_dir/$base_name.out"

	# Executar o programa com o arquivo de entrada e capturar a saída
	# E medir o tempo de execução
	start_time=$(date +%s.%N)
	./program <"$input_file" >temp_output.txt
	end_time=$(date +%s.%N)

	execution_time=$(echo "$end_time - $start_time" | bc)

	# Comparar a saída gerada com a saída esperada
	if diff -q temp_output.txt "$output_file" >/dev/null; then
		echo "Teste $base_name: Passou (Tempo de execução: $execution_time segundos)"
		pass_count=$((pass_count + 1))
	else
		echo "Teste $base_name: Falhou (Tempo de execução: $execution_time segundos)"
		echo "Diferenças:"
		diff temp_output.txt "$output_file"
		fail_count=$((fail_count + 1))
	fi

	# Limpar a saída temporária
	rm temp_output.txt
done

# Exibir o resumo dos testes
echo "Total de testes: $test_count"
echo "Passou: $pass_count"
echo "Falhou: $fail_count"
echo "Acertos: $pass_count de $test_count"

# Remover o executável
rm program
