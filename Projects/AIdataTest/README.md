# Trading Analysis App

A web application for analyzing stock market data with technical indicators.

## Features

- Real-time stock data visualization
- Technical indicators (SMA, RSI)
- Interactive charts
- User-friendly interface

## Installation

1. Clone the repository
2. Install the required packages:
   ```bash
   pip install -r requirements.txt
   ```

## Usage

1. Start the Flask application:
   ```bash
   python app.py
   ```
2. Open your web browser and navigate to `http://localhost:5000`
3. Enter a stock symbol (e.g., AAPL for Apple)
4. Select the date range for analysis
5. Click "Analyze" to view the charts

## Technical Indicators

- Simple Moving Average (SMA) 20 and 50 days
- Relative Strength Index (RSI) 14 days

## Dependencies

- Flask
- Pandas
- NumPy
- yfinance
- Plotly
- ta (Technical Analysis library) 