#!/bin/bash
echo "=================================================="
echo "  EEBUS Chatbot Environment Setup (WSL / Linux)  "
echo "=================================================="

# Create virtual environment if it doesn't exist
if [ ! -d "venv" ]; then
    echo "📦 Creating virtual environment 'venv'..."
    python3 -m venv venv
fi

# Activate virtual environment
echo "⚡ Activating virtual environment..."
source venv/bin/activate

# Upgrade pip and install dependencies
echo "📥 Installing required dependencies..."
pip install --upgrade pip
pip install -r requirements.txt

# Create .env if not exists
if [ ! -f ".env" ]; then
    echo "📝 Creating .env file from .env.example..."
    cp .env.example .env
    echo "⚠️ Please edit .env and insert your GOOGLE_API_KEY!"
fi

echo ""
echo "=================================================="
echo "  Setup Complete! Next steps:"
echo "  1. Add your API key to .env"
echo "  2. Run ingestion:  python eebus_ingest.py"
echo "  3. Launch chatbot: python qabot.py"
echo "=================================================="
