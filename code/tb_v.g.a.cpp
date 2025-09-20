#include "VVGA.h"                    // Verilated model header
#include "verilated.h"              // Core Verilator functionality
#include "verilated_vcd_c.h"        // For VCD waveform output
#include <iostream>                 // Optional: For progress logs

int main(int argc, char **argv) {
    Verilated::commandArgs(argc, argv);

    // the top module
    VVGA* top = new VVGA;

    // VCD waveform tracing
    Verilated::traceEverOn(true);
    VerilatedVcdC* tfp = new VerilatedVcdC;
    top->trace(tfp, 99);
    tfp->open("wave.vcd");  // VCD file for GTKWave

    int sim_time = 0;

    // Apply reset for a few cycles
    top->reset = 1;
    for (int i = 0; i < 5; ++i) {
        top->clk = 0; top->eval(); tfp->dump(sim_time++);
        top->clk = 1; top->eval(); tfp->dump(sim_time++);
    }
    top->reset = 0;

    // Main simulation loop
    for (int i = 0; i < 200000; ++i) {
        top->clk = 0; top->eval(); tfp->dump(sim_time++);
        top->clk = 1; top->eval(); tfp->dump(sim_time++);

        // Optional progress output
        if (i % 50000 == 0)
            std::cout << "Simulation time: " << sim_time << std::endl;
    }

    // Clean up
    tfp->close();
    delete tfp;
    delete top;

    std::cout << "Simulation complete. View waveform with: gtkwave wave.vcd\n";
    return 0;
}
