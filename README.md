# 🧮 GTK Scientific & Basic Calculator

A modern calculator application built using **C + GTK 3**, featuring **basic** and **scientific** modes, full expression handling, memory operations, angle mode switching (Rad/Deg), and a responsive, clean UI with custom styling.

---

## 📌 Features

### 🔢 **Basic Mode**

* Standard arithmetic operations
* Percentage support
* Backspace, clear input (CE), and clear all (C)
* Decimal input handling
* Responsive grid layout

### 🧪 **Scientific Mode**

* Trigonometric functions: `sin`, `cos`, `tan` (Rad/Deg)
* Logarithmic functions: `log`, `ln`
* Power functions: `x²`, `x^y`, `10^x`, `e^x`
* Factorial `x!`
* Absolute `|x|`
* Inverse `1/x`
* Square root `√`
* Constants: `π`, `e`
* Parentheses support

### 🧠 **Memory Operations**

* `M+` — Add to memory
* `M-` — Subtract from memory
* `MR` — Recall memory
* `MC` — Clear memory

### 🔄 **Modes**

* Switch between **Basic Mode** and **Scientific Mode**
* Toggle **Radians / Degrees**

---

## 🖼️ User Interface Overview

The calculator UI is built using:

* **GTK Grids** for the keypad
* **GtkLabel** for display
* **A notebook widget** to switch between Basic & Scientific pages
* A fully customizable CSS-based theme

Both pages maintain clean spacing, fixed button sizes, and consistent UI behavior.

---

## 🏗️ Project Structure

