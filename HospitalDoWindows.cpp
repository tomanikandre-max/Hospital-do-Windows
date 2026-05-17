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
#include <set>
#include <vector>
#include <mutex>

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#define NOGDI              
#define NOUSER  
#endif
#include <windows.h>
#undef near
#undef far
#undef LoadImage
#undef DrawText
#undef Rectangle
#undef PlaySound
#undef ShowCursor
#undef CloseWindow
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
std::mutex logMutex;
bool processandoOtimizacao = false;
std::string etapaAtual = "";
int pagina = 0;
char path[260];
void ExecutarComLog(std::string comando);
void DesligarAnunciosDoWindows();
void ThreadOtimizacao(bool Antivirus, bool Temp, bool Compact, bool Add, bool Cache, bool Log, bool sfc, char lingua);

int main()
{
    int x = 600, y = 500;
    char lingua = ' ';
    char comando2[560];

    _getcwd(path, sizeof(path));

    InitWindow(x, y, "Hospital do Windows");
    GuiSetStyle(DEFAULT, TEXT_SIZE, 30);
    SetTargetFPS(60);

    sprintf_s(comando2, "%s\\Roboto\\Roboto-VariableFont_wdth,wght.ttf", path);
    Font Roboto = LoadFontEx(comando2, 800, 0, 800);
    sprintf_s(comando2, "%s\\Icones\\Icon.png", path);
    Texture2D icone2 = LoadTexture(comando2);
    Image icone = LoadImage(comando2);
    SetWindowIcon(icone);
    UnloadImage(icone);

    bool AntivirusOpt = false;
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
        else if (pagina == 1)
        {
            DrawRectangleRounded({ 20, 20, 560, 460 }, 0.1f, 10, { 45, 49, 58, 255 });
            DrawRectangleRoundedLines({ 20, 20, 560, 460 }, 0.1f, 10, 2, { 60, 65, 75, 255 });
            if (!processandoOtimizacao)
            {
                GuiSetStyle(DEFAULT, TEXT_SIZE, 18);
                if (lingua == 'p')
                {
                    GuiCheckBox((Rectangle)caixademarcar1, "Executar varredura antivirus", &AntivirusOpt);
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
                    GuiCheckBox((Rectangle)caixademarcar1, "Run antivirus scan", &AntivirusOpt);
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
                GuiSetStyle(DEFAULT, TEXT_SIZE, 26);
                if (GuiButton({ 370, 400, 190, 70 }, lingua == 'p' ? "OTIMIZAR" : "START")) {
                    std::thread(ThreadOtimizacao, AntivirusOpt, Temp, Compact, Add, Cache, Log, sfc, lingua).detach();
                }
            }
            else
            {
                DrawRectangle(25, 25, 550, 450, { 20, 22, 26, 255 });
                GuiSetStyle(DEFAULT, TEXT_SIZE, 18);
                std::string etapaCopia;
                {
                    std::lock_guard<std::mutex> trava(logMutex); 
                    etapaCopia = etapaAtual;
                } 

                if (etapaCopia.empty()) {
                    DrawText(lingua == 'p' ? "Iniciando..." : "Starting...", 40, 45, 22, LIME);
                }
                else {
                    DrawText(etapaCopia.c_str(), 40, 45, 22, LIME);
                }

                int espacamentoY = 95;
                {
                    std::lock_guard<std::mutex> trava(logMutex);
                    for (const auto& linhaLog : ultimasLinhas) {
                        if (!linhaLog.empty()) {
                            std::string linhaCurta = linhaLog.substr(0, 52);
                            DrawText(linhaCurta.c_str(), 40, espacamentoY, 15, RAYWHITE);
                            espacamentoY += 32;
                        }
                    }
                }

                GuiLock();
                GuiButton({ 380, 390, 180, 60 }, lingua == 'p' ? "RODANDO..." : "RUNNING...");
                GuiUnlock();
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
            std::lock_guard<std::mutex> trava(logMutex);
            ultimasLinhas.push_back(linha);
            if (ultimasLinhas.size() > 8)
            {
                ultimasLinhas.erase(ultimasLinhas.begin());
            }
        }
    }
    _pclose(pipe);
}

void DesligarAnunciosDoWindows() {
    HKEY chaveAberta;
    DWORD desligar = 0;
    DWORD proibir = 1;
    const char* caminhoHKCU = "Software\\Microsoft\\Windows\\CurrentVersion\\ContentDeliveryManager";
    if (RegOpenKeyExA(HKEY_CURRENT_USER, caminhoHKCU, 0, KEY_WRITE, &chaveAberta) == ERROR_SUCCESS) {
        RegSetValueExA(chaveAberta, "SubscribedContent-338387Enabled", 0, REG_DWORD, (BYTE*)&desligar, 4);
        RegSetValueExA(chaveAberta, "SubscribedContent-338388Enabled", 0, REG_DWORD, (BYTE*)&desligar, 4);
        RegSetValueExA(chaveAberta, "SubscribedContent-338389Enabled", 0, REG_DWORD, (BYTE*)&desligar, 4);
        RegSetValueExA(chaveAberta, "SubscribedContent-314563Enabled", 0, REG_DWORD, (BYTE*)&desligar, 4);
        RegSetValueExA(chaveAberta, "SystemPaneSuggestionsEnabled", 0, REG_DWORD, (BYTE*)&desligar, 4);
        RegSetValueExA(chaveAberta, "SilentInstalledAppsEnabled", 0, REG_DWORD, (BYTE*)&desligar, 4);
        RegCloseKey(chaveAberta);
    }
    const char* caminhoPoliticas = "Software\\Policies\\Microsoft\\Windows\\CloudContent";
    if (RegOpenKeyExA(HKEY_LOCAL_MACHINE, caminhoPoliticas, 0, KEY_WRITE, &chaveAberta) == ERROR_SUCCESS) {
        RegSetValueExA(chaveAberta, "DisableWindowsConsumerFeatures", 0, REG_DWORD, (BYTE*)&proibir, 4);
        RegSetValueExA(chaveAberta, "DisableTailoredExperiencesWithDiagnosticData", 0, REG_DWORD, (BYTE*)&proibir, 4);
        RegCloseKey(chaveAberta);
    }
}

void ThreadOtimizacao(bool AntivirusOpt, bool Temp, bool Compact, bool Add, bool Cache, bool Log, bool sfc, char lingua)
{
    std::string p = path;
    processandoOtimizacao = true;
    {
        std::lock_guard<std::mutex> trava(logMutex);
        ultimasLinhas.clear();
    }

    if (AntivirusOpt) {
        {
            std::lock_guard<std::mutex> trava(logMutex);
            etapaAtual = (lingua == 'p') ? "Executando Antivirus..." : "Running Antivirus...";
        }
        std::string antivirus = "cmd.exe /c \"" + p + "\\Antivirus.exe\" /silent /scan /clean ";
        ExecutarComLog(antivirus);
    }
    if (Temp) {
        {
            std::lock_guard<std::mutex> trava(logMutex);
            etapaAtual = (lingua == 'p') ? "Limpando Temporarios..." : "Cleaning Temp Files...";
        }
        ExecutarComLog("cmd.exe /c \"pushd %temp% && rmdir /s /q . 2>nul\"");
        ExecutarComLog("cmd.exe /c \"pushd %windir%\\Temp && rmdir /s /q . 2>nul\"");
        ExecutarComLog("cmd.exe /c \"pushd %windir%\\Prefetch && rmdir /s /q . 2>nul\"");
        ExecutarComLog("cmd.exe /c \"rd /s /q %systemdrive%\\$Recycle.bin 2>nul\"");
    }
    if (Compact) {
        {
            std::lock_guard<std::mutex> trava(logMutex);
            etapaAtual = (lingua == 'p') ? "Compactando OS..." : "Compacting OS...";
        }
        ExecutarComLog("compact /compactos:always");
    }
    if (Add) {
        {
            std::lock_guard<std::mutex> trava(logMutex);
            etapaAtual = (lingua == 'p') ? "Removendo Anuncios..." : "Removing Ads...";
        }
        DesligarAnunciosDoWindows();
    }
    if (Cache) {
        {
            std::lock_guard<std::mutex> trava(logMutex);
            etapaAtual = (lingua == 'p') ? "Limpando Caches..." : "Cleaning Caches...";
        }
        ExecutarComLog("ipconfig /flushdns");
        ExecutarComLog("cmd.exe /c \"pushd %localappdata%\\D3DSCache && rmdir /s /q . 2>nul\"");
        ExecutarComLog("cmd.exe /c \"pushd %programdata%\\Microsoft\\Diagnosis\\DownloadedSettings && rmdir /s /q . 2>nul\"");
        ExecutarComLog("cmd.exe /c \"pushd %localappdata%\\Microsoft\\Windows\\Notifications && del /f /q /s * 2>nul\"");
        ExecutarComLog("cmd.exe /c \"del /f /q /s %appdata%\\Microsoft\\Windows\\Recent\\* 2>nul\"");
    }
    if (Log) {
        {
            std::lock_guard<std::mutex> trava(logMutex);
            etapaAtual = (lingua == 'p') ? "Limpando Logs..." : "Clearing Logs...";
        }
        ExecutarComLog("cmd.exe /c \"pushd %windir%\\Logs && rmdir /s /q . 2>nul\"");
        ExecutarComLog("cmd.exe /c \"pushd %localappdata%\\CrashDumps && rmdir /s /q . 2>nul\"");
        ExecutarComLog("cmd.exe /c \"pushd %programdata%\\Microsoft\\Windows\\WER\\Temp && rmdir /s /q . 2>nul\"");
    }
    if (sfc) {
        {
            std::lock_guard<std::mutex> trava(logMutex);
            etapaAtual = (lingua == 'p') ? "Verificando arquivos (SFC)..." : "Verifying files (SFC)...";
        }
        ExecutarComLog("cmd.exe /c sfc /scannow");
        {
            std::lock_guard<std::mutex> trava(logMutex);
            etapaAtual = (lingua == 'p') ? "Reparando Imagem (DISM)..." : "Repairing Image (DISM)...";
        }
        ExecutarComLog("cmd.exe /c DISM.exe /Online /Cleanup-image /Restorehealth");
        ExecutarComLog("cmd.exe /c DISM.exe /Online /Cleanup-Image /StartComponentCleanup /ResetBase");
    }

    int msgBoxID = MessageBox(NULL,
        (lingua == 'p') ? "Deseja reiniciar agora para aplicar as alteracoes?" : "Do you want to restart now to apply changes?",
        (lingua == 'p') ? "Concluido" : "Finished",
        MB_YESNO | MB_ICONQUESTION);

    if (msgBoxID == IDYES) {
        system("shutdown /r /f /t 5");
    }

    processandoOtimizacao = false;
    etapaAtual = "";
}
