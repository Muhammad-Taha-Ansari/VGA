# 🎮 VGA Controller (800x600 @ 85Hz) – Verilog + SDL2 + GTKWave + Quartus + OpenLane

This project implements a fully modular VGA controller in Verilog that generates 800×600 resolution video at 85Hz.  
The design is:
- Simulated using **GTKWave** and **SDL2**
- Analyzed using **Quartus Prime**
- Synthesized to ASIC using **OpenLane**

---

## 🧠 Overview

A VGA signal requires generating synchronization pulses (HSYNC & VSYNC) along with RGB pixel values at precisely timed intervals. This design includes pixel counters, synchronization logic, and a test pattern generator to produce visible output on a VGA screen.

---

## 🗂️ Project Structure

| File                   | Description                                      |
|------------------------|--------------------------------------------------|
| `VGA.v`                | Top-level module; connects all submodules        |
| `horizontal_counter.v` | Generates horizontal pixel count                 |
| `vertical_counter.v`   | Generates vertical line count                    |
| `sync_generator.v`     | Produces HSYNC, VSYNC, and video_on signals      |
| `test_pattern.v`       | Outputs RGB values based on current pixel        |
| `tb_vga.cpp`           | Verilator testbench for waveform (GTKWave)       |
| `tb_VGA.cpp`           | SDL2 testbench for real-time VGA output         |

---

## ⚖️ Tools Used

| Tool        | Purpose                                |
|-------------|----------------------------------------|
| **SDL2**    | VGA output (real-time via SDL2 window) |
| **GTKWave** | Waveform analysis of Verilog signals   |
| **Quartus** | RTL Viewer & Simulation                |
| **OpenLane**| ASIC synthesis (PDK 45nm)              |

---

## 📺 VGA Timing (800×600 @ 85Hz)

| Parameter         | Value                                                           |
|------------------|------------------------------------------------------------------|
| Horizontal Pixels | 800 (Active) + 32 (FP) + 64 (Sync) + 152 (BP) = **1048 total**  |
| Vertical Lines    | 600 (Active) + 1 (FP) + 3 (Sync) + 27 (BP) = **631 total**      |
| Refresh Rate      | ~85Hz                                                           |
| Pixel Clock       | ~56.250 MHz                                                      |

---

## ⚙️ Simulation

### ▶️ SDL2 Output (Live Display)

```bash```
`verilator -Wall --cc VGA.v --exe tb_VGA.cpp \
  sync_generator.v test_pattern.v horizontal_counter.v vertical_counter.v \
  -LDFLAGS "-lSDL2"`

`make -C obj_dir -f VVGA.mk VVGA
./obj_dir/VVGA`

### 💡 SDL2 must be installed:
```bash```
`sudo apt install libsdl2-dev`

---

## 📉 GTKWave Simulation
### Waveform dump using Verilator
`verilator -Wall --cc VGA.v --exe tb_vga.cpp \
  sync_generator.v test_pattern.v horizontal_counter.v vertical_counter.v \
  --trace`

`make -C obj_dir -f VVGA.mk VVGA
./obj_dir/VVGA
gtkwave dump.vcd`

### 📝 In tb_vga.cpp, include:
`VerilatedVcdC* tfp = new VerilatedVcdC;
top->trace(tfp, 99);
tfp->open("dump.vcd");`

---

## 🧠 RTL View & Simulation in Quartus
### Create a new Quartus project.
1. Add all .v files.
2. Set VGA.v as the top module.
3. Compile design.
4. Use:
      . RTL Viewer to see the block diagram.
      . Waveform Editor for behavioral simulation.

---

## 🏭 OpenLane ASIC Flow
### 📂 File Setup
#### Place Verilog files in:
```OpenLane/designs/VGA/src/```
Then, create `config.tcl` inside `OpenLane/designs/VGA/`:
`set ::env(DESIGN_NAME) VGA
set ::env(VERILOG_FILES) [glob $::env(DESIGN_DIR)/src/*.v]
set ::env(TOP_MODULE) VGA
set ::env(CLOCK_PORT) clk
set ::env(CLOCK_PERIOD) 17.8  ;# ~56.25MHz`

---

## 🚀 Running OpenLane
`cd OpenLane
make mount
./flow.tcl -design VGA`
### 📦 Output artifacts:
1. GDSII layout (.gds)
2. DEF/LEF files
3. Power reports
4. Synthesis netlists

---

## 👤 Author
####     Muhammad Taha Ansari
#### 📘 Electrical Engineering (2027), NED University
#### 💻 Digital Design • Frontend Dev • Simulation Enthusiast
#### 🌐 GitHub | ✉️ Email

   

