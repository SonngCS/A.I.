Ciência da Computação
6 semestre - Universidade Católica de Santos

OTIMIZAÇÃO COMBINATÓRIA UTILIZANDO INTELIGÊNCIA ARTIFICIAL - CO.N1.16 - 2023/2

Grupo:
ARTHUR HENRIQUE SILVA (127575)
ERIC SHIRAISHI DE FREITAS (5722278)
GABRIEL CARVALHO SANTANA (9933297)
GABRIEL FERREIRA PEREIRA (3418479)
VITOR CORDEIRO PAES PRIETO (6204033)

Tema escolhido: Preparação de uma mochila para um acampamento

#####################################################################################
CÓDIGO:

Dependências:
Ter gcc instalado (E adicionado no path, caso o sistema utilizado seja Windows)
Bibliotecas Numpy e matplotlib instaladas

Execução do código:

Versão Jupyter notebook - Mantenha os arquivos no mesmo diretório e execute as células do notebook;

Versão terminal - Mantenha os arquivos no mesmo diretório e execute plot.py. ALTERNATIVAMENTE: Rode o makefile (ou compile manualmente) e execute apenas o código em C para receber os arquivos de output.

GOOGLE COLAB:
https://colab.research.google.com/drive/1-9AiSV9322f4cLTks9gnlC-ZbaF0YvOG?usp=sharing

Para executar o código no google colab, abra a aba de "arquivos" e copie o código em C (genetic.c, genetic.h, main.c e makefile) para o diretório do ambiente de execução.
Os itens devem ser colados ao lado da pasta "sample_data", criada pelo próprio colab.

Output:
Gráficos na tela - Evolução dos melhores indivíduos, das médias entre os indivíduos e dos piores indivíduos (por geração ou época);
Results.txt - Arquivo com todas as informações da última geração executada pelo código;
Data.txt - Dados numéricos de todas as gerações. Os valores são, respectivamente: melhor indivíduo, média dos indivíduos, pior indivíduo, e geração. (Usado pelo script em python para reconhecer o número de épocas -ou gerações- e plotar gráficos.)

Modificando valores:
Para modificar valores como o tamanho da população, elitismo e tamanho do cromossomo (este deve estar em sincronia com o tamanho da lista de itens e vetores de peso, valor e volume), edite as macros #DEFINE no início do arquivo "genetic.h".
OBS: A lógica do código foi criada pensando em números pares para população e elitismo.

