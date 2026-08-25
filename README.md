# SleepHelper

> **An embedded sleep monitoring and sleep-environment management system based on ESP32.**

SleepHelper is a modular embedded system designed to monitor environmental conditions during sleep, collect and process sleep-related data, and generate a simplified **SleepScore (0–100)** representing overall sleep quality.

The project combines embedded programming, sensor integration, data acquisition, user-interface design, and software architecture into a single hardware-software system.

**Project status:** `In Development`
**Platform:** `ESP32`
**Framework:** `Arduino`
**Language:** `C++`
**Development environment:** `PlatformIO / VS Code`

---

## Overview

Sleep quality is influenced by multiple environmental and behavioral factors. SleepHelper aims to provide a compact system capable of monitoring these factors throughout a sleep session and using the collected data to evaluate the quality of the sleeping environment.

The system is designed around three main stages:

```text
Sensor Data
     ↓
Sleep Session
     ↓
Data Analysis
     ↓
SleepScore (0–100)
```

The embedded device operates independently, while mobile application integration is planned as a future development stage.

---

## Features

### Implemented

- ESP32-based embedded platform
- SSD1306 OLED display
- Real-time digital clock
- Menu-based user interface
- Multiple device screens
- Temperature monitoring
- Humidity monitoring
- Ambient light monitoring
- Button-based navigation
- Modular C++ architecture
- Sensor management layer
- Sleep session state management
- PlatformIO project structure
- Wokwi-based prototyping and simulation

### In Development

- Sleep session data acquisition
- Periodic sensor sampling
- Measurement history
- SleepScore calculation
- Alarm functionality
- Device settings
- Persistent sleep data storage
- Sleep statistics

### Planned

- CO₂ monitoring
- Noise-level monitoring
- Mobile application
- Device-to-phone communication
- Historical sleep data visualization
- Advanced sleep statistics
- Automated lighting integration
- Additional environmental sensors

---

## SleepScore

SleepHelper will calculate a **SleepScore ranging from 0 to 100** based on multiple sleep-related factors.

Planned scoring factors include:

| Factor                | Description                           |
| --------------------- | ------------------------------------- |
| Sleep Duration        | Total duration of the sleep session   |
| Sleep Schedule        | Consistency and timing of sleep       |
| Light Exposure        | Ambient light conditions during sleep |
| Noise Exposure        | Environmental noise levels            |
| Temperature           | Sleeping environment temperature      |
| Humidity              | Relative humidity during sleep        |
| CO₂ Concentration     | Indoor air quality                    |
| Phone Usage           | Device usage before sleep             |
| User Sleep Assessment | User-reported sleep quality           |
| Phone Left On Device  | Phone stays away during sleep         |

Each factor will contribute to the final score using an individual weighting system.

---

### Core Modules

#### `DisplayManager`

Responsible for all OLED-related functionality, including:

- menu rendering,
- screen rendering,
- clock display,
- environmental data display,
- system information.

#### `SensorManager`

Responsible for:

- communicating with connected sensors,
- collecting current measurements,
- providing a unified `SensorData` structure to the rest of the system.

#### `SleepSession`

Responsible for:

- starting and ending sleep sessions,
- tracking session state,
- periodically collecting sensor measurements,
- storing measurements associated with the current session.

#### `SleepScore`

Responsible for:

- processing collected sleep data,
- evaluating individual sleep factors,
- applying factor weights,
- calculating the final SleepScore.

#### `Clock`

Provides the system with time information used by the user interface and sleep-session management.

---

## Hardware

### Current Prototype

- ESP32 development board
- SSD1306 OLED display
- DHT22 temperature/humidity sensor
- Light sensor
- Push buttons
- Potentiometer

### Planned Hardware

- CO₂ sensor
- Noise-level sensor
- Improved ambient light sensor
- Dedicated real-time clock
- Buzzer / speaker for alarm functionality
- Additional environmental sensors

---

## Software Stack

| Component            | Technology         |
| -------------------- | ------------------ |
| Microcontroller      | ESP32              |
| Programming Language | C++                |
| Framework            | Arduino            |
| Build System         | PlatformIO         |
| IDE                  | Visual Studio Code |
| Simulation           | Wokwi              |
| Display              | Adafruit SSD1306   |
| Graphics             | Adafruit GFX       |
| Temperature/Humidity | DHT library        |

---

## Project Structure

```text
SleepHelper/
│
├── docs/
│   └── project-proposal.pdf
│
├── images/
│   └── ...
│
├── SleepHelper/
│   ├── include/
│   │   ├── clock.h
│   │   ├── display_manager.h
│   │   ├── sensor_manager.h
│   │   ├── sensors.h
│   │   ├── sleep_session.h
│   │   └── sleep_score.h
│   │
│   ├── src/
│   │   ├── main.cpp
│   │   ├── clock.cpp
│   │   ├── display_manager.cpp
│   │   ├── sensor_manager.cpp
│   │   ├── sleep_session.cpp
│   │   └── sleep_score.cpp
│   │
│   └── platformio.ini
│
└── README.md
```

---

## Data Collection

Sensor measurements are collected during an active `SleepSession`.

Different environmental parameters may use different sampling intervals depending on their expected variability and relevance to the final SleepScore.

The collected data will eventually follow a structure similar to:

```text
Sleep Session
│
├── Start Time
├── End Time
│
└── Measurements
    ├── Timestamp
    ├── Temperature
    ├── Humidity
    ├── Light
    ├── Noise
    └── CO₂
```

The collected measurements will then be processed by the `SleepScore` module.

---

## Development Approach

The project is being developed incrementally, with individual hardware and software components tested independently before being integrated into the complete system.

```text
Component Prototype
        ↓
Hardware Simulation
        ↓
Module Development
        ↓
Module Integration
        ↓
System Testing
        ↓
Physical Prototype
        ↓
Data Collection
        ↓
SleepScore Analysis
```

Wokwi is currently used for rapid prototyping and simulation of the embedded system. Physical hardware testing is performed as individual components and system modules become available.

---

## Repository Documentation

Additional project documentation is stored in the `docs/` directory.

This includes the original project proposal and will eventually contain additional technical documentation, system diagrams, design decisions, and development notes.

The `images/` directory contains visual documentation of the hardware development process and prototype iterations.

---

## Roadmap

- [x] Initial ESP32 prototype
- [x] OLED interface
- [x] Menu navigation
- [x] Clock implementation
- [x] Temperature and humidity monitoring
- [x] Light monitoring
- [x] Modular project architecture
- [x] Sensor management
- [x] Sleep session foundation
- [ ] Periodic measurement storage
- [ ] SleepScore implementation
- [ ] Alarm system
- [ ] Settings interface
- [ ] Persistent data storage
- [ ] Additional environmental sensors
- [ ] Physical prototype
- [ ] Mobile application
- [ ] Device-to-mobile communication

---

## Project Status

SleepHelper is currently under active development.

The current stage focuses on establishing a reliable modular embedded architecture and implementing the core data acquisition and sleep-session systems before moving toward advanced analysis and hardware integration.

The architecture is intentionally designed to allow additional sensors, functionality, and external interfaces to be introduced without significantly restructuring the existing system.

---

**Author:** Wiktoria Buko  
**© 2026 Wiktoria Buko. All rights reserved.**
