# Smart Solar Charge Controller for Low-Cost Off-Grid Devices

**Vishwakarma Awards 2026–27**  
**Application ID:** VK26-IITH-SE-0098

## Project Overview

A low-cost solar charge controller based on Perturb and Observe (P&O) Maximum Power Point Tracking (MPPT), intended for 12 V off-grid applications.

The project brings together power electronics, embedded firmware, simulation and enclosure design.

## Repository Structure

### `firmware/`
Contains the C++ source files and headers for the controller firmware, sensing and telemetry.

### `hardware/`
Contains the KiCad PCB layout, schematic, project settings and custom component footprints.

### `mechanical/`
Contains the FreeCAD enclosure model, STEP export and Python macro used to generate the conceptual 3D design.

### `mppt_sim.py`
Contains the MPPT simulation script.

## Design Approach

The proposed system combines a power-conversion stage, voltage and current sensing, an embedded controller, and battery/load protection.

The P&O algorithm is intended to adjust the converter operating point to track the solar panel's maximum power point.

## Current Status

The repository contains the design files and supporting source code for the project.

The enclosure is a conceptual CAD model. PCB design-rule checks, component-footprint validation, physical fit and hardware performance require final verification before fabrication and deployment.

No measured performance or hardware validation is claimed here unless supported by test results.

## Tools

- KiCad — schematic and PCB design
- FreeCAD — enclosure modelling
- Python — MPPT simulation
- C++ — controller firmware

