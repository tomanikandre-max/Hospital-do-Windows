#include <filesystem>
#include <string>
#include <fstream>
#pragma warning(disable : 4996)
#include <cstdio>
#include <cstdlib>
#include <iomanip>
#include <cstring>
#include <direct.h>
#include <thread>
#include <vector>
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#define NOGDI             
#define NOUSER  
#endif
#undef Rectangle
#undef CloseWindow
#undef ShowCursor
#undef PlaySound
extern "C" {
#include "raylib.h"
}
#define RAYGUI_IMPLEMENTATION
#define MB_ICONQUESTION 0x00000020L
#define MB_YESNO 0x00000004L
#define MB_ICONINFORMATION   0x00000040L
#define IDYES 6
extern "C" {
    __declspec(dllimport) int __stdcall MessageBoxA(void* hWnd, const char* lpText, const char* lpCaption, unsigned int uType);
}
#define MessageBox MessageBoxA
#include "raygui.h"
#define SW_HIDE 0
namespace fs = std::filesystem;
std::vector<std::string> ultimasLinhas;
bool processandoOtimizacao = false;
std::string etapaAtual = "";
void ExecutarComLog(std::string comando);
void ThreadOtimizacao(bool Antivirus, bool Temp, bool Compact, bool Add, bool Cache, bool Log, bool sfc, char lingua);
int pagina = 0;
char path[260];
int main()
{
    int contagemLetras = 11;
    int comandoEnviado = 2;
    int letras = 11;
    int x = 600, y = 500;
    char caminho;
    char lingua = ' ';
    char comando1[560];
    bool estaMarcado = false;
    char comando2[560];
    char comando3[560];
    char comando[2048];
    Vector2 posicaoTexto2 = { 310, 20 };
    Vector2 posicaoTexto55 = { 320, 350 };
    _getcwd(path, sizeof(path));
    InitWindow(x, y, "Hospital do Windows");
    GuiSetStyle(DEFAULT, TEXT_SIZE, 30);
    SetTargetFPS(60);
    sprintf_s(comando2, "%s\\Roboto\\Roboto-VariableFont_wdth,wght.ttf", path);
    Font Roboto = LoadFontEx(comando2, 800, 0, 800);
    sprintf_s(comando2, "%s\\Icones\\Icon.png", path);
    Texture2D icone2 = LoadTexture(comando2);
    sprintf_s(comando2, "%s\\Icones\\Icon.png", path);
    Image icone = LoadImage(comando2);
    SetWindowIcon(icone);
    UnloadImage(icone);
    bool Antivirus = false;
    bool Temp = false;
    bool Compact = false;
    bool Add = false;
    bool Cache = false;
    bool Log = false;
    bool sfc = false;
    Rectangle caixademarcar1 = { 50, 50, 15, 15 };
    Rectangle caixademarcar2 = { 50, 100, 15, 15 };
    Rectangle caixademarcar3 = { 50, 150, 15, 15 };
    Rectangle caixademarcar4 = { 50, 200, 15, 15 };
    Rectangle caixademarcar5 = { 50, 250, 15, 15 };
    Rectangle caixademarcar6 = { 50, 300, 15, 15 };
    Rectangle caixademarcar7 = { 50, 350, 15, 15 };
    while (!WindowShouldClose())
    {
        Color corFundo = { 33, 37, 43, 255 };
        if (pagina == 0 || pagina == 1) {
            corFundo = { 33, 37, 43, 255 };
        }
        else {
            corFundo = { 235, 235, 240, 255 };
        }
        GuiSetStyle(DEFAULT, TEXT_COLOR_NORMAL, ColorToInt(WHITE));
        GuiSetFont(Roboto);
        GuiSetStyle(BUTTON, BASE_COLOR_NORMAL, ColorToInt({ 33, 37, 43, 255 }));
        GuiSetStyle(BUTTON, TEXT_COLOR_NORMAL, ColorToInt(WHITE));
        GuiSetStyle(BUTTON, BASE_COLOR_FOCUSED, ColorToInt({ 80, 85, 95, 255 }));
        GuiSetStyle(BUTTON, TEXT_COLOR_FOCUSED, ColorToInt(WHITE));
        GuiSetStyle(BUTTON, BASE_COLOR_PRESSED, ColorToInt(corFundo));
        GuiSetStyle(BUTTON, TEXT_COLOR_PRESSED, ColorToInt(BLACK));
        BeginDrawing();
        ClearBackground(corFundo);
        if (pagina == 0) {
            DrawRectangleRounded({ 20, 20, 560, 460 }, 0.1f, 10, { 45, 49, 58, 255 });
            DrawRectangleRoundedLines({ 20, 20, 560, 460 }, 0.1f, 10, 2, { 60, 65, 75, 255 });
            DrawTexture(icone2, 230, 20, WHITE);
            GuiLabel({ 30, 50, 300, 30 }, "Welcome to");
            GuiLabel({ 30, 80, 400, 30 }, "Windows Hospital");
            GuiLabel({ 30, 140, 300, 30 }, "Bem vindo ao");
            GuiLabel({ 30, 170, 400, 30 }, "Hospital do Windows");
            GuiLabel({ 30, 230, 300, 30 }, "Selecione sua lingua:");
            GuiLabel({ 30, 320, 400, 30 }, "Select your language:");

            GuiButton({ 370 , 400, 190, 70 }, "English");


            if (GuiButton({ 370, 30, 190, 70 }, "Portugues")) {
                lingua = 'p';
                pagina = 1;
            }
            if (GuiButton({ 370, 400, 190, 70 }, "English")) {
                lingua = 'e';
                pagina = 1;
            }
        }
        if (pagina == 1)
        {
            DrawRectangleRounded({ 20, 20, 560, 460 }, 0.1f, 10, { 45, 49, 58, 255 });
            DrawRectangleRoundedLines({ 20, 20, 560, 460 }, 0.1f, 10, 2, { 60, 65, 75, 255 });

            if (lingua == 'p')
            {
                GuiCheckBox((Rectangle)caixademarcar1, "Executar varredura antivirus", &Antivirus);
                GuiCheckBox((Rectangle)caixademarcar2, "Remover Arquivos temporarios", &Temp);
                GuiCheckBox((Rectangle)caixademarcar3, "Compactar arquivos OS", &Compact);
                GuiCheckBox((Rectangle)caixademarcar4, "Remover anuncios de segundo plano", &Add);
                GuiCheckBox((Rectangle)caixademarcar5, "Limpar de cache de DNS e Download\\*", &Cache);
                GuiCheckBox((Rectangle)caixademarcar6, "Limpar Logs do Sistema", &Log);
                GuiCheckBox((Rectangle)caixademarcar7, "Limpar Arquivos corrompidos", &sfc);
                if (GuiButton({ 70, 400, 190, 70 }, "VOLTAR"))
                {
                    pagina = 0;
                }
            }
            else
            {
                GuiCheckBox((Rectangle)caixademarcar1, "Run antivirus scan", &Antivirus);
                GuiCheckBox((Rectangle)caixademarcar2, "Remove temporary files", &Temp);
                GuiCheckBox((Rectangle)caixademarcar3, "Compact OS files", &Compact);
                GuiCheckBox((Rectangle)caixademarcar4, "Remove background ads", &Add);
                GuiCheckBox((Rectangle)caixademarcar5, "Clear DNS and Download Cache\\*", &Cache);
                GuiCheckBox((Rectangle)caixademarcar6, "Clear System Logs", &Log);
                GuiCheckBox((Rectangle)caixademarcar7, "Clear corrupted files", &sfc);
                if (GuiButton({ 70, 400, 190, 70 }, "BACK"))
                {
                    pagina = 0;
                }
            }
            if (!processandoOtimizacao) {
                if (GuiButton({ 370, 400, 190, 70 }, "OK")) {
                    std::thread operacao(ThreadOtimizacao, Antivirus, Temp, Compact, Add, Cache, Log, sfc, lingua);
                    operacao.detach();
                }
            }
            else {
                GuiLock();
                GuiButton({ 370, 400, 190, 70 }, lingua == 'p' ? "RODANDO" : "RUNNING");
                GuiUnlock();

                DrawRectangle(25, 25, 550, 450, { 20, 22, 26, 245 });
                GuiSetStyle(DEFAULT, TEXT_SIZE, 18);

                if (etapaAtual.empty()) {
                    DrawText(lingua == 'p' ? "Iniciando..." : "Starting...", 40, 50, 24, RAYWHITE);
                }
                else {
                    DrawText(etapaAtual.c_str(), 40, 50, 24, RAYWHITE);
                }

                int espacamentoY = 110;
                for (const auto& linhaLog : ultimasLinhas) {
                    if (!linhaLog.empty()) {
                        std::string linhaCurta = linhaLog.substr(0, 55);
                        DrawText(linhaCurta.c_str(), 40, espacamentoY, 16, LIGHTGRAY);
                        espacamentoY += 35;
                    }
                }
                GuiSetStyle(DEFAULT, TEXT_SIZE, 30);
            }
        }
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
void ExecutarComLog(std::string comando) 
{
    FILE* pipe = _popen(comando.c_str(), "r");
    if (!pipe) return;

    char buffer[256];
    while (fgets(buffer, sizeof(buffer), pipe) != NULL) 
    {
        std::string linha = buffer;
        if (!linha.empty() && linha.back() == '\n') linha.pop_back();

        if (!linha.empty()) 
        {
            ultimasLinhas.push_back(linha);
            if (ultimasLinhas.size() > 5) 
            {
                ultimasLinhas.erase(ultimasLinhas.begin());
            }
        }
    }
    _pclose(pipe);
}
void ThreadOtimizacao(bool Antivirus, bool Temp, bool Compact, bool Add, bool Cache, bool Log, bool sfc, char lingua) 
{
    processandoOtimizacao = true;
    ultimasLinhas.clear();

    if (Antivirus) {
        etapaAtual = (lingua == 'p') ? "Executando Antivirus..." : "Running Antivirus...";
        std::string p = path;
        std::string antivirus = "cmd.exe /c \"" + p + "\\Antivirus.exe\" /silent /scan /clean ";
        ExecutarComLog(antivirus);

    }
    if (Temp) {
        etapaAtual = (lingua == 'p') ? "Limpando Temporarios..." : "Cleaning Temp Files...";
        ExecutarComLog("cmd.exe /c \"pushd %temp% && rmdir /s /q . 2>nul\"");
        ExecutarComLog("cmd.exe /c \"pushd %windir%\\Temp && rmdir /s /q . 2>nul\"");
        ExecutarComLog("cmd.exe /c \"pushd %windir%\\Prefetch && rmdir /s /q . 2>nul\"");
        ExecutarComLog("cmd.exe /c \"rd /s /q %systemdrive%\\$Recycle.bin 2>nul\"");
    }
    if (Compact) {
        etapaAtual = (lingua == 'p') ? "Compactando OS..." : "Compacting OS...";
        ExecutarComLog("compact /compactos:always");
    }
    if (Add) {
        etapaAtual = (lingua == 'p') ? "Removendo Anuncios..." : "Removing Ads...";
        ExecutarComLog("reg add \"HKLM\\Software\\Policies\\Microsoft\\Windows\\CloudContent\" /v \"DisableWindowsConsumerFeatures\" /t REG_DWORD /d 1 /f");
        ExecutarComLog("reg add \"HKLM\\Software\\Policies\\Microsoft\\Windows\\CloudContent\" /v \"DisableTailoredExperiencesWithDiagnosticData\" /t REG_DWORD /d 1 /f");
        ExecutarComLog("reg add \"HKLM\\Software\\Policies\\Microsoft\\Windows\\UserProfile\" /v \"DisableUserProfileEngagement\" /t REG_DWORD /d 1 /f");
        ExecutarComLog("reg add \"HKLM\\Software\\Policies\\Microsoft\\Windows\\CurrentVersion\\ContentDeliveryManager\" /v \"DisableSystemPaneSuggestions\" /t REG_DWORD /d 1 /f");
        ExecutarComLog("reg add \"HKCU\\Software\\Microsoft\\Windows\\CurrentVersion\\ContentDeliveryManager\" /v \"SubscribedContent-338387Enabled\" /t REG_DWORD /d 0 /f");
        ExecutarComLog("reg add \"HKCU\\Software\\Microsoft\\Windows\\CurrentVersion\\ContentDeliveryManager\" /v \"SubscribedContent-338389Enabled\" /t REG_DWORD /d 0 /f");
        ExecutarComLog("reg add \"HKCU\\Software\\Microsoft\\Windows\\CurrentVersion\\ContentDeliveryManager\" /v \"SystemPaneSuggestionsEnabled\" /t REG_DWORD /d 0 /f");
    }

    if (Cache) {
        etapaAtual = (lingua == 'p') ? "Limpando Caches..." : "Cleaning Caches...";
        ExecutarComLog("ipconfig /flushdns");
        ExecutarComLog("cmd.exe /c \"net stop wuauserv /y && timeout /t 2 /nobreak >nul && rmdir /s /q %systemroot%\\SoftwareDistribution\\Download && mkdir %systemroot%\\SoftwareDistribution\\Download && net start wuauserv /y\"");
        ExecutarComLog("cmd.exe /c \"pushd %localappdata%\\D3DSCache && rmdir /s /q . 2>nul\"");
    }

    if (Log) {
        etapaAtual = (lingua == 'p') ? "Limpando Logs..." : "Clearing Logs...";
        ExecutarComLog("cmd.exe /c \"pushd %windir%\\Logs && rmdir /s /q . 2>nul\"");
        ExecutarComLog("cmd.exe /c \"pushd %localappdata%\\CrashDumps && rmdir /s /q . 2>nul\"");
        ExecutarComLog("cmd.exe /c \"pushd %programdata%\\Microsoft\\Windows\\WER\\Temp && rmdir /s /q . 2>nul\"");
    }
    if (sfc) {
        etapaAtual = (lingua == 'p') ? "Verificando arquivos (SFC)..." : "Verifying files (SFC)...";
        ExecutarComLog("cmd.exe /c sfc /scannow");

        etapaAtual = (lingua == 'p') ? "Reparando Imagem (DISM)..." : "Repairing Image (DISM)...";
        ExecutarComLog("cmd.exe /c DISM.exe /Online /Cleanup-image /Restorehealth");
    }
    int msgBoxID = MessageBox(NULL,
        (lingua == 'p') ? "Deseja reiniciar agora para aplicar as alteracoes?" : "Do you want to restart now to apply changes?",
        (lingua == 'p') ? "Concluido" : "Finished",
        MB_YESNO | MB_ICONQUESTION);

    if (msgBoxID == 6) {
        system("shutdown /r /f /t 5");
    }
    processandoOtimizacao = false;
    etapaAtual = "";
}
