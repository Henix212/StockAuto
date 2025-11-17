# 📦 StockAuto: Automated Stock Management System

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![GitHub Repository](https://img.shields.io/badge/GitHub-Henix212%2FStockAuto-blue)](https://github.com/Henix212/StockAuto.git)

## Introduction

**StockAuto** is an engineering project developed as part of our curriculum at **ESEO (École Supérieure d'Électronique de l'Ouest)**. The objective of this system is to design and build an **autonomous vehicle capable of automating stock management, storage tasks** within a controlled environment.

This repository contains all the source code of the project (new_main branch)

---

## 🛠️ Architecture and Key Components

The project is structured around a handling vehicle and a precise gripping system, with a particular focus on power supply and reliable control.

### Main Hardware Components

| Subsystem | Key Component | Role |
| :--- | :--- | :--- |
| **Movement** | **NEMA 17** Stepper Motors | Ensures the vehicle's precise movement and positioning. |
| **Motor Control** | **A4988 DMOS** Drivers | Manages and provides microstepping for the stepper motors. |
| **Gripping** | **SG90** Micro Servo | Actuates the gripper mechanism designed via 3D modeling. |
| **Power Supply** | **LM2596** Module | Voltage regulation to meet the varying power needs of the components. |

### Electronic Design (Custom PCB)

The project includes the design of a **custom Printed Circuit Board (PCB)** to centralize and optimize the control electronics. This design adhered to strict rules (DRC) and includes:
* The integration of **decoupling capacitors** placed close to sensitive components.
* Optimized tracks for thermal dissipation and signal integrity.
* The addition of **test points** to simplify setup and debugging.
---

You can see the custom pcb on the report (reportBranch)

## 🚀 Quick Start

To retrieve all project files (source code, schematics, etc.) from the repository:

```bash
git clone [https://github.com/Henix212/StockAuto.git](https://github.com/Henix212/StockAuto.git)
cd StockAuto/
