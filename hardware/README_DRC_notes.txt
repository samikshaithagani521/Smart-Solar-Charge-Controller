MPPT controller — footprint-library consistency update

What changed in this revision
- Rebuilt each MPPT_Custom library footprint directly from the corresponding embedded footprint geometry in mppt_controller.kicad_pcb.
- Normalized library reference/value labels and removed board-only placement, UUID, and net-assignment metadata while preserving local pad positions/sizes, drills, pad shapes, layers, and graphical geometry.
- This specifically addresses DRC messages of the form “Footprint ... does not match copy in library MPPT_Custom.”

Verification limits
- KiCad DRC was not available in this environment, so the final DRC warning count is not independently confirmed here. Open the project and run Inspect > Design Rules Checker.
- These edits make the library definitions reflect the board's current footprints; they do not certify the footprints against manufacturer datasheets or prove electrical/thermal suitability. Verify the actual terminal block, shunts, semiconductor pinouts, and inductor lead spacing before fabrication.
- No intentional copper routing, net assignment, pad placement on the board, zone, or outline changes were made during this library-consistency update.
