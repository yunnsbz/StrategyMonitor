# StrategyMonitor

This project is a simulation of a strategy monitoring interface built with Qt.  
It mimics the behavior of a live trading monitor, displaying strategies and their corresponding orders in a visually clear and interactive way.  
**Note:** This is a standalone simulation — it does not connect to any real trading systems or data feeds.

## Features

- **Strategy List Panel**  
  View all strategies with ID, type, and current status (Running / Paused).

- **Order Table View**  
  Displays detailed order information including:
  - Strategy name
  - Order ID
  - Side (Buy/Sell)
  - Price
  - Filled Volume
  - Active Volume

- **Filtering & Sorting**  
  - Filter orders by price and volume via right-click on table headers.
  - Filter strategies by status (Running / Paused).
  - Sort table by clicking column headers.

- **Interactive UI**  
  User-friendly layout with informative tooltips and visual status indicators.

## Preview

> ⚠️ **Note:** This UI was designed and tested with Windows dark theme enabled.  
> If you are using light mode, visual appearance (especially color contrasts) may not be optimal.

![App Screenshot](https://github.com/yunnsbz/StrategyMonitor/blob/main/preview.png)

## Tech Stack

- C++17
- Qt 6 (Widgets)
- CMake
- Model/View architecture with filtering and proxy models
