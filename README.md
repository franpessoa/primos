# Geração de números primos
Gera todos os números primos até uma determinada quantidade, usando o uma versão paralelizada do crivo de Erastótenes.

## Compilando 
É necessário ter um compilador C++ e cmake instalados

Clone o repositório

```
git clone https://github.com/franpessoa/primos.git
```

Compile

```
mkdir build && cd build && cmake .. && make
```

Usando (partindo do diretório `build`)

```
./src/cli/primos_cli <teto de geração> <arquivo de saída>
```

Por exemplo, para gerar os primos até 1000 e colocá-los no arquivo saída.txt

```
./src/cli/primos_cli 1000 saída.txt
```

## Cuidados 
Esse programa realmente usa todos os recursos do seu computador, então ao tentar gerar números grandes, pode ocorrer lentidão ou travamentos completos. Por exemplo, meu computador trava completamente gerando números maiores que 10^9 
