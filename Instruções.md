# Para que servem estas instruções?
Se você não estiver confiando no release pronto, estas instruções mostram detalhadamente como compilar o Hospital do Windows direto na sua maquina.
# Ferramentas nessessárias
* Baixe [Visual Studio Community](https://aka.ms/vs/17/release/vs_community.exe)
* Baixe [Raylib para MSVC](https://github.com/raysan5/raylib/releases/download/6.0/raylib-6.0_win64_msvc16.zip)
* Baixe o [Raygui.h](https://github.com/raysan5/raygui/archive/refs/tags/4.0.zip)
# Configurações do Visual Studio
* Coloque o Raygui na pasta em que está o AsepriteAutoBuild.cpp
* No Visual Studio ja com um novo projeto vazio importe o **HospitalDoWindows.cpp** em "Arquivos de origem"
* Isso é o opicional, mas mude o projeto de Debug para Relase para melhor qualidade, e certifique-se que esteja em x64
* Vá em projeto > Propriedades > Vinculador > Arquivos de manifesto > Nível de execução UAC e coloque: **requireAdministrator(/level='requireAdministrator')**
* Ainda em Vinculador vá em Systema > SubSystem e coloque: **Windows (/SUBSYSTEM:WINDOWS)**
* Como vamos usar a função **main** ainda em Vinculador vá em Avançado > Ponto de Entrada, e insira **mainCRTStartup**
* Vá em projeto > Propriedades > Vinculador, e em Dependências adicionais apague tudo e coloque: **raylib.lib;winmm.lib;$(CoreLibraryDependencies);%(AdditionalDependencies)**
* Vá em projeto > Propriedades > C/C++ > Linguagem e certifiquece que em **Padrão da linguagem C++** esteja em **Padrão ISO C++17 (/std:c++17)**
* Vá em projeto > Propriedades > C/C++ > Geral > Diretórios de Inclusão Adicionais, e passe o caminho da pasta Include do Raylib
* Vá nas propriedades do projeto > Vinculador (Linker) > Geral > Diretórios de Biblioteca Adicionais, passe o caminho da pasta Lib do Raylib
* Vá em Arquivos de recurso > Adicionar > Recurso > Importar, e importe o arquivo .ico da pasta icon extraida para a pasta em que o programa está rodando
# Por fim executar
Compile o programa, vá na \pasta do projeto\x64\Release(ou Degub)\e cole a pasta Icones e Roboto extraidas, o arquivo **Antivirus.exe** por fim, execute o programa normalmente
