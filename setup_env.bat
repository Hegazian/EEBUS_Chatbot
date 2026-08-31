@echo off
echo ==================================================
echo   EEBUS Chatbot Environment Setup (Windows)
echo ==================================================

set "VENV_DIR=venv"
if exist "venv\bin\activate" (
    echo ℹ️ Found Linux/WSL virtual environment in 'venv'.
    echo 📦 Using dedicated Windows virtual environment 'venv_win'...
    set "VENV_DIR=venv_win"
)

if not exist "%VENV_DIR%\Scripts\activate.bat" (
    echo 📦 Creating Windows virtual environment '%VENV_DIR%'...
    python -m venv %VENV_DIR%
)

echo ⚡ Activating virtual environment...
call %VENV_DIR%\Scripts\activate.bat

echo 📥 Installing required dependencies...
python -m pip install --upgrade pip
pip install -r requirements.txt

if not exist ".env" (
    echo 📝 Creating .env file from .env.example...
    copy .env.example .env
    echo ⚠️ Please edit .env and insert your GOOGLE_API_KEY!
)

echo.
echo ==================================================
echo   Setup Complete! Next steps:
echo   1. Add your API key to .env
echo   2. Run ingestion:  python eebus_ingest.py
echo   3. Launch chatbot: python qabot.py
echo ==================================================
pause
