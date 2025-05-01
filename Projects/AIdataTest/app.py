from flask import Flask, render_template, request, jsonify
import yfinance as yf
import pandas as pd
import plotly.graph_objects as go
from plotly.utils import PlotlyJSONEncoder
import json
import ta

app = Flask(__name__)

@app.route('/')
def index():
    return render_template('index.html')

@app.route('/analyze', methods=['POST'])
def analyze():
    data = request.json
    symbol = data.get('symbol')
    start_date = data.get('start_date')
    end_date = data.get('end_date')
    
    # 데이터 가져오기
    stock = yf.Ticker(symbol)
    df = stock.history(start=start_date, end=end_date)
    
    # 기술적 지표 계산
    df['SMA_20'] = ta.trend.sma_indicator(df['Close'], window=20)
    df['SMA_50'] = ta.trend.sma_indicator(df['Close'], window=50)
    df['RSI'] = ta.momentum.rsi(df['Close'], window=14)
    
    # 차트 생성
    fig = go.Figure()
    
    # 주가 차트
    fig.add_trace(go.Candlestick(
        x=df.index,
        open=df['Open'],
        high=df['High'],
        low=df['Low'],
        close=df['Close'],
        name='Price'
    ))
    
    # 이동평균선
    fig.add_trace(go.Scatter(
        x=df.index,
        y=df['SMA_20'],
        name='SMA 20',
        line=dict(color='blue')
    ))
    
    fig.add_trace(go.Scatter(
        x=df.index,
        y=df['SMA_50'],
        name='SMA 50',
        line=dict(color='red')
    ))
    
    # RSI 차트
    fig_rsi = go.Figure()
    fig_rsi.add_trace(go.Scatter(
        x=df.index,
        y=df['RSI'],
        name='RSI',
        line=dict(color='purple')
    ))
    
    # 레이아웃 설정
    fig.update_layout(
        title=f'{symbol} Price Chart',
        yaxis_title='Price',
        xaxis_title='Date'
    )
    
    fig_rsi.update_layout(
        title='RSI',
        yaxis_title='RSI',
        xaxis_title='Date'
    )
    
    # JSON으로 변환
    price_chart = json.dumps(fig, cls=PlotlyJSONEncoder)
    rsi_chart = json.dumps(fig_rsi, cls=PlotlyJSONEncoder)
    
    return jsonify({
        'price_chart': price_chart,
        'rsi_chart': rsi_chart
    })

if __name__ == '__main__':
    app.run(debug=True) 