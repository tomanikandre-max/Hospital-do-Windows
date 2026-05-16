# Hospital do Windows (C++)

O **Hospital do Windows** é uma ferramenta feita em **C++ com Raylib e RayGUI** focada em manutenção, limpeza e otimização do Windows de forma simples e visual.  
O programa reúne diversas tarefas úteis de reparo e limpeza em uma interface amigável, permitindo executar processos importantes sem precisar abrir o Prompt de Comando manualmente.

# Créditos

Eu obviamente preciso credibilizar a Microsoft pelo Windows, além dos desenvolvedores das bibliotecas Raylib e RayGUI usadas neste projeto.

Caso queira apoiar o projeto, considere deixar uma estrela no repositório oficial do GitHub:

[Hospital do Windows no GitHub](https://github.com/tomanikandre-max/Hospital-do-Windows)

# O que este projeto faz?

O Windows pode acumular arquivos temporários, cache, logs e até arquivos corrompidos com o tempo.  
O **Hospital do Windows** automatiza diversos processos úteis de manutenção do sistema:

* Executa verificação de antivírus.
* Remove arquivos temporários do sistema.
* Limpa cache de DNS e cache de downloads do Windows Update.
* Remove anúncios e sugestões em segundo plano do Windows.
* Compacta arquivos do sistema operacional usando CompactOS.
* Remove logs desnecessários.
* Executa reparação de arquivos corrompidos usando **SFC** e **DISM**.
* Interface gráfica moderna feita com **Raylib**.
* Sistema multilíngue (**Português e Inglês**).
* Exibe logs em tempo real durante as operações.

# Tecnologias Utilizadas

* **C++**
* **Raylib**
* **RayGUI**
* **Windows CMD / PowerShell**
* **WinAPI**

# Requisitos

* **Windows 10 ou Windows 11 x64**
* Permissões de administrador
* Conexão com internet (para algumas operações do Windows)

# Como usar

1. Vá na aba **Releases** do GitHub e baixe o executável do programa:

[Baixar Hospital do Windows](https://github.com/tomanikandre-max/Hospital-do-Windows/releases)
ou [baixe o código fonte](https://github.com/tomanikandre-max/Hospital-do-Windows/archive/refs/heads/main.zip) e siga o [intruções.md]() para compilar.
2. Execute o programa.

3. Escolha sua linguagem:
   * Português
   * English

4. Marque as opções desejadas:
   * Antivirus
   * Limpeza de temporários
   * Compactação do Windows
   * Limpeza de cache
   * Correção de arquivos corrompidos
   * Entre outras

5. Clique em **OK** e aguarde a execução.

# Funcionalidades Principais

## Limpeza de Temporários

Remove:

* `%temp%`
* `Windows\Temp`
* `Prefetch`
* Lixeira do sistema

## Reparação do Sistema

Executa automaticamente:

```cmd
sfc /scannow
DISM /Online /Cleanup-image /Restorehealth
```

## Remoção de Anúncios do Windows

Desativa:

* Sugestões do menu iniciar
* Conteúdo promocional
* Recomendações automáticas
* Experiências personalizadas do Windows

## Limpeza de Cache

Inclui:

* `ipconfig /flushdns`
* Cache do Windows Update
* Cache DirectX (`D3DSCache`)
* Limpeza de drivers antigos

# Interface

O programa possui:

* Interface gráfica moderna
* Tema escuro
* Logs em tempo real
* Feedback visual durante os processos
* Reinicialização automática opcional após conclusão

# Compilação

Caso queira compilar manualmente:

## Requisitos

* [Visual Studio Community](https://aka.ms/vs/17/release/vs_community.exe)
* [Raylib](https://www.raylib.com/)
* [RayGUI](https://github.com/raysan5/raygui)

## Compilar

Abra o projeto no Visual Studio e compile normalmente em:

* **Release x64**

# Avisos

⚠️ Algumas funções modificam configurações internas do Windows.  
⚠️ Recomenda-se criar um ponto de restauração antes de usar.  
⚠️ O programa deve ser executado como administrador.

---

# Sobre o Autor

Sou um desenvolvedor de 11 anos apaixonado por **C/C++**, automação de sistemas e desenvolvimento desktop.  
Criei o **Hospital do Windows** para facilitar tarefas de manutenção do Windows de forma simples, rápida e acessível para qualquer pessoa.
