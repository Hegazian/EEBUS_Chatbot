@echo off
echo ==================================================
echo   EEBUS Chatbot Environment Setup (Windows)
echo ==================================================

if not exist "venv\Scripts\activate.bat" (
    echo 📦 Creating Windows virtual environment 'venv'...
    python -m venv venv
)

echo ⚡ Activating virtual environment...
call venv\Scripts\activate.bat

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
