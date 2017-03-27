# Heightmap Generator

This is a heightmap generator I made a while back for UE4. It should work for any terrain system however and I may revisit this as I have more of a need for tiling maps now.


CommandLine for HGEntry
--- 
So I intended this to be a tool that was integratable within the engine itself, and while I may make it a plugin for UE4 at some point, but I did provide an example image writer.

HGEntry is invoked using 3 arguments;

| Argument | Data Type |
| ---|--- |
| Matrix Size |  uint16_t  |
| Random Seed |  uint32_t  |
| Noise Multiplier |  uint32_t  |
