#!/bin/bash

# Verifica se o número correto de argumentos foi passado
if [ "$#" -ne 3 ]; then
	echo "Uso: $0 <executável> <arquivo_entradas> <arquivo_saidas_esperadas>"
	exit 1
fi

executavel=$1
arquivo_entradas=$2
arquivo_saidas=$3

# Verifica se os arquivos existem
if [ ! -f "$executavel" ]; then
	echo "Erro: O executável '$executavel' não foi encontrado."
	exit 1
fi

if [ ! -f "$arquivo_entradas" ]; then
	echo "Erro: O arquivo de entradas '$arquivo_entradas' não foi encontrado."
	exit 1
fi

if [ ! -f "$arquivo_saidas" ]; then
	echo "Erro: O arquivo de saídas esperadas '$arquivo_saidas' não foi encontrado."
	exit 1
fi

# Inicializa variáveis
total_testes=0
testes_passados=0

# Função para ler blocos de um arquivo
ler_blocos() {
	local arquivo=$1
	local bloco=""
	local blocos=()
	while IFS= read -r linha || [ -n "$linha" ]; do
		if [ -z "$linha" ]; then
			blocos+=("$bloco")
			bloco=""
		else
			bloco="$bloco$linha\n"
		fi
	done <"$arquivo"
	# Adiciona o último bloco, se não estiver vazio
	if [ -n "$bloco" ]; then
		blocos+=("$bloco")
	fi
	echo "${blocos[@]}"
}

# Ler blocos de entrada e saída
entradas=$(ler_blocos "$arquivo_entradas")
saidas=$(ler_blocos "$arquivo_saidas")

# Iterar sobre blocos de entrada e saída
IFS=$'\n' read -r -d '' -a entradas_array <<<"$entradas"
IFS=$'\n' read -r -d '' -a saidas_array <<<"$saidas"

# Verificar se o número de blocos de entrada e saída são iguais
if [ ${#entradas_array[@]} -ne ${#saidas_array[@]} ]; then
	echo "Erro: O número de blocos de entrada e saída esperada não correspondem."
	exit 1
fi

for i in "${!entradas_array[@]}"; do
	total_testes=$((total_testes + 1))
	entrada="${entradas_array[$i]}"
	saida_esperada="${saidas_array[$i]}"

	saida_obtida=$($executavel <<<"$entrada")

	if [ "$saida_obtida" == "$saida_esperada" ]; then
		testes_passados=$((testes_passados + 1))
	else
		echo "Teste $total_testes falhou."
		echo "Entrada:"
		echo -e "$entrada"
		echo "Saída esperada:"
		echo -e "$saida_esperada"
		echo "Saída obtida:"
		echo -e "$saida_obtida"
	fi
done

echo "Total de testes: $total_testes"
echo "Testes passados: $testes_passados"
echo "Testes falhados: $((total_testes - testes_passados))"

# Finaliza o script
exit 0
