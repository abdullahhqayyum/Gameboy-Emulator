# Gameboy-Emulator
Bringing the classic GameBoy experience back to life with Snake, Wordle, and Hangman—built in C++ and SFML using solid OOP principles.
This project recreates a digital console experience featuring three iconic games: Snake, Wordle, and Hangman. It's more than just fun—it's a demonstration of object-oriented programming (OOP) in action.

---

## 🚀 Project Overview

Step into the shoes of a retro console engineer. This project is a virtual GameBoy clone that boots up, greets players, and delivers three timeless mini-games—each designed with unique mechanics, visual systems, and player progression. 

The twist? Every element is built using object-oriented design patterns, emphasizing clean architecture, reusability, and modular design.

---

## 🛠 Tech Stack

- **Language:** C++  
- **Graphics Library:** SFML (Simple and Fast Multimedia Library)  
- **Design Paradigm:** Object-Oriented Programming (Inheritance, Polymorphism, Abstraction, Composition)

---

## 🧩 GameBoy Features

- **Custom Menu System:** Game selection, profile management, and game boot-up
- **Player Profiles:** Track scores, store progress, and celebrate achievements
- **Core Engine Elements:**
  - Power states (on/off)
  - Responsive input handling
  - Visual output and optional sound system

---

## 🎮 The Game Line-Up

### 🐍 Snake
- Responsive, grid-based movement
- Increasing difficulty with every meal
- Controlled via arrow keys or WASD
- Score-based progression

### 🔤 Wordle
- Virtual keyboard and interactive feedback
- Limits: 3 attempts every 15 minutes
- Real-time hint coloring system
- Emulates the daily puzzle style

### 🪢 Hangman
- Guess-the-word gameplay with life tracking
- Optional word categories and hint system
- Visual hangman progression for incorrect guesses

---

## 📚 Deliverables

- A modular class hierarchy representing the console, games, and players
- Clear demonstration of key OOP principles across systems
- Diagram showing relationships between core classes
- Documentation explaining system design, trade-offs, and implementation strategies

---

---

## 🧪 How to Build & Run (If Implemented)

### 🛠 Build Instructions

```bash
# Clone the repository
git clone https://github.com/your-username/classic-gameboy-reborn.git
cd classic-gameboy-reborn

# Create and move into the build directory
mkdir build && cd build

# Generate build files
cmake ..

# Compile the project
make
```
### Run
```bash
./ClassicGameBoy
```
